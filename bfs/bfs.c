#include "stdio.h" //printf, fscanf
#include "stdlib.h" //malloc, realloc, free

void print_usage() {
    printf("usage: bfs [filename]\n");
}


struct RingQueue {
    int * data;
    int size;
    int count;
    int index;
};

struct RingQueue RingQueue_init(int size) {
    struct RingQueue queue;
    queue.data = malloc(size * sizeof(int));
    queue.size = size;
    queue.count = 0;
    queue.index = 0;

    return queue;
}

void RingQueue_exit(struct RingQueue * queue) {
    free(queue->data);
    queue->size = 0;
    queue->count = 0;
    queue->index = 0;
}

int eject(struct RingQueue * queue) {
    int value = queue->data[queue->index];
    queue->count--;
    queue->index = (queue->index + 1) % queue->size;

    return value;
}

void inject(struct RingQueue * queue, int value) {
    int ndx = (queue->index + queue->count) % queue->size;
    queue->data[ndx] = value;
    queue->count++;
}


void breadth_first_search(int ** graph, int nodes, int vertex) {

    int * dist = malloc(nodes * sizeof(int));
    for (int u = 0; u < nodes; u++)
        dist[u] = -1;


    dist[vertex] = 0;
    struct RingQueue Q = RingQueue_init(nodes);
    inject(&Q, vertex);


    while(Q.count > 0) {
        int u = eject(&Q);

        for (int v = 0; v < nodes; v++) {
            if(graph[u][v]) {
                if(dist[v] == -1){
                    inject(&Q, v);
                    dist[v] = dist[u] + 1;
                }
            }
        }
    }


    for (int u = 0; u < nodes; u++) {
        printf("%d ", dist[u]);
    }
    printf("\n");

}


int main(int argc, char * argv[]) {

    if(argc > 1) {

        char * filename = argv[1];

        FILE * input_file = fopen(filename, "r");

        if( input_file != 0 ) {


            int nodes, edges;
            if(fscanf(input_file, "%d %d\n", &nodes, &edges)!=2);
                //read error

            int graph_size = nodes;
            int * graph_degrees = calloc(graph_size, sizeof(int));

            int ** graph = malloc(sizeof(int *) * graph_size);
            for (int i = 0; i < graph_size; i++) {
                graph[i] = calloc(graph_size, sizeof(int));
            }

            int node_a;
            int node_b;
            while(fscanf(input_file, "%d %d\n", &node_a, &node_b) == 2) {
                graph[node_a - 1][node_b - 1] = 1;
            }

            breadth_first_search(graph, nodes, 0);

            for (int i = 0; i < graph_size; i++) {
                free(graph[i]);
            }
            free(graph);
        } else {
            print_usage();
            printf("file read error.\n");
        }

    } else {
        print_usage();
        printf("no filename given\n");
    }

    return 0;

}

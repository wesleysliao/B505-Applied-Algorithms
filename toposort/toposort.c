#include "stdio.h" //printf, fscanf
#include "stdlib.h" //malloc, realloc, free

void print_usage() {
    printf("usage: toposort [filename]\n");
}


void previsit(int vertex, int * pre, int * clock) {
    pre[vertex] = *clock;
    *clock = *clock + 1;
}

void postvisit(int vertex, int * post, int * clock) {
    post[vertex] = *clock;
    *clock = *clock + 1;
}



int explore(int ** graph, int graph_vertices, int vertex, int * visited, int * pre, int * post, int * clock) {

    if (visited == NULL) {
        visited = calloc(graph_vertices, sizeof(int));
    }

    visited[vertex] = 1;

    //previsit(vertex, pre, clock);
    for (int u = 0; u < graph_vertices; u++) {

        if (graph[vertex][u] > 0) {
            if (!visited[u]) {
                explore(graph, graph_vertices, u, visited, pre, post, clock);
            }
        }
    }
    postvisit(vertex, post, clock);
}

void depth_first_search(int ** graph, int graph_vertices, int * visited, int * pre, int * post) {

    int clock = 0;

    for (int vertex = 0; vertex < graph_vertices; vertex++) {

        if (!visited[vertex]) {
            explore(graph, graph_vertices, vertex, visited, pre, post, &clock);
        }

    }
}


void toposort(int ** graph, int graph_vertices, int * post) {
    int * sorted = calloc(graph_vertices, sizeof(int));
    for (int vertex = 0; vertex < graph_vertices; vertex++)
        sorted[post[vertex]] = vertex + 1;

    for (int vertex = graph_vertices - 1; vertex >= 0; vertex--)
        printf("%d ", sorted[vertex]);
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

            int * visited = calloc(nodes, sizeof(int));
            int * pre = calloc(nodes, sizeof(int));
            int * post = calloc(nodes, sizeof(int));

            depth_first_search(graph, nodes, visited, pre, post);

            toposort(graph, nodes, post);

            free(visited);
            free(pre);
            free(post);
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

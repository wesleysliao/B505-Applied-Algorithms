#include "stdio.h" //printf, fscanf
#include "stdlib.h" //malloc, realloc, free
#include "string.h" //memset

void print_usage() {
    printf("usage: toposort [filename]\n");
}


void previsit(int vertex, int * pre, int * cc) {
    pre[vertex] = *cc;
}

void postvisit(int vertex, int * post, int * clock) {
    post[vertex] = *clock;
    *clock = *clock + 1;
}



void explore(int ** graph, int graph_vertices, int vertex, int * visited, int * pre, int * post, int * clock, int * explore_count) {
    if (visited == NULL) {
        visited = calloc(graph_vertices, sizeof(int));
    }

    visited[vertex] = 1;

    previsit(vertex, pre, explore_count);
    for (int u = 0; u < graph_vertices; u++) {

        if (graph[vertex][u] > 0) {
            if (!visited[u]) {
                explore(graph, graph_vertices, u, visited, pre, post, clock, explore_count);
            }
        }
    }
    postvisit(vertex, post, clock);
}


void explore_order(int ** graph, int graph_vertices, int vertex, int * order, int * visited, int * pre, int * post, int * clock, int * explore_count) {
    if (visited == NULL) {
        visited = calloc(graph_vertices, sizeof(int));
    }

    visited[vertex] = 1;

    previsit(vertex, pre, explore_count);
    for (int index = 0; index < graph_vertices; index++) {
        int u = order[index];

        if (graph[vertex][u] > 0) {
            if (!visited[u]) {
                explore_order(graph, graph_vertices, u, order, visited, pre, post, clock, explore_count);
            }
        }
    }
    postvisit(vertex, post, clock);
}

void depth_first_search(int ** graph, int graph_vertices, int * visited, int * pre, int * post) {

    int clock = 0;

    int explore_count = 0;

    for (int vertex = 0; vertex < graph_vertices; vertex++) {

        if (!visited[vertex]) {
            explore_count++;
            explore(graph, graph_vertices, vertex, visited, pre, post, &clock, &explore_count);
        }

    }
}


void dfs_order(int ** graph, int graph_vertices, int * order, int * visited, int * pre, int * post) {

    int clock = 0;

    int explore_count = 0;

    for (int index = 0; index < graph_vertices; index++) {
        int vertex = order[index];

        if (!visited[vertex]) {
            explore_count++;
            explore_order(graph, graph_vertices, vertex, order, visited, pre, post, &clock, &explore_count);
        }

    }
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
            int ** graph_r = malloc(sizeof(int *) * graph_size);
            for (int i = 0; i < graph_size; i++) {
                graph[i] = calloc(graph_size, sizeof(int));
                graph_r[i] = calloc(graph_size, sizeof(int));
            }

            int node_a;
            int node_b;

            while(fscanf(input_file, "%d %d\n", &node_a, &node_b) == 2) {
                graph[node_a - 1][node_b - 1] = 1;
                graph_r[node_b - 1][node_a - 1] = 1;
            }

            int * visited = calloc(nodes, sizeof(int));
            int * cc = calloc(nodes, sizeof(int));
            int * post = calloc(nodes, sizeof(int));

            depth_first_search(graph_r, nodes, visited, cc, post);


            for (int i = 0; i < nodes; i++) {
                printf("%d ", post[i]);
            }
            printf("\n");

            int * order = calloc(nodes, sizeof(int));
            for (int i = 0; i < nodes; i++) {
                order[(nodes - 1) -post[i]] = i;
                //order[post[i]] = i;
            }
            for (int i = 0; i < nodes; i++) {
                printf("%d ", order[i]);
            }
            printf("\n");


            memset(visited, 0, sizeof(int) * nodes);
            memset(cc, 0, sizeof(int) * nodes);
            memset(post, 0, sizeof(int) * nodes);
            dfs_order(graph, nodes, order, visited, cc, post);


            int ccmax = 0;
            for (int i = 0; i < nodes; i++) {
                printf("%d ", cc[i]);
                if(cc[i] > ccmax) {
                    ccmax = cc[i];
                }
            }
            printf("\n%d\n", ccmax);


            free(visited);
            free(order);
            free(cc);
            free(post);


            for (int i = 0; i < graph_size; i++) {
                free(graph[i]);
                free(graph_r[i]);
            }
            free(graph);
            free(graph_r);
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

#include "stdio.h" //printf, fscanf
#include "stdlib.h" //malloc, realloc, free

void print_usage() {
    printf("usage: doubledegree [filename]\n");
}


int main(int argc, char * argv[]) {

    if(argc > 1) {

        char * filename = argv[1];

        FILE * input_file = fopen(filename, "r");

        if( input_file != 0 ) {


            int nodes, edges;
            fscanf(input_file, "%d %d\n", &nodes, &edges);

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
                graph[node_b - 1][node_a - 1] = 1;

                graph_degrees[node_a - 1]++;
                graph_degrees[node_b - 1]++;
            }

            /*
            printf("adjacency matrix:\n");
            for (int i = 0; i < graph_size; i++) {
                for (int j = 0; j < graph_size; j++) {
                    printf("% 3d ", graph[i][j]);
                }
                printf("\n");
            }
            */

            printf("node degree:\n");
            for (int i = 0; i < graph_size; i++) {
                printf("% 3d ", graph_degrees[i]);
            }
            printf("\n");

            printf("neighbor degree:\n");
            for (int i = 0; i < graph_size; i++) {
                int sum = 0;
                for (int j = 0; j < graph_size; j++) {
                    if (j == i) continue;
                    sum += graph[i][j] * graph_degrees[j];
                }
                printf("%d ", sum);
            }
            printf("\n");


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

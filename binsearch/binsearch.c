#include "stdio.h"
#include "stdlib.h"



void print_usage() {
    printf("usage: binsearch [filename]\n");
}


int binsearch(int * array, int low_index, int high_index, int key) {
    if(high_index < low_index) return -1;
    int middle = low_index + ((high_index - low_index) / 2);
    if (key == array[middle]) {
        return middle + 1;
    }
    else if (array[middle] > key) {
        return binsearch(array, low_index, middle - 1, key);
    }
    else {
        return binsearch(array, middle + 1, high_index, key);
    }
}


int main(int argc, char * argv[]) {

    if(argc > 1) {

        char * filename = argv[1];

        FILE * input_file = fopen(filename, "r");

        if( input_file != 0 ) {
            int n, m;

            fscanf(input_file, "%d\n", &n);
            fscanf(input_file, "%d\n", &m);

            int * A = malloc(sizeof(int) * n);
            int * keys = malloc(sizeof(int) * m);

            fscanf(input_file, "%d", &A[0]);
            for(int i = 1; i < n; i++) {
                fscanf(input_file, " %d", &A[i]);
            }

            fscanf(input_file, "\n%d", &keys[0]);
            for(int i = 1; i < m; i++) {
                fscanf(input_file, " %d", &keys[i]);
            }

            printf("sortedarray:");
            for(int i = 0; i < n; i++) {
                printf(" %d", A[i]);
            }
            printf("\nkeys:");
            for(int i = 0; i < m; i++) {
                printf(" %d", keys[i]);
            }
            printf("\n");


            printf("key indices:");
            for(int i = 0; i < m; i++) {
                printf(" %d",  binsearch(A, 0, n - 1, keys[i]));
            }
            printf("\n");



            free(A);
            free(keys);

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

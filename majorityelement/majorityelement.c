#include "stdio.h" //printf, fscanf
#include "stdlib.h" //malloc, free
#include "string.h" //memcpy



void print_usage() {
    printf("usage: majorityelement [filename]\n");
}


void swap(int * array, int a_index, int b_index) {
    int temp = array[a_index];
    array[a_index] = array[b_index];
    array[b_index] = temp;
}


int majorityelement(int * array, int start_index, int n) {
    if(start_index >= n) return -1;

    int test_value = array[start_index];

    int j = start_index;
    for(int i = start_index + 1; i < n; i++) {

        if(array[i] == test_value) {
            swap(array, i, ++j);
        }
    }
    int value_count = (j - start_index + 1);
    if(value_count > (n / 2)) return test_value;
    else return majorityelement(array, start_index + j + 1, n);
}


int main(int argc, char * argv[]) {

    if(argc > 1) {

        char * filename = argv[1];

        FILE * input_file = fopen(filename, "r");

        if( input_file != 0 ) {
            int k, n;
            fscanf(input_file, "%d %d", &k, &n);

            int ** A = malloc(sizeof(int *) * k);
            for( int i = 0; i < k; i++ ) {
                A[i] = malloc(sizeof(int) * n);

                fscanf(input_file, "\n%d", &A[i][0]);
                for(int j = 1; j < n; j++) {
                    fscanf(input_file, " %d", &A[i][j]);
                }
            }


            int * result = malloc(sizeof(int) * k);

            for( int i = 0; i < k; i++) {
                printf("array %d:", i);
                for(int j = 0; j < n; j++) {
                    printf(" %d", A[i][j]);
                }
                printf("\n");

                result[i] = majorityelement(A[i], 0, n);
            }

            printf("results:");
            for( int i = 0; i < k; i++) {
                printf(" %d", result[i]);
            }
            printf("\n");


            free(result);
            for(int i = 0; i < k; i++) free(A[i]);
            free(A);
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

#include "stdio.h" //printf, fscanf
#include "stdlib.h" //malloc, free
#include "string.h" //memcpy



void print_usage() {
    printf("usage: mergesort [filename]\n");
}

void merge(int * array, int a_low, int a_high, int b_low, int b_high) {

    int merged_size = (a_high - a_low + 1) + (b_high - b_low + 1);

    int * merged_array = malloc(merged_size * sizeof(int));

    int a_index = 0;
    int b_index = 0;
    for (int i = 0; i < merged_size; i++) {
        if (a_index + a_low > a_high) {
            merged_array[i] = array[b_low + b_index++];
        } else if (b_index + b_low > b_high) {
            merged_array[i] = array[a_low + a_index++];
        } else {

            if(array[a_low + a_index] <= array[b_low + b_index]) {
                merged_array[i] = array[a_low + a_index++];
            } else {
                merged_array[i] = array[b_low + b_index++];
            }
        }
    }

    memcpy(&(array[a_low]), merged_array, merged_size * sizeof(int));
    free(merged_array);
}

void mergesort(int * array, int low_index, int high_index) {

    if(high_index == low_index) return;

    int middle = low_index + ((high_index - low_index) / 2);

    mergesort(array, low_index, middle);
    mergesort(array, middle + 1, high_index);

    merge(array, low_index, middle, middle + 1, high_index);
}


int main(int argc, char * argv[]) {

    if(argc > 1) {

        char * filename = argv[1];

        FILE * input_file = fopen(filename, "r");

        if( input_file != 0 ) {
            int n;
            fscanf(input_file, "%d\n", &n);

            int * A = malloc(sizeof(int) * n);

            fscanf(input_file, "%d", &A[0]);
            for(int i = 1; i < n; i++) {
                fscanf(input_file, " %d", &A[i]);
            }

            printf("unsorted array:");
            for(int i = 0; i < n; i++) {
                printf(" %d", A[i]);
            }
            printf("\n");

            mergesort(A, 0, n - 1);

            printf("sorted array:");
            for(int i = 0; i < n; i++) {
                printf(" %d", A[i]);
            }

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

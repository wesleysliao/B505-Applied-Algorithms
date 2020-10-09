#include "stdio.h" //printf, fscanf
#include "stdlib.h" //malloc, free
#include "string.h" //memcpy



void print_usage() {
    printf("usage: quicksort [filename]\n");
}


void swap(int * array, int a_index, int b_index) {
    int temp = array[a_index];
    array[a_index] = array[b_index];
    array[b_index] = temp;
}


int partition(int * array, int start_index, int end_index) {

    int pivot_value = array[start_index];

    int j = start_index;
    for(int i = start_index + 1; i <= end_index; i++) {

        if(array[i] <= pivot_value) {
            swap(array, i, ++j);
        }
    }

    int pivot_index = j;
    swap(array, start_index, pivot_index);

    return pivot_index;
}


void quicksort(int * array, int start_index, int end_index) {

    if(start_index >= end_index) return;

    int pivot_index = partition(array, start_index, end_index);

    quicksort(array, start_index, pivot_index - 1);
    quicksort(array, pivot_index + 1, end_index);
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

            quicksort(A, 0, n - 1);

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

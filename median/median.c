#include "stdio.h" //printf, fscanf
#include "stdlib.h" //malloc, free
#include "string.h" //memcpy



void print_usage() {
    printf("usage: median [filename]\n");
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


int median(int * array, int start_index, int end_index, int k) {

    int pivot_index = partition(array, start_index, end_index);

    if ((pivot_index + 1) == k) return pivot_index;
    else if ((pivot_index + 1) > k) return median(array, start_index, pivot_index, k);
    else return median(array, pivot_index + 1, end_index, k);
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

            int k;
            fscanf(input_file, "\n%d", &k);

            printf("input array:");
            for(int i = 0; i < n; i++) {
                printf(" %d", A[i]);
            }
            printf("\n");
            printf("finding %dth smallest element\n", k);

            int result_index = median(A, 0, n - 1, k);

            printf("element index %d with value %d\n", result_index, A[result_index]);


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

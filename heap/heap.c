#include <stdio.h> //printf, fscanf
#include <stdlib.h> //malloc, free
#include <string.h> //memcpy
#include <math.h> //ceil



void print_usage() {
    printf("usage: majorityelement [filename]\n");
}


void swap(int * array, int a_index, int b_index) {
    int temp = array[a_index];
    array[a_index] = array[b_index];
    array[b_index] = temp;
}


int btree_parent(int i) {
    return ((i + 1) / 2) - 1;
}

int btree_left(int i) {
    return (2 * (i + 1)) - 1;
}

int btree_right(int i) {
    return (2 * (i + 1));
}


void max_heap(int * heap_array, int array_len, int node_index) {

    int node_value = heap_array[node_index];

    int left_index = btree_left(node_index);
    int right_index = btree_right(node_index);

    int largest_index;
    if( left_index < array_len && heap_array[left_index] > heap_array[node_index]) {
        largest_index = left_index;
    } else {
        largest_index = node_index;
    }

    if ( right_index < array_len && heap_array[right_index] > heap_array[largest_index] ) {
        largest_index = right_index;
    }

    if ( largest_index != node_index ) {
        swap(heap_array, node_index, largest_index);
        max_heap(heap_array, array_len, largest_index);
    }
}


int main(int argc, char * argv[]) {

    if(argc > 1) {

        char * filename = argv[1];

        FILE * input_file = fopen(filename, "r");

        if( input_file != 0 ) {
            int n;
            fscanf(input_file, "%d", &n);

            int * A = malloc(sizeof(int) * n);

            fscanf(input_file, "%d", &A[0]);
            for(int i = 1; i < n; i++) {
                fscanf(input_file, " %d", &A[i]);
            }


            printf("original array: ");
            for(int i = 0; i < n; i++) {
                printf("%d ", A[i]);
            }
            printf("\n");

            for (int i = (n / 2); i > 0; i--)
                max_heap(A, n, i-1);

            printf("max-heapified array: ");
            for(int i = 0; i < n; i++) {
                printf("%d ", A[i]);
            }
            printf("\n");

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

#include "stdio.h"
#include "stdlib.h"



void print_usage() {
    printf("usage: insort [filename]\n");
}


int main(int argc, char * argv[]) {

    if(argc > 1) {

        char * filename = argv[1];

        FILE * input_file = fopen(filename, "r");

        if( input_file != 0 ) {
            int list_len = 0;

            fscanf(input_file, "%d\n", &list_len);
            printf("list length: %d\n", list_len);

            int * list = malloc(sizeof(int) * list_len);

            fscanf(input_file, "%d", &list[0]);
            for(int i = 1; i < list_len; i++) {
                fscanf(input_file, " %d", &list[i]);
            }

            printf("initial list:\n");
            for(int i = 0; i < list_len; i++) {
                printf("%d ", list[i]);
            }
            printf("\n\n");

            int swap_count = 0;
            for(int i = 1; i < list_len; i++) {
                int k = i;
                while ((k > 0) && (list[k] < list[k - 1])) {

                    int temp = list[k - 1];
                    list[k - 1] = list[k];
                    list[k] = temp;
                    swap_count++;

                    k--;
                }
            }


            printf("list sorted in %d swaps:\n", swap_count);
            for(int i = 0; i < list_len; i++) {
                printf("%d ", list[i]);
            }
            printf("\n");


            free(list);
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

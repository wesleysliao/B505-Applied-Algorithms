#include "stdio.h" //printf, fscanf
#include "stdlib.h" //malloc, realloc, free, qsort
#include "string.h" //memcpy



void print_usage() {
    printf("usage: coins [filename]\n");
}



int minimum_coins(int total, int * coins, int number_of_denominations, int depth) {

    for(int i = (number_of_denominations - 1); i >= 0; i--) {

        int remainder = total - coins[i];
        if (remainder == 0) return depth + 1;
        else if (remainder > 0) return minimum_coins(remainder, coins, number_of_denominations, depth + 1);
        else continue;
    }
    return -1;
}



int main(int argc, char * argv[]) {

    if(argc > 1) {

        char * filename = argv[1];

        FILE * input_file = fopen(filename, "r");

        if( input_file != 0 ) {

            int total;
            fscanf(input_file, "%d\n", &total);

            int number_of_denominations = 1;
            int * coins = malloc(sizeof(int) * number_of_denominations);

            fscanf(input_file, "%d", &coins[0]);
            int new_coin = 0;
            while(fscanf(input_file, ",%d", &new_coin) > 0) {
                printf(" i %d", number_of_denominations);
                coins = realloc(coins, sizeof(int) * number_of_denominations);
                coins[number_of_denominations++] = new_coin;
            }

            int compare_ints(const void* a, const void* b)
            {
                int arg1 = *(const int*)a;
                int arg2 = *(const int*)b;

                if (arg1 < arg2) return -1;
                if (arg1 > arg2) return 1;
                return 0;
            }
            qsort(coins, number_of_denominations, sizeof(int), compare_ints);

            printf("desired total: %d\n", total);
            printf("there are %d coin denominations:", number_of_denominations);
            for(int i = 0; i < number_of_denominations; i++) {
                printf(" %d", coins[i]);
            }
            printf("\n");



            int minumum_change = minimum_coins(total, coins, number_of_denominations, 0);

            printf("making change requires %d coins.\n", minumum_change);

            free(coins);
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

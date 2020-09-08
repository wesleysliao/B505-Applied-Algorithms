#include "stdio.h"
#include "stdlib.h"



int main(int argc, char * argv[]) {

    if(argc > 1) {
        unsigned long n = atol(argv[1]);

        printf("n = %lu\n", n);


        unsigned long * list = (unsigned long *) malloc((n + 1) * sizeof(unsigned long));
        list[0] = 0;
        list[1] = 1;

        for (int i = 2; i <= n; i++) {
            list[i] = list[i - 1] + list[i - 2];
        }

        printf("result = %lu\n", list[n]);

        free(list);
    }

    return 0;

}

#include "stdio.h" //printf, fscanf
#include "stdlib.h" //malloc, free
#include "string.h" //memcpy



void print_usage() {
    printf("usage: editdist [filename]\n");
}

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int min_3(int a, int b, int c) {
    return (min(min(a, b), c));
}

int edit_distance(char * a, int a_size, char * b, int b_size) {

    int n = a_size + 1;
    int m = b_size + 1;

    int ** D = malloc(sizeof(int *) * n);
    for(int i = 0; i < n; i++) {
        D[i] = calloc(m, sizeof(int));
        D[i][0] = i;
    }

    for(int j = 0; j < m; j++) {
        D[0][j] = j;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {

            int insertion = D[i][j - 1] + 1;
            int deletion = D[i - 1][j] + 1;
            int match = D[i - 1][j - 1];
            int mismatch = D[i - 1][j - 1] + 1;

            if(a[i - 1] == b[j - 1]) {
                D[i][j] = min_3(insertion, deletion, match);
            } else {
                D[i][j] = min_3(insertion, deletion, mismatch);
            }
        }
    }


    int retval = D[n - 1][m - 1];
    for(int i = 0; i < n; i++) {
        free(D[i]);
    }
    free(D);

    return retval;
}


int main(int argc, char * argv[]) {

    if(argc > 1) {

        char * filename = argv[1];

        FILE * input_file = fopen(filename, "r");

        if( input_file != 0 ) {

            char * a = NULL;
            int a_size = 0;
            char new_char = '\0';
            while(fscanf(input_file, "%c", &new_char) > 0) {
                if(new_char == '\n') {
                    break;
                } else {
                    a = realloc(a, sizeof(int) * ++a_size);
                    a[a_size - 1] = new_char;
                }
            }

            char * b = NULL;
            int b_size = 0;
            while(fscanf(input_file, "%c", &new_char) > 0) {
                if(new_char == '\n' || new_char == EOF) {
                    break;
                } else {
                    b = realloc(b, sizeof(int) * ++b_size);
                    b[b_size - 1] = new_char;
                }
            }

            printf("string a: ");
            for(int i = 0; i < a_size; i++) printf("%c", a[i]);
            printf("\n");
            printf("string b: ");
            for(int i = 0; i < b_size; i++) printf("%c", b[i]);
            printf("\n");

            int edit_dist = edit_distance(a, a_size, b, b_size);
            printf("edit distance: %d\n", edit_dist);

            free(a);
            free(b);
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

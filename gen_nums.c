#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VAL 1000000
int main() {
    int i, r;
    FILE *outfile = fopen("numarr.txt", "w");
    srand(time(NULL));
    for (i = 1; i <= MAX_VAL; i++) {
        r = rand() % MAX_VAL;
        if (i % 100 == 0)
            fprintf(outfile, "%d\n", r);
        else
            fprintf(outfile, "%d ", r);
    }
    fclose(outfile);

    return 0;
}
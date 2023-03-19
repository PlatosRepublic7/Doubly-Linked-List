#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/time.h>


void get_nums(char *inF, int *num_arr, int num_to_get);
int convert_to_int(char num_string[9], int slen);
int get_power(int base, int exp);


void get_nums(char *inF, int *num_arr, int num_to_get) {
    int i = 0, nums_done = 0, num_len = 0, val;
    char c;
    char num_string[9] = ".........";
    FILE *infile = fopen(inF, "r");
    while (1) {
        c = fgetc(infile);
        if (c == EOF)
            break;
        if (isdigit(c)) {
            while (!isspace(c)) {
                num_string[num_len] = c;
                num_len++;
                c = fgetc(infile);
            }
            
            val = convert_to_int(num_string, num_len);
            num_arr[nums_done] = val;
            nums_done++;
            
            if (nums_done == num_to_get)
                break;
            
            for (i = 0; i < 9; i++) {
                if (num_string[i] == '.')
                    break;
                else
                    num_string[i] = '.';
            }
            num_len = 0;
        }
        else
            continue;
    }
    fclose(infile);
}

int convert_to_int(char num_string[9], int slen) {
    int total = 0, i;
    int exp = slen - 1;
    for (i = 0; i < slen; i++) {
        total += (int)(num_string[i] - '0') * get_power(10, exp);
        exp--;
    }

    return total;
}

int get_power(int base, int exp) {
    int total = 1, i;
    for (i = 0; i < exp; i++) {
        total *= base;
    }

    return total;
}

void print_progress(int count, int max) {
    float fcount = (float)count;
    float fmax = (float)max;
    float percentage = (fcount / fmax) * 100; 
    printf("\x1b[1F");
    printf("\x1b[2K");
    printf("%.2f%%", percentage);
    printf("\n");

    /*
    if ((int)percentage % 2 == 0) {
        num_char = percentage / 2;
        printf("\x1b[1F");
        printf("\x1b[2K");
        printf();
        for (i = 0; i < num_char; i++) {
            printf("%c", c);
        }
        printf("\n");
    }
    */
}

long current_timestamp() {
    struct timeval te;
    long milliseconds = 0L;
    gettimeofday(&te, NULL);
    milliseconds = te.tv_sec * 1000L + te.tv_usec / 1000;
    return milliseconds;
}
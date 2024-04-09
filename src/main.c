#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define ALPHABET_LENGTH 27

void print_mat(int mat[][ALPHABET_LENGTH], int dim);

void print_char(int c);

int get_char_pos(char c);

int main() {
    int mat[ALPHABET_LENGTH][ALPHABET_LENGTH];

    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        for (int j = 0; j < ALPHABET_LENGTH; j++) {
            mat[i][j] = 0;
        }
    }

    print_mat(mat, 27);

    FILE *file;
    char src[] = "../files/example.txt";

    file = fopen(src, "r");
    int charcount = 0;

    char buf[10000];
    int alphabet[27];
    char *token;
    while (fgets(buf, 10000, file)) {
        token = strtok(buf, " \n");
        while (token != NULL) {
            for (int i = 0; token[i] != '\0'; i++) {
                int index = get_char_pos(tolower(token[i]));
                if (index >= 0 && index <= 27) {
                    alphabet[index]++;
                }
                int indexI = get_char_pos(tolower(token[i]));
                int indexJ = get_char_pos(tolower(token[i + 1]));
                if (indexI != -1 && indexJ != -1) {
                    mat[indexI][indexJ] += 1;
                }
                charcount++;
            }
            charcount++;
            token = strtok(NULL, " \n"); // Get next word
        }
    }

    printf("\n");
    print_mat(mat, ALPHABET_LENGTH);
    printf("\n");

    printf("The char count resulted in: %i\n", charcount);
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        print_char(i);
        printf(": %i\n", alphabet[i]);
    }
    return 0;
}

void print_mat(int mat[][ALPHABET_LENGTH], int dim) {

    printf("  ");

    for (int i = 0; i < dim; i++) {
        print_char(i);
    }

    putchar('\n');

    for (int i = 0; i < dim; i++) {
        print_char(i);
        for (int j = 0; j < dim; j++) {
            printf("%i ", mat[i][j]);
        }
        putchar('\n');
    }
}

void print_char(int c) {
    if (c < 14) {
        printf("%c ", 'a' + c);
    } else if (c > 14 && c < 27) {
        printf("%c ", 'a' + c - 1);
    } else {
        printf("+ ");
    }
}

int get_char_pos(char c) {

    if ((c < 'a' || (c > 'z' && c <= CHAR_MAX)) && c != 50097) {
        return -1;
    } else if (c <= 'n') {
        return c - 'a';
    } else if (c >= 'o' && c <= 'z') {
        return c - 'a' + 1;                 
    } else {
        return 14;
    }

}

#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAXLEN 100
#define MAXLINE 100

char *mat[MAX][MAX];

void printmat();

int main(int argc, char **argv)
{
    FILE *fp;
    char *getcell(char **);
    char line[MAXLINE], *ptr;
    int y, x;

    if (argc == 1) {
        printf("Usage: csv FILE\n");
        return 0;
    } else {
        if ((fp = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s: could not open %s\n", argv[0], argv[1]);
            return 0;
        }
        for (y = 0; fgets(line, MAXLINE, fp) != NULL; y++)
            for (x = 0, ptr = line; (mat[y][x] = getcell(&ptr)) != NULL; x++)
                ;
    }

    printmat();
}

void printmat()
{
    int i, j;

    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++)
            if (mat[i][j] != NULL)
                printf("%4.4s ", mat[i][j]);
        printf("\n");
    }
}

char *getcell(char **ptr)
{
    static char cell[MAXLINE];
    char *cellp = cell;

    if (**ptr == '\n') /* end of line */
        return NULL;
    while ((*cellp = **ptr) != ',' && **ptr != '\n')
        cellp++, ptr[0]++;
    *cellp = '\0';
    if (**ptr != '\n')
        ptr[0]++; /* move pointer past comma */
    return strdup(cell);
}
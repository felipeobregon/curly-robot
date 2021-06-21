#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAXLEN 100
#define MAXLINE 100

int main(int argc, char **argv)
{
    FILE *fp;
    char *getcell(char **);
    char line[MAXLINE];
    char *cellp, *ptr, *mat[MAX][MAX];

    if (argc == 1) {
        printf("Usage: csv FILE\n");
        return 0;
    } else {
        if ((fp = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s: could not open %s\n", argv[0], argv[1]);
            return 0;
        }
        while (fgets(line, MAXLINE, fp)) { /* returns NULL on EOF or error */
            ptr = line;
            while ((cellp = getcell(&ptr)) != NULL)
                printf("%10s|", cellp);
            printf("\n");
        }
    }
}

char cell[MAXLINE];

char *getcell(char **ptr)
{
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
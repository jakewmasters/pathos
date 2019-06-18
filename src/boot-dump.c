#include <stdlib.h>
#include <stdio.h>

int
main()
{
    FILE *fp;
    int c;

    fp = fopen("boot.out", "rb");
    if (fp == NULL){
        fprintf(stderr, "error opening file\n");
        exit(1);
    }
    while ((c = getc(fp)) != EOF){
        printf("%x\n", c);
    }
    fclose(fp);
    return 0;
}
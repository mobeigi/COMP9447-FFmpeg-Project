#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
vuln(char * s)
{

        char buf[256];
        strcpy(buf, s);
}

void
check(char *s)
{
        char random[8] = {0};
        unsigned int * ptr = (unsigned int *) s;
        FILE * f = fopen("/dev/urandom", "rb");

        fgets(random, 8, f);
        fclose(f);

        *ptr ^= 0xdeadbeef;
        ptr++;
        *ptr ^= 0xdeadbeef;

        if(strcmp(random, s) == 0)
                vuln(s+8);
        exit(-1);
}

int
main(int argc, char *argv[])
{
        if (argc != 2)
                exit(-4);

        check(argv[1]);

        return 0;
}

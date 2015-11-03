#include <stdio.h>

void
call(int addr)
{
        int m = 0;
        void (*blah)(void *);

        blah = addr;
        blah(&m);
}

int
main(int argc, char *argv[], char *envp[])
{
        int val, i;

        if (argc != 2 || strcmp(argv[0], "./level3") != 0 || strlen(argv[1]) > 12)
        {
                printf("Wrong arguments\n");
                exit(-1);
        }

        if (envp[0] != NULL) {
                printf("Environment variables in use\n");
                exit(-2);
        }

        val = strtol(argv[1], NULL, 10);

        if (val != 0) {
                call(val);
        }
}

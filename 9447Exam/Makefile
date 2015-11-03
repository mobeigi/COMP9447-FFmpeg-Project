CC = gcc
CFLAGS = -m32 -z execstack -fno-stack-protector

%:
	$(CC) $(CFLAGS) $@.c -o $@

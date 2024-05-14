#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int next_read_error = 0;

void test_gnl(int fd, const char *expected)
{
    char *line = get_next_line(fd);
    if ((line == NULL && expected == NULL) || (line != NULL && expected != NULL && strcmp(line, expected) == 0))
    {
        printf("PASS: %s\n", expected ? expected : "NULL");
    }
    else
    {
        printf("FAIL: expected '%s', got '%s'\n", expected ? expected : "NULL", line ? line : "NULL");
    }
    free(line);
}

int main()
{
    		char *name = "read_error.txt";
		int fd = open(name, O_RDONLY);
		/* 1 */ test_gnl(fd, "aaaaaaaaaa\n");
		/* 2 */ test_gnl(fd, "bbbbbbbbbb\n");
		// set the next read call to return -1
		next_read_error = 1;
		if (BUFFER_SIZE > 100) {
			char *temp;
			do {
				temp = get_next_line(fd);
				free(temp);
			} while (temp != NULL);
		}
		/* 3 */ test_gnl(fd, NULL);
		next_read_error = 0;
		close(fd);
		fd = open(name, O_RDONLY);
		/* 4 */ test_gnl(fd, "aaaaaaaaaa\n");
		/* 5 */ test_gnl(fd, "bbbbbbbbbb\n");
		/* 6 */ test_gnl(fd, "cccccccccc\n");
		/* 7 */ test_gnl(fd, "dddddddddd\n");
		/* 8 */ test_gnl(fd, NULL);
		
    close(fd);
    return 0;
}



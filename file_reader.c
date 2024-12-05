
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdint.h>

int open_file(char *filepath)
{
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (fd < 0)
        return 84;
    return fd;
}

void read_file(char *filepath)
{
    int fd = open_file(filepath);
    if (fd == -1) {
        fprintf(stderr, "Error opening file: %s\n", filepath);
        return;
    }
    char buffer[1024];

    while (1) {
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read <= 0)
            break;
        printf("%s", buffer);
        fflush(stdout);
        usleep(100000);
        memset(buffer, 0, sizeof(buffer));
        close(fd);
        break;
    }
}

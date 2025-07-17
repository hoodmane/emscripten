#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
    mkdir("blah", 0777);
    int fd = open("blah/a.txt", O_CREAT);
    assert(fd > 0);
    close(fd);
    // Remove execute permissions on the directory.
    chmod("blah", 0666);
    // Make sure readdir lists ., .., and blah even though we removed execute
    // permissions
    DIR* dir = opendir("blah");
    assert(dir != 0);
    for (;;) {
        struct dirent *a = readdir(dir);
        if (a == NULL) {
            break;
        }
        printf("name: %s\n", a->d_name);
        printf("d_type: %d\n", a->d_type);
    }
    printf("success\n");
}

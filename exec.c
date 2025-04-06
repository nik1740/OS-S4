#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
pid_t pid = fork();
if (pid == -1) {
perror("fork");
exit(EXIT_FAILURE);
} else if (pid == 0) {
execl("/bin/ls", "ls", "-l", NULL);
perror("execl");
exit(EXIT_FAILURE);
} else {
wait(NULL);
printf("Child process finished.\n");
}
return 0;
}

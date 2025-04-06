#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>


int main() {
    pid_t p = vfork();
    if(p<0) {
        perror("fork failed");
        exit(1);
    } else if(p==0) {
        printf("heloo from child (PID : %d)\n",getpid());
    } else {
        printf("Hello from parent(Child PID)\n",p);
    }
    return 0;
}
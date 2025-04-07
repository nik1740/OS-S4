#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 1024
void main(){
char *shm, *ptr;
key_t key = ftok("shmfile.txt",'R');
int shmid = shmget(key, SHM_SIZE, IPC_CREAT |0666); //creating shared memory segment
shm = shmat(shmid, NULL, 0); //attach shm
  ptr = shm;
sprintf(ptr, "Shared Memory Content");
printf("Data Written To Shared Memory\n");ptr = shm;
printf("Data In The SHM: ");while(*ptr != '\0'){
printf("%c", *ptr);ptr++;
}
shmdt(shm); //detach shm
shmctl(shmid, IPC_RMID, NULL);
}

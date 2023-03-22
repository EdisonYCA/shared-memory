#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

extern int errno;

int main(){
   /* Server Code */
   key_t key = ftok("./memory", 1234); // generates a key for the shared memory
   int sm_id; // id for shared memory
   
   // create share memory
   if((sm_id = shmget(key, 100, IPC_CREAT | 0644)) < 0){
    perror("server: shmget");
    exit(1);
   }

   // attach to the shared memory
   char *address = shmat(sm_id, 0, 0);
   if(address < 0){
      perror("shared memory attach");
      exit(1);
   }

   
   


}
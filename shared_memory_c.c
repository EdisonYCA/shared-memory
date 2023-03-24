#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

extern int errno;

int main(){
   printf("\nClient Executed...\n");
   /* Client Code */
   key_t key = ftok("./memory", 1234); // generates a key for the shared memory
   int sm_id; // id for shared memory
   
   /* Create share memory */
   if((sm_id = shmget(key, 100, 0)) < 0){
    perror("server: shmget");
    exit(1);
   }

   /* Attach to the shared memory */
   char *address = (char *) shmat(sm_id, 0, 0);
   if(address < 0){
      perror("shared memory attach");
      exit(1);
   }

   printf("Client read: %s", address);



}
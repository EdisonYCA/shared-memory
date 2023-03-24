#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

extern int errno;

int main(int argc, char *argv[]){
   /* Server Code */
   key_t key = ftok("./memory", 1234); // generates a key for the shared memory
   int sm_id; // id for shared memory
   
   /* create share memory */
   if((sm_id = shmget(key, 100, IPC_CREAT | 0644)) < 0){
    perror("server: shmget");
    exit(1);
   }

   /* attach to the shared memory */
   char *address = (char *) shmat(sm_id, 0, 0);
   if(address < 0){
      perror("shared memory attach");
      exit(1);
   }

   /* write a character to shared memory */
   char* to_write = "Hello, World.\n";
   strcpy(address, to_write);
   printf("wrote value to memory: %s\n", to_write);

   /* execute client */
    pid_t pid = fork(); // create a fork of the program

    if(pid < 0){
        perror("Error");
        exit(EXIT_FAILURE);
    }

    if(pid == 0){
        char path[2048]; // will store the client file path

        // get client path
        if(getcwd(path, sizeof(path)) > 0){
            strcat(path, "/shmc");
        } else{
            perror("Get cwd");
            exit(1);
        }
        
        // execute the client
        if(execv(path, argv) == -1){
            perror("Exec client");
        }
    }
}
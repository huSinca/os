#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */




void barbar();
void customer();
void waitingRoom();


void main(void)
{   
    
    pid_t pid;
    printf("Generating a Process..\n");
    switch(pid = fork()){
        
        case -1:
            printf("Fork failed\n");
            break;
        case 0:
            printf("Child process # %d is created.\n", getpid());
            barbar();
            break;
        default:
            //sleep(1);
            printf("Parent process # %d : generating another child.\n", getpid());
            
    }
    
}

void barbar(){
    
}

void customer(){
    
    
}

void waitingRoom(){
    
    
}



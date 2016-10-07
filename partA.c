#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */




void barber();
void customer();
void waitingRoom();


void main(void)
{   
    int barberFlag=0, waitingFlag=0;
    pid_t pid;
    printf("Generating a Process..\n");
    switch(pid = fork()){
        
        case -1:
            printf("Fork failed\n");
            break;
        case 0:
            printf("Child process #%d is created.\n", getpid());
            barber();
            break;
        default:
            //sleep(1);
            printf("Parent process #%d : generating another child.\n", getpid());
            switch(pid = fork()){
                case -1:
                    printf("Fork failed\n");
                    break;
                case 0:
                    printf("Child process #% is created.\n", getpid());
                    waitingRoom();
                default:
                    printf("Parent process #% is acting as customerGenerator.", getpid());
                    customerGenerator();
                
                
            }
    }
    
}

void barber(){
    printf("Barber Process #%d: ready to accept first process.", getpid());
    if(BarberFlag=0){
        
        
        
        
    }
}

void customerGenerator(){
    printf("Customer Generator Process #%d: ready to create processes.", getpid());
    while()
    
}

void waitingRoom(){
    printf("WaitingRoom Process #%d: ready.", getpid());
    
}



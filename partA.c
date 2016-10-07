#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */




void barber();
void customerGenerator();
void waitingRoom();


void main(void)
{   
    int barberFlag, waitingFlag;
    barberFlag = 0;
    waitingFlag = 0;
    pid_t pid; int test;
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
            sleep(2); // so the output would make sense.
            test = getpid();
            printf("Parent process #%d : generating another child.\n", getpid());
            switch(pid = fork()){
                case -1:
                    printf("Fork failed\n");
                    break;
                case 0:
                    printf("Child process #%d is created.\n", getpid());
                    waitingRoom();
                default:
                    sleep(2); // so the output would make sense.
                    if(test == getpid()){
                        printf("Parent process #%d is acting as customerGenerator.\n", getpid());
                        customerGenerator();
                    }

            }
    }
    
}

void barber(){
    printf("Barber Process #%d: ready to accept Customers.\n", getpid());
    
}

void customerGenerator(){

         printf("Customer Generator Process #%d: ready to create Customers.\n", getpid());
    
    
}

void waitingRoom(){
    printf("WaitingRoom Process #%d: ready to accept Customers.\n", getpid());
    
}


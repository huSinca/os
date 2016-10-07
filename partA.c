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

//global flags
int barberFlag, waitingCount;


void main(void)
{   
    barberFlag = 0;
    waitingCount = 0;
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
                    if(test == getpid()){ // test variable holds the id of the parent.
                        printf("Parent process #%d is acting as customerGenerator.\n", getpid());
                        customerGenerator();
                    }

            }
    }
    
}

void barber(){
    if(barberFlag==0){
        barberFlag = 1;
        
        printf("Customer #%d: getting haircut.\n", getpid());
        
        sleep(1);
    
        
    }
    barberFlag = 0;
    printf("Customer #%d: done\n", getpid());

}

void customerGenerator(){
    printf("Customer Generator Process #%d: ready to create Customers.\n", getpid());
         /* fork child processes */
    pid_t pid;
    for (int i = 0; i < 5; i++){
        pid = fork ();
        if (pid < 0)              /* check for error      */
            printf ("Fork error.\n");
        else if (pid == 0)
            break;                  /* child processes */
    }
    //******************   PARENT PROCESS   ****************/
    if(pid!=0){
        // wait for all children to exit)
        while(pid=waitpid(-1, NULL, 0)){
            if(errno == ECHILD)
                break;
        }
        printf("\nParent: All children have finished.\n");
        
        
    }else{ //******************   CHILD PROCESS   *****************/
        while(1){
            if(waitingCount < 3){
               waitingRoom(); // goes to waiting room then waiting room sends the process to barber.
               break;
            }
            sleep(0.5);
        }
        
    }
    
}

void waitingRoom(){
    if(waitingCount < 3){
        waitingCount++; // incrementing how many process is entered.
        printf("Customer #%d: is in waiting room.\n", getpid());
        while(1){
            if(barberFlag == 0){
                waitingCount--; 
                barber();
                break;
            }
            sleep(0.5);
        }
    }
    
}


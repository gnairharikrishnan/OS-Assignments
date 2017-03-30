/***********************************************************************************************************************
 Project Name:      OS_Assignment3_Shared Memory
 File name:         receiver.c
 Description:       The project requires two simple C programs to communicate with each other using shared
                    memory. This file, receiver.c  runs in an infinite background loop receiving alpha numeric
                    values as input from the user, one line at a time. After reading one line from the standard input
                    This program then sends this information to the other program only if the line contains 
                    the secret code "C00L". The sharing of data between the two processes takes place via
                    shared memory.
 
                    Disclaimer: If you are reading this code on my git hub, ignore the main.c file. Instructions on
                    executing the code can be found in the Read_me file.
 
 Author:            Harikrishnan G Nair on 10/23/16.
************************************************************************************************************************
                            Copyright © 2016 New York University. All rights reserved.
***********************************************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

char *sh_ptr;                                                              //Pointer to access the shared memory.

/*********************************************************************************************************************
 
 Function name:     create_shared_mem
 Description:       The function creates a shared memory. And performs Error handling if something goes wrong.

 **********************************************************************************************************************/


int create_shared_mem()
{
    key_t Key;
    int shared_memory_id;
    Key = 100;                                                             //Random value for the Key (should be same in both programs)
    shared_memory_id = shmget(Key, SHM_SIZE, IPC_CREAT | 0666);            //Creating and Getting the shared memory ID
    
    if (shared_memory_id < 0)                                              //Error Handling if segment was not created
    {
        perror("Shared memory segment could not be created!!");
        exit(EXIT_FAILURE);
    }
    
    sh_ptr = shmat(shared_memory_id, NULL, 0);                             //Attaching the shared memory to sh_ptr
    
    if (sh_ptr == (char *) -1)                                             //Error Handling if the attach failed
    {
        perror("Shared memory segment could not be attached!!");
        exit(EXIT_FAILURE);
    }
    return(0);
}

/*********************************************************************************************************************
 
 Function name:     check_and_push()
 Description:       The receives the alpha numeric input. Check if it contains the secret code C00L.
 
**********************************************************************************************************************/

int check_and_push()
{
    char *flag;
    char *user_input = malloc(sizeof(char)*BUFSIZ);
    for(;;)                                                             //The background infinite loop.
    {
        
        printf("Enter the data to be sent: ");
        fgets(user_input, BUFSIZ, stdin);
        flag = strstr (user_input,"C00L");                              //Check if the input has the secret code C00L
        
        if (flag!=NULL)
        {
            strcpy(sh_ptr,user_input);                                  //Copy data into the shared memory
        }
        
        while(*sh_ptr!='\0')                                            // Waits until the next data is received
        {
            sleep(1);
        }
    }

    return(0);
}

/*********************************************************************************************************************
 
 Function name:     main()
 Description:       This function is where the execution begins. It calls create_shared_mem function and check_and_push
                    function.
 
 **********************************************************************************************************************/

int main()
{
    
    create_shared_mem();
    check_and_push();
    return(0);
    
}


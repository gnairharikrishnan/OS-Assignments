/*********************************************************************************************************************
 Project Name:      OS_Assignment3_Shared Memory
 File name:         processor.c
 Description:       The project requires two simple C programs to communicate with each other using shared
                    memory. This file, processor.c  creates an output file secrets.out. It then increments 
                    the counter depending on the number of alpha numeric elements in the array.
 
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

char *sh_ptr;

/*********************************************************************************************************************
 
 Function name:     get_shared_mem
 Description:       The function creates a shared memory. And performs Error handling if something goes wrong.
 
**********************************************************************************************************************/


int get_shared_mem()
{
    key_t Key;
    int shared_memory_id;
    Key = 100;                                                             //Random value for the Key (should be same in both programs)
    shared_memory_id = shmget(Key, SHM_SIZE, IPC_CREAT | 0666);            //Getting the shared memory ID
    
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

/************************************************************************************************************************
 
 Function name:     main()
 Description:       This function is where the execution begins. It calls create_shared_mem function and then counts the
                    number of alpha numerals. It then prints the content received and the alpha neumerals into the 
                    secrets.out file.
 
*************************************************************************************************************************/

int main(void)
{
    
    int counter;
    char *i;
    FILE * fptr;
    fptr = fopen("secrets.out","w");                                      //Creating the output file secrects.out
    get_shared_mem();
    for(;;)
    {
        if (*sh_ptr != '\0')
        {
            counter = 0;
            for (i=sh_ptr; *i != '\0'; i++)
            {
                if (*i=='0'||*i=='1'||*i=='2'||*i=='3'||*i=='4'||*i=='5'||*i=='6'||*i=='7'||*i=='8'||*i=='9') //Counting the number of alpha numerals
                {
                				counter++;
                }
            }
            fptr = fopen("secrets.out","a");                             //Opening the output file in append mode.
            fprintf(fptr,"The text received is: %sThe count of numerals: %d\n",sh_ptr,counter);  //Printing the data into secrets.out file.
            fclose(fptr);
            *sh_ptr = '\0';
        }
    }
    
    if (shmdt(sh_ptr) == -1)                                             // Error Handling if shared memory segment could not be detached
    {
        perror("Shared memory segment not detached!!");
        exit(1);
    }
}


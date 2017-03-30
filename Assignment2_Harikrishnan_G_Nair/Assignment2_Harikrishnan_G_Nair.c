/****************************************************************************************
Program name:   OS_Assignment_Multithreading
Description:    The program creates a child thread. The main program and the child 
                thread then increase a global counter. The child thread exits when 
                the value is greater than 25. In the code provided in the assignment,
                execution stops after the counter value hits 27 (because when counter
                value of the child is equal to 25 the counter is still incremented and 
                printed. The control then goes to the main program which increments and
                prints 27). Because the mutex is not released inside the section which 
                checks for the counter value and exits, the resourcesare still with the 
                child thread and execution gets stuck and will not go forward. When
                we add the code to release the mutex, we can see that the once the value 
                of the counter exceeds 25, the execution continues, but only the main 
                thread prints the counter value.

 Author:        Harikrishnan G Nair on 10/10/16.
 
*****************************************************************************************
         Copyright © 2016 New York University. All rights reserved.
*****************************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex_1;

int counter;

void *child1(void *arg)
{
    while(1){
        pthread_mutex_lock(&mutex_1);
        sleep(1);
        if(counter > 25)
        {
            pthread_mutex_unlock(&mutex_1); //Unlocking the mutex before exiting the child thread.
            pthread_exit(NULL);
        }
        else
            counter++;
        pthread_mutex_unlock(&mutex_1);
        printf("Child1: counter=%d\n", counter);
    }
}


int main(void)
{
    pthread_t tid1;
    counter = 0;
    
    pthread_mutex_init(&mutex_1,NULL);
    pthread_create(&tid1,NULL,child1,NULL);
    do{
        pthread_mutex_lock(&mutex_1);
        sleep(1);
        counter++;
        pthread_mutex_unlock(&mutex_1);
        printf("Main: counter=%d\n", counter);
        
    }while(1);
    pthread_exit(0);
}

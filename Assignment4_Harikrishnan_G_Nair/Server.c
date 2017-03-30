/****************************************************************************************
 Program name:      OS_Assignment_Socket_Programming
 File name:         Server.c
 Description:       The program gets user input from the client.c checks if the input has 
                    the text C00L in it, if it does, then it saves the data into a file and 
                    counts the number of digits in the file. Kindly refer to the detailed 
                    inline comments for more information. A readme.pdf file with details on
                    how to execute the code is also attached.
 
 Author:            Harikrishnan G Nair on 10/10/16.
 
 *****************************************************************************************
            Copyright © 2016 New York University. All rights reserved.
 *****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <netdb.h>
#include <arpa/inet.h>


//Global variable and function declarations
int sum, l=0,tot_sum=0;
void sum_gen();
int count_digits(char *str);

/*******************************************************************************************
 
 Function name:     Main function
 Description:       The Program execution begins here.
 
*******************************************************************************************/

int main(int C, char *V[])
{
    //Interrupt call back to check for interupts, if Control + C is pressed, it calls the function that generates summary
    signal (SIGINT,sum_gen);
    
    //Socket descriptor
    int sck_dsc;
    int buf_len, n_fd;
    struct sockaddr_in serv_ad,clnt_addr;
    socklen_t s_size;
    char s[100], buff[BUFSIZ];
    char *flag;
    
    //Creating Secrets.out
    FILE * fp;
    fp = fopen("Secrets.out","w");
    fclose(fp);
    
    //Creating the socket
    sck_dsc= socket(AF_INET,SOCK_STREAM,0);
    
    //Error Handling if socket creation failed
    if(sck_dsc<0)
    {
        printf("!!Socket Creation Failed!!");
        return(0);
    }
    
    //Populating the server
    memset(&serv_ad, 0, sizeof(serv_ad));
    serv_ad.sin_family = AF_INET;
    serv_ad.sin_port = htons(5000);
    serv_ad.sin_addr.s_addr = htonl(INADDR_ANY);
    
    
    // Error handling if Bind Fails
    if (bind(sck_dsc,(struct sockaddr*)&serv_ad,sizeof(serv_ad)) < 0)
    {
        close(sck_dsc);
        printf("!!Bind Failed!!");
        return(0);
    }
    
    
    // Blocking function that Listens to incoming sockets and waits for a connection
    if (listen(sck_dsc, 1) < 0)
    {
        printf("!!Failed to  listen!!");
        return(0);
    }
    printf("!!Waiting for connections!!\n");
    
    s_size = sizeof(clnt_addr);
    n_fd = accept(sck_dsc, (struct sockaddr *)&clnt_addr, &s_size);
    
    //Error handling for accept
    if (n_fd < 0)
    {
        printf("!!Accept!!");
    }
    printf("Connected to: %s \n", inet_ntop(AF_INET, &clnt_addr.sin_addr, s, sizeof (s)));
    
    
    //Infinte loop that waits for text
    for (;;)
    {
        // error is raised if buffer is not received
        if ((buf_len = recv(n_fd, buff, BUFSIZ-1, 0)) < 0)
        {
            printf("!!Could not receive data from client!!");
            return(0);
        }
        
        // '\0' to signalize the termination of the string.
        buff[buf_len] = '\0';
        
        //Checking if the Data received has the secret code
        flag = strstr (buff,"C00L");
        if (flag!=NULL)
        {
            l++;
            
            // Output Received string
            printf("String received: %s",buff);
            
            fp = fopen("Secrets.out","a");
            
            //Counting the number of digits in the received string
            sum=count_digits(buff);
            
            //Counting the total number of digits across all received inputs
            tot_sum=tot_sum+sum;
            
            //Write the data and the number of Alpha numerals into the
            fprintf(fp, "No of Alpha numerals: %d \nThe String you have entered is: \n", sum);
            fputs(buff, fp);
            fclose(fp);
        }
     }
    
    return 0;
    
}

/*******************************************************************************************
 
 Function name:     count_digits
 Description:       The function counts the number of digits in the received string.
 
 *******************************************************************************************/

int count_digits(char *str)
{
    char *i;
    int count;
    if (*str != '\0')
    {
        count = 0;
        for (i=str; *i != '\0'; i++)
        {
            if (*i=='0'||*i=='1'||*i=='2'||*i=='3'||*i=='4'||*i=='5'||*i=='6'||*i=='7'||*i=='8'||*i=='9') //Counting the number of alpha numerals
            {
                count++;
            }
        }
    }
    return count;
}

/*******************************************************************************************
 
 Function name:     sum_gen
 Description:       Generates the summary when the interrupt is received.
 
 *******************************************************************************************/

void sum_gen()
{
    printf("\nTotal lines received: %d \n",l);
    printf("Total digit count: %d \n ",tot_sum);
    
}

/*********************************************************************************************
                                End of program code 

*********************************************************************************************/

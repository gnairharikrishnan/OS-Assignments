/********************************************************************************************
 Project Name:      OS_Assignment5_RPC
 File name:         server.c
 Description:       The project requires two simple C programs to communicate with
                    each other using Remote procedural calls (RPC). This file,
                    server.c  houses the RPC call back, commrpc_1_svc. It receives the
                    message from client.c. It checks for the secret key and prints the
                    received message. If the message has the secret key, it creates a file
                    called secrets.out and prints the total number of digits in the text
                    and the text itself
 
 Author:            Harikrishnan G Nair on 11/29/16.
 **********************************************************************************************
                Copyright © 2016 New York University. All rights reserved.
 **********************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "os.h"


//RPC call back
int * commrpc_1_svc( char ** msg, struct svc_req * req)
{
    //File pointer
    FILE *fp;
    
    //Return value for the client file
    static int rvalue;
    int i=0;
    char buff[1000];
    int flag = 0;
    
    //Creating secrets.out file
    fp = fopen("secrets.out","a");
    //Error handling if file not created
    if (fp == (FILE *) NULL)
    {
        rvalue = 0;
        return(&rvalue);
    }
    
    strcpy(buff,*msg);
    
    printf("Data Recieved: %s",*msg);
    //Count the number of zeros in the recieved text
    int count = 0;
    for(i=0;i<strlen(*msg);i++)
        {
            if(buff[i]>='0'&& buff[i]<='9')
            {
                count ++;
            }
        }
    
    //Writing the data recieved and the number of digits to the secrets.out file
    fprintf(fp,"Text received: %s \nTotal Number of Alpha numerals: %d\n \n",*msg, count);
    
    //Making sure that the pointer is free for the next time
    *msg=NULL;
    fclose(fp);
    rvalue = 1;
	
    return(&rvalue);
	
}


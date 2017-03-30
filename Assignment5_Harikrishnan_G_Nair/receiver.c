
/********************************************************************************************
Project Name:      OS_Assignment5_RPC
File name:         receiver.c
Description:       The project requires two simple C programs to communicate with 
                   each other using Remote procedural calls (RPC). This file, 
                   client.c  runs in an infinite background loop receiving alpha 
                   numeric values as input from the user, one line at a time. After 
                   reading one line from the standard input, the program then sends
                   this information to the other program only if the line contains 
                   the secret code "C00L".
 
Author:            Harikrishnan G Nair on 11/29/16.
**********************************************************************************************
                Copyright © 2016 New York University. All rights reserved.
**********************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "os.h"
#include <rpc/rpc.h>

void main(int argc, char ** argv)
{
    CLIENT * client;
    char * host;
    int * check;
    char * message;
	int flag;
    char Buff[256];
    
    //Error handling if wrong format used
    if (argc != 2)
    {
        fprintf(stderr, "Wrong Format!! %s <host>\n",argv[0]);
        exit(1);
    }
    
    host = argv[1];

    for(;;)
	{
        //Getting user input
        printf("Enter the data to be sent: ");
        fgets(Buff,BUFSIZ,stdin);
        message=Buff;
 
        //Connecting to the server
        client = clnt_create(host, COMM, COMMVERSION, "tcp");

        //Error handling if connection failed
        if (client == NULL)
        {
            clnt_pcreateerror(host);
            exit(1);
        }
        //Checking if the input has the secret key
        flag=strstr(message, "C00L");
        
        if (flag!=NULL)
        {
            //Calling RPC
            check = commrpc_1(&message, client);
            
            //Error handling if RPC failed
            if (check == (int *) NULL)
            {
                clnt_perror(client, host);
                exit(1);
            }
            printf("Success!! Message sent to %s\n",host);
        }
        else
        {
            //Error message display
            printf("Secret Key Not found!! Please try again!!\n");
        }
        
    }
}



/****************************************************************************************
 Program name:      OS_Assignment_Socket_Programming
 File name:         Client.c
 Description:       The program creates a socket and connects to a server. It then gets user 
                    input from the user. It goes on to checks if the input has the text C00L 
                    in the input and then sends the data to server.c. Please refer to the inline
                    comments for more information. For information on how to execute the code and
                    sample input output screenshot, please refer to the 
 
 Author:            Harikrishnan G Nair on 10/10/16.
 
 *****************************************************************************************
            Copyright © 2016 New York University. All rights reserved.
 *****************************************************************************************/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<errno.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<sys/stat.h>
#include	<fcntl.h>


int main(int argc, char *argv[])
{
    //Socket Descriptor
    int sck_dsc;
    char *flag;
    struct sockaddr_in serv_ad;
    
    //Allocating the data buffer
    char *Data_buf = malloc(sizeof(char)*BUFSIZ);
    
    //Error Handling
    if (argc != 3)
    {
        printf("!!Invalid Argument! Use this format : (IP address) (Port Number (configured to 5000))!! \n");
        return(0);
    }
    //Creating the socket
    sck_dsc = socket(AF_INET, SOCK_STREAM, 0);
    
    //Error handling if the socket could not be created
    if(sck_dsc < 0)
    {
        printf("!!The Socket could not be created!!!");
        return(0);
    }
    
    //Populating the server to connect
    memset(&serv_ad, 0, sizeof serv_ad );
    serv_ad.sin_family = AF_INET;
    serv_ad.sin_port = htons(atoi(argv[2]));
    serv_ad.sin_addr.s_addr = inet_addr(argv[1]);
    
    //Connecting to the server and Error handling if connection failed
    if(connect(sck_dsc, (struct sockaddr*)&serv_ad, sizeof serv_ad ) < 0)
    {
        printf("!!Cannot Connect to server!!");
        return(0);
    }
    
    //Infinite loop to keep receiving input
    for(;;)
    {
        printf("Kindly provide your input along with the secret code: ");
        memset(Data_buf, 0, sizeof Data_buf);
        fgets(Data_buf, BUFSIZ, stdin);
        
        //Check if the input contains the secret keyword C00L
        flag = strstr (Data_buf,"C00L");
        
        if (flag!=NULL)
        {
            if (send(sck_dsc, Data_buf, strlen(Data_buf), 0) < 0)
            {
                printf("!!The Data Could not be sent!!");
            }
        }
    }
    return 0;
}

/*********************************************************************************
                            End of program code
 
 *********************************************************************************/


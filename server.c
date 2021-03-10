#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SIZE 1024

int main(int argc, char* argv[]){
    int udpSocket,bufferSize,messageSize;
    int returnStatus = 0;
    struct sockaddr_in udpServer,udpClient;
    char buff[SIZE];
    char message[SIZE];

    socklen_t lengthofClient;
    lengthofClient = sizeof(udpClient);
    
    /* check for the right number of arguments */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1); }
    /*Create a socket*/
    udpSocket=socket(AF_INET,SOCK_DGRAM,0);
    if(udpSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else{
        printf("Socket created.\n");
    }

    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = htonl(INADDR_ANY);
    udpServer.sin_port = htons(atoi(argv[1]));

    memset(buff,'\0',SIZE);
    memset(message,'\0',SIZE);
    strcpy(message,"\nAnybody there? ");
    messageSize=strlen(message);

    write(0,message,messageSize);

    returnStatus=bind(udpSocket,(struct sockaddr*)&udpServer,sizeof(udpServer));
    /*check for binding*/
    if(returnStatus==0){
        for(;;){
            time_t date;
            time(&date);

            /*check for receiving*/
            if((recvfrom(udpSocket,buff,sizeof(buff),0,(struct sockaddr*)&udpClient,&lengthofClient))<0){
                 memset(message,'\0',SIZE);
                 strcpy(message,"\nOops, error in receiving");   
                 messageSize=strlen(message);
                 write(0,message,messageSize);
                }
           
            memset(message,'\0',SIZE);
            strcpy(message,"\nI got the message: ");
            messageSize=strlen(message);
            write(0,message,messageSize);
            write(0,buff,strlen(buff));

            /*check for sending*/
            if((sendto(udpSocket,ctime(&date),strlen(ctime(&date)),0,(struct sockaddr*)&udpClient,sizeof(udpClient)))<0){
                memset(message,'\0',SIZE);
                strcpy(message,"\nOops,Error in sending");   
                messageSize=strlen(message);
                write(0,message,messageSize);
               }

        }
    }

    else{
        memset(message,'\0',SIZE);
        strcpy(message,"\nOops,Error in bind");
        messageSize=strlen(message);
        write(0,message,messageSize);
    }
}

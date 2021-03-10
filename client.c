#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define BUFF 1024

int main(int argc, char* argv[]){

    int udpSocket;
    struct sockaddr_in udpClient, udpServer;
    socklen_t servlen;
    char buff[BUFF];
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <ip address> <port>\n", argv[0]);
        exit(1); 
        }
    udpSocket = socket(AF_INET,SOCK_DGRAM,0);
    if(udpSocket == -1){
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
        }
    else {
        printf("Socket created.\n");
        }
    
    udpClient.sin_family = AF_INET;
    udpClient.sin_port = htons(atoi(argv[2]));
    udpClient.sin_addr.s_addr = INADDR_ANY;

    for(;;){
        printf("Enter the string : ");
        scanf("%s",buff);
        if((sendto(udpSocket,buff,strlen(buff),0,(struct sockaddr*)&udpClient,sizeof(udpClient)))<0){
            printf("Error");
            }
  
        recvfrom(udpSocket,buff,sizeof(buff),0,(struct sockaddr*)&udpClient,&servlen);
        printf("Time is %s\n",buff);
    }

}

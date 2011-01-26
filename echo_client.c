/* -*- mode: C; c-basic-offset: 2; indent-tabs-mode: nil -*- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "readwritehelper.h"
#include "portNUMS_defined.h"
#include <netinet/in.h>
#include <netdb.h>



int main(int argc, char *argv[])
{
  int port;
  struct hostent * host;
  if ( argc==1 || argc==2 ) {
    printf("put a host name and port number!!\n");
    exit(1);
  }
  else if (argc==3){
      host=gethostbyname(argv[1]);
      port=atoi(argv[2]);
  }
  else{
    printf("too many arguements\n");
    exit(1);
  }
  
  int SDtoServer;
  //int SDfromSubServer;
  //  int connectnum;
  char message[255];
  char clientname[255];//aka pid #
  struct sockaddr_in destination;

  umask(0000);
  memset(&destination, 0, sizeof(destination));
  destination.sin_family=AF_INET;

  memcpy((char*)&destination.sin_addr.s_addr, (char *)host->h_addr, host->h_length);
  destination.sin_port=htons(port);

  

  umask(0000);
 
  while(1){
    SDtoServer=socket(AF_INET,SOCK_STREAM,0);
    if (SDtoServer <0)
      printf("socket failed from client\n");
    else
      printf("socket worked from client\n");
    
    
    if(connect(SDtoServer,(struct sockaddr *) &destination, sizeof(destination)) < 0)
      printf("connection failed\n");
    else
      printf("connection worked \n");
    
    
    char sending[255];
    fgets(sending, 255, stdin);
    sending[strlen(sending)-1]='\0';
    // printf("what i inputted: %s \n", sending);
    
    
    writehelp(SDtoServer, sending,strlen(sending)+1);
    readhelp(SDtoServer, message, 255); 
    
    printf("message: %s ", message);
    if (strcmp("enter new number:",message)==0)
      {
        char newtemp[255];
        fgets(newtemp, 255, stdin);
        newtemp[strlen(newtemp)-1]='\0';
        writehelp(SDtoServer,newtemp,strlen(newtemp)+1);
      }
  
    shutdown(SDtoServer, SHUT_RDWR);
  }

  return 1;
}

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

int main() {

  int SDfromClient;
  int newSD;
  int checknum=0;
  char messageFromClient[255];
  char messageToClient[255];//aka pid #
  int DefaultPort=8080;
  struct sockaddr_in destination;

  memset(&destination, 0, sizeof(destination));
  destination.sin_family=AF_INET;
  destination.sin_port=htons(DefaultPort);
  destination.sin_addr.s_addr=htonl(INADDR_ANY);

  struct sockaddr clientinfo;
  memset(&clientinfo, 0, sizeof(clientinfo));//sets the whole struct to be filled with zeros...?

  umask(0000);

  printf("before anything\n");
  SDfromClient=socket(AF_INET,SOCK_STREAM,0);

  if (SDfromClient<0)
    printf("socket failed\n");
  else
    printf("socket worked socketnum:%d \n", SDfromClient);

  if ( (checknum = bind(SDfromClient, (struct sockaddr *) &destination, sizeof(destination))) < 0) {
    printf("bind failed\n");
    return 0;
  } else {
    printf("Successful bind\n");
  }

  if ( (checknum=listen(SDfromClient, 2)) < 0 ) {
    printf("listen failed\n");
    return 0;
  } else {
    printf("Listening on INADDR_ANY\n");
  }

  if ( (newSD=accept(SDfromClient, NULL, NULL)) < 0  )
    {
      printf ("accept failed\n");
      return 0;
    } 
  else {
    printf("Accepting connections...\n");  
  }
  strcpy(&messageFromClient,(char *)readhelp(newSD,&messageFromClient,255));
  // &messageFromClient=readhelp(newSD,&messageFromClient,255);
  printf("Message from client: %s\n", messageFromClient);
  //  strcpy(&messageToClient,messageFromClient);
  // strcat(&messageToClient, " back \n");
  checknum=write(newSD, messageToClient, strlen(messageToClient)+1);
  
  shutdown(SDfromClient, SHUT_RDWR);
  
  
  return 1;
}

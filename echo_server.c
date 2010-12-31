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
#include <string.h>

int main() {

  int SDfromClient;
  int newSD;
  int checknum=0;
  char messageFromClient[255];
  char messageToClient[255];//aka pid #
  int DefaultPort=8080;
  struct sockaddr{
    sa_family_t sinfamily; //AF_INET
    in_port_t sin_port; //is a port number
    struct in_addr sin_addr; //an IP address
  };

  struct in_addr {
    uint32_t s_addr;     /* address in network byte order */
  };
  struct sockaddr *destination;
  destination=(struct sockaddr *)malloc(sizeof(struct sockaddr));
  destination->sinfamily=AF_INET;
  destination->sin_port=htons(DefaultPort);
  destination->sin_addr.s_addr=INADDR_ANY;

  struct sockaddr clientinfo;
  memset(&clientinfo, 0, sizeof(clientinfo));//sets the whole struct to be filled with zeros...?
  umask(0000);
  printf("before anything\n");
  SDfromClient=socket(AF_INET,SOCK_STREAM,0);
  if (SDfromClient<0)
    printf("socket failed\n");
  else
    printf("socket worked socketnum:%d \n", SDfromClient);
  checknum=bind(SDfromClient,destination, sizeof(struct in_addr));
  if (checknum<0)
    printf("bind failed\n");
  else
    printf("bind worked \n");
  checknum=listen(SDfromClient, 2);
  if (checknum<0)
    printf("listen failed\n");
  else
    printf("listen worked\n");

  newSD=accept(SDfromClient,&clientinfo, sizeof(struct in_addr));
  if (newSD<0)
    printf ("accept failed\n");
  else
    printf("accept worked\n");  
  read(newSD,messageFromClient,255);
   printf("Message from client: %s\n", messageFromClient);
  checknum=write(newSD, messageToClient, strlen(messageToClient)+1);
  
  shutdown(newSD, SHUT_RDWR);
 
  
  return 1;
}

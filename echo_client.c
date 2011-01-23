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


int main() {

  int SDtoServer;
  //int SDfromSubServer;
  //  int connectnum;
  char message[255];
  char clientname[255];//aka pid #
  struct sockaddr_in destination;

  umask(0000);
  memset(&destination, 0, sizeof(destination));
  destination.sin_family=AF_INET;
  destination.sin_port=htons(8004);
  destination.sin_addr=htonl(127.0.0.1);

  

  umask(0000);
  sprintf(clientname, "%d", getpid()); // sets the name to be the pid
  
  SDtoServer=socket(AF_INET,SOCK_STREAM,0);
  if (SDtoServer <0)
    printf("socket failed from client\n");
  else
    printf("socket worked from client\n");
  if(connect(SDtoServer,(struct sockaddr *) &destination, sizeof(destination)) < 0)
    printf("connection failed\n");
  else
    printf("connection worked \n");
  

  writehelp(SDtoServer, clientname,strlen(clientname)+1);
  readhelp(SDtoServer, message, 255); 
 
  printf("message: %s ", message);
  
  shutdown(SDtoServer, SHUT_RDWR);


  return 1;
}

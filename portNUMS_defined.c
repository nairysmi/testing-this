/* -*- mode: C; c-basic-offset: 2; indent-tabs-mode: nil -*- */

#include "portNUMS_defined.h"
#include <stdio.h>
#include <string.h>

int portnumhelper(char * name, int id)
{
  int port;
  
  
  if(strcmp(name,"light")==0)
    {
      port=light; port=port+id;
      // printf(" porttttt: %d ", port);
      return port;
    }
  if(strcmp(name,"oven")==0)
    {
      port=oven; port=port+id;
      // printf(" porttttt: %d ", port);
      return port;
    }
  if(strcmp(name,"refrigerator")==0)
    {
      port=refrigerator; port=port+id;
      // printf(" porttttt: %d ", port);
      return port;
    }
  if(strcmp(name,"tv")==0)
    {
      port=tv; port=port+id;
      // printf(" porttttt: %d ", port);
      return port;
    }
  printf("NONE OF THE APPLIANCES MATCH\n");
  return -1;  
}

/* -*- mode: C; c-basic-offset: 2; indent-tabs-mode: nil -*- */

#include "portNUMS_defined.h"
#include <stdio.h>
#include <string.h>


//TAKES A NAME AND ID AND MAKES A PORT NUMBER FROM THEM
//RETURNS THE PORT NUMBER
int portnumhelper(char * name, int id)
{
  int port;
  if(strcmp(name,"light")==0)
    {
      port=light; port=port+id;
      return port;
    }
  if(strcmp(name,"oven")==0)
    {
      port=oven; port=port+id;
      return port;
    }
  if(strcmp(name,"refrigerator")==0)
    {
      port=refrigerator; port=port+id;
      return port;
    }
  if(strcmp(name,"tv")==0)
    {
      port=tv; port=port+id;
      return port;
    }
  printf("NONE OF THE APPLIANCES MATCH\n");
  return -1;  
}

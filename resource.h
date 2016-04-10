/*

  RESOURCE.H
  ==========
  (c) Copyright Paul Griffiths 1999
  Email: mail@paulgriffiths.net

  Interface to functions for returning a resource.

*/


#ifndef PG_RESOURCE_H
#define PG_RESOURCE_H
#define WINDOW_X    50
#define WINDOW_Y    10
#define STRING_SIZE     18


#include "reqhead.h"         /*  for struct ReqInfo  */


/*  Function prototypes  */

int Return_Resource (int conn, int resource, struct ReqInfo * reqinfo);
int Check_Resource  (struct ReqInfo * reqinfo);
int Return_Error_Msg(int conn, struct ReqInfo * reqinfo);
void welcome_window ();

void set_root_dir(char *parameter);


#endif  /*  PG_RESOURCE_H  */

#include <unistd.h>
#include <fcntl.h>

#include <string.h>
#include <stdio.h>

#include "resource.h"
#include "reqhead.h"
#include "helper.h"


/*  Change this string to change the root directory that
    the server will use, i.e. /index.html will translate
    here to /home/httpd/html/index.html                   */

static char server_root[1000] = ".";


/*  Returns a resource  */

int Return_Resource(int conn, int resource, struct ReqInfo * reqinfo) {

    char c;
    int  i;

    while ( (i = read(resource, &c, 1)) ) {
	if ( i < 0 )
	    Error_Quit("Error reading from file.");
	if ( write(conn, &c, 1) < 1 )
	    Error_Quit("Error sending file.");
    }

    return 0;
}


/*  Tries to open a resource. The calling function can use
    the return value to check for success, and then examine
    errno to determine the cause of failure if neceesary.    */

int Check_Resource(struct ReqInfo * reqinfo) {

    /*  Resource name can contain urlencoded
	data, so clean it up just in case.    */

    CleanURL(reqinfo->resource);

    
    /*  Concatenate resource name to server root, and try to open  */

    strcat(server_root, reqinfo->resource);
    return open(server_root, O_RDONLY);
}


/*  Returns an error message  */

int Return_Error_Msg(int conn, struct ReqInfo * reqinfo) {
    
    char buffer[100];

    sprintf(buffer, "<HTML>\n<HEAD>\n<TITLE>Server Error %d</TITLE>\n"
	            "</HEAD>\n\n", reqinfo->status);
    Writeline(conn, buffer, strlen(buffer));

    sprintf(buffer, "<BODY>\n<H1>Server Error %d</H1>\n", reqinfo->status);
    Writeline(conn, buffer, strlen(buffer));

    sprintf(buffer, "<P>The request could not be completed.</P>\n"
	            "</BODY>\n</HTML>\n");
    Writeline(conn, buffer, strlen(buffer));

    return 0;

}

int get_parameter(char *conf_str, char *result) {

	char *temp_array = NULL; 
	int file_size = 0;
	int str_size = 0;

	FILE * fdConfig; 
	fdConfig = fopen ("config.txt", "r");  


	if (fdConfig == NULL) {
		printf ("[Error]: File not found! \n");
		return 1;
	}

	fseek(fdConfig, 0, SEEK_END);
	file_size = ftell(fdConfig);
	fseek(fdConfig, 0, SEEK_SET);
	printf("val = %d\n", file_size);
	temp_array = (char*) malloc(file_size);

	if (temp_array == NULL)
		return 1;

        while (! feof(fdConfig)) {
            fgets (temp_array, 100, fdConfig);
            str_size = strlen (conf_str) + 3;
            char *res = strstr(temp_array, conf_str);
            if (res != NULL) 
                strcpy(result, res + str_size);
        }
        
    

	printf("YO KNIGGA!\n");
	printf ("Returned String 1: %s\n", result);

	free(temp_array);
	fclose (fdConfig); 
}

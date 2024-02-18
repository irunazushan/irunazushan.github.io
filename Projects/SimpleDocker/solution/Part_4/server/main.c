#include <stdio.h> 
#include <fcgiapp.h>

int main(void) { 
    FCGX_Init(); 

    FCGX_Request request; 
    if(FCGX_InitRequest(&request, 0, 0) != 0) 
    { 
        printf("Can not init request\n"); 
	    return 1; 
    }

    while (FCGX_Accept_r(&request) >= 0) {
        printf("request is accepted\n"); 
        FCGX_PutS("Content-type: text/html\r\n", request.out); 
        FCGX_PutS("\r\n", request.out);
        FCGX_PutS("<h1>Hello, World!<h1>\r\n", request.out); 
        FCGX_Finish_r(&request); 
    }
    return 0; 
}
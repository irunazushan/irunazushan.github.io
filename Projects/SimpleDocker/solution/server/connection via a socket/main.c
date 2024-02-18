#include <stdio.h> 
#include <fcgiapp.h>

#define SOCKET_PATH "127.0.0.1:9000" 
static int socketId; 

int main(void) { 
    FCGX_Init(); 
    socketId = FCGX_OpenSocket(SOCKET_PATH, 0); 
    if(socketId < 0) {
        printf("Can not open socket\n");  
	    return 1; 
    } 
    FCGX_Request request; 
    if(FCGX_InitRequest(&request, socketId, 0) != 0) 
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

#include <stdio.h>
#include <string.h>
#include "civetweb.h"
#include "functionslist.h" 
#include<stdlib.h>

// This function will be called by civetweb on every new request.
static int begin_request_handler(struct mg_connection *conn)
{   
    const struct mg_request_info *request_info = mg_get_request_info(conn);  
    char content[100];  
    int content_length;    
    
    int index = search(root, request_info->uri);  
    if(index >= 0){
        const char *num = request_info->query_string;                   
        char *temp = (char *)functions[index]((void *)num);         
        content_length = snprintf(content, sizeof(content),
                                      "%s",
                                      temp);  
        free(temp);      
    }
    
    mg_printf(conn,
              "HTTP/1.1 200 OK\r\n" 
              "Content-Type: text/plain\r\n"
              "Content-Length: %d\r\n"        
              "\r\n"
              "%s",
              content_length, content);   
    
    return 1;
}

int main(int argc, char *argv[]) 
{   
    if(argc != 3){
        printf("usage: ./flask <PORT_NUM> <NUM_THREADS> \n");
        exit(1);
    }
    struct mg_context *ctx;
    struct mg_callbacks callbacks; 

    root = insert(root, urls[0], 0);

    for(int i=1; i<7; i++){
        insert(root, urls[i], i); 
    }
    
    // preorder(root);
    // printf("-------- INORDER -----\n");
    // inorder(root);

    char *PORT_NUM = argv[1];
    char *THREAD_NUM = argv[2]; 
    
    const char *options[] = {"listening_ports", PORT_NUM, "num_threads", THREAD_NUM,  NULL};

    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.begin_request = begin_request_handler;

    ctx = mg_start(&callbacks, NULL, options);

    getchar();

    mg_stop(ctx);

    return 0;
}

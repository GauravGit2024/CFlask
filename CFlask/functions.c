#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functionslist.h"

bst* create(const char *url, int function_index){
    
    bst* node = (bst*)(malloc(sizeof(bst)));   
    node->left = NULL;
    node->right = NULL;
    node->url = url;
    node->function_index = function_index;

    return node;
}

bst* insert(bst *root, const char *url, int function_index){
    if(root == NULL){
        return create(url, function_index);
    } 

    if(strcmp(url, root->url) > 0){
        root->right =  insert(root->right, url, function_index);
    } else {
        root->left = insert(root->left, url, function_index);
    }
    return root;
}

int search(bst* root, const char *url){
    if(root == NULL){
        return -1;
    }
    if(strcmp(root->url, url) == 0)
        return root->function_index;

    // printf("searching %s\n", root->url);

    if(strcmp(root->url, url) < 0)
        return search(root->right, url);
    else 
        return search(root->left, url);
}

// void preorder(bst *root){
//     if(root == NULL){
//         return;
//     }  
//     printf("%s : %d\n", root->url, root->function_index);
//     preorder(root->left);
//     preorder(root->right);
// }

// void inorder(bst *root){
//     if(root == NULL){
//         return;
//     }  
//     inorder(root->left);
//     printf("%s : %d\n", root->url, root->function_index);
//     inorder(root->right);
// }

struct bst* root = NULL;

void* square(void *arg){

    char *temp = (char *)(malloc(sizeof(char)*100));
    strcpy(temp,"1");
    
    if(!arg){
        return (void *) temp;
    }

    char *buffer = (char *)arg;
   
    if(buffer[3] != '=' || buffer[4] > 57 || buffer[4] < 48){
        return (void *) temp;
    }
    strcpy(temp,"");   
    strcat(temp, buffer+4);
    
    int content;
    content = (atoi)(temp);
    content = (content)*(content);
    
    sprintf(temp, "%d", content);
    
    return (void*) temp;

}

void* cube(void *arg){

    char *temp = (char *)(malloc(sizeof(char)*100));
    strcpy(temp,"1");
    
    if(!arg){
        return (void *) temp;
    }

    char *buffer = (char *)arg;   
   
    if(buffer[3] != '=' || buffer[4] > 57 || buffer[4] < 48){
        return (void *) temp;
    }   
    
    strcpy(temp,"");
    strcat(temp, buffer+4);
    
    int content;
    content = (atoi)(temp);
    content = (content)*(content)*(content);
    
    sprintf(temp, "%d", content);

    return (void*) temp;

}

void* prime(void *arg){

    char *temp = (char *)(malloc(sizeof(char)*100));
    strcpy(temp,"False");
    
    if(!arg){
        return (void *) temp;
    }

    char *buffer = (char *)arg;    
   
    if(buffer[3] != '=' || buffer[4] > 57 || buffer[4] < 48){
        return (void *) temp;
    }

    strcpy(temp,"");   
    strcat(temp, buffer+4);

    int content ;
    content = (atoi)(temp);
    
    strcpy(temp,"False");
    for(int i=2; i<content; i++){
        if(content%i == 0)
            return (void *) temp;
    }
    strcpy(temp,"True");
    return (void *) temp;

}

void* pingpong(void *arg){

    char *temp = (char *)(malloc(sizeof(char)*100));
    strcpy(temp,"PingPong");
    
    if(!arg){
        return (void *) temp;
    }
    char *buffer = (char *)(malloc(sizeof(char)*100));
    strcpy(buffer, (char *)arg);
   
    if(buffer[0] != 's' || buffer[1] != 't' || buffer[2] != 'r' || buffer[3] != '=' || buffer[4] == '\0'){
        strcpy(buffer, temp);
        free(temp);
        return (void *) buffer;
    }
    strcpy(buffer, buffer+4);   
    free(temp);
    return (void *) (buffer);
}

void* hello(void *arg){
    
    char *temp = (char *)(malloc(sizeof(char)*100));
    strcpy(temp,"Hello");
    
    if(!arg){
        return (void *) temp;
    }
    
    char *buffer = (char *)arg;
   
    if(buffer[0] != 's' || buffer[1] != 't' || buffer[2] != 'r' || buffer[3] != '=' || buffer[4] == '\0'){
        return (void *) temp;
    }   

    strcpy(temp,"Hello, ");
    strcat(temp, buffer+4);

    return (void *) temp;

}

void* home(void *arg){

    char *content = (char *)(malloc(sizeof(char)*100));
    strcpy(content, "Hello World");
    return (void*) content;

}

void* fibonacci(void *arg){
    char *temp = (char *)(malloc(sizeof(char)*100));
    strcpy(temp,"1");
    
    if(!arg){
        return (void *) temp;
    }
    
    char *buffer = (char *)arg;    
    
    if(buffer[3] != '=' || buffer[4] > 57 || buffer[4] < 48){
        return (void *) temp;
    }

    strcpy(temp,"");   
    strcat(temp, buffer+4);

    int content;
    content = (atoi)(temp);
    
    // printf("content %d\n", content);

    long long int a = 0;
    long long int b = 1;
    long long int c=1;
    for(int i=2; i<=content; i++){
        c = a + b;
        b = c;
        a = b;
    }

    sprintf(temp, "%lld", c);

    return (void *) temp;
}
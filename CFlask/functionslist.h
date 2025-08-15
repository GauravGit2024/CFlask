#ifndef FUNCLIST
#define FUNCLIST
#include<stdio.h>
#include "functions.h"

typedef struct bst{
    const char *url;
    struct bst *left;
    struct bst *right;
    int function_index;
} bst;

extern void* home(void*);
extern void* square(void*);
extern void* cube(void*);
extern void* hello(void*);
extern void* pingpong(void*);
extern void* prime(void*);
extern void* fibonacci(void*);

extern bst* create(const char *url, int function_index);
extern bst* insert(bst *root, const char *url, int function_index);
extern int search(bst* root, const char *url);
// extern void preorder(bst *root);
// extern void inorder(bst *root);

extern struct bst* root;

static void* (*functions[])(void*) = {
[home_route]    home,
[square_route] square,
[cube_route] cube,
[hello_route] hello,
[pingpong_route] pingpong,
[prime_route] prime,
[fibonacci_route] fibonacci
};

static char *urls[] = {"/", "/square", "/cube", "/helloworld", "/pingpong", "/arithematic/prime",  "/arithematic/fibonacci"};

// void* (*p[7]) (void *) = {home, square, cube, hello,  pingpong, prime, fibonacci};
#endif

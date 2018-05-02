/*
This is a demo c programm to Solve Infix to Post fix conversion.

The tsack is based on the work from lab2.

Platform: 
- GCC Version: (Apple LLVM version 9.0.0 (clang-900.0.39.2) Target: x86_64-apple-darwin16.7.0) 
- Online Complier (https://www.onlinegdb.com/online_c_compiler)
Author: Tim
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char     data;
    struct node    *link;
}Node;

typedef struct{
    unsigned int     count;
    Node    *top;
}StackHead;

StackHead *CreateStack(){
    StackHead *myStack = (StackHead *) malloc (sizeof(StackHead));
    // malloc (sizeof (StackHead))
    myStack->count = 0;
    myStack->top = NULL;
    return myStack;
}
void printNodesCount(StackHead *myStack){
    
    if (myStack->count==0) {
        printf("Stack is Empty\n");
        
    }
    // else if (myStack ==NULL) {
    //     printf("Stack is deleted");
    // }
    else {
        printf ("%d elements in stak\n", myStack->count);   
        
    }
}

void printStack(StackHead *myStack){
    if (myStack->count==0) {
        printf("Stack is Empty\n");
        
    }
    else {
        printf("\n######## %u elements in this stack:########\n", myStack->count);
        Node *top = myStack->top;
        while (top != NULL){
            printf("%c ,", top->data);
            top = top-> link;
        }
        printf("\n########Stack printing end########\n");
    }

}

void Push(StackHead *myStack, char data){
    Node *pNew = (Node *) malloc (sizeof(Node));
    pNew -> data = data;
    pNew -> link = myStack -> top;
    myStack->top = pNew;
    myStack -> count ++;
    
}

char Pop(StackHead *myStack) {
  char rv =0;
  if (myStack -> count !=0) {

    Node *pTop = myStack->top;
    myStack->top = pTop->link;
    myStack -> count --;
    rv = pTop -> data;
    free (pTop);
    pTop = NULL;
  }
  else {
    printf("Stack is empty.\n");
  }
  return rv;
}

void CleanStack(StackHead *myStack){
    printf("Cleaning the stack");
    while (myStack->top != NULL){
        Pop(myStack);
    }
}

void DeleteStack(StackHead *myStack){
    printf("Deleting the stack");
    free(myStack);
    myStack = NULL;
}

void Populate(StackHead *myStack, int n) {
    int seed =1;
    printf("Populating the stack with seed %d \n", seed);
    // set the seed
    srand(seed);
    // populate the stack with random number
    for (int i = 0; i<n; i++){
        char data = (char)(rand()%(100+1-1)) +1;
        Push(myStack, data);
    }
}


char *infix2postfix(char *infixstr){

}

char *infix2prefix(char *infixstr){

}



int main()
{
    StackHead *myStack;

    // create
    myStack = CreateStack();
    printNodesCount(myStack);
    // populate
    int n = 7;
    Populate (myStack, n);
    // printNodesCount(myStack);
    printStack(myStack);
    
    // testt drop one
    char l = Pop(myStack);
    printf ("Data Poped %c \n and now there are ", l);
    // printNodesCount(myStack);
    printStack(myStack);



    // test to empty stack
    // CleanStack(myStack);
    // printNodesCount(myStack);
    
    // test to delete the stack
    // DeleteStack(myStack);
}
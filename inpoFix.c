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
#include <string.h>

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
        printf ("%d elements in stack\n", myStack->count);   
        
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
    printf("Stack is empty When Popping.\n");
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

int isALetter(char ch)
{
    // in this assignment, letter is trated as a numebr between operators
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

int getPriority(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
 
    case '*':
    case '/':
        return 2;
 
    case '^':
        return 3;
    }
    return -1;
}

void strrev(char * str)
{
    /*
    Reversing a string in C. (n.d.). Retrieved from https://stackoverflow.com/questions/784417/reversing-a-string-in-c 
    */

    /* skip null */
    if (str == 0)
    {
        return;
    }

    /* skip empty string */
    if (*str == 0)
    {
        return;
    }

    /* get range */
    char *start = str;
    char *end = start + strlen(str) - 1; /* -1 for \0 */
    char temp;

    /* reverse */
    while (end > start)
    {
        /* swap */
        temp = *start;
        *start = *end;
        *end = temp;

        /* move */
        ++start;
        --end;
    }
}


int *infix2postfix(char *infixstr){
    int length = strlen(infixstr);
    char ch;

    int i;
    int ii;

    StackHead *myStack = CreateStack();

    if (!myStack) {
        return -1;
    }

    for ( i=0, ii=-1; i< length; ++i){
        ch = infixstr[i];

        if ( isALetter(ch)){
            
            infixstr[++ii] = ch;
        }
        else if ( ch == '(' ) {
            // push it to stack
            Push(myStack, ch);

        }else if (ch == ')'){
            // pop and output from stack unti finding ()
            while (myStack->count!=0 && myStack-> top -> data != '('){
                infixstr[++ii] = Pop(myStack);
            }

            if (myStack->count!=0 && myStack-> top -> data != '('){
                printf("Wrong expression\n");
                return -1;
            }else {
                Pop (myStack);
            }
        }else{
            // an operator
            while (myStack->count!=0 && getPriority(ch) <= getPriority(myStack-> top -> data)){
                infixstr[++ii] = Pop(myStack);
            }
            Push(myStack, ch);
        }
    }
    // pop all operators
    while (myStack->count!=0){
        infixstr[++ii] = Pop(myStack);
    }
    infixstr[++ii] ='\0';
    // printf("%s \n", infixstr );
}

int *infix2prefix(char *infixstr){
    int length = strlen(infixstr);
    // rever the char array
    strrev(infixstr);
    char ch;

    // swap ( and )
    for (int i = 0; i < length; i++) {
 
        if (infixstr[i] == '(') {
            infixstr[i] = ')';
            i++;
        }
        else if (infixstr[i] == ')') {
            infixstr[i] = '(';
            i++;
        }
    }

    // transform it to postfix
    infix2postfix(infixstr);
    strrev(infixstr);
}



int main()
{
    // StackHead *myStack;

    // // create
    // myStack = CreateStack();
    // printNodesCount(myStack);
    // // populate
    // int n = 7;
    // Populate (myStack, n);
    // // printNodesCount(myStack);
    // printStack(myStack);
    
    // // testt drop one
    // char l = Pop(myStack);
    // printf ("Data Poped %c \n and now there are ", l);
    // // printNodesCount(myStack);
    // printStack(myStack);

    char expression1[]= "A*(B+C/D)^E-F*(G-H)";

    printf("Enter the expression: \n");
    scanf("%s", expression1);



    // the right output should be ABCD/+E^*FGH-*-
    printf("original infix %s\n", expression1);
    infix2postfix(expression1);
    printf("postfix %s\n", expression1);

    infix2prefix(expression1);
    printf("prefix %s\n", expression1);




}
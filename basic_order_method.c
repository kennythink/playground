#include <stdio.h>  
#include <stdbool.h>  
#include <assert.h>  
#include <stdlib.h>  
#include <string.h> // memset   

//#define TDEBUG
  
#define CHECK_RESULT(b, n) \
{ \
        if (b) \
            printf("%-30s passed.\n", n); \
        else \
        { \
            printf("%-30s failed, exit now.\n", n); \
            exit(-1); \
        } \
} 
  
#ifdef TDEBUG  
    #define tprint(x...) printf(x)  
#else  
    #define tprint(x...)  
#endif  

#define MAXSIZE 40

typedef struct _node {
    int data[MAXSIZE];
    int len;
} t_node;

void dump(t_node node);
bool compare(t_node s, t_node t);
t_node *bubble_sort(t_node *n, bool req_asc);


int main() 
{
    t_node node, refnode;
    node.len = sizeof(node.data)/sizeof(node.data[0]);
    refnode.len = node.len;
    //tprint("node len: %d\n", node.len);
     
    int i;
    for (i=0; i<node.len; i++) 
        refnode.data[i] = node.data[i] = i;
    tprint("Ref node: -> \n");
    dump(refnode);
    tprint("----\n");

    bubble_sort(bubble_sort(&node, false), true);
    CHECK_RESULT(compare(refnode, node), "bubble_sort"); 

    return 0; 
}

/* -------------------------------------------------- below is funcion implementation ------------------------------------------ */

/*
 * ref to: https://en.wikipedia.org/wiki/Bubble_sort
 * req_asc, if true, sort result would from low to high, otherwise high to low.
*/
t_node *bubble_sort(t_node *n, bool req_asc) 
{
    int i, j, flag, tmp;
    for (i=0; i<n->len-1; i++) 
    {
        flag = 0;
        for (j=0; j<n->len-i-1; j++) 
        {
            if ((!req_asc && n->data[j] < n->data[j+1]) ||
                 (req_asc && n->data[j] > n->data[j+1])) {
                flag = 1;
                tmp = n->data[j],  n->data[j] = n->data[j+1], n->data[j+1] = tmp; 
            }
        } 
        if (flag == 0)
            break; 
    }

    dump(*n);    
    return (n);
}


void dump(t_node node)  
{ 
    static int count = 0; 
    int i; 
    tprint("print times: %d  ->", count); 
    for (i=0; i<node.len; i++)  
        tprint("%2d ", node.data[i]);  
    tprint("\n"); 
    count++; 
    return ;  
}


bool compare(t_node s, t_node t) 
{
    if (s.len != t.len)
        return false;
    int i;
    for (i=0; i<s.len; i++) {
        if (s.data[i] != t.data[i])
            return false;
    }    
    return true; 
}
 

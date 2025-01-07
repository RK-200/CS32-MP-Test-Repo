#include "sequence_of_trees.c"
#include <stdio.h>

int main(){
    list* a = malloc(sizeof(list));
    a->size = 0;
    a->left_head = NULL;
    a->right_head = NULL;
    a->nodes = 0;
    a->leftmost = 0;
    a->rightmost = 0;
    push_left(a,1);
    push_left(a,2);
    push_left(a,3);
    push_left(a,4);
    push_left(a,5);
    push_left(a,6);
    int64_t c[6] = {1,2,3,4,5,6};
    list* b = make(6,c);
    list* d = make(6,c);
    printf("%d",get(d,0));
    printf("%d",get(d,1));
    printf("%d",get(d,2));
    printf("%d",get(d,3));
    printf("%d",get(d,4));
    printf("%d",get(d,5));
    printf("\n");
    printf("%d",pop_right(d));
    printf("%d",pop_right(d));
    printf("%d",pop_right(d));
    printf("%d",pop_right(d));
    printf("%d",pop_right(d));
    printf("%d",pop_right(d));
    printf("\n");
    printf("%d",pop_left(b));
    printf("%d",pop_left(b));
    printf("%d",pop_left(b));
    printf("%d",pop_left(b));
    printf("%d",pop_left(b));
    printf("%d",pop_left(b));
    
    return 0;
}
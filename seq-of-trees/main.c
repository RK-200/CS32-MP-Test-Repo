#include "sequence_of_trees.c"
#include <stdio.h>


void print_list(list* l);
void print_list(list* l){
    printf("[");
    for(int i=0;i<l->nodes-1;i++){
        printf("%lld, ",get(l,i));
    }
    printf("%lld]\n",get(l,l->nodes-1));
}

void print_deg(list* l){
    printf("[");
    node* tmp = l->left_head;
    for(int i=0;i<l->size-1;i++){
        
        printf("%lld, ",tmp->degree);
        tmp = tmp->right;
    }
    printf("%lld]\n",l->right_head->degree);
}


int main(){
    char control = 'a';
    int64_t val = 0;
    int idx = 0;
    int64_t arr[1] = {0}; //TODO: make this editable in bash
    list* test = make(0,arr);

    while (control != 'n'){
    scanf("%c",&control);
    switch (control){
        case 'a':
        scanf("%lld",&val);
        push_left(test,val);
        break;
        
        case 'b':
        scanf("%lld",&val);
        push_right(test,val);
        break;

        case 'c':
        printf("%s\n",pop_left(test) ? "true" : "false");
        break;

        case 'd':
        printf("%s\n",pop_right(test) ? "true" : "false");
        break;

        case 'e':
        printf("%lld\n",peek_left(test));
        break;

        case 'f':
        printf("%lld\n",peek_right(test));
        break;

        case 'g':
        printf("%d\n",size(test));
        break;

        case 'h':
        printf("%s\n",empty(test) ? "true" : "false");
        break;

        case 'i':
        scanf("%d",&idx);
        printf("%lld\n",get(test,idx));
        break;

        case 'j':
        scanf("%d",&idx);
        scanf("%lld",&val);
        set(test,idx,val);
        break;

        case 'k':
        reverse(test);
        break;

        case 'l':
        print_list(test);
        break;

        case 'm':
        printf("%d\n",test->nodes);
        break;

        case 'o':
        print_deg(test);
        break;
    }
}

    int64_t t[3] = {1,2,3};
    list* b = make(3,t);
    reverse(b);
    print_list(b);

    return 0;
}

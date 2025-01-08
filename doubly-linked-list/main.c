#include "doubly_linked_list.c"
#include <stdio.h>


void print_list(list* l);
void print_list(list* l){
    printf("[");
    for(int i=0;i<l->size-1;i++){
        printf("%lld, ",get(l,i));
    }
    printf("%lld]\n",get(l,l->size-1));
}

int main(){
    char control = 'a';
    int64_t val = 0;
    int idx = 0;
    int64_t arr[1] = {0};
    list* test = make(1,arr);

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

    }
}

    return 0;
}
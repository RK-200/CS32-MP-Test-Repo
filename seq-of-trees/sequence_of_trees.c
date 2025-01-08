#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "sequence_of_trees.h"

node* new_node(int64_t val){ //function to create a new node
    //initializes default node parameters
    node* ret = malloc(sizeof(node));
    ret->degree = 0;
    ret->val = val;//assigns the passed variable v to val
    ret->left_child = NULL;
    ret->right_child = NULL;
    ret->left = NULL;
    ret->right = NULL;
    return ret; //returns the created node
}

node* n_union(node* a,node* b){ 
    node* ret = malloc(sizeof(node));
    ret->val = 0;
    ret->degree = a->degree+1;
    
    ret->left_child = a;
    ret->right_child = b;

    ret->left = NULL;
    ret->right = NULL;

    a->left = NULL;
    a->right = NULL;
    b->left = NULL;
    b->right = NULL;

    return ret;
    
}

list *make(int n, int64_t *seq){
    list* ret = malloc(sizeof(list));//initializes a list variable and assigns default list parameters
    ret->left_head = NULL;
    ret->right_head = NULL;
    ret->size = 0;
    ret->nodes = 0;
    ret->leftmost = 0;
    ret->rightmost = 0;
    ret->reverse = false;
    for(int i=0;i<n;i++){//iterating through the sequence and using n push_right()s generates the sequence of trees in the proper order in O(l) time 
        push_right(ret,seq[i]);
    }
    return ret;
}

void merge(list* l,char start){
    if(start == 'l'){
        if(l->size > 1){
            while(l->size > 1 && l->left_head->degree == l->left_head->right->degree){
                node* r_temp = NULL;
                if(l->left_head->right->right != NULL){
                    r_temp = l->left_head->right->right;
                }
                l->left_head = n_union(l->left_head,l->left_head->right);
                l->left_head->right = r_temp;
                l->size--;
                if(l->size > 1){
                    l->left_head->right->left = l->left_head; 
                }
            }
        }
        if(l->size == 1){
            l->right_head = l->left_head;
        }
        return;
    }
    else{
        if(l->size > 1){
            while(l->size > 1 && l->right_head->degree == l->right_head->left->degree){
                node* l_temp = NULL;
                if(l->right_head->left->left != NULL){
                    l_temp = l->right_head->left->left;
                }
                l->right_head = n_union(l->right_head->left,l->right_head);
                l->right_head->left = l_temp;
                
                l->size--;
                if(l->size > 1){
                    l->right_head->left->right = l->right_head; 
                }
            }
        }
        if(l->size == 1){
            l->left_head = l->right_head;
        }
        return;
    }
}


void push_left(list *l, int64_t v){
    if(l->reverse){
        l->reverse = false;
        push_right(l,v);
        l->reverse = true;
        return; 
    }
    node* new = new_node(v);
    l->leftmost = v;

    if(l->size == 0){
        l->left_head = new;
        l->right_head = new;
        l->rightmost = v;
    }
    else{
        node* tmp = l->left_head;
        l->left_head = new;
        l->left_head->right = tmp;
        tmp->left = new;
    }
    l->size++;
    l->nodes++;
    merge(l,'l');
}

void split(list *l, char start){
    if(start == 'l'){
        while(l->left_head->degree > 0){
            //split
            if(l->size == 1){
                node* lh= l->left_head;
                l->left_head = lh->left_child;
                l->right_head = lh->right_child;
                l->left_head->right = l->right_head;
                l->right_head->left = l->left_head;
                l->left_head->left = NULL;
                l->right_head->right= NULL;
            }
            else{
                node* lh= l->left_head;
                l->left_head = lh->left_child;
                l->left_head->left = NULL;
                l->left_head->right = lh->right_child;
                l->left_head->right->left = l->left_head;
                l->left_head->right->right = lh->right;
                lh->right->left = l->left_head->right;
    
            }
            l->size++;
        }
    }else{
        while(l->right_head->degree != 0){
            //split
            if(l->size == 1){
                node* lh= l->right_head;
                l->right_head = lh->right_child;
                l->left_head = lh->left_child;
                l->right_head->left = l->left_head;
                l->left_head->right = l->right_head;
                l->left_head->left = NULL;
                l->right_head->right= NULL;
            }
            else{
                node* lh= l->right_head;
                l->right_head = lh->right_child;
                l->right_head->right = NULL;
                l->right_head->left = lh->left_child;
                l->right_head->left->right = l->right_head;
                l->right_head->left->left = lh->left;
                lh->left->right = l->right_head->left;
    
            }
            l->size++;
        }
    }
}

void push_right(list *l, int64_t v){
    if(l->reverse){
        l->reverse = false;
        push_left(l,v);
        l->reverse = true;
        return; 
    }
    node* new = new_node(v);
    l->rightmost = v;

    if(l->size == 0){
        l->left_head = new;
        l->right_head = new;
        l->leftmost = v;
    }
    else{
        node* tmp = l->right_head;
        l->right_head = new;
        l->right_head->left = tmp;
        tmp->right = new;
    }
    l->size++;
    l->nodes++;
    merge(l,'r');
}
bool pop_left(list *l){
    int64_t ret =0;
    if (l->size == 0){
        return false;
    }
    if(l->reverse){
        l->reverse = false;
        ret = pop_right(l);
        l->reverse = true;
        return ret; 
    }
    l->nodes--;
    
    split(l,'l');

    l->size--;
    
    node* tmp = l->left_head;
    ret = tmp->val;
    free(tmp);
    if(l->size == 0){
        l->left_head = NULL;
        l->right_head = NULL;
        l->leftmost = 0;
        l->rightmost = 0;
        return true;
    }
    if(l->size >1){
        l->left_head = l->left_head->right;
        merge(l,'l');
        merge(l,'r');    
    }
    else{l->left_head=l->right_head;l->right_head = l->left_head;}
    
    l->leftmost = get(l,0);
    return true;
}
bool pop_right(list *l){ 
    int64_t ret =0;
    if (l->size == 0){
        return false;
    }
    if(l->reverse){
        l->reverse = false;
        ret = pop_left(l);
        l->reverse = true;
        return ret; 
    }
    l->nodes--;
    
    split(l,'r');
    
    l->size--;
    
    node* tmp = l->right_head;
    ret = tmp->val;
    free(tmp);
    if(l->size == 0){
        l->left_head = NULL;
        l->right_head = NULL;
        l->leftmost = 0;
        l->rightmost = 0;
        return true;
    }
    if(l->size >1){
        l->right_head = l->right_head->left;
        merge(l,'l');
        merge(l,'r');
    }
    else{l->right_head=l->left_head;l->left_head = l->right_head;}
    
    l->rightmost = get(l,l->nodes-1);
    return true;
}
int64_t peek_left(list *l){
    if(l->size == 0 ){
        printf("empty");
        assert(0!=0);
    }
    if(l->reverse){
        return l->rightmost;
    }
    return l->leftmost;
}
int64_t peek_right(list *l){
    if(l->reverse){
        l->leftmost;
    }
    return l->rightmost;
}
int size(list *l){
    return l->nodes;
}
bool empty(list *l){
    return (l->size == 0) ? true : false;
}
void reverse(list *l){
    l->reverse ^= true;
}
node* traverse(list *l,int i){
    int64_t s = -1,res;
    node* n = l->left_head;
    while(s<i){
        if(s!=-1){n=n->right;}
        res = (1 << n->degree);
        s += res;
        
    }
    int64_t i2 = i - (s - (1 << n->degree));
    int64_t k = 1 << n->degree;
    while (n->degree!= 0){
        if (k/2 >= i2){
            n = n->left_child;
            k = k/2;
        }else{
            n = n->right_child;
            k = k/2;
            i2 -= k;
        }
    }
    return n;
}

int64_t get(list *l, int i){ 
    if(l->size == 0 || i >= l->nodes || i < 0){
        printf("index error");
        assert(0!=0);
    }

    if(l->reverse){
        i = l->nodes-i-1;
    }

    node* ret = traverse(l,i);
    
    return ret->val;

}
void set(list *l, int i, int64_t v){
    if(l->size == 0 || i >= l->nodes || i < 0){
        printf("index error");
        assert(0!=0);
    }

    if(l->reverse){
        i = l->nodes-i-1;
    }

    node* ret = traverse(l,i);
    ret->val = v;
}




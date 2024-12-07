#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

struct node{
    int modelno;
    char modelname[30];
    int price;
    struct node *parent;
    struct node *left;
    struct node *right;
};

struct node *createnode(int modelno,char modelname[],int price){
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->modelno=modelno;
    strcpy(temp->modelname,modelname);
    temp->price=price;
    temp->parent=temp->left=temp->right=NULL;
}


void inorder(struct node *root){
    if(root==NULL){
        return ;
    }
    inorder(root->left);
    printf("%d %s %d\n",root->modelno,root->modelname,root->price);
    inorder(root->right);
}

void preorder(struct node *root){
    if(root==NULL){
        return ;
    }
    printf("%d %s %d\n",root->modelno,root->modelname,root->price);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct node *root){
    if(root==NULL){
        return ;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d %s %d\n",root->modelno,root->modelname,root->price);
}

struct node *add(struct node*temp,struct node*x){
    if(temp==NULL){
        return x;
    }
    
    if(temp->modelno < x->modelno){
        temp->right = add(temp->right,x);
        temp->right->parent=temp;
    }
    else{
        temp->left = add(temp->left,x);
        temp->left->parent=temp;
    }
    return temp;
}

struct node *search(struct node *root,int x){
    if(root==NULL){
        return NULL;
    }
    struct node *temp=root;
    while(temp!=NULL){
        if(temp->modelno == x){
            return temp;
        }
        else if(temp->modelno > x){
            temp=temp->left;
        }
        else{
            temp=temp->right;
        }
    }
    return temp;
}


void modify(struct node*root,int modelnu,int newpri){
    struct node*req=search(root,modelnu);
    if(req==NULL){
                printf("-1\n");
                return; 
    }
    req->price = newpri;
}

struct node* getSuccessor(struct node* curr) {
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

struct node * delete(struct node*root,struct node *x){


    if(root==NULL){
        return NULL;
    }
    if(root->modelno > x->modelno){
        root->left = delete(root->left,x);
    }
    else if(root->modelno < x->modelno){
        root->right = delete(root->right,x);
    }
    else{
        if(root->left == NULL){
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        if(root->right == NULL){
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        struct node*succ=getSuccessor(root);
        root->modelno=succ->modelno;
        strcpy(root->modelname,succ->modelname);
        root->price=succ->price;
        root->right=delete(root->right,succ);
    }
    return root;
}


int main(){


    

    char c;
    struct node*root=NULL;
    do{
        scanf("%c",&c);
        if(c=='a'){
            int modelno;
            char modelname[30];
            int price;
            scanf("%d%s%d",&modelno,modelname,&price);
            struct node *x=createnode(modelno,modelname,price);
            root=add(root,x);
        }
        if(c=='s'){
            int modelnu;
            scanf("%d",&modelnu);
            struct node*req=search(root,modelnu);
            if(req==NULL){
                printf("-1\n");
                continue;
            }
            printf("%d %s %d\n",req->modelno,req->modelname,req->price);
        }
        if(c=='d'){
            int modelnu;
            scanf("%d",&modelnu);
            struct node *req=search(root,modelnu);
            if(req==NULL){
                printf("-1\n");
                continue;
            }
            root=delete(root,req);
        }
        if(c=='i'){
            inorder(root);
            printf("\n");
        }
        if(c=='p'){
            preorder(root);
            printf("\n");
        }
        if(c=='t'){
            postorder(root);
            printf("\n");
        }
        if(c=='m'){
            int modelnu,newpri;
            scanf("%d",&modelnu);
            scanf("%d",&newpri);
            modify(root,modelnu,newpri);
        }


    }while(c!='e');

}
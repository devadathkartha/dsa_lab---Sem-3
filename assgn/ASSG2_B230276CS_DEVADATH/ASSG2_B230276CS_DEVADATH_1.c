#include<stdio.h>
#include<stdlib.h>

struct node{
    struct node*left;
    struct node*right;
    int val;
    int height;
};


struct node* createnode(int x){
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->left=NULL;
    temp->right=NULL;
    temp->val=x;
    temp->height=0;
    return temp;
}

int max(int a,int b){
    return (a>b)?a:b;
}

int gethigh(struct node *root){
    if(root==NULL){
        return -1;
    }
    return root->height;
}

struct node* find(struct node*root,int n){
    if(root==NULL){
        return NULL;
    }
    if(root->val==n){
        return root;
    }
    else if(root->val < n){
        return find(root->right,n);
    }
    else{
        return find(root->left,n);
    }
    return NULL;
}

int avlbalancefactor(struct node*root,int n){
    if(root==NULL){
        return 0;
    }
    if(root->val == n){
        return gethigh(root->left)-gethigh(root->right);
    }
    else if(root->val < n){
        avlbalancefactor(root->right,n);
    }
    else{
        avlbalancefactor(root->left,n);
    }
}

struct node* srotatewithleft(struct node*root){
    struct node*temp=root->left;
    root->left=temp->right;
    temp->right=root;
    root->height=max(gethigh(root->left),gethigh(root->right))+1;
    temp->height=max(gethigh(temp->left),root->height)+1;
    return temp;
}

struct node* srotatewithright(struct node*root){
    struct node*temp=root->right;
    root->right=temp->left;
    temp->left=root;
    root->height=max(gethigh(root->left),gethigh(root->right))+1;
    temp->height=max(gethigh(temp->right),root->height)+1;
    return temp;
}

struct node* drotatewithleft(struct node* root){
    root->left=srotatewithright(root->left);
    return srotatewithleft(root);
}

struct node* drotatewithright(struct node* root){
    root->right=srotatewithleft(root->right);
    return srotatewithright(root);
}


struct node* insert(struct node*root,int n,int *l,int *r){
    if(root==NULL){
        root=createnode(n);
        return root;
    }
    else if(n < root->val){
        root->left=insert(root->left,n,l,r);
        if(gethigh(root->left) - gethigh(root->right) > 1){
            if(n < root->left->val){
                root = srotatewithleft(root);
                (*r)++;
            }
            else{
                root = drotatewithleft(root);
                (*l)++;
                (*r)++;
            }
        }
    }
    else if(n > root->val){
        root->right=insert(root->right,n,l,r);
        if((gethigh(root->right)-gethigh(root->left)) > 1){
            if(n > root->right->val){
                root = srotatewithright(root);
                (*l)++;
            }
            else{
                root = drotatewithright(root);
                (*r)++;
                (*l)++;
            }
        }
    }

    root->height = max(gethigh(root->left),gethigh(root->right))+1;
    return root;
}

void postord(struct node*root){
    if(root==NULL){
        return;
    }
    postord(root->left);
    postord(root->right);
    printf("%d ",root->val);
}

void printfind(struct node*root,int n){
    if(root->val==n){
        printf("%d ",root->val);
        return;
    }
    else if(root->val < n){
        printf("%d ",root->val);
        printfind(root->right,n);
        return;
    }
    else{
        printf("%d ",root->val);
        printfind(root->left,n);
        return;
    }
}

struct node *minnode(struct node*root){
    struct node* temp=root;
    while(temp->left!=NULL){
        temp=temp->left;
    }
    return temp;
}

struct node* deletenode(struct node*root,int n,int *l,int*r,int a[],int *idx){
    if(root==NULL){
        return NULL;
    }
    if(n < root->val){
        a[*(idx)]=root->val;
        (*idx)+=1;
        root->left = deletenode(root->left,n,l,r,a,idx);
    }
    else if(n>root->val){
        a[*(idx)]=root->val;
        (*idx)+=1;
        root->right = deletenode(root->right,n,l,r,a,idx);
    }
    else{
        if((root->left==NULL)||(root->right==NULL)){
            struct node* temp= (root->left)?root->left:root->right;
            if(temp==NULL){
                temp=root;
                root=NULL;
            }
            else{
                *root=*temp;
            }
            free(temp);
        }
        else{
            struct node* minte=minnode(root->right);
            root->val=minte->val;
            root->right= deletenode(root->right,minte->val,l,r,a,idx);
        }
    }
    if(root==NULL){
        return NULL;
    }
    root->height= 1 + max(gethigh(root->left),gethigh(root->right));

    int bl=gethigh(root->left)-gethigh(root->right);

    if(bl>1){
        if(gethigh(root->left->left)-gethigh(root->left->right)>=0){
            (*r)++;
            return srotatewithleft(root);
        }
        else{
            (*l)++;
            (*r)++;
            return drotatewithleft(root);
        }
    }
    else if(bl<-1){
        if(gethigh(root->right->left)-gethigh(root->right->right)<0){
            (*l)++;
            return srotatewithright(root);
        }
        else{
            (*l)++;
            (*r)++;
            return drotatewithright(root);
        }
    }
    return root;
}


int main(){

    struct node*root=NULL;
    char c;
    int l=0;
    int r=0;
    int idx=0;
    do{
        scanf("%c",&c);
        int d;
        if(c=='i'){
            scanf("%d",&d);
            root=insert(root,d,&l,&r);
        }
        if(c=='f'){
            scanf("%d",&d);
            if(find(root,d)){
                printfind(root,d);
                printf("\n");
            }
            else{
                printf("-1\n");
            }
        }
        if(c=='p'){
            postord(root);
            printf("\n");
        }
        if(c=='s'){
             printf("%d %d\n",l,r);
        }
        if(c=='d'){
            scanf("%d",&d);
            if(find(root,d)){
                int ar[100000];
                root=deletenode(root,d,&l,&r,ar,&idx);
                printf("%d ",d);
                for(int i=(--idx);i>=0;i--){
                    printf("%d ",ar[i]);
                }
                printf("\n");
            }
            else{
                printf("-1\n");
            }
        }
        if(c=='b'){
            scanf("%d",&d);
            printf("%d\n",avlbalancefactor(root,d));
        }

    }while(c!='e');


}
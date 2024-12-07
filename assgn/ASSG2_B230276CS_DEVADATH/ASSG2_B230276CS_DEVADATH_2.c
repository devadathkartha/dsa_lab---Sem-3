#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct node{
    struct node*left;
    struct node*right;
    int val;
    int ans;
    int height;
};


struct node* createnode(int x,int ans){
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->left=NULL;
    temp->right=NULL;
    temp->val=x;
    temp->ans=ans;
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


struct node* insert(struct node*root,int n,int ans,int *l,int *r){
    if(root==NULL){
        root=createnode(n,ans);
        return root;
    }
    else if(n < root->val){
        root->left=insert(root->left,n,ans,l,r);
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
        root->right=insert(root->right,n,ans,l,r);
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

void inord(struct node*root,int ar[],int *idx){
    if(root==NULL){
        return;
    }
    inord(root->left,ar,idx);
    ar[(*idx)]=root->val;
    (*idx)+=1;
    inord(root->right,ar,idx);
}



int main(){

    struct node*root=NULL;
    char c;
    int l=0;
    int r=0;
    
    do{
        scanf("%c",&c);
        int d;
        int ans;
        if(c=='i'){
            scanf("%d%d",&d,&ans);
            if(find(root,d)){
                struct node *found=find(root,d);
                found->ans=ans;
            }
            else{
                root=insert(root,d,ans,&l,&r);
            }
        }
        if(c=='u'){
            scanf("%d",&d);
            int o=0;
            int min=INT_MAX;
            int ar[100000];
            inord(root,ar,&o);
            for(int i=o-1;i>=0;i--){
                if(ar[i]>=d){
                    if(min>ar[i]){
                        min=ar[i];
                    }
                }
            }
            if(min!=INT_MAX){
                struct node*mini=find(root,min);

                printf("%d %d\n",mini->val,mini->ans);
            }
            else{
                printf("-1\n");
            }
        }
        if(c=='f'){
            scanf("%d",&d);
            if(find(root,d)){
                printf("%d %d\n",find(root,d)->val,find(root,d)->ans);
            }
            else{
                printf("-1\n");
            }
        }
        
        if(c=='e'){
             if(root==NULL){
                printf("1\n");
             }
             else printf("0\n");
        }

        if(c=='d'){
            int idx=0;
            if(root!=NULL){
                int ar[100000];
                inord(root,ar,&idx);
                for(int i=(idx-1);i>=0;i--){
                    printf("%d ",ar[i]);
                }
                printf("\n");
            }
            else{
                printf("-1\n");
            }
        }
        if(c=='s'){
            int k=0;
            int ar[100000];
            if(root==NULL){
                printf("0\n");
            }
            else{
                inord(root,ar,&k);
                printf("%d\n",k); 
            }
        }

    }while(c!='t');


}
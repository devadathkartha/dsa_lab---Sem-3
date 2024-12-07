#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

struct node{
    struct node *left;
    struct node* right;
    int val;
    int height;
};

struct node* createnode(int x){
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->left=NULL;
    temp->right=NULL;
    temp->val=x;
    temp->height=0;
}

int max(int a,int b){
    return (a>b)?a:b;
}

int min(int a,int b){
    return (a<b)?a:b;
}

int mod(int x){
    return (x>=0)?x:(-1*x);
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
}

int getheight(struct node *root){
    if(root==NULL){
        return -1;
    }
    return root->height;
}

int getbalance(struct node*root){
    if(root==NULL){
        return 0;
    }
    return getheight(root->left)-getheight(root->right);
}

int findind(char str[],int s,int e){
    int cnt=0;
    int i=s;
    while(i<=e){
        if(str[i]=='('){
            cnt++;
            
        }
        else if(str[i]==')'){
            cnt--;
            if(cnt==0){
                return i;
            }
        }
        i++;
    }
    return -1;
}

struct node* treefromstring(char str[],int s,int e){
    if(s>e){
        return NULL;
    }

    int num=0;
    while(s<=e && str[s]>='0' && str[s]<='9'){
        num=(num*10)+(str[s]-'0');
        s++;
    }
    struct node*root=createnode(num);


    int idx=-1;
    
    s++;
    if(s<=e && str[s]=='('){
        idx=findind(str,s,e);
    }

    if(idx!=-1){
        root->left=treefromstring(str,s+2,idx-2);
        root->right=treefromstring(str,idx+4,e-2);
    }
    return root;
}

void stringfromtree(struct node*root){
    if(root==NULL){
        return;
    }
    printf("%d ",root->val);
    if(root->left==NULL && root->right==NULL){
        return;
    }
    printf("( ");
    stringfromtree(root->left);
    printf(") ");
    printf("( ");
    stringfromtree(root->right);
    printf(") ");
}

struct node* lrotate(struct node*root){
    struct node *temp=root->right;
    root->right=temp->left;
    temp->left=root;
    root->height=max(getheight(root->left),getheight(root->right))+1;
    temp->height= max(root->height,getheight(temp->right))+1;
    return temp;
}

struct node* rrotate(struct node*root){
    struct node *temp=root->left;
    root->left=temp->right;
    temp->right=root;
    root->height=max(getheight(root->left),getheight(root->right))+1;
    temp->height= max(root->height,getheight(temp->left))+1;
    return temp;
}

struct node* rlrotate(struct node*root){
    root->right=rrotate(root->right);
    return lrotate(root);
}

struct node* lrrotate(struct node*root){
    root->left = lrotate(root->left);
    return rrotate(root);
}

struct node* insert(struct node*root,int x){
    if(root==NULL){
        root=createnode(x);
        return root;
    }
    else if (x < root->val){
        root->left=insert(root->left,x);
        if(getbalance(root)>1){
            if(x < root->left->val){
                root=rrotate(root);
            }
            else{
                root=lrrotate(root);
            }
        }
    }
    else if (x > root->val){
        root->right=insert(root->right,x);
        if(getbalance(root)<-1){
            if(x > root->right->val){
                root=lrotate(root);
            }
            else{
                root=rlrotate(root);
            }
        }
    }

    root->height= max(getheight(root->left),getheight(root->right))+1;
    return root;
}

void preorder(struct node* root){
    if(root==NULL){
        return;
    }
    printf("%d ",root->val);
    preorder(root->left);
    preorder(root->right);
}

struct node* seqins(struct node*root,char ins[]){
    int o=0;
    while(ins[o]!='\0'){
        o++;
    }
    o=o-1;
    
    int s=0;
    
    while(s<o){
        while(s<o && ins[s]==' '){
            s++;
        }
        int num=0;
        while(s<o && ins[s]>='0' && ins[s]<='9'){
            num=num*10+(ins[s]-'0');
            s++;
        }
        if(num!=0){
            root=insert(root,num);
        }

    }
    return root;
}

struct node *minnode(struct node*root){
    struct node* temp=root;
    while(temp->left){
        temp=temp->left;
    }
    return temp;
}

struct node *maxnode(struct node*root){
    struct node* temp=root;
    while(temp->right){
        temp=temp->right;
    }
    return temp;
}

struct node* deletenode(struct node*root,int n){
    if(root==NULL){
        return NULL;
    }
    if(n < root->val){
        root->left = deletenode(root->left,n);
    }
    else if(n>root->val){
        root->right = deletenode(root->right,n);
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
            root->right= deletenode(root->right,minte->val);
        }
    }
    if(root==NULL){
        return NULL;
    }
    root->height= 1 + max(getheight(root->left),getheight(root->right));

    int bl=getheight(root->left)-getheight(root->right);

    if(bl>1){
        if(getheight(root->left->left)-getheight(root->left->right)>=0){
            return rrotate(root);
        }
        else{
            return lrrotate(root);
        }
    }
    else if(bl<-1){
        if(getheight(root->right->left)-getheight(root->right->right)<0){
            return lrotate(root);
        }
        else{
            return rlrotate(root);
        }
    }
    return root;
}

struct node* deletekeys(struct node*root,int n1,int n2,int *p){
    if(root==NULL){
        return NULL;
    }
    root->left=deletekeys(root->left,n1,n2,p);
    root->right=deletekeys(root->right,n1,n2,p);
    if(root->val<=n2 && root->val>=n1){
        root=deletenode(root,root->val);
        (*p)++;
        return root;
    }

    int bl=getbalance(root);

    if(bl>1){
        if(getheight(root->left->left)-getheight(root->left->right)>=0){
            return rrotate(root);
        }
        else{
            return lrrotate(root);
        }
    }
    else if(bl<-1){
        if(getheight(root->right->left)-getheight(root->right->right)<0){
            return lrotate(root);
        }
        else{
            return rlrotate(root);
        }
    }
    return root;

    
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

int rightmost(struct node*root){
    struct node*temp=root;
    while(temp->right!=NULL){
        temp=temp->right;
    }
    return temp->val;
}

struct node* getsucc(struct node*root,int x){
    struct node*temp=root;
    struct node* succ=root;
    while(temp!=NULL){
        if(x>temp->val){
            temp=temp->right;
        }
        else if(x<temp->val){
            succ=temp;
            temp=temp->left;
        }
        else{
            if(temp->right){
                return minnode(temp->right);
            }
            else{
                return succ;
            }
        }
    }
    
}

struct node* getpred(struct node*root,int x){
    struct node*temp=root;
    struct node* pred=root;
    while(temp!=NULL){
        if(x>temp->val){
            pred=temp;
            temp=temp->right;
        }
        else if(x<temp->val){
            temp=temp->left;
        }
        else{
            if(temp->left){
                return maxnode(temp->left);
            }
            else{
                return pred;
            }
        }
    }
    
}

void preordersum(struct node* root,int *sum){
    if(root==NULL){
        return;
    }
    preordersum(root->left,sum);
    (*sum)+=root->val;
    preordersum(root->right,sum);
}

int main(){
    char c;
    struct node *root=NULL;
    char arr[10000];
    fgets(arr,10000,stdin);
    int k=0;
    while(arr[k]!='\0'){
        k++;
    }
    
    root=treefromstring(arr,0,k-1);
    
    do{
        scanf("%c",&c);
        if(c=='a'){
            char ins[10000];
            getchar();
            fgets(ins,10000,stdin);
            root=seqins(root,ins);
            stringfromtree(root);
            printf("\n");
            
        }
        if(c=='b'){
            int n1,n2;
            scanf("%d %d",&n1,&n2);
            int p=0;
            root=deletekeys(root,n1,n2,&p);
            if(p>0){
                printf("%d ",p);
                preorder(root);
                printf("\n");
            }
            else{
                printf("-1\n");
            }
        }
        if(c=='c'){
            int f;
            scanf("%d",&f);
            struct node*found=find(root,f);
            if(found && found->val!=rightmost(root)){
                struct node*suc=getsucc(root,f);
                printfind(root,suc->val);
                printf("\n");
            }
            else{
                printf("%d\n",getheight(root));
            }
        }

        if(c=='d'){
            int r;
            int sum=0;
            scanf("%d",&r);
            if(find(root,r)){
                struct node*subroot=find(root,r);
                preordersum(subroot,&sum);
                printf("%d ",sum);
                stringfromtree(subroot);
                printf("\n");
            }
            else{
                printf("-1\n");
            }
        }

        if(c=='e'){
            int w;
            scanf("%d",&w);
            if(root->left==NULL && root->right==NULL){
                printf("-1\n");
            }
            else if(find(root,w)){
                struct node*found=find(root,w);
                struct node*suc=getsucc(root,w);
                struct node*pred=getpred(root,w);
                if(!suc && !pred){
                    printf("-1\n");
                }
                else if(suc && !pred){
                    printf("%d\n",suc->val);
                }
                else if(pred && !suc){
                    printf("%d\n",pred->val);
                }
                else{
                    int mini=min(mod(found->val - pred->val),mod(suc->val - found->val));
                    if(mini == mod(found->val - pred->val)){
                        printf("%d\n",pred->val);
                    }
                    else{
                        printf("%d\n",suc->val);
                    }
                }
            }
            else{
                printf("-1\n");
            }
        }
        
    }while(c!='g');
}
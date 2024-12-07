#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct node{
    struct node *left;
    struct node *right;
    int val;
};

struct node* createNode(int x){
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->val=x;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

int search(int ar[],int strt,int end,int val){
    for(int i=strt;i<=end;i++){
        if(ar[i]==val){
            return i;
        }
    }
    return -1;
}

struct node *buildTree(int inord[],int preord[],int inSt,int inEnd,int *pInd){
    if(inSt>inEnd){
        return NULL;
    }

    struct node *temp = createNode(preord[*pInd]);
    *pInd=(*pInd)+1;
    if(inSt==inEnd){
        return temp;
    }

    int inx=search(inord,inSt,inEnd,temp->val);

    temp->left = buildTree(inord,preord,inSt,inx-1,pInd);
    temp->right = buildTree(inord,preord,inx+1,inEnd,pInd);

    return temp;
}

void inord(struct node *root){
    if(root==NULL){
        return;
    }
    inord(root->left);
    printf("%d ",root->val);
    inord(root->right);
}

void postord(struct node*root){
    if(root==NULL){
        return;
    }
    postord(root->left);
    postord(root->right);
    printf("%d ",root->val);
}



void zigzaglevelOrder(struct node* root, int n)
{
    struct node* queue[2 * n];
    int top = -1;
    int front = 1;
    queue[++top] = NULL;
    queue[++top] = root;
    queue[++top] = NULL;
 
    int prevFront = 0, count = 1;
    while (1) {
        struct node* curr = queue[front];
        if (curr == NULL) {
            if (front == top)
                break;
            else {   
                if (count % 2 == 0) {
                    for (int i = prevFront + 1; i < front; i++)
                        printf("%d ", queue[i]->val);
                }
                else {
                    for (int i = front - 1; i > prevFront; i--)
                        printf("%d ", queue[i]->val);
                }
                prevFront = front;
                count++;
                front++;
                queue[++top] = NULL;
 
                continue;
            }
        }
 
        if (curr->left != NULL)
            queue[++top] = curr->left;
        if (curr->right != NULL)
            queue[++top] = curr->right;
        front++;
    }
 
    if (count % 2 == 0) {
        for (int i = prevFront + 1; i < top; i++)
            printf("%d ", queue[i]->val);
    }
    else {
        for (int i = top - 1; i > prevFront; i--)
            printf("%d ", queue[i]->val);
    }
}

void levelmax(struct node *root,int ar[],int d,int *manma){
    if(!root){
        return;
    }
    *manma = ((*manma)>d)? *manma:d;

    ar[d] = (ar[d] > root->val) ? ar[d] : root->val;
    levelmax(root->left,ar,d+1,manma);
    levelmax(root->right,ar,d+1,manma);
}

int height(struct node*root){
    if(root==NULL){
        return 0;
    }
    return 1+ ((height(root->left)>height(root->right))?height(root->left):height(root->right));
}

int diameter(struct node*root){

    if(root==NULL){
        return 0;
    }

    int lht = height(root->left);
    int rht = height(root->right);

    int ldi = diameter(root->left);
    int rdi = diameter(root->right);

    int maxdi= ((ldi>rdi)?ldi:rdi);
    return ((lht+rht+1)>maxdi)?(lht+rht+1):(maxdi); 
}

void rightleafsum(struct node*root,int *sum){
    if(root==NULL){
        return;
    }

    if(root->right){
        if(root->right->left == NULL && root->right->right == NULL){
            (*sum) += root->right->val;
        }
    }

    rightleafsum(root->left,sum);
    rightleafsum(root->right,sum);
}



int main(){

    int n;
    scanf("%d",&n);

    int pre[n],ino[n];
    for(int i=0;i<n;i++){
        scanf("%d",&ino[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&pre[i]);
    }

    int pInd=0;
    struct node *root= buildTree(ino,pre,0,n-1,&pInd);

    char c;
    

    do{
        scanf("%c",&c);

        if(c=='p'){
            postord(root);
            printf("\n");
        }
        if(c=='z'){
            zigzaglevelOrder(root,n);
            printf("\n");
        }
        if(c=='m'){
            int ar[n] ;
            int manma=0;
            for(int i=0;i<n;i++){
                ar[i]=INT_MIN;
            }
            levelmax(root,ar,0,&manma);
            for(int i=0;i<=manma;i++){
                printf("%d ",ar[i]);
            }
            printf("\n");
        }
        if(c=='d'){
            printf("%d\n",diameter(root));
        }
        if(c=='s'){
            int sum=0;
            rightleafsum(root,&sum);
            printf("%d\n",sum); 
        }

    }while(c!='e');

}

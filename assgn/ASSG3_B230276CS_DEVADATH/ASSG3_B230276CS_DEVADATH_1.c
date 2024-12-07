#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct node{
    char name[30];
    char rno[20];
    int age;
    struct node* next;
};

int hashfn(char name[],int age){
    int sum=0;
    for(int k=0;name[k]!='\0';k++){
        sum=sum+name[k]-'0';
    }
    sum+=age;
    int hashed=sum%4;
    return hashed;
}


void selectionSort(char arr[][30], int n)
{
    int i, j, min_idx;
    char minStr[30];
    for (i = 0; i < n-1; i++)
    {
        int min_idx = i;
        strcpy(minStr, arr[i]);
        for (j = i+1; j < n; j++){
            if (strcmp(minStr, arr[j]) > 0){
                strcpy(minStr, arr[j]);
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            char temp[30];
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[min_idx]);
            strcpy(arr[min_idx], temp);
        }
    }
}


struct node* createnode(char name[],char rno[],int age){
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    strcpy(temp->name,name);
    strcpy(temp->rno,rno);
    temp->age=age;
    temp->next=NULL;
    return temp;
}

struct node* insert(struct node* t,char name[],char rno[],int age){
    if(t==NULL){
        t=createnode(name,rno,age);
    }
    else{
        struct node* g=t;
        while(g->next!=NULL){
            g=g->next;
        }
        g->next=createnode(name,rno,age);
    }
    return t;
}

int gias(char name[],struct node* arr[]){
    for(int i=0;i<4;i++){
        struct node*temp=arr[i];
        while(temp!=NULL){
            if(!strcmp(temp->name,name)){
                return hashfn(temp->name,temp->age);
            }
            temp=temp->next;
        }
    }
    return -1;
}

void sd(char rno[],struct node*arr[]){
    int flg=0;
    for(int i=0;i<4;i++){
        struct node*temp=arr[i];
        while(temp!=NULL){
            if(!strcmp(temp->rno,rno)){
                flg=1;
                printf("%s %s %d\n",temp->name,temp->rno,temp->age);
                return;
            }
            temp=temp->next;
        }
    }
    if(!flg){
        printf("-1\n");
    }
}

void gcal(struct node* arr[],int k){
    struct node*temp=arr[k];
    struct node*t2=temp;
    int cnt=0;
    while(temp!=NULL){
        temp=temp->next;
        cnt++;
    }

    char sa[cnt][30];
    for(int i=0;i<cnt;i++){
        strcpy(sa[i],t2->name);
        t2=t2->next;
    }

    selectionSort(sa,cnt);

    printf("%d ",cnt);
    for(int i=0;i<cnt;i++){
        printf("%s ",sa[i]);
    }
    printf("\n");

}

void glbb(struct node* arr[],int m,char ar[]){
    struct node*temp=arr[m];
    int flag=0;
    while(temp!=NULL){
        char big1=tolower(temp->rno[7]);
        char big2=tolower(temp->rno[8]);
        char ar1=tolower(ar[0]);
        char ar2=tolower(ar[1]);
        if(big1==ar1){
            if(big2==ar2){
                flag=1;
                printf("%s ",temp->name);
            }   
        }
        temp=temp->next;
    }
    if(!flag){
        printf("-1");
    }
    printf("\n");

}

void gtabb(struct node* arr[], int sno, int dno, char br[]) {
    struct node* temp = arr[sno];
    struct node* prev = NULL;
    int flag = 0;
    int cn = 0;

    char br1 = tolower(br[0]);
    char br2 = tolower(br[1]);
    while (temp != NULL) {
        char big1 = tolower(temp->rno[7]);
        char big2 = tolower(temp->rno[8]);

        if (big1 == br1 && big2 == br2) {
            flag = 1;
            if (prev == NULL) {
                arr[sno] = temp->next;
            } else {
                prev->next = temp->next;
            }
            struct node* to_move = temp;
            temp = temp->next;
            arr[dno] = insert(arr[dno], to_move->name, to_move->rno, to_move->age);
            cn++;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }

    printf("%d\n", cn);
}


int main(){
    int n;
    scanf("%d",&n);
    
    struct node* arr[4];
    for(int i=0;i<4;i++){
        arr[i]=NULL;
    }
    for(int i=0;i<n;i++){
        char name[30],rno[20];
        int age;
        scanf("%s%s%d",name,rno,&age); 
        int hasd=hashfn(name,age);
        arr[hasd]=insert(arr[hasd],name,rno,age);
    }


    char o;

    do{
        scanf("%c",&o);
        if(o=='a'){
            char searchname[30];
            scanf("%s",searchname);
            printf("%d\n",gias(searchname,arr));
        }
        if(o=='b'){
            int ind;
            scanf("%d",&ind);
            gcal(arr,ind);
        }
        if(o=='c'){
            int p;
            char ar[3];
           
            scanf(" %d",&p);
            scanf(" %s",ar);
            glbb(arr,p,ar);
        }
        if(o=='d'){
            char rnoo[20];
            scanf(" %s",rnoo),
            sd(rnoo,arr);
        }
        if(o=='e'){
            int sno,dno;
            char bra[5];
            scanf("%d%d",&sno,&dno);
            scanf(" %s",bra);
            gtabb(arr,sno,dno,bra);
        }
    }while(o!='f');
}
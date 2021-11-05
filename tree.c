// Binary Search Tree ADT implementation ... 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "readData.h"
#include <string.h>

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)
#define UR(tree)    ((tree)->UR)

typedef struct URLlist
{
    int urID;
    char name[100];
    int count;
    float tfidf;
    struct URLlist *next;
}URLlist;


typedef struct Node 
{
   char data[30];
   URLlist *UR;
   Tree left, right;
} Node;


void Lower(char *ch1)
{
    int len=strlen(ch1);
    //char ch[len];
    int j=0;
    for(j=0;j<len;j++)
    {
        if(ch1[j]>=65 && ch1[j]<=90)
            ch1[j]=ch1[j]+32;
    }
    
    ch1[len]='\0';
}
        
Tree GetInvertedList(PRlist L)
{
    FILE *fp;
    int i=0;
    char ch[100];
    char *filename;
    int flag=0;
    Tree t_root = NULL;
    PRlist curr=L;
    int urid=-1;
    //PRlist new=L;
    while(curr!=NULL)
    {
        strcpy(ch,curr->name);
        urid=getID(L,ch);
        filename=ch;
        strcat(filename,".txt");
        printf("filename=%s\n",filename);
        i=0;
        flag=0;
        fp=fopen(filename,"r");
        if(fp==NULL)
            printf("the file can not open\n");
        while(fscanf(fp,"%s",ch)==1)
        {
           
            
            if(strcmp(ch,"Section-2")==0 )
                flag=1;
            if(flag==1)
            { 
                if(strcmp(ch,"#end")==0)
                    break;
                if(strcmp(ch,"Section-2")==0 || strcmp(ch,",")==0 || strcmp(ch,".")==0 || strcmp(ch,";")==0)
                        i=0;
                else
                {
                    int len=strlen(ch);
                    Lower(ch); 
                    if(ch[len-1]=='.' || ch[len-1]==',' || ch[len-1]==';')
                        ch[len-1]='\0'; 
                    printf("---%s\n",ch); 
                    t_root=TreeInsert(t_root,ch,urid);
                }
            }
         }
        fclose(fp);  
    curr=curr->next;
    }


            
    return t_root;       

}



URLlist *newNodeL(char *name, int urID) 
{
    
        URLlist *new = malloc(sizeof(URLlist));
        strcpy(new-> name,name);
        new->count=1;
        new-> urID=urID;
        new->next = NULL;
       
    
    return new;
}


// make a new node containing data
Tree newTNode(char *it, int urID, URLlist *cur) 
{
   Tree new = malloc(sizeof(Node));
   new->UR=cur;
   new->UR->next=NULL;
   
   assert(new != NULL);
   UR(new)->urID=urID;
   strcpy(data(new) , it);
   left(new) = right(new) = NULL;
   return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      printf("%d\n", data(t));
      showTreeR(left(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}

// compute height of Tree
int TreeHeight(Tree t) {

   // not yet implemented

   return -1;
}

// count #nodes in Tree
int TreeNumNodes(Tree t) {
   if (t == NULL)
      return 0;
   else
      return 1 + TreeNumNodes(left(t)) + TreeNumNodes(right(t));
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;
   else if (strcmp(it,data(t))<0)
      return TreeSearch(left(t), it);
   else if (strcmp(it,data(t))>0)
      return TreeSearch(right(t), it);
   else                                 // it == data(t)
      return true;
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, char *it, int urID) //change
{
   int flag1=0;
   //URLlist *head=UR(t);
   URLlist *new,*last;
   //char ch[1000];
   
   if (t == NULL)
   {
        //printf("===========");
        printf("it=%s, id=%d\n",it, urID);
      new=newNodeL(it,urID);  
      t = newTNode(it,urID,new);
       
   }
   else if (strcmp(it,data(t))<0)
      left(t) = TreeInsert(left(t), it, urID);
   else if (strcmp(it,data(t))>0)
      right(t) = TreeInsert(right(t), it, urID);
   else if(strcmp(it,data(t))==0)
   {
        URLlist *curr=UR(t);
        while(curr!=NULL)
        { 
            flag1=0;
            if(curr->urID==urID)
            {
                 curr->count++;
                 printf("============count=%d\n",curr->count);
                 flag1=1;
                 break;
            }
            
            if(curr->next==NULL)
                last=curr;
        curr=curr->next;
        }   
            if(flag1!=1)
            {   
                    printf("########it=%s, $$$$$$$$id=%d\n",it, urID);
                    new=newNodeL(it,urID);
                    last->next=new;
                    last=new;
            }

   }   
   return t;
}

Tree joinTrees(Tree t1, Tree t2) {
   if (t1 == NULL)
      return t1;
   else if (t2 == NULL)
      return t2;
   else {
      Tree curr = t2;
      Tree parent = NULL;
      while (left(curr) != NULL) {    // find min element in t2
	 parent = curr;
	 curr = left(curr);
      }
      if (parent != NULL) {
	 left(parent) = right(curr);  // unlink min element from parent
	 right(curr) = t2;
      }
      left(curr) = t1;
      return curr;                    // min element is new root
   }
}

// delete an item from a Tree
Tree TreeDelete(Tree t, Item it) {
   if (t != NULL) {
      if (it < data(t))
	 left(t) = TreeDelete(left(t), it);
      else if (it > data(t))
	 right(t) = TreeDelete(right(t), it);
      else {
	 Tree new;
	 if (left(t) == NULL && right(t) == NULL) 
	    new = NULL;
	 else if (left(t) == NULL)    // if only right subtree, make it the new root
	    new = right(t);
	 else if (right(t) == NULL)   // if only left subtree, make it the new root
	    new = left(t);
	 else                         // left(t) != NULL and right(t) != NULL
	    new = joinTrees(left(t), right(t));
	 free(t);
	 t = new;
      }
   }
   return t;
}

Tree rotateRight(Tree n1) {
   if (n1 == NULL || left(n1) == NULL)
      return n1;
   Tree n2 = left(n1);
   left(n1) = right(n2);
   right(n2) = n1;
   return n2;
}

Tree rotateLeft(Tree n2) {
   if (n2 == NULL || right(n2) == NULL)
      return n2;
   Tree n1 = right(n2);
   right(n2) = left(n1);
   left(n1) = n2;
   return n1;
}

Tree insertAtRoot(Tree t, Item it) {

   printf("Not yet implemented.\n");
   
   return t;
}

Tree partition(Tree t, int i) {
   if (t != NULL) {
      assert(0 <= i && i < TreeNumNodes(t));
      int m = TreeNumNodes(left(t));
      if (i < m) {
	 left(t) = partition(left(t), i);
	 t = rotateRight(t);
      } else if (i > m) {
	 right(t) = partition(right(t), i-m-1);
	 t = rotateLeft(t);
      }
   }
   return t;
}

Tree rebalance(Tree t) {
   int n = TreeNumNodes(t);
   if (n >= 3) {
      t = partition(t, n/2);           // put node with median key at root
      left(t) = rebalance(left(t));    // then rebalance each subtree
      right(t) = rebalance(right(t));
   }
   return t;
}
/*void sort(Tree t)
{
    sort(t->left);
    printf("%s\n", t->data);
    sort(t->right);
}*/

int main(int argc, char *argv[])
{
    
    PRlist L=GetCollection();
    Tree t=GetInvertedList(L);
    printf("=%s\n", t->data);
    printf("-=%s\n", t->left->data);
    URLlist *curr=t->left->UR;
    while(curr!=NULL)
    {
            printf("++++++++++++++%d   ----------uid%d\n",curr->count,curr->urID);
    curr=curr->next;
    }
    
    //sort(t);
    return 0;

}

#include "readData.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*typedef struct PRlistNode 
{
   char         name[100];       //name of the web
   int          urID;       //urID e.g.:ur131
   int          outlinknum; 
   double       pagerank;   //weight                  
   struct PRlistNode *next; 
} PRlistNode;
*/

//int getID(PRlist,char* urname);

// create a new PRlistNode
PRlistNode *newNode(char *name, int urID) 
{
    
        PRlistNode *new = malloc(sizeof(PRlistNode));
        strcpy(new-> name,name);
        new-> urID=urID;
        new->next = NULL;
       
    
    return new;
}



// assume that the file is open for reading
PRlist GetCollection()
{
    FILE *fp;
    PRlistNode *head=NULL;
    PRlistNode *new;
    PRlistNode *curr;
    int urid=0;
    char ch[1000];
    //char *n;
    fp=fopen("collection.txt","r");
    if(fp==NULL)
        printf("the file can not open\n");
    else
    {
        while(fscanf(fp,"%s",ch)==1)
        {
            
            //fscanf(fp,"%s",ch);
            new=newNode(ch,urid);
            //printf("ch=%s\n",ch);
            urid++;
            if(head==NULL)
	        {
			    head=new;
			    curr=new;
		    }
		    else // insert at the end
		    {
		    	curr->next=new;
			    curr=new;
		    }
        }
    }
    fclose(fp);
    /*new=head;
    while(new!=NULL)
    {
    printf("name=%s url=%d\n",new->name,new->urID);
    new=new->next;
    }*/
    return head;
}
   
int getID(PRlist L,char* urname)
{
    //PRlistNode *head;
    PRlist curr=L;
    int id=-1;
    while(curr!=NULL)
    {
        if(strcmp(urname,curr->name)==0)
            id=curr->urID;
            
    curr=curr->next;
    }
    return id;
}   
    
int getNUM(PRlist L)
{
    int count=0;
    PRlist curr=L;
    while(curr!=NULL)
    {
        count++;
        curr=curr->next;
    }
    return count;

}   






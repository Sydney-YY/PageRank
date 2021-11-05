#include <stdbool.h>
typedef struct PRlistNode 
{
   char         name[100];       //name of the web
   int          urID;       //urID e.g.:ur131
   int          outlinknum; 
   double       pagerank;   //weight                  
   struct PRlistNode *next; 
} PRlistNode;
typedef struct PRlistNode *PRlist;

int getID(PRlist L, char *urname);
PRlist GetCollection();
int getNUM(PRlist);
//PRList insertLL(PRList, int);
//PRList deleteLL(PRList, int);
//bool inLL(List, int);
//void freeLL(List);
//void showLL(List);

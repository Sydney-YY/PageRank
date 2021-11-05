#include <stdbool.h>







Graph createPRgraph(PRlist L);
int oneinlinknum_arrary(Graph g, int pinode, int pi[],int num);
int totalinlink(Graph g,int pjnode);
float oneoutlink(Graph g,int pinode);
float totaloutlink(Graph g,int pjnode);
void PageRankW(float d, double diffPR, int maxIterations);
void getoutlinknum(Graph g,PRlist L);



// ?rva004DDA9A@Pathfinder@@QAEHPAH0HHPAVRva004DD9E3@@@Z
// partial score=0.8 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Oy-
enum PathfindLayerEnum { PATHFIND_LAYER_GROUND=0 };
class PathfindCell;
class Rva004DD9E3 { public: int rva004DD9E3(int,int,int); };
class Rva002E6CFE { public: int x,step,remaining; void rva002E6CFE(int,int,int); };
class Pathfinder { public:
 PathfindCell *getCell(PathfindLayerEnum,int,int);
 int rva004DDA9A(int *,int *,int,int,Rva004DD9E3 *);
};
static __forceinline int prevVertex(int n,int count) { return n ? n-1 : count-1; }
static __forceinline int nextVertex(int n,int count) { int next=n+1; return next==count ? 0 : next; }
int Pathfinder::rva004DDA9A(int *x,int *y,int numEdges,int layer,Rva004DD9E3 *visitor)
{
 int count=1;
 for(int i=1;i<numEdges;++i) {
   if(x[i]!=x[count-1] || y[i]!=y[count-1]) { x[count]=x[i]; y[count]=y[i]; ++count; }
 }
 numEdges=count;
 while(numEdges>2 && x[0]==x[numEdges-1] && y[0]==y[numEdges-1]) --numEdges;
 if(numEdges<3) return -1;
 int top=0,maxY=0;
 for(int i=1;i<numEdges;++i) {
   if(y[i]<y[top] || (y[i]==y[top] && x[i]<x[top])) top=i;
   if(y[i]>maxY) maxY=y[i];
 }
 int scanY=y[top],leftIndex=top;
 Rva002E6CFE left,right;
 left.rva002E6CFE(x[top],x[prevVertex(top,numEdges)],y[prevVertex(top,numEdges)]-scanY);
 leftIndex=prevVertex(leftIndex,numEdges);
 int rightStart=top;
 while(y[rightStart]==y[nextVertex(rightStart,numEdges)]) rightStart=nextVertex(rightStart,numEdges);
 right.rva002E6CFE(x[rightStart],x[nextVertex(rightStart,numEdges)],y[nextVertex(rightStart,numEdges)]-y[rightStart]);
 int rightIndex=nextVertex(rightStart,numEdges);
 while(scanY<=maxY) {
   int start=(left.x+128)/256,finish=(right.x+128)/256;
   for(int cellX=start;cellX<=finish;) {
     PathfindCell *cell=getCell((PathfindLayerEnum)layer,cellX,scanY);
     ++cellX;
     if(cell) { int result=visitor->rva004DD9E3((int)cell,cellX-1,scanY); if(result) return result; }
   }
   ++scanY;
   left.x+=left.step; --left.remaining;
   while(left.remaining==0) {
     int before=prevVertex(leftIndex,numEdges);
     int dy=y[before]-y[leftIndex];
     if(dy<0) break;
     left.rva002E6CFE(x[leftIndex],x[before],dy);
     leftIndex=prevVertex(leftIndex,numEdges);
   }
   right.x+=right.step; --right.remaining;
   while(right.remaining==0) {
     int after=nextVertex(rightIndex,numEdges);
     int dy=y[after]-y[rightIndex];
     if(dy<0) break;
     right.rva002E6CFE(x[rightIndex],x[after],dy);
     rightIndex=nextVertex(rightIndex,numEdges);
     if(right.remaining<0) return 0;
   }
 }
 return 0;
}

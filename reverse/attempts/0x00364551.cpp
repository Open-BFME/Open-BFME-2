// ?rva00364551@Path@@QAEXPAVObject@@HHPBUCoord3D@@@Z
// partial score=0.9579316494039477 date=2026-10-09
// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Target 364551..3649B1 RET16. ZH Path::optimize node/LOS semantic guide.
// WB F1DC10 confirms backwards/forwards scans. Retail supplies step counts,
// portal exclusions, template108 flag, and optional tail-direction constraint.
#include "Lib/Coord3D.h"
#include <math.h>
#include <stdlib.h>
struct PathAngle2D {float x,y;void normalize(){float inv=1.0f/(float)sqrt(x*x+y*y);x*=inv;y*=inv;}};
struct PathTemplateView {char pad[0x108];unsigned flags108;};
class Object {public:void *vtable;PathTemplateView *templ;};
class PathNode {public:PathNode *next,*previous,*nextOptimized;Coord3D pos;int layer;bool canOptimize;char pad1D[3];int portalID;bool hasPortal()const{return portalID!=0x7fffffff;}};
enum PathfindLayerEnum {LAYER_GROUND=1};
class Pathfinder {public:
 int IsNonPinchedCliffCell(int,int);
 int IsLinePassableForOptimize(void *,void *,PathfindLayerEnum,const Coord3D *,const Coord3D *,void *);
 bool IsGroundLineOnly(const Coord3D *,const Coord3D *);
};
class AI {public:char pad00[0x10];Pathfinder *m_pathfinder;Pathfinder *pathfinder()const{return m_pathfinder;}};
extern AI *TheAI;
int Rva002E6E6CGet(int);
class Path {public:
 void rva00364551(Object *,int,int,const Coord3D *);
 void *vtable;PathNode *first,*last;bool optimized;
};
void Path::rva00364551(Object *obj,int surfaces,int blocked,const Coord3D *input)
{
 PathNode *anchor,*node;
 if(input) {
  anchor=last;
  while(anchor && anchor->previous) {
   int layer=anchor->layer,curLayer=anchor->layer,distance=0;
   for(node=anchor->previous;node;node=node->previous) {
    Pathfinder *finder=TheAI->pathfinder();distance+=10;
    bool passable=false;
    if((unsigned char)finder->IsNonPinchedCliffCell((int)&node->pos,layer))passable=true;
    else {
     int dx=node->pos.x-anchor->pos.x,dy=node->pos.y-anchor->pos.y;
     if(dx==0 && abs(dy)==distance)passable=true;
     if(dy==0 && abs(dx)==distance)passable=true;
     if(abs(dx)==abs(dy) && abs(dx)==distance)passable=true;
     if(!passable && (unsigned char)TheAI->pathfinder()->IsLinePassableForOptimize(obj,(void *)surfaces,(PathfindLayerEnum)layer,&anchor->pos,&node->pos,(void *)blocked))passable=true;
    }
    if((unsigned char)Rva002E6E6CGet(curLayer)) {
     if(node->layer!=curLayer) {layer=node->layer;if(distance>30)passable=false;}
    } else if(node->previous && node->previous->layer!=curLayer) {
     if(distance>30)passable=false;
    }
    curLayer=node->layer;
    if(passable) {
     if(anchor==last && distance>50) {
      PathAngle2D delta;delta.x=node->pos.x-anchor->pos.x;delta.y=node->pos.y-anchor->pos.y;float inv=1.0f/(float)sqrt(delta.x*delta.x+delta.y*delta.y);delta.x*=inv;delta.y*=inv;float dot=input->x*delta.x+input->y*delta.y;
      if(fabs(dot)<0.9f)passable=false;
     }
     if(passable && node->canOptimize) {node->nextOptimized=anchor;continue;}
    }
    node->nextOptimized=anchor;break;
   }
   anchor=node;
  }
 } else {
  bool groundOnly=(obj->templ->flags108>>11)&1;
  anchor=first;
  while(anchor && anchor->next) {
   int count=0,layer=anchor->layer,curLayer=anchor->layer;
   int portals=(unsigned char)(anchor->portalID!=0x7fffffff)?0:3;
   int distance=0;
   for(node=anchor->next;node;node=node->next) {
    count++;distance+=10;Pathfinder *finder=TheAI->pathfinder();portals++;
    bool passable=false;
    if((unsigned char)finder->IsNonPinchedCliffCell((int)&node->pos,layer))passable=true;
    else {
     int dx=node->pos.x-anchor->pos.x,dy=node->pos.y-anchor->pos.y;
     if(dx==0 && abs(dy)==distance)passable=true;
     if(dy==0 && abs(dx)==distance)passable=true;
     if(abs(dx)==abs(dy) && abs(dx)==distance)passable=true;
     if(!passable) {
      if(node->portalID==0x7fffffff && portals<3)passable=true;
      if(node->portalID!=0x7fffffff)passable=true;
      PathNode *probe=node->next;
      int steps=0;while(probe){if(probe->portalID!=0x7fffffff)passable=true;probe=probe->next;steps++;if(steps>3)break;}
      if(!passable && (unsigned char)TheAI->pathfinder()->IsLinePassableForOptimize(obj,(void *)surfaces,(PathfindLayerEnum)layer,&anchor->pos,&node->pos,(void *)blocked))passable=true;
     }
    }
    if((unsigned char)Rva002E6E6CGet(curLayer)) {
     if(node->layer!=curLayer) {layer=node->layer;if(distance>30)passable=false;}
     if(groundOnly && !passable) {
      int dx=node->pos.x-last->pos.x,dy=node->pos.y-last->pos.y;
      if(abs(dx)+abs(dy)<40 && TheAI->pathfinder()->IsGroundLineOnly(&anchor->pos,&node->pos))passable=true;
     }
    } else if(node->next && node->next->layer!=curLayer) {
     if(distance>30)passable=false;
    }
    curLayer=node->layer;
    if(passable && node->canOptimize) {anchor->nextOptimized=node;continue;}
    if(count>1)node=node->previous;
    else anchor->nextOptimized=node;
    break;
   }
   anchor=node;
  }
 }
 optimized=true;
}

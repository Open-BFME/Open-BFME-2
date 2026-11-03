// ?rva00364551@Path@@QAEXPAVObject@@H_NPBM@Z
// cl: /I. /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Path optimize pass (WorldBuilder Path::optimize sibling, MathCoord2D.h Coord2D::GetLength/Normalize inlined):
// portal exclusions, template108 ground-only flag, and an optional tail-direction constraint (|dot| < 0.9).
// The direction check is Coord2D delta(dx, dy); delta.Normalize(); fabs(delta.Dot(*input)): the WB debug body
// shows GetLength (sqrt) then 1.0f / len and x *= inv, y *= inv; retail inlines both (forced here).
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include <math.h>
#include <stdlib.h>
struct PathAngle2D {
 float x,y;
 PathAngle2D(float ax,float ay):x(ax),y(ay){}
 __forceinline float length()const{return (float)sqrt(x*x+y*y);}
 __forceinline void normalize(){float len=length();float inv=1.0f/len;x*=inv;y*=inv;}
 float dot(const Coord3D *c)const{return x*c->x+y*c->y;}
};
struct PathTemplateView {char pad[0x108];unsigned flags108;};
class Object {public:void *vtable;PathTemplateView *templ;};
#include "../../../Include/GameLogic/PathNode.h"
enum PathfindLayerEnum {LAYER_GROUND=1};
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;
int isGroundOrBridgeLayer(int);
class Path {public:
 void rva00364551(Object *,int,bool,const float *);
 void *vtable;PathNode *first,*last;bool optimized;
};
void Path::rva00364551(Object *obj,int surfaces,bool blocked,const float *facing)
{
const Coord3D *input=(const Coord3D *)facing;
 PathNode *anchor,*node;
 if(input) {
  anchor=last;
  while(anchor && anchor->m_prev) {
   int layer=anchor->m_layer,curLayer=anchor->m_layer,distance=0;
   for(node=anchor->m_prev;node;node=node->m_prev) {
    Pathfinder *finder=TheAI->pathfinder();distance+=10;
    bool passable=false;
    if((unsigned char)finder->IsNonPinchedCliffCell((int)&node->m_pos,layer))passable=true;
    else {
     int dx=node->m_pos.x-anchor->m_pos.x,dy=node->m_pos.y-anchor->m_pos.y;
     if(dx==0 && abs(dy)==distance)passable=true;
     if(dy==0 && abs(dx)==distance)passable=true;
     if(abs(dx)==abs(dy) && abs(dx)==distance)passable=true;
     if(!passable && (unsigned char)TheAI->pathfinder()->IsLinePassableForOptimize(obj,(void *)surfaces,(PathfindLayerEnum)layer,&anchor->m_pos,&node->m_pos,*(void *const *)&blocked))passable=true;
    }
    if((unsigned char)isGroundOrBridgeLayer(curLayer)) {
     if(node->m_layer!=curLayer) {layer=node->m_layer;if(distance>30)passable=false;}
    } else if(node->m_prev && node->m_prev->m_layer!=curLayer) {
     if(distance>30)passable=false;
    }
    curLayer=node->m_layer;
    if(passable) {
     if(anchor==last && distance>50) {
      PathAngle2D delta(node->m_pos.x-anchor->m_pos.x,node->m_pos.y-anchor->m_pos.y);
      delta.normalize();float dot=delta.dot(input);
      if(fabs(dot)<0.9f)passable=false;
     }
     if(passable && node->m_canOptimize) {node->m_nextOpti=anchor;continue;}
    }
    node->m_nextOpti=anchor;break;
   }
   anchor=node;
  }
 } else {
  bool groundOnly=(obj->templ->flags108>>11)&1;
  anchor=first;
  while(anchor && anchor->m_next) {
   int count=0,layer=anchor->m_layer,curLayer=anchor->m_layer;
   int portals=(unsigned char)(anchor->m_portalID!=0x7fffffff)?0:3;
   int distance=0;
   for(node=anchor->m_next;node;node=node->m_next) {
    count++;distance+=10;Pathfinder *finder=TheAI->pathfinder();portals++;
    bool passable=false;
    if((unsigned char)finder->IsNonPinchedCliffCell((int)&node->m_pos,layer))passable=true;
    else {
     int dx=node->m_pos.x-anchor->m_pos.x,dy=node->m_pos.y-anchor->m_pos.y;
     if(dx==0 && abs(dy)==distance)passable=true;
     if(dy==0 && abs(dx)==distance)passable=true;
     if(abs(dx)==abs(dy) && abs(dx)==distance)passable=true;
     if(!passable) {
      if(node->m_portalID==0x7fffffff && portals<3)passable=true;
      if(node->m_portalID!=0x7fffffff)passable=true;
      PathNode *probe=node->m_next;
      for(int steps=0;steps<=3;steps++){if(!probe)break;if(probe->m_portalID!=0x7fffffff)passable=true;probe=probe->m_next;}
      if(!passable && (unsigned char)TheAI->pathfinder()->IsLinePassableForOptimize(obj,(void *)surfaces,(PathfindLayerEnum)layer,&anchor->m_pos,&node->m_pos,*(void *const *)&blocked))passable=true;
     }
    }
    if((unsigned char)isGroundOrBridgeLayer(curLayer)) {
     if(node->m_layer!=curLayer) {layer=node->m_layer;if(distance>30)passable=false;}
     if(groundOnly && !passable) {
      int dx=node->m_pos.x-last->m_pos.x,dy=node->m_pos.y-last->m_pos.y;
      if(abs(dx)+abs(dy)<40 && TheAI->pathfinder()->IsGroundLineOnly(&anchor->m_pos,&node->m_pos))passable=true;
     }
    } else if(node->m_next && node->m_next->m_layer!=curLayer) {
     if(distance>30)passable=false;
    }
    curLayer=node->m_layer;
    if(passable && node->m_canOptimize) {anchor->m_nextOpti=node;continue;}
    if(count>1)node=node->m_prev;
    else anchor->m_nextOpti=node;
    break;
   }
   anchor=node;
  }
 }
 optimized=true;
}

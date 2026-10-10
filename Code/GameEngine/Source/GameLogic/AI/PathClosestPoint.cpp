// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG /ICode/Libraries/Include/Lib
// Fresh328B native body363930..363A78 RET8. Existing Path constructor,
// optimized-node scan and position setter establish the Path/PathNode views.
// Target bytes independently show links0/8, positionC, selected10 and fraction14;
// ZH AIPathfind.h is a path/closest-point semantic lead, with differing cache
// and link layouts, so its layout and method name are not asserted here.
// The target searches segment projections, clamps the fraction to[0,1], and
// retains the best start node. The only call is the owned debug-position setter.
#include "Coord3D.h"
class Pathfinder {public:void SetDebugPathPosition(const Coord3D*);};
class AI;extern AI *TheAI;
struct PathAIView {char unknown[0x10];Pathfinder *pathfinder;};
class PathNode {public:PathNode *next,*previous,*nextOptimized;Coord3D position;int layer;bool canOptimize;int waypointID;};
class Path {public:bool rva00363930(const Coord3D*,bool);private:void *unknown;PathNode *path,*tail;bool optimized;char pad[3];PathNode *selected;float fraction;};
bool Path::rva00363930(const Coord3D *position,bool useOptimized) {
 if(!path)return false;
 PathNode *bestNode=0;
 if(!selected)selected=path;
 PathNode *node=selected;
 float bestDistance=10000000000.0f;
 float bestFraction=0.0f;
 PathNode *next=node->nextOptimized;
 while(next) {
  float dx=(useOptimized?next:node->next)->position.x-node->position.x;
  float dy=(useOptimized?next:node->next)->position.y-node->position.y;
  float px=position->x-node->position.x;
  float py=position->y-node->position.y;
  float t=(px*dx+py*dy)/(dx*dx+dy*dy);
  if(t<0.0f)t=0.0f;else if(t>1.0f)t=1.0f;
  float x=t*dx+node->position.x-position->x;
  float y=t*dy+node->position.y-position->y;
  float distance=x*x+y*y;
  if(distance<bestDistance){bestDistance=distance;bestNode=node;bestFraction=t;}
  else if(bestDistance<0.1f)break;
  node=useOptimized?next:node->next;
  next=node->nextOptimized;
 }
 if(bestNode) {
  selected=bestNode;fraction=bestFraction;
  ((PathAIView*)TheAI)->pathfinder->SetDebugPathPosition(position);
  return true;
 }
 return false;
}

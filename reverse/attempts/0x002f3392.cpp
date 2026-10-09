// ?rva002F3392@Pathfinder@@QAE_NPAVPathNode@@0IPAUCoord3D@@11@Z
// partial score=0.8864 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// Clean BF1 f989 AIPathfind.cpp offset/segment obstacle detour is primary guide.
// Native2F3392..2F35AF RET24/WB D4EC40 establishes segment/tall-building role.
// Original source signature unresolved; existing neutral pin spelling preserved.
// Canonical scalar Coord3D adapter and static nonthrowing offset helper match
// the native private EAX/ECX/EBX convention. Helper160 and circle caller292 are
// recovered in PathfinderRadialOffset.cpp; this candidate now resolves normally.
// Remaining543 vs541: object EAX then ESI move + SSE radius/delta/store ordering.
typedef float Real;
#include "Coord3D.h"
#include "Coord2D.h"
struct Rva002E7A62Position : Coord3D {
 Rva002E7A62Position(const Coord3D&r){x=r.x;y=r.y;z=r.z;}
};
class Object { public: unsigned char pad[0x38]; Coord3D position;unsigned char pad44[0xB8-0x44];float radius; const Coord3D* getPosition() const { return &position; }float getRadius()const{return radius;} };
static void Rva002E7A62Offset(const Coord3D& from, Coord3D& insert, const Coord3D& to, Object* obj, Real radius) throw()
{
	Real dx = to.x - from.x;
	Real dy = to.y - from.y;
	Rva002E7A62Position objPos(*obj->getPosition());
	Real objDx = objPos.x - from.x;
	Real objDy = objPos.y - from.y;
	Real crossProduct = dx*objDy - dy*objDx;
	Coord3D fromToNormal;
	fromToNormal.z = 0;
	if (crossProduct>0) {
		fromToNormal.x = dy;
		fromToNormal.y = -dx;
	} else {
		fromToNormal.x = -dy;
		fromToNormal.y = dx;
	}
	fromToNormal.normalize();
	insert = *obj->getPosition();
	insert.x += fromToNormal.x*radius;
	insert.y += fromToNormal.y*radius;
}

enum PathfindLayerEnum {LAYER_GROUND=1};
struct Rva002F1BD5Info {Object*theTallBuilding;unsigned int ignoreBuilding;};
class PathNode {public:
 const Coord3D*getPosition()const{return &pos;}
 void setPosition(const Coord3D*p){pos=*p;}
private: unsigned char pad[0xC];Coord3D pos;
};
class Pathfinder {public:
 int iterateCellsAlongLine(const Coord3D*,const Coord3D*,PathfindLayerEnum,Rva002F1BD5Info*);
 bool rva002F3392(PathNode*,PathNode*,unsigned int,Coord3D*,Coord3D*,Coord3D*);
};
bool Pathfinder::rva002F3392(PathNode*curNode,PathNode*nextNode,unsigned int ignoreBuilding,Coord3D*insertPos1,Coord3D*insertPos2,Coord3D*insertPos3){
 Rva002F1BD5Info info;info.theTallBuilding=0;info.ignoreBuilding=ignoreBuilding;
 Rva002E7A62Position fromPos(*curNode->getPosition());
 Rva002E7A62Position toPos(*nextNode->getPosition());
 for(int i=0;i<2;i++){
  int ret=iterateCellsAlongLine(&fromPos,&toPos,LAYER_GROUND,&info);
  if(ret!=0&&info.theTallBuilding){
   Object*tallBuilding=info.theTallBuilding;
   Rva002E7A62Position bldgPos(*tallBuilding->getPosition());
   Coord2D delta;float radius=tallBuilding->getRadius()+20.0f;
   delta.x=toPos.x-bldgPos.x;delta.y=toPos.y-bldgPos.y;
   if(delta.length()<=radius*0.98){
    if(delta.length()<0.1)delta.x=1;
    delta.normalize();
    float dx=delta.x*radius;float dy=delta.y*radius;
    toPos.x=bldgPos.x+dx;toPos.y=bldgPos.y+dy;
    nextNode->setPosition(&toPos);continue;
   }
   delta.x=fromPos.x-bldgPos.x;delta.y=fromPos.y-bldgPos.y;
   if(delta.length()<=radius*0.98){
    if(delta.length()<0.1)delta.x=1;
    delta.normalize();
    float dx=delta.x*radius;float dy=delta.y*radius;
    fromPos.x=bldgPos.x+dx;fromPos.y=bldgPos.y+dy;
   }
   Rva002E7A62Offset(fromPos,*insertPos2,toPos,tallBuilding,radius);
   Rva002E7A62Offset(fromPos,*insertPos1,*insertPos2,tallBuilding,radius);
   Rva002E7A62Offset(*insertPos2,*insertPos3,toPos,tallBuilding,radius);
   return true;
  }
 }
 return false;
}

// ?adjustToMeleeDestination@Pathfinder@@QAE_NPAVObject@@ABVLocomotorSet@@PAUCoord3D@@@Z
// partial score=0.924811862244898 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /I.
typedef bool Bool;
// Native2ED7F7..2EDCF7 RETC. WB D45C80 independently names AdjustToMeleeDestination;
// existing pinned ABI from rowed AIUpdateInterface::requestMeleeApproachPath.
// Target-supplied 16B movement query, template56C/634 and spiral budget1200;
// neighbouring ZH checkDestination/GetCell and BF1 probes are semantic guides.
#include "Code/Libraries/Include/Lib/Coord3D.h"
struct ICoord2D {int x,y;};
enum PathfindLayerEnum {PATHFIND_LAYER_GROUND=0};
class LocomotorSet;
struct Rva002E8BCFSrc{char pad[0x10];int m10;char pad14;bool m15;};
class Rva002E8BCF{public:Rva002E8BCF(const Rva002E8BCFSrc*,bool,int,bool);int m0;bool m4,m5;int m8;bool mC;};
struct Rva002ED7F7Template {char pad[0x56C];int width;char pad570[0x634-0x570];bool centerOff;};
class Object{public:int rva0028B511()const;bool rva0028AFBB()const;char pad[4];Rva002ED7F7Template*definition;char pad8[0x38-8];float position[3];};
class PathfindCell{public:char pad[8];unsigned short zone;char padA[2];unsigned packed;unsigned short quickZone()const{return zone;}int getType()const{return packed&15;}};
class TerrainLogic{public:PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);};extern TerrainLogic *TheTerrainLogic;
class GameData;extern const GameData *TheGameData;
struct Rva002ED7F7Budget{char pad[0x1200];int maxSteps;};
void Rva002EBCA7Split(void*,int*,unsigned char*);
ICoord2D*Rva002E7875WorldToCell(ICoord2D*,bool,const Coord3D*);
class Rva002E7964{public:void rva002E7964(ICoord2D*,unsigned char,const Coord3D*);};
class Rva002E99F9Sub460{public:unsigned short rva0053241F(void*,unsigned short);unsigned short rva00531FD4(void*,unsigned short);};
class Rva002EC3CEProbes{public:bool rva002EAA41(int,int,int,int,int,bool);bool rva002E7BF0(int,int,bool,int,int,int,void*,bool);};
class Pathfinder{public:PathfindCell*getCell(PathfindLayerEnum,int,int);PathfindCell*rva002E8BF8(PathfindLayerEnum,const Coord3D*);bool adjustToMeleeDestination(Object*,const LocomotorSet&,Coord3D*);char pad[0x460];Rva002E99F9Sub460 zones;};
static __forceinline void subtractMelee(Coord3D &a,const Coord3D&b){a.x-=b.x;a.y-=b.y;a.z-=b.z;}
static __forceinline float distanceMelee(const Coord3D&a){return a.z*a.z+a.y*a.y+a.x*a.x;}
extern "C" __declspec(dllimport) double __cdecl floor(double);
float Sin(float x);
float Cos(float x);

// REAL_TO_INT_FLOOR: the IAT floor then an x87 round-to-integer store.
static __forceinline int realToIntFloor(float f)
{
	float floored = (float)floor((double)f);
	long i;
	__asm {
		fld [floored]
		fistp [i]
	}
	return i;
}

static const float PATHFINDER_CELL_INV = 1.0f / 10.0f;
__declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
{
	int ix;
	int iy;
	if (center) {
		ix = realToIntFloor(pos->x * PATHFINDER_CELL_INV);
		iy = realToIntFloor(pos->y * PATHFINDER_CELL_INV);
	} else {
		ix = realToIntFloor(pos->x * PATHFINDER_CELL_INV + 0.5f);
		iy = realToIntFloor(pos->y * PATHFINDER_CELL_INV + 0.5f);
	}
	out->x = ix;
	out->y = iy;
	return out;
}

bool Pathfinder::adjustToMeleeDestination(Object*obj,const LocomotorSet&set,Coord3D*dest){
 int radius;Bool center;Rva002EBCA7Split(obj,&radius,(unsigned char*)&center);
 union{ICoord2D cell;struct{int oldX;int steps;}walk;}state;((Rva002E7964*)this)->rva002E7964(&state.cell,center,dest);if(state.cell.x<0)return false;
 PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(obj,dest);union{PathfindCell *cell;int left;}progress;progress.cell=getCell(layer,state.cell.x,state.cell.y);
 Coord3D from;from.x=obj->position[0];from.y=obj->position[1];from.z=obj->position[2];Coord3D delta;delta.x=from.x;delta.y=from.y;delta.z=from.z;subtractMelee(delta,*dest);float bestDist=distanceMelee(delta);
 ICoord2D start;Rva002E7875WorldToCell(&start,true,&from);PathfindLayerEnum fromLayer=(PathfindLayerEnum)obj->rva0028B511();PathfindCell *fromCell=rva002E8BF8(fromLayer,&from);if(!fromCell)return false;
 int width=obj->definition->width;bool centerOff=obj->definition->centerOff;
 Rva002E8BCF query((const Rva002E8BCFSrc*)&set,!centerOff,width-1,obj->rva0028AFBB());
 Rva002E99F9Sub460 *zoneView=&zones;
 unsigned zone=zoneView->rva0053241F(&query,fromCell->quickZone());bool bridge=false;
 if(fromCell->getType()==4){bridge=true;unsigned ground=zoneView->rva00531FD4(&query,zone);zone=zoneView->rva0053241F(&query,ground);}
 if(zone==zoneView->rva0053241F(&query,progress.cell->quickZone())&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,state.cell.x,state.cell.y,layer,radius,center))return true;
 int x=state.cell.x,y=state.cell.y;progress.left=((const Rva002ED7F7Budget*)TheGameData)->maxSteps;state.walk.steps=1;
 while(progress.left>0){
 for(int i=state.walk.steps;i>0;--i){++x;--progress.left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}

 for(int i=state.walk.steps;i>0;--i){++y;--progress.left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}
++state.walk.steps;
 for(int i=state.walk.steps;i>0;--i){--x;--progress.left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}

 for(int i=state.walk.steps;i>0;--i){--y;--progress.left;if(((Rva002EC3CEProbes*)this)->rva002E7BF0((int)&query,zone,center,x,y,layer,dest,bridge)){
  delta=from;subtractMelee(delta,*dest);if(bestDist>distanceMelee(delta)&&((Rva002EC3CEProbes*)this)->rva002EAA41((int)obj,x,y,layer,radius,center))return true;
 }}
++state.walk.steps;
 }
 return false;
}

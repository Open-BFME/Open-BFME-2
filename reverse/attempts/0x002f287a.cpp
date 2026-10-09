// ?AdjustToPossibleDestination@Pathfinder@@QAE_NPAVObject@@ABVLocomotorSet@@PAUCoord3D@@@Z
// partial score=0.65 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /ICode/Libraries/Include/Lib
// Semantic donor BF1 0bef414b PathfinderAdjustToPossibleDestination.cpp.
// WB D455F0 and complete native2F287A..2F2B88 RET12; target deltas retained.
#include "Coord3D.h"
struct ICoord2D { int x,y; };
enum PathfindLayerEnum { UNKNOWN=0,GROUND=1 };
struct Rva002E8BCFSrc;
class LocomotorSet;
class Rva002E8BCF { public: Rva002E8BCF(const Rva002E8BCFSrc *,bool,int,bool); int m0; bool m4,m5; int m8; bool mC; };
struct PossibleTemplate { char prefix[0x56c]; int maxLayer; char gap[0x634-0x570]; unsigned char aircraftFlag; };
class Object { public: int rva0028B511() const; bool rva0028AFBB() const; void *vtable; PossibleTemplate *definition; char prefix[0x38-8]; float position[3]; };
class PathfindCell { public: char prefix[8]; unsigned short zone; unsigned short reserved; unsigned info; };
class TerrainLogic { public: PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *); };
extern TerrainLogic *TheTerrainLogic;
class GlobalData; extern GlobalData *TheWritableGlobalData;
class Rva002E7964 { public: void rva002E7964(ICoord2D *,unsigned char,const Coord3D *); };
class Rva002E99F9Sub460 { public: unsigned short rva0053241F(void *,unsigned short); unsigned short rva00531FD4(void *,unsigned short); };
class Rva002EC3CEProbes { public: bool rva002E7BF0(int,int,bool,int,int,int,void *,bool); };
void Rva002EBCA7Split(void *,int *,unsigned char *);
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
class Pathfinder { public:
 bool AdjustToPossibleDestination(Object *,const LocomotorSet &,Coord3D *);
 PathfindCell *getCell(PathfindLayerEnum,int,int);
 PathfindCell *rva002E8BF8(PathfindLayerEnum,const Coord3D *);
 unsigned char bfmeWrapE6E90(void *,void *,void *,void *,void *,void *);
};
static __forceinline bool possibleFootprint(Pathfinder *p,Object *object,int x,int y,int layer,int radius,bool center) {
 // Native RET24 uses four-byte words and tests only the final low-byte bool.
 typedef unsigned char (Pathfinder::*Call)(Object *,int,int,int,int,bool);
 Call typed=reinterpret_cast<Call>(&Pathfinder::bfmeWrapE6E90);
 return (p->*typed)(object,x,y,layer,radius,center)!=0;
}
bool Pathfinder::AdjustToPossibleDestination(Object *object,const LocomotorSet &set,Coord3D *destination) {
 int radius; bool center;
 Rva002EBCA7Split(object,&radius,reinterpret_cast<unsigned char *>(&center));
 int i,j,zone; bool obstacle; PathfindLayerEnum layer;
 // Radius/center remain live; coordinate locals end before the spiral.
 ICoord2D goal;
 reinterpret_cast<Rva002E7964 *>(this)->rva002E7964(&goal,center,destination);
 if(goal.x<0) return false;
 layer=TheTerrainLogic->getLayerForDestination(object,destination);
 PathfindCell *goalCell=getCell(layer,goal.x,goal.y);
 Coord3D from;
 from.x=object->position[0];from.y=object->position[1];from.z=object->position[2];
 ICoord2D start;
 Rva002E7875WorldToCell(&start,true,&from);
 PathfindCell *parent=rva002E8BF8((PathfindLayerEnum)object->rva0028B511(),&from);
 if(!parent) return false;
 int maxLayer=object->definition->maxLayer;
 unsigned char aircraftFlag=object->definition->aircraftFlag;
 bool computerControlled=object->rva0028AFBB();
 Rva002E8BCF profile(reinterpret_cast<const Rva002E8BCFSrc *>(&set),aircraftFlag==0,maxLayer-1,computerControlled);
 Rva002E99F9Sub460 *zones=reinterpret_cast<Rva002E99F9Sub460 *>((char *)this+0x460);
 zone=zones->rva0053241F(&profile,parent->zone);
 obstacle=false;
 if((parent->info&15)==4) { obstacle=true;zone=zones->rva00531FD4(&profile,zone);zone=zones->rva0053241F(&profile,zone); }
 if(zone==zones->rva0053241F(&profile,goalCell->zone) && possibleFootprint(this,object,goal.x,goal.y,layer,radius,center)) return true;
 i=goal.x;j=goal.y;
 int limit=*(int *)((char *)TheWritableGlobalData+0x11fc);
 int delta=1;
 while(limit>0) {
  for(int count=delta;count>0;--count) {
   ++i;--limit;
   if(reinterpret_cast<Rva002EC3CEProbes *>(this)->rva002E7BF0((int)&profile,zone,center,i,j,layer,destination,obstacle) && possibleFootprint(this,object,i,j,layer,radius,center)) return true;
  }
  for(int count=delta;count>0;--count) {
   ++j;--limit;
   if(reinterpret_cast<Rva002EC3CEProbes *>(this)->rva002E7BF0((int)&profile,zone,center,i,j,layer,destination,obstacle) && possibleFootprint(this,object,i,j,layer,radius,center)) return true;
  }
  ++delta;
  for(int count=delta;count>0;--count) {
   --i;--limit;
   if(reinterpret_cast<Rva002EC3CEProbes *>(this)->rva002E7BF0((int)&profile,zone,center,i,j,layer,destination,obstacle) && possibleFootprint(this,object,i,j,layer,radius,center)) return true;
  }
  for(int count=delta;count>0;--count) {
   --j;--limit;
   if(reinterpret_cast<Rva002EC3CEProbes *>(this)->rva002E7BF0((int)&profile,zone,center,i,j,layer,destination,obstacle) && possibleFootprint(this,object,i,j,layer,radius,center)) return true;
  }
  ++delta;
 }
 return false;
}


// ?Rva002E7875WorldToCell@@YAPAUICoord2D@@PAU1@_NPBUCoord3D@@@Z @0x002E7875 162B
// Free world-to-cell converter used by Pathfinder clamp/validate callers
// (0x002E7917 0x002E7964 read this+0x14/0x18/0x1c/0x20 as m_extent).
// Donor pattern: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/
// Rva003F8820Pathfinder.cpp REAL_TO_INT_FLOOR and PathfinderObjectCell.cpp
// centerInCell floor vs floor+0.5. Scale 0.1 at 0x7C2424, half 0.5 at 0x7C26F0.
// Inline asm fld/fistp in fast_round avoids _ftol so the CRT floor narrow plus
// fld/fistp pair matches retail x87 shape.

typedef int Int;
typedef float Real;

static const Real INV = 1.0f / 10.0f;

extern "C" __declspec(dllimport) double __cdecl floor(double);

static __forceinline Real fast_floor(Real f)
{
	return (Real)floor((double)f);
}

static __forceinline long fast_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define R2I(x) (fast_round(fast_floor(x)))

__declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
{
	int ix;
	int iy;
	if (center) {
		ix = R2I(pos->x * INV);
		iy = R2I(pos->y * INV);
	} else {
		ix = R2I(pos->x * INV + 0.5f);
		iy = R2I(pos->y * INV + 0.5f);
	}
	out->x = ix;
	out->y = iy;
	return out;
}


// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// TerrainLogic::iterateTreesNearAPoint, retail 0x00284DD2..0x00285177 (933 B, EH).
// Name: WB twin C52910 (target evidence). Semantic source: BFME1 a7c38d3b
// TerrainRecordScan001AEFF0.cpp (donor), adapted from BFME1's by-value 0x30-byte
// records to BFME2's record pointer list at +0x578 (native evidence).
// Native converts floor/ceil results with inline x87 FISTP; /QIfist is rejected
// with /arch:SSE, so the same primitive as TerrainLogicFindPositionAround.cpp is used.
// TerrainTreeRecord reads: the first record load goes through the donor's byte offset, the
// filter tests read the list again (native reloads [esi+eax]), and the list is
// re-read after the cylinder GeometryInfo is constructed for the CollidesWith
// argument (native reloads +0x578 there).
#include "Coord3D.h"
// All floor operations inline here; keep the unused wrapper local.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
struct TerrainTreeBounds {Coord3D lo,hi;};
struct Rva0087DC00Vec {int x,y,z;};
class Rva0087DC00 {public:void get(Rva0087DC00Vec*);};
enum GeometryType {GEOMETRY_SPHERE,GEOMETRY_CYLINDER,GEOMETRY_BOX};
class GeometryInfo {public: GeometryInfo(GeometryType,bool,float,float,float);virtual ~GeometryInfo();
 bool CollidesWith(const Coord3D &,float,const GeometryInfo &,const Coord3D &,float) const;
 char pad04[12]; float m_minorRadius;char pad14[0x5c-0x14];};
class BfmeX1035;
class BfmeT1035
{
public:
	void bfmeUse1035(BfmeX1035 *p, int b);
	int m_bfmeV; // +0x00 +0x00
};
struct TerrainTreeRecord {Coord3D position;int key;char pad10[8];bool flag18;char pad19[15];int amount;bool flag2c,flag2d;short next; bool isF18() const {return flag18;}};
// +0x578 is TerrainLogic's record-pointer vector (the seed's Rva0027D098 view);
// these records are read through the tree view at the use.
class Rva0027D098;
class TerrainLogic {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void fetchBounds(void *out);
 char pad04[0x578-4]; Rva0027D098 **begin,**end,**capacity;char pad584[4];short buckets[50*50];
 void iterateTreesNearAPoint(const Coord3D*,float,GeometryInfo*,BfmeT1035*,bool,int);
};
void TerrainLogic::iterateTreesNearAPoint(const Coord3D *position,float angle,
 GeometryInfo *geometry,BfmeT1035 *action,bool skipFlag18,int mode) {
 float radius=geometry->m_minorRadius;
 Coord3D center;
 ((Rva0087DC00*)geometry)->get((Rva0087DC00Vec*)&center);
 center.x+=position->x;center.y+=position->y;center.z+=position->z;
 int count=end-begin;
 if(count==0)return;
 radius+=7.0f;
 TerrainTreeBounds extent;
 fetchBounds(&extent);
 float x=center.x-radius,y=center.y-radius;
 if(x<extent.lo.x)x=extent.lo.x;
 if(y<extent.lo.y)y=extent.lo.y;
 if(x>extent.hi.x)x=extent.hi.x;
 if(y>extent.hi.y)y=extent.hi.y;
 int minX=fast_float2long_round((float)floor(((x-extent.lo.x)/(extent.hi.x-extent.lo.x))*49.9f));
 int minY=fast_float2long_round((float)floor(((y-extent.lo.y)/(extent.hi.y-extent.lo.y))*49.9f));
 x=center.x+radius;y=center.y+radius;
 if(x<extent.lo.x)x=extent.lo.x;
 if(y<extent.lo.y)y=extent.lo.y;
 if(x>extent.hi.x)x=extent.hi.x;
 if(y>extent.hi.y)y=extent.hi.y;
 int maxX=fast_float2long_round((float)ceil(((x-extent.lo.x)/(extent.hi.x-extent.lo.x))*49.9f));
 int maxY=fast_float2long_round((float)ceil(((y-extent.lo.y)/(extent.hi.y-extent.lo.y))*49.9f));
 for(int i=minX;i<maxX;++i) {
  for(int j=minY;j<maxY;++j) {
   int index=buckets[j*50+i];
   while(index!=-1 && index>=0 && index<count) {
    TerrainTreeRecord **base=(TerrainTreeRecord **)begin;
    unsigned offset=index*sizeof(TerrainTreeRecord*);
    TerrainTreeRecord *record=*(TerrainTreeRecord**)((char*)base+offset);
    if(!record->key) {index=record->next;continue;}
    if(skipFlag18 && base[index]->isF18()) {index=record->next;continue;}
    if(mode==1) {if(!base[index]->flag2c) {index=record->next;continue;}}
    else if(mode==2) {if(!base[index]->flag2d) {index=record->next;continue;}}
    Coord3D delta; delta.x=base[index]->position.x; delta.y=base[index]->position.y; delta.z=base[index]->position.z;
    delta.x-=center.x;delta.y-=center.y;delta.z-=center.z;
    GeometryInfo cylinder(GEOMETRY_CYLINDER,false,20.0f,7.0f,7.0f);
    if(radius*radius>(delta.x*delta.x+delta.y*delta.y+delta.z*delta.z)) {
     TerrainTreeRecord **list=(TerrainTreeRecord **)begin;
     if(geometry->CollidesWith(*position,angle,cylinder,list[index]->position,0.0f))
      action->bfmeUse1035((BfmeX1035*)record,(int)&center);
    }
    index=record->next;
   }
  }
 }
}

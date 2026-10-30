// ?rva003642DF@Path@@QAE?AURva003642DFResult@@M@Z
// WorldBuilder twin 0xF1CA10 Path::PeekAlongPath (pathfinder_path.cpp); the 16-byte result is copied
// out through the ICF-folded memberwise copy 0x0004254E (fold-proof pin) and default-built by 0x00326BE6.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /I.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <new>
#include <math.h>

typedef int Int;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct Rva003642DFNode {
 Rva003642DFNode *next,*previous,*optimized;Coord3D position;int layer;bool canOptimize;int portal;
};
struct Rva003642DFResult
{
	Rva003642DFResult();
	__declspec(noinline) Rva003642DFResult(const Rva003642DFResult &);
	Rva003642DFNode *m_node;
	Coord3D m_pos;
};

class Rva0008BB38FloatField
{
public:
	Real get() const;
};

class PathNode
{
public:
	PathNode(const Coord3D *position, PathfindLayerEnum layer) throw();

	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_waypointID;
};

class Rva00065964ObjectPool
{
public:
	void *rva002635C2() throw();
};

class Path
{
public:
	void rva003649B1(const PathNode *arg);
	Rva003642DFResult rva003642DF(Real dist);
	Rva003642DFResult rva00364521(const Rva0008BB38FloatField *arg);

private:
	char m_pad00[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;char padD[3];Rva003642DFNode *current;float fraction;Coord3D last;
};

double __cdecl Rva00363CF3Distance(const Coord3D *,const Coord3D *);
struct PathPeekPortal { char pad[0x60];int type; };
class PathPeekTerrain {public:
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
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual PathPeekPortal *getPortal(int);};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
__declspec(noinline) Rva003642DFResult::Rva003642DFResult(const Rva003642DFResult &v) { m_node=v.m_node;m_pos.x=v.m_pos.x;m_pos.y=v.m_pos.y;m_pos.z=v.m_pos.z; }
static __forceinline void peekSub(Coord3D &pos,const Coord3D &offset){pos.x-=offset.x;pos.y-=offset.y;pos.z-=offset.z;}
static __forceinline void peekAdd(Coord3D &pos,const Coord3D &offset){pos.x+=offset.x;pos.y+=offset.y;pos.z+=offset.z;}
static __forceinline void peekScale(Coord3D &pos,float scale){pos.x*=scale;pos.y*=scale;pos.z*=scale;}
inline __declspec(noinline) Rva003642DFResult::Rva003642DFResult(){m_node=0;}
Rva003642DFResult Path::rva003642DF(Real distance)
{
 if(distance<0.1f)distance=0.1f;
 Rva003642DFResult result;
 if(!m_path) {
  result.m_node=(Rva003642DFNode*)m_path;result.m_pos.x=0;result.m_pos.y=0;result.m_pos.z=0;
  last.x=0;last.y=0;last.z=0;return result;
 }
 result.m_node=current;
 if((1 ? result.m_node==0 : result.m_node==0))result.m_node=(Rva003642DFNode*)m_path;
 float startFraction=fraction;
 Rva003642DFNode *next;
 next=result.m_node->optimized;
 if(next!=0) do {
  float length=(float)Rva00363CF3Distance(&next->position,&result.m_node->position);
  float scale=1.0f;
  if(next->portal!=0x7fffffff) {
   PathPeekPortal *portal=((PathPeekTerrain *)TheTerrainLogic)->getPortal(next->portal);
   if(portal) {
    if(portal->type==1 && (1.0f-startFraction)*length>=distance)length=distance/(1.0f-startFraction)-0.1f;
    else if(portal->type==3) {
     scale=length/((float)fabs((double)(next->position.z-result.m_node->position.z))+1.0f);
     if(scale>1.0f)scale=1.0f;
     else if(scale<0.5f)scale*=0.85f;
    }
   }
  }
  float remain=(1.0f-startFraction)*length;
  Rva003642DFNode *interpolationNode=result.m_node->optimized;
  if(interpolationNode ? remain>=distance*scale : remain>=distance*scale) {
   scale=scale/length;scale*=distance;scale+=startFraction;float lerpFactor=scale;
   result.m_pos=interpolationNode->position;
   _ReadWriteBarrier();
   Coord3D delta;
   delta.x=result.m_pos.x-result.m_node->position.x;
   delta.y=result.m_pos.y-result.m_node->position.y;
   delta.z=result.m_pos.z-result.m_node->position.z;
   delta.x*=lerpFactor;delta.y*=lerpFactor;delta.z*=lerpFactor;
   result.m_pos.x=result.m_node->position.x+delta.x;
   result.m_pos.y=result.m_node->position.y+delta.y;
   result.m_pos.z=result.m_node->position.z+delta.z;
   _ReadWriteBarrier();
   result.m_pos=result.m_pos;
   last=result.m_pos;return result;
  }
  distance-=remain/scale;startFraction=0.0f;
  result.m_node=result.m_node->optimized;
 } while((next=result.m_node->optimized)!=0);
 result.m_node=(Rva003642DFNode*)m_pathTail;result.m_pos=result.m_node->position;last=result.m_pos;return result;
}

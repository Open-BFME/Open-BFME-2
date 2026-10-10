// ?rva003642DF@Path@@QAE?AURva003642DFResult@@M@Z
// partial score=0.8836897052993261 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /I.
// ?rva003649B1@Path@@QAEXPBVPathNode@@@Z @0x003649B1 134B via Path append donor
// Evidence: duplicate-position guard via ucomiss on +0xc/+0x10 vs tail; pool g_pathNodePool allocate plus rowed PathNode ctor with arg+0xc/layer+0x18 plus waypoint+0x20; linking head+4 tail+8 optimized+0xc matches PathAppendNode.
#include <new>

typedef int Int;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

#include "Code/Libraries/Include/Lib/Coord3D.h"

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

// g_pathNodePool: matched references place it at VA 0xe01e94 (zero-filled; a plain-data view).
Rva00065964ObjectPool g_pathNodePool;

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

Rva003642DFResult Path::rva00364521(const Rva0008BB38FloatField *arg)
{
	if (arg)
		return rva003642DF(arg->get());
	return rva003642DF(40.0f);
}

void Path::rva003649B1(const PathNode *arg)
{
	if (m_isOptimized && m_pathTail) {
		if (arg->m_position.x == m_pathTail->m_position.x && arg->m_position.y == m_pathTail->m_position.y)
			return;
	}
	void *mem = g_pathNodePool.rva002635C2();
	PathNode *node = mem ? new (mem) PathNode(&arg->m_position, arg->m_layer) : 0;
	node->m_waypointID = arg->m_waypointID;
	PathNode *tail = m_pathTail;
	if (tail) {
		tail->m_next = node;
		node->m_previous = tail;
	}
	if (m_isOptimized && m_pathTail)
		m_pathTail->m_nextOptimized = node;
	m_pathTail = node;
	if (m_path == 0)
		m_path = node;
}

extern "C" double __cdecl fabs(double);
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
extern PathPeekTerrain *TheTerrainLogic;
__declspec(noinline) Rva003642DFResult::Rva003642DFResult(const Rva003642DFResult &v) { m_node=v.m_node;m_pos.x=v.m_pos.x;m_pos.y=v.m_pos.y;m_pos.z=v.m_pos.z; }
static __forceinline void peekSub(Coord3D &a,const Coord3D &b){a.x-=b.x;a.y-=b.y;a.z-=b.z;}
static __forceinline void peekAdd(Coord3D &a,const Coord3D &b){a.x+=b.x;a.y+=b.y;a.z+=b.z;}
static __forceinline void peekScale(Coord3D &a,float f){a.x*=f;a.y*=f;a.z*=f;}
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
 if(!result.m_node)result.m_node=(Rva003642DFNode*)m_path;
 float t=fraction;
 while(Rva003642DFNode *next=result.m_node->optimized) {
  Rva003642DFNode *node=result.m_node;
  float length=(float)Rva00363CF3Distance(&next->position,&node->position);
  float scale=1.0f;
  if(next->portal!=0x7fffffff) {
   PathPeekPortal *portal=TheTerrainLogic->getPortal(next->portal);
   if(portal) {
    if(portal->type==1 && (1.0f-t)*length>=distance)length=distance/(1.0f-t)-0.1f;
    else if(portal->type==3) {
     scale=length/((float)fabs(next->position.z-node->position.z)+1.0f);
     if(scale>1.0f)scale=1.0f;
     else if(scale<0.5f)scale*=0.85f;
    }
   }
  }
  float remain=(1.0f-t)*length;
  node=result.m_node->optimized;
  if(remain>=distance*scale) {
   scale=scale/length;scale*=distance;scale+=t;float f=scale;
   result.m_pos=node->position;
   result.m_pos.x-=result.m_node->position.x;result.m_pos.y-=result.m_node->position.y;result.m_pos.z-=result.m_node->position.z;result.m_pos.x*=f;result.m_pos.y*=f;result.m_pos.z*=f;result.m_pos.x+=result.m_node->position.x;result.m_pos.y+=result.m_node->position.y;result.m_pos.z+=result.m_node->position.z;
   last=result.m_pos;return result;
  }
  distance-=remain/scale;t=0.0f;result.m_node=node;
 }
 result.m_node=(Rva003642DFNode*)m_pathTail;result.m_pos=result.m_node->position;last=result.m_pos;return result;
}

// cl: /MD /O1 /G7 /arch:SSE /ICode/Libraries/Include/Lib
//
// ?xfer@AITacticSiege@@UAEXPAVXfer@@@Z, retail 0x005DC903, 56 bytes.
// Slot 5 (offset 0x14) of vtable 0x00876808 (class of ??1Rva005DC87B rowed
// at 0x005DC87B in Rva005DC73CDerived.cpp). Version(1,1) via Xfer slot 0x28
// then base ?xfer@AITactic@@UAEXPAVXfer@@@Z at 0x004EDA8C then
// XferObjectID at this+0x58. Evidence: ctor 0x005DC85F zeroes dword +0x58,
// callers 0x005A9C13 0x005A9D11 call this from tactic xfers, base pin and
// XferObjectID row 0x003060B2. Layout from Rva005A9ACDTactic.cpp
// (AITacticSiege over AITacticOffensive over AITactic, int at +0x58).

class Xfer
{
public:
	class Version;
	virtual ~Xfer();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual Xfer &operator==(Version &value);
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	OBJECTID_INVALID = -1
};

void XferObjectID(Xfer *xfer, enum ObjectID *objectID);

class Team;
class AITactic
{
public:
	virtual ~AITactic();
 Team*rva004ECECD(int);
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(void *unit, void *unused);
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
};

class Rva002C589B;
class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	char m_pad04[0x10 - 4];
	bool m_running; // +0x10
	char m_pad11[0x20 - 0x11];
	Rva002C589B *m_record; // +0x20
	void *m_owner; // +0x24
	char m_pad28[0x58 - 0x28];
};

class Object;

class GameLogic
{
public:
	class Object *findObjectByID(enum ObjectID id);
};

extern GameLogic *TheGameLogic;

class AITacticSiege : public AITacticOffensive
{
public:
	virtual ~AITacticSiege();
	virtual void xfer(Xfer *xfer);
	class Object *rva005DCAE5();
 bool isWallBreached();bool findWallTarget();
	enum ObjectID m_58; // +0x58
};

void AITacticSiege::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	AITactic::xfer(xfer);
	XferObjectID(xfer, &m_58);
}

// ?rva005DCAE5@AITacticSiege@@QAEPAVObject@@XZ, retail 0x005DCAE5, 15 bytes.
// Object at this+0x58 via TheGameLogic->findObjectByID; callers 0x005A9B2E
// 0x005A9DED 0x005DCAF4, callee row 0x00049DC5.
Object *AITacticSiege::rva005DCAE5()
{
	return TheGameLogic->findObjectByID(m_58);
}

// Native 5DC93B/5DC9C8 are complete141/285B functions despite old wrong-image
// boundary verdicts. WB AITacticSiege.cpp callgraph names both wall queries.
// Reference guide: existing matched AITactic.cpp member/record walkers plus
// BFME1 MAKE_DLINK_HEAD member iterator through the current shared provider.
// No clean AITacticSiege donor is present at f98983a7d3bb. Target template
// flag bytes stay numeric: no unsupported KindOf names are inferred.
#include "Coord3D.h"
struct SiegeTemplateBits {unsigned char bytes[0x122];};
class Object {public:
 unsigned char pad0[4];SiegeTemplateBits*definition;
 unsigned char pad8[0x38-8];Coord3D position;
 unsigned char pad44[0x74-0x44];ObjectID id;
 unsigned char pad78[0x438-0x78];unsigned char status438;
};
template<class T>class DLINK_ITERATOR {
public:DLINK_ITERATOR(){} T*current;unsigned char state[20];void advance();
 T*cur()const{return current;}bool done()const{return !current;}
};
class Team {public:DLINK_ITERATOR<Object>iterate_TeamMemberList()const;Object*rva0039E8EB();};
class Rva002C589B {public:Object*rva002C5DA6();unsigned char pad[12];Coord3D position;};
class Pathfinder {public:
 bool QuickDoesPathExistToStructure(Object*,const Coord3D*,Object*,int);
 bool QuickDoesPathExist(Object*,const Coord3D*,const Coord3D*,int);
};
class AI {public:unsigned char pad[16];Pathfinder*pathfinder;};
extern AI*TheAI;
bool AITacticSiege::isWallBreached() {
 Team*team=rva004ECECD(0);
 Object*unit=0;
 DLINK_ITERATOR<Object>it=team->iterate_TeamMemberList();
 while(!it.done()) {
  if(unit)break;
  Object*obj=it.cur();
  if(obj && ((obj->definition->bytes[0x108]&8) || (obj->definition->bytes[0x113]&4)))unit=obj;
  it.advance();
 }
 bool result=false;
 if(unit) {
  Object*target=m_record->rva002C5DA6();
  Pathfinder*pathfinder=TheAI->pathfinder;
  result=target ? pathfinder->QuickDoesPathExistToStructure(unit,&unit->position,target,0) : pathfinder->QuickDoesPathExist(unit,&unit->position,&m_record->position,0);
 }
 return result;
}
struct Rva002A8AB1Record {public:void*rva002C6ACB();};
class Player;
class Rva002A8F24 {public:Rva002A8AB1Record*rva002A8AB1(void*);void*rva002A8F24(Player*);};
extern Rva002A8F24*g_00DFEEF8;
class Rva0025BFF8 {public:Object*rva0025BFF8(int);};
namespace _STL {
 template<class T>struct hash;template<class T>struct equal_to;
 template<class T>class allocator;
 template<class K,class V>struct pair;
 template<class K,class V,class H,class E,class A>class hash_map {public:unsigned int bucket_count()const;};
}
// Existing AITactic.cpp uses this retained provider spelling for the ten-byte
// (+8 - +4)/4 count. Here it is a consuming ABI view of the owned-ID range;
// the target getter at25BFF8 independently proves32-bit IDs after a prefix.
// This use does not establish a hash-map identity for the target collection.
typedef _STL::hash_map<int,int,_STL::hash<int>,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,int> > > AITacticAssistIndex;
struct SiegeStore {void*word0;void*word4;Rva0025BFF8*list;};
bool AITacticSiege::findWallTarget() {
 const Coord3D*center=&rva004ECECD(0)->rva0039E8EB()->position;
 Coord3D position;position.x=center->x;position.y=center->y;
 Rva002A8AB1Record*record=g_00DFEEF8->rva002A8AB1(m_owner);
 if(record->rva002C6ACB()) {
  SiegeStore*store=(SiegeStore*)g_00DFEEF8->rva002A8F24((Player*)record->rva002C6ACB());
  Rva0025BFF8*list=store->list;
  float nearest=0;
  Object*selected=0;
  for(unsigned i=0;i<((AITacticAssistIndex*)list)->bucket_count();++i) {
   Object*obj=list->rva0025BFF8(i);
   if(obj && !(obj->status438&1) && !(obj->definition->bytes[0x118]&4) &&
    ((obj->definition->bytes[0x121]&8) || ((obj->definition->bytes[0x11f]&0x20) && !(obj->definition->bytes[0x10f]&0x10)))) {
     float dx=obj->position.x-position.x,dy=obj->position.y-position.y;
     float distance=dx*dx+dy*dy;
     if(!selected || distance<nearest) {selected=obj;nearest=distance;}
   }
  }
  if(selected) {m_58=selected->id;return true;}
 }
 return false;
}

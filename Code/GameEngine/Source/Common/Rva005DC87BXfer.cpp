// cl: /MD /ICode/Libraries/Include/Lib
//
// ?xfer@AITacticSiege@@UAEXPAVXfer@@@Z, retail 0x005DC903, 56 bytes.
// Slot 5 (offset 0x14) of vtable 0x00876808 (class of ??1Rva005DC87B rowed
// at 0x005DC87B in Rva005DC73CDerived.cpp). Version(1,1) via Xfer slot 0x28
// then base ?xfer@AITactic@@UAEXPAVXfer@@@Z at 0x004EDA8C then
// XferObjectID at this+0x58. Evidence: ctor 0x005DC85F zeroes dword +0x58,
// callers 0x005A9C13 0x005A9D11 call this from tactic xfers, base pin and
// XferObjectID row 0x003060B2. Layout from Rva005A9ACDTactic.cpp
// (AITacticSiege over AITacticOffensive over AITactic, int at +0x58).

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/Common/XferVersion.h"

#include "GameLogicObjectLookupView.h"

void XferObjectID(Xfer *xfer, enum ObjectID *objectID);

class Team;
#include "../../Include/Common/AITactic.h"
#include "../../Include/Common/AITacticOffensive.h"

class Object;


extern GameLogic *TheGameLogic;

class AITacticSiege : public AITacticOffensive
{
public:
	AITacticSiege(const AsciiString &tacticName);
	virtual ~AITacticSiege();
	virtual void xfer(Xfer *xfer);
	bool rva005DCAF4();
	class Object *rva005DCAE5();
	bool sideHasIdleSiegeWeapons();
	bool isWallBreached();
	bool findWallTarget();
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
#include "../GameLogic/Object/object.h"
template<class T>class DLINK_ITERATOR {
public:DLINK_ITERATOR(){} T*current;unsigned char state[20];void advance();
 T*cur()const{return current;}bool done()const{return !current;}
};
#include "../../Include/Common/TeamBFME2.h"
class Rva002C589B {public:Object*rva002C5DA6();unsigned char pad[12];Coord3D position;};
#include "../../Include/GameLogic/AIPathfind.h"
#include "../../Include/GameLogic/AI.h"
bool AITacticSiege::isWallBreached() {
 Team*team=rva004ECECD(0);
 Object*unit=0;
 DLINK_ITERATOR<Object>it=team->iterate_TeamMemberList();
 while(!it.done()) {
  if(unit)break;
  Object*obj=it.cur();
  if(obj && ((((const SiegeTemplateBits *)obj->m_template)->bytes[0x108]&8) || (((const SiegeTemplateBits *)obj->m_template)->bytes[0x113]&4)))unit=obj;
  it.advance();
 }
 bool result=false;
 if(unit) {
  Object*target=((Rva002C589B *)m_field20)->rva002C5DA6();
  Pathfinder*pathfinder=TheAI->pathfinder();
  result=target ? pathfinder->QuickDoesPathExistToStructure(unit,&unit->m_cachedPos,target,0) : pathfinder->QuickDoesPathExist(unit,&unit->m_cachedPos,&((Rva002C589B *)m_field20)->position,0);
 }
 return result;
}
struct Rva002A8AB1Record {public:void*rva002C6ACB();};
class Player;
#include "../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24*TheSkirmishAIManager;
class Rva0025BFF8
{
public:
	Object *rva0025BFF8(int index);
};
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
 const Coord3D*center=&rva004ECECD(0)->rva0039E8EB()->m_cachedPos;
 Coord3D position;position.x=center->x;position.y=center->y;
 Rva002A8AB1Record*record=TheSkirmishAIManager->rva002A8AB1(m_field24);
 if(record->rva002C6ACB()) {
  SiegeStore*store=(SiegeStore*)TheSkirmishAIManager->rva002A8F24((Player*)record->rva002C6ACB());
  Rva0025BFF8*list=store->list;
  float nearest=0;
  Object*selected=0;
  for(unsigned i=0;i<((AITacticAssistIndex*)list)->bucket_count();++i) {
   Object*obj=list->rva0025BFF8(i);
   if(obj && !(obj->m_privateStatus&1) && !(((const SiegeTemplateBits *)obj->m_template)->bytes[0x118]&4) &&
    ((((const SiegeTemplateBits *)obj->m_template)->bytes[0x121]&8) || ((((const SiegeTemplateBits *)obj->m_template)->bytes[0x11f]&0x20) && !(((const SiegeTemplateBits *)obj->m_template)->bytes[0x10f]&0x10)))) {
     float dx=obj->m_cachedPos.x-position.x,dy=obj->m_cachedPos.y-position.y;
     float distance=dx*dx+dy*dy;
     if(!selected || distance<nearest) {selected=obj;nearest=distance;}
   }
  }
  if(selected) {m_58=selected->m_id;return true;}
 }
 return false;
}

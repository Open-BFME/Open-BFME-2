// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?getPlayerMask@Rva00341C54Filter@@UAEHXZ
// retail 0x00341C30, 36 bytes: slot 2 of the AIStates partition filter
// vftable 0x00C122F0 (slot 1 is its allow 0x00341C54). The filter keeps an
// Object at +0x08: no controlling player gives -1 (every player), otherwise
// the players with relationship 4 to that player, the shape of the rowed
// Rva00261409Filter::getPlayerMask with an object instead of a player.
#include "../../Common/GameLogicObjectLookupView.h"
class Player
{
public:
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
};
enum Relationship{REL_ZERO=0};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct FilterCoordCopy : Coord3D
{
 __forceinline FilterCoordCopy(const Coord3D &p) { x=p.x; y=p.y; z=p.z; }
};
class Rva00390533{public:bool rva00390533();};
class Object
{
public:
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object*)const;
	char pad00[0x38];
 Coord3D pos; // +0x38
 char pad44[0x258-0x44];
 int ai258; // +0x258; pointer word passed under the existing opaque ABI
 Rva00390533 *physics; // +0x25C
 char pad260[0x438-0x260];
 unsigned char flags; // +0x438
};
class PlayerList
{
public:
	int getPlayersWithRelationship(int srcPlayerIndex, unsigned int allowedRelationships, bool flag);
};
extern PlayerList *ThePlayerList;	// VA 0x00DFEEE8
class Rva000421C8
{
public:
	virtual bool allow(Object *obj) = 0;
private:
	int m_04;
};
class Rva00341C54Filter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
private:
	Object *m_obj; // +0x08
	int m_weapon; // +0x0C
};
int Rva00341C54Filter::getPlayerMask()
{
	Player *player = m_obj->getControllingPlayer();
	if (!player)
		return -1;
	int index = player->m_playerIndex;
	return ThePlayerList->getPlayersWithRelationship(index, 4, false);
}

class Rva002F23A6{public:bool rva002F23A6(Object*,int,int,Coord3D*,Object*);};
class AI{public:char pad[0x10];Rva002F23A6*pathfinder;};
extern AI*TheAI;
extern GameLogic*TheGameLogic;
extern "C" void*theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void*,const char*,...);

// Slot1 of C122F0; WB E2E130 independently gives the reject flags,
// relationship/physics checks and melee engagement callback purpose.
// Native complete200B has target offsets438/25C/258 and log level1B4.
bool Rva00341C54Filter::allow(Object *obj)
{
 if (obj->flags & 1)
  goto reject;
 if ((m_obj->flags ^ obj->flags) & 8)
  goto reject;
 if (m_obj->getRelationship(obj) != REL_ZERO)
  goto reject;
 if (!obj->physics || !obj->physics->rva00390533())
  goto accepted;
reject:
 return false;
accepted:
 FilterCoordCopy pos = obj->pos;
 // +0x1B4 lies in the shared GameLogic view's observed prefix.
 if (*reinterpret_cast<const int*>(reinterpret_cast<const char*>(TheGameLogic)+0x1B4)>0)
 {
  if (theLogicRandomLogFile)
   fprintf(theLogicRandomLogFile,"FUCK OFF DESYNC: AIAttackFireDuringApproachState::computePath will call FindMeleeEngagmentLocation with pos=%f,%f",pos.x,pos.y);
 }
 int ai = m_obj->ai258;
 Rva002F23A6 *pf = TheAI->pathfinder;
 return pf->rva002F23A6(m_obj,m_weapon,ai+0x1CC,&pos,obj);
}

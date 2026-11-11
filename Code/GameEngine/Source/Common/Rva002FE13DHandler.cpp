// cl: /Os /MD
// ?allow@Rva002FE13DFilter@@UAE_NPAVObject@@@Z @0x002FE13D 86B evidence: REF table slot 0x008071B8 neighbours FileClass Get_File_Handle; flags Object+0x438 bits 1 8; ptr+0x25c bool check pinned 0x00390533; block+0x10e 0x40 +0x115 0x20; final pinned Object getRelationship 0x0028D156
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object;
class Player;
#include "../../Include/GameLogic/Rva00390533.h"

struct FlagBlock
{
	char m_pad[0x10E];
	unsigned char m_10E;
	char m_pad10F[0x115 - 0x10E - 1];
	unsigned char m_115;
};

class Object
{
public:
	Relationship getRelationship(const Object *that) const;
	Player *getControllingPlayer() const;

public:
	void *m_vtbl;
	FlagBlock *m_block4;
	char m_pad08[0x125 - 8];
	unsigned char m_125;
	char m_pad126[0x25C - 0x126];
	Rva00390533 *m_p25C;
	char m_pad260[0x438 - 0x260];
	unsigned char m_flags438;
};

#include "../../Include/Common/Player.h"

#include "../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

// Partition filter with vftable 0x00C071B4: allow (slot 1) and
// getPlayerMask (slot 2).
class Rva002FE13DFilter
{
public:
	virtual ~Rva002FE13DFilter();
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Object *m_pad4;
	Object *m_target;
};

bool Rva002FE13DFilter::allow(Object *obj)
{
	unsigned char flags = obj->m_flags438;
	if (flags & 1)
		return 0;
	else {
		if (flags & 8)
			return 0;
		if (obj->m_p25C != 0) {
			if (obj->m_p25C->rva00390533())
				return 0;
		}
		FlagBlock *blk = obj->m_block4;
		if ((blk->m_10E & 0x40) != 0)
			return 0;
		if ((blk->m_115 & 0x20) != 0)
			return 0;
		return m_target->getRelationship(obj) == ENEMIES ? true : false;
	}
}

// ?getPlayerMask@Rva002FE13DFilter@@UAEHXZ @0x002FE108 53B evidence: VTABLE slot 2 table 0x008071B4 neighbour Rva002FE13D; this+8 Object for rowed getControllingPlayer 0x0028AFA9; flag 0x125 bit 0x40; Player+0x54 via ThePlayerList rowed getPlayersWithRelationship 0x002A7C70 args 0 4
int Rva002FE13DFilter::getPlayerMask()
{
	Player *player = m_target->getControllingPlayer();
	if (player == 0)
		return -1;
	if ((m_target->m_125 & 0x40) == 0) {
		int f54 = player->getPlayerIndex();
		return ThePlayerList->getPlayersWithRelationship(f54, 4, false);
	} else {
		return -1;
	}
}

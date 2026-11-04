// cl: /DNDEBUG /DBFME_SB_CLEAR_DECL /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc /ICode/Libraries/Include
//
// ?rva004051BC@Rva004051BC@@QAEXHPBUCoord3D@@@Z, retail 0x004051BC, 156 bytes.
// Unlock-lane body called from 0x00405258: player-index guard at this+0x2B
// stride 4 bit 0x80, ThePlayerList range query through the pinned
// ThePartitionManager float-radius overload at 0x00625610 (row
// ?bfmeForwardWideC spells the radius as int), single Rva000421C8 filter
// carrying the getNthPlayer result, then ExperienceTracker level bump
// through the pin-only 0x0039B4EC for each hit whose +0x264 tracker is
// present. The row's int radius and void* next are noted here and the
// float/Object spellings are used as the bytes require. Evidence: caller
// 0x004052F7, prev/next // cl:, ThePlayerList/ThePartitionManager pins,
// vtable-free QAE naming with ret 8.

class Player;
class PlayerList;
class ExperienceTracker;
class Rva000421C8;
class Object;

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../Include/GameLogic/PartitionFilter.h"

// The player filter whose vftable slots are allow 0x00260E2A and
// getPlayerMask 0x00260E1E, spelled as SpecialAbilityUpdate.cpp spells it.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

#include "PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

#include "../../Include/GameLogic/ExperienceTracker.h"

// The approved TU's Object view (VictorySystem.cpp); m_experienceTracker at
// +0x264 is object.h's.
struct VictoryObjectTemplate { char pad[0x109]; unsigned char flags109; char pad10a[9]; unsigned char flags113; };

class Object { public: Player *getControllingPlayer() const; char pad0[4]; VictoryObjectTemplate *tmpl; char pad8[0x264-8]; ExperienceTracker *m_experienceTracker; char pad268[0x438-0x268]; unsigned char flags438; };

struct Rva004051BCEntry
{
	unsigned char flag;
	char pad[3];
};

class Rva004051BC
{
public:
	void rva004051BC(int playerIndex, const Coord3D *pos);
private:
	char m_pad00[0x20];
	float m_radius20; // +0x20
	char m_pad24[0x2B - 0x24];
	Rva004051BCEntry m_guards[8]; // +0x2B stride 4, bit 0x80 skips
};

void Rva004051BC::rva004051BC(int playerIndex, const Coord3D *pos)
{
	if ((m_guards[playerIndex].flag & 0x80) != 0)
		return;
	Player *player = ThePlayerList->getNthPlayer(playerIndex);
	Rva00260E2AFilter filter(player);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(pos, m_radius20, 1, &filter, 0);
	for (Object *other = hits.next(); other != 0; other = hits.next()) {
		ExperienceTracker *tracker = other->m_experienceTracker;
		if (tracker == 0)
			continue;
		tracker->rva0039B4EC(1, true, false);
	}
}

// cl: /O1 /MD /arch:SSE /G7
// ?enemyHasAFortress@AISpellBookStructureBaseKill@@QAE_NPAVObject@@@Z, retail
// 0x005D7558, 102 bytes. Renamed from the address placeholder
// Rva005EE816::rva005D7558: the WorldBuilder lead is
// AISpellBookStructureBaseKill::enemyHasAFortress in EA's own
// AISpellBookPowers/AISpellBookStructureBaseKill.cpp (asserts myAI line 63,
// stats line 68, structureStats line 71).
// Body: the caster's controlled player -> the AI record chain (rowed
// 0x002A8AB1, 0x002C6ACB) -> the structure statistics hash map (rowed
// 0x002A8F24, hash_map::bucket_count 0x002BEDAB, index lookup 0x0025BFF8);
// true when any structure in it carries kind bit 0xC2, which is the fortress
// kind the picker above it masks (AISpecialPowerPickers.cpp sets 194).
class Object;
class Player;

// Native object template, +0x120 holds the kind-of flags; bit 0x04 of that
// byte is the 0xC2 test the WorldBuilder body shows (BitFlags test on it).
struct StructureTemplate
{
	char m_pad000[0x120];
	unsigned char m_kindFlags;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad000[0x04];
	StructureTemplate *m_template;
};

class Player;

// 0x002A8AB1 by its row name (Rva002A8AB1.cpp): the AI record for a player.
// Declared a struct to keep the pinned mangling (PAU, not PAV).
#include "../../../../../Include/Common/Rva002A8AB1Record.h"

#include "../../../../../Include/GameLogic/Rva002A8F24.h"

extern Rva002A8F24 *TheSkirmishAIManager;

namespace _STL
{
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class A, class B> struct pair
{
	A first;
	B second;
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned bucket_count() const;
};
}

// The per-player structure statistics map: index -> object.
class Rva0025BFF8 : public _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > >
{
public:
	Object *rva0025BFF8(int index);
};

struct Rva002A8F24Result
{
	char m_pad00[8];
	Rva0025BFF8 *m_hash;
};

class AISpellBookStructureBaseKill
{
public:
	bool enemyHasAFortress(Object *source);
};

bool AISpellBookStructureBaseKill::enemyHasAFortress(Object *source)
{
	Player *controlling = source->getControllingPlayer();
	Rva002A8AB1Record *record = TheSkirmishAIManager->rva002A8AB1(controlling);
	void *owner = record->rva002C6ACB();
	if (owner != 0)
	{
		Rva002A8F24Result *store = static_cast<Rva002A8F24Result *>(TheSkirmishAIManager->rva002A8F24(static_cast<Player *>(owner)));
		Rva0025BFF8 *stats = store->m_hash;
		unsigned count = stats->bucket_count();
		for (unsigned i = 0; i < count; ++i)
		{
			Object *structure = stats->rva0025BFF8(i);
			if (structure->m_template->m_kindFlags & 4)
				return true;
		}
	}
	return false;
}

// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?Rva0028867DCheck@@YA_NPBX@Z, retail 0x0028867D, 37 bytes.
// Multiplayer-gated zero-check on bytes at +0x101/+0x102 via TheBfmeGlob 0x00DFE78C gate (rowed bfmeCall939D 0x0023C6FD).
// Evidence: 5 callers home object into ESI for post-call reads (0x00288937 0x0028895A 0x00288DCD 0x00288E59 0x002897E6);
// adjacent byte getters at 0x002885EC (+0x102) and 0x002885F3 (+0x101) prove the offsets;
// same-gate donor Rva0031DF89 selects offsets via TheBfmeGlob; static ESI-arg convention per Rva008B8F80 precedent.

extern class GameLogic *TheGameLogic;

#include "../../Include/Common/BfmeGlob939D.h"

#define TheBfmeGlob (*(BfmeGlob939D **)&TheGameLogic)

struct Rva0028867DData
{
	char m_pad[0x101];
	unsigned char m_b101;
	unsigned char m_b102;
};

static bool Rva0028867DCheck(const void *level)
{
	const Rva0028867DData *levelData = (const Rva0028867DData *)level;
	if (TheBfmeGlob->bfmeCall939D())
		return levelData->m_b101 == 0;
	return levelData->m_b102 == 0;
}

// absent-from-retail: keeps the static alive with the ESI argument convention.
// TU-local: the identical global copy in ExperienceLevelSystem.cpp provides the
// linked definition, so this one stays out of the link entirely.
static bool Rva0028867DCaller(const void *level)
{
	if (level)
		return Rva0028867DCheck(level);
	return false;
}

// Native00288D88..00288E21, 153B, RET12: existing store pin carries the
// two-word handle result ABI. Native query00288C68 takes one object word
// and returns the list; its original parameter spelling remains unknown.
// Handle/list/node/override layout copied from the verified ExperienceLevelSystem.cpp.
#include "../../Include/Common/Overridable.h"
// Zero Hour's inline getFinalOverride walk as retail inlines it here: the
// first level only, then the out-of-line friend_getFinalOverride (0x001E35DF).
static inline Overridable *firstLevelFinalOverride(Overridable *overridable)
{
    if (overridable->friend_getNextOverride())
        return overridable->friend_getNextOverride()->friend_getFinalOverride();
    return overridable;
}
class ExperienceLevel : public Overridable
{
public:
    char unknown10[0x18-0x10];
    int required;
    char unknown1C[0xFC-0x1C];
    int rank;
};
struct ExperienceLevelNode
{
    ExperienceLevelNode *next, *prev;
    ExperienceLevel data;
};
class ExperienceLevelIterator
{
public:
    ExperienceLevelIterator() {}
    ExperienceLevelIterator(const ExperienceLevelIterator &other) : node(other.node) {}
    ExperienceLevelNode *node;
};
class ExperienceLevelList
{
public:
    ExperienceLevelNode *sentinel;
};
struct ExperienceLevelHandle
{
    ExperienceLevelHandle() {}
    ExperienceLevelHandle(ExperienceLevelList *value) : list(value) {}
    ExperienceLevelHandle(ExperienceLevelList *value, const ExperienceLevelIterator &where)
        : list(value), iter(where) {}
    ExperienceLevelHandle(const ExperienceLevelHandle &other) : list(other.list), iter(other.iter) {}
    ExperienceLevelList *list;
    ExperienceLevelIterator iter;
};
extern "C" bool rva0007E394CursorEqual(const ExperienceLevelHandle &a, const ExperienceLevelHandle &b);
class ThingTemplate;
#include "../../Include/GameLogic/ExperienceLevelStore.h"
ExperienceLevelHandle ExperienceLevelStore::rva00288D88(int object, int limit)
{
    ExperienceLevelList *list = rva00288C68(object);
    if (!list) return ExperienceLevelHandle(0);
    ExperienceLevelHandle best(0);
    int greatest = -1;
    ExperienceLevelNode *end = list->sentinel;
    for (ExperienceLevelNode *node=end->next; node!=end; node=node->next)
    {
        ExperienceLevel *level = static_cast<ExperienceLevel *>(firstLevelFinalOverride(&node->data));
        if (level && Rva0028867DCheck(level))
        {
            int required = level->required;
            if (required <= limit && (rva0007E394CursorEqual(best, ExperienceLevelHandle(0)) || required > greatest))
            {
                ExperienceLevelIterator iter;
                iter.node = node;
                best = ExperienceLevelHandle(list, iter);
                greatest = required;
            }
        }
    }
    return best;
}

// Native00288E21..00288E8D RET12: existing template/rank handle pin from
// ScriptActions::doCreateUnitRevivalEntry003C6381 establishes the argument
// domains and result ABI. The GetLevelRank provider0028879C independently
// proves +FC; this body's final override and eligibility calls establish the
// same loop representation as the verified sibling00288D88.
ExperienceLevelHandle ExperienceLevelStore::rva00288E21(const ThingTemplate *object, int rank) const
{
    ExperienceLevelList *list = const_cast<ExperienceLevelStore *>(this)->rva00288C68(reinterpret_cast<int>(object));
    if (!list) return ExperienceLevelHandle(0);
    ExperienceLevelNode *end = list->sentinel;
    for (ExperienceLevelNode *node=end->next; node!=end; node=node->next)
    {
        ExperienceLevel *level = static_cast<ExperienceLevel *>(firstLevelFinalOverride(&node->data));
        if (level && Rva0028867DCheck(level) && level->rank == rank)
        {
            ExperienceLevelIterator iter;
            iter.node = node;
            return ExperienceLevelHandle(list, iter);
        }
    }
    return ExperienceLevelHandle(0);
}

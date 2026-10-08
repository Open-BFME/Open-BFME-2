// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?Rva0028867DCheck@@YA_NPBX@Z, retail 0x0028867D, 37 bytes.
// Multiplayer-gated zero-check on bytes at +0x101/+0x102 via TheBfmeGlob 0x00DFE78C gate (rowed bfmeCall939D 0x0023C6FD).
// Evidence: 5 callers home object into ESI for post-call reads (0x00288937 0x0028895A 0x00288DCD 0x00288E59 0x002897E6);
// adjacent byte getters at 0x002885EC (+0x102) and 0x002885F3 (+0x101) prove the offsets;
// same-gate donor Rva0031DF89 selects offsets via TheBfmeGlob; static ESI-arg convention per Rva008B8F80 precedent.

extern class GameLogic *TheGameLogic;

class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

#define TheBfmeGlob (*(BfmeGlob939D **)&TheGameLogic)

struct Rva0028867DData
{
	char m_pad[0x101];
	unsigned char m_b101;
	unsigned char m_b102;
};

static bool Rva0028867DCheck(const void *p)
{
	const Rva0028867DData *d = (const Rva0028867DData *)p;
	if (TheBfmeGlob->bfmeCall939D())
		return d->m_b101 == 0;
	return d->m_b102 == 0;
}

// absent-from-retail: keeps the static alive with the ESI argument convention.
bool Rva0028867DCaller(const void *p)
{
	if (p)
		return Rva0028867DCheck(p);
	return false;
}

// ?Rva0028891FCheck@@YG_NPBQBXPBX@Z, retail 0x0028891F, 33 bytes.
// Chain on Rva0028867DCheck: null guard plus equality-against-first guard then ESI call with +8.
// Evidence: callers at 0x00288ADA plus 19 others push two dwords; same-TU static call gives lea esi call shape.
bool __stdcall Rva0028891FCheck(const void *const *p1, const void *p2)
{
	if (!p1)
		return false;
	if (p2 == *p1)
		return false;
	return Rva0028867DCheck((const char *)p2 + 8);
}

// Native00288D88..00288E21, 153B, RET12: existing store pin carries the
// two-word handle result ABI. Native query00288C68 takes one object word
// and returns the list; its original parameter spelling remains unknown.
// Handle/list/node/override layout copied from the verified ExperienceLevelSystem.cpp.
class Overridable
{
public:
    Overridable *friend_getFinalOverride();
    Overridable *getFinalOverride()
    {
        if (next) return next->friend_getFinalOverride();
        return this;
    }
private:
    void *vptr;
    Overridable *next;
};
class ExperienceLevel : public Overridable
{
public:
    char unknown08[0x18-8];
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
class ExperienceLevelStore
{
public:
    ExperienceLevelHandle rva00288D88(int object, int limit);
    ExperienceLevelHandle rva00288E21(const ThingTemplate *object, int rank) const;
    ExperienceLevelList *rva00288C68(int object);
};
ExperienceLevelHandle ExperienceLevelStore::rva00288D88(int object, int limit)
{
    ExperienceLevelList *list = rva00288C68(object);
    if (!list) return ExperienceLevelHandle(0);
    ExperienceLevelHandle best(0);
    int greatest = -1;
    ExperienceLevelNode *end = list->sentinel;
    for (ExperienceLevelNode *node=end->next; node!=end; node=node->next)
    {
        ExperienceLevel *level = static_cast<ExperienceLevel *>(node->data.getFinalOverride());
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
        ExperienceLevel *level = static_cast<ExperienceLevel *>(node->data.getFinalOverride());
        if (level && Rva0028867DCheck(level) && level->rank == rank)
        {
            ExperienceLevelIterator iter;
            iter.node = node;
            return ExperienceLevelHandle(list, iter);
        }
    }
    return ExperienceLevelHandle(0);
}

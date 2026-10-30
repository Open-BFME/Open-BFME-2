// cl: /O1 /MD
// ?rva0037E421@Rva0037E421@@QAEPAXH@Z @0x0037E421 48B
// Bounds-checked accessor for the 216-byte (0xD8) element vector at +0x04/+0x08.
// Returns null when index < 0 or index >= (finish-start)/216 via signed idiv (cdq),
// else start+index*216. Proven by 14 direct callers needing this exact shape.
// Unlock lane; landing unblocks 11 functions. No donor; recipe follows
// Rva00219B9EAccessor signed-idiv precedent with /O1 keeping idiv.
// Honest-address name: owner unknown so Rva0037E421 class, void* return, int index.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Player;
class Xfer;
class Rva001EAE6FHelper
{
	char m_data[0x80];
public:
	Rva001EAE6FHelper *clear80() throw();
	// Keep the existing clear worker while constructing this member in order.
	__forceinline Rva001EAE6FHelper() throw() { clear80(); }
};
class Rva004E04FD
{
	char m_data[0x18];
public:
	Rva004E04FD() throw();
};
class Object;
class Image;

class UnitRevivalEntry
{
public:
	UnitRevivalEntry();
	UnitRevivalEntry(Object *object);
	UnitRevivalEntry(const UnitRevivalEntry &that);
	~UnitRevivalEntry();
	UnitRevivalEntry &operator=(const UnitRevivalEntry &that);
	void *getThingTemplate();
	void setThingTemplateName(const AsciiString &name);
	void rva0037E473(Xfer *xfer);
	int revivalEntryCalcTimeToBuild(const Player *player, Object *producer);
	int revivalEntryCalcCostToBuild(const Player *player, Object *producer);
	const Image *calcButtonImage(const Player *player);

	int m_00;
	int m_04;
	float m_08;
	int m_0C;
	int m_10;
	Rva001EAE6FHelper m_14;
	int m_94;
	int m_98;
	unsigned int m_9C; // build time, from the template's float via _ftol
	bool m_A0;
	bool m_A1;
	int m_A4;
	int m_A8;
	int m_AC;
	Rva004E04FD m_B0;
	int m_C8;
	float m_CC;
	int m_D0;
	AsciiString m_str; // +0xD4
};
typedef UnitRevivalEntry Elem216;
struct Vec216 { Elem216 *m_start; Elem216 *m_finish; Elem216 *m_end; };
static __forceinline unsigned VecSize(Vec216 *v) { return v->m_finish - v->m_start; }
static __forceinline Elem216 &VecAt(Vec216 *v, int i) { return v->m_start[i]; }
class Player;
class Object;
class Image;

class Rva0037E421 {
    int m_00;
    Vec216 m_vec;
public:
    void *rva0037E421(int index);
    void *rva0037E915(int index);
    unsigned char rva0037E7BC(int index);
    void *rva0037E451(int key);
    unsigned char productionSystemCancelUnitCreate(int key);
    void *rva0037E7A5(int index);
};
void *Rva0037E421::rva0037E421(int index)
{
    if (index < 0)
        return 0;
    unsigned int count = VecSize(&m_vec);
    if ((unsigned int)index < count)
        return &VecAt(&m_vec, index);
    return 0;
}
// ?rva0037E7BC@Rva0037E421@@QAEEH@Z @0x0037E7BC 30B
// Chain of rva0037E421; returns element+0x98 == -1 as unsigned char, else 0.
// Proven by caller at 0x00392C96 and the rowed callee; same class and flags.
unsigned char Rva0037E421::rva0037E7BC(int index)
{
    void *p = rva0037E421(index);
    if (!p)
        return 0;
    return ((Elem216 *)p)->m_98 == -1;
}
// ?rva0037E451@Rva0037E421@@QAEPAXH@Z @0x0037E451 34B
// Linear search of the same 216-byte vector for element with m_A4 == key.
// Proven by 4 callers and the +4/+8 vector with 0xD8 stride; same class and flags.
void *Rva0037E421::rva0037E451(int key)
{
    Elem216 *p = m_vec.m_start;
    Elem216 *end = m_vec.m_finish;
    for (; p != end; ++p) {
        if (p->m_A4 == key)
            return p;
    }
    return 0;
}
// ?productionSystemCancelUnitCreate@Rva0037E421@@QAEEH@Z @0x0037E7DA 59B
// Chain of rva0037E451; if element missing or m_98 == -1 return 0 else set
// m_98/m_A4 to -1 via or -1, m_CC to 1.0f via movss, return 1. Proven by caller
// at 0x0049DCE7 and the shared 1.0f literal at 0x00BBB8D8; same class, /arch:SSE for movss.
unsigned char Rva0037E421::productionSystemCancelUnitCreate(int key)
{
    Elem216 *e = (Elem216 *)rva0037E451(key);
    if (!e)
        return 0;
    if (e->m_98 != -1) {
        e->m_98 = -1;
        e->m_A4 = -1;
        e->m_CC = 1.0f;
        return 1;
    }
    return 0;
}
// ?rva0037E7A5@Rva0037E421@@QAEPAXH@Z @0x0037E7A5 23B
// Chain of rva0037E421 then rowed UnitRevivalEntry::getThingTemplate; null if element missing.
// Proven by 5 callers and rowed callees 0x0037E421 and 0x0037E270; same class and flags.
void *Rva0037E421::rva0037E7A5(int index)
{
    void *p = rva0037E421(index);
    if (!p)
        return 0;
    return ((UnitRevivalEntry *)p)->getThingTemplate();
}
// ?rva0037E6E8@Rva0037E6E8@@QAEHPAX0@Z @0x0037E6E8 159B
// Leaf body called by ProductionUpdate::calcTotalProductionFrames at 0x0049CD8E via Player+0x738 slot.
// Entry lookup via Rva0037E421::rva0037E451, controlling-player gate via
// Object::getControllingPlayer plus Rva002A9BF2 == 3, PlayerList gate via
// TheSkirmishAIManager plus Rva002A8AB1, time via UnitRevivalEntry::
// revivalEntryCalcTimeToBuild with this+0x10 player, scale = min(1.0f,
// *(TheSkirmishAIManager+0x854)), return (int)(t*(1.0f-scale)). No donor; recipe follows
// UpgradeTemplate::rva0026EE30 precedent for (int)void* plus TheSkirmishAIManager plus void* args.
// Honest-address name: owner unknown so Rva0037E6E8 class, void* void* args (PAX0 compression).
class Object
{
public:
    Player *getControllingPlayer() const;
};
class Rva002A9BF2
{
public:
    void *rva002A9BF2();
};
class Rva003A2BD4M08;
struct Rva002A8AB1Record;
// 0x002A8AB1 by its row name (Rva002A8AB1.cpp).
class Rva002A8F24
{
public:
    Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *TheSkirmishAIManager;
class Rva0037E6E8 : public Rva0037E421
{
public:
    Player *m_10;
    int rva0037E6E8(void *extra, void *object);
    int rva0037E649(int index, Object *object);
    float rva0037E898(int index, int *cost, Object *object);
    float rva0037E815(int index, Object *object);
};
int Rva0037E6E8::rva0037E6E8(void *extra, void *object)
{
    void *entry = rva0037E451((int)extra);
    if (!entry)
        return 0;
    Object *obj = (Object *)object;
    void *p1 = obj->getControllingPlayer();
    if ((int)((Rva002A9BF2 *)p1)->rva002A9BF2() == 3) {
        void *p2 = obj->getControllingPlayer();
        if (TheSkirmishAIManager->rva002A8AB1((Rva003A2BD4M08 *)p2)) {
            float *limitPtr = (float *)((char *)TheSkirmishAIManager + 0x854);
            float scale = (1.0f > *limitPtr) ? *limitPtr : 1.0f;
            int t = ((UnitRevivalEntry *)entry)->revivalEntryCalcTimeToBuild(m_10, obj);
            return (int)((float)t * (1.0f - scale));
        }
    }
    return ((UnitRevivalEntry *)entry)->revivalEntryCalcTimeToBuild(m_10, obj);
}
// ?rva0037E787@Rva0037E787@@QAEHPAX0@Z @0x0037E787 30B
// Gap body between 0x0037E6E8 and 0x0037E7A5 in the same TU.
// Entry lookup via Rva0037E421::rva0037E421 then direct time via UnitRevivalEntry::
// revivalEntryCalcTimeToBuild with this+0x10 player. Called at 0x005DAFA4 with
// ecx = AIBuildableUnit+0x738 member. Same +0x10 player layout as Rva0037E6E8.
// Honest-address name: owner unknown so Rva0037E787 class, void* void* args (PAX0 compression).
class Rva0037E787 : public Rva0037E421
{
public:
    Player *m_10;
    int rva0037E787(void *extra, void *object);
};
int Rva0037E787::rva0037E787(void *extra, void *object)
{
    void *entry = rva0037E421((int)extra);
    if (!entry)
        return 0;
    return ((UnitRevivalEntry *)entry)->revivalEntryCalcTimeToBuild(m_10, (Object *)object);
}
// ?rva0037EDC6@Rva0037EDC6@@QAEPBVImage@@H@Z @0x0037EDC6 26B
// Leaf body between 0x0037EBEA calcButtonImage and 0x0037EDE0 productionSystem.
// Entry lookup via Rva0037E421::rva0037E421 then UnitRevivalEntry::
// calcButtonImage with the this+0x10 Player pointer; native37ECB0 and37ED3B
// establish this use. Same +0x10 layout as
// UnitRevivalTracker::productionSystemQueueCreateUnit in UnitRevivalTracker.cpp
// which passes its Player to calcButtonImage. Both callees are now rowed.
// Honest-address name: owner unknown so Rva0037EDC6 class,
// const Image* return, int index.
class Rva0037EDC6 : public Rva0037E421
{
public:
    Player *m_10;
    const Image *rva0037EDC6(int index);
};
const Image *Rva0037EDC6::rva0037EDC6(int index)
{
    void *entry = rva0037E421(index);
    if (!entry)
        return 0;
    return ((UnitRevivalEntry *)entry)->calcButtonImage(m_10);
}

// Native 37E649..37E6E8 RET8; index-based cost twin of the full rowed
// key-based time body above. Both consume the same 216-byte entry and
// owner +10 Player slot. This body uses the rowed index accessor37E421,
// rowed cost helper37E18A, and the native PlayerList discount field+850.
// Original owner and public method names remain unproven.
int Rva0037E6E8::rva0037E649(int index, Object *object)
{
    void *entry = rva0037E421(index);
    if (!entry)
        return 0;
    void *p1 = object->getControllingPlayer();
    if ((int)((Rva002A9BF2 *)p1)->rva002A9BF2() == 3) {
        void *p2 = object->getControllingPlayer();
        if (TheSkirmishAIManager->rva002A8AB1((Rva003A2BD4M08 *)p2)) {
            float *limitPtr = (float *)((char *)TheSkirmishAIManager + 0x850);
            float scale = (1.0f > *limitPtr) ? *limitPtr : 1.0f;
            int cost = ((UnitRevivalEntry *)entry)->revivalEntryCalcCostToBuild(m_10, object);
            return (int)((float)cost * (1.0f - scale));
        }
    }
    return ((UnitRevivalEntry *)entry)->revivalEntryCalcCostToBuild(m_10, object);
}

// Native37E898..37E915: unrecruited entries report cost and completed
// progress; active entries use elapsed/start divided by revival time.
float Rva0037E6E8::rva0037E898(int index, int *cost, Object *object) {
 Elem216 *entry = static_cast<Elem216 *>(rva0037E421(index));
 if (entry) {
  if (entry->m_98 == -1) {
   if (cost) *cost = reinterpret_cast<UnitRevivalEntry *>(entry)->revivalEntryCalcCostToBuild(m_10, object);
   return 1.0f;
  }
  int time = reinterpret_cast<UnitRevivalEntry *>(entry)->revivalEntryCalcTimeToBuild(m_10, object);
  if (time > 0) return ((float)TheGameLogic->getFrame() - entry->m_98) / time;
 }
 return 0.0f;
}


// Native37E815..37E87A: build progress of the indexed entry, 0 for a missing
// or unrecruited entry, elapsed/start over the revival time otherwise, 1 when
// that time is not positive. The rest written as the null test's else keeps
// retail's first shared zero block (the -1 test jumps back to it).
float Rva0037E6E8::rva0037E815(int index, Object *object)
{
 Elem216 *entry = static_cast<Elem216 *>(rva0037E421(index));
 if (!entry) return 0.0f;
 else
 {
  if (entry->m_98 == -1) return 0.0f;
  int time = reinterpret_cast<UnitRevivalEntry *>(entry)->revivalEntryCalcTimeToBuild(m_10, object);
  if (time > 0) return ((float)TheGameLogic->getFrame() - entry->m_98) / time;
  return 1.0f;
 }
}

// Native37E915..37E94A and caller49CCF0. Same measured +4/+8 216B array
// as this unit's getters; indexed entry uses owned getThingTemplate37E270.
// A local array base before pointer indexing preserves native ESI divisor
// and ECX receiver. Direct entries.at(index) emits a different 51B shape.
void *Rva0037E421::rva0037E915(int index)
{
    unsigned int count = VecSize(&m_vec);
    if ((unsigned int)index < count && index >= 0) {
        UnitRevivalEntry *base = m_vec.m_start;
        return (base + index)->getThingTemplate();
    }
    return 0;
}

// cl: /MD
// ?rva0037E421@Rva0037E421@@QAEPAXH@Z @0x0037E421 48B
// Bounds-checked accessor for the 216-byte (0xD8) element vector at +0x04/+0x08.
// Returns null when index < 0 or index >= (finish-start)/216 via signed idiv (cdq),
// else start+index*216. Proven by 14 direct callers needing this exact shape.
// Unlock lane; landing unblocks 11 functions. No donor; recipe follows
// Rva00219B9EAccessor signed-idiv precedent with /O1 keeping idiv.
// Honest-address name: owner unknown so Rva0037E421 class, void* return, int index.
struct Elem216 { char m_pad00[0x98]; int m_98; char m_pad9C[0xA4 - 0x9C]; int m_a4; char m_padA8[0xCC - 0xA8]; float m_cc; char m_padD0[0xD8 - 0xD0]; };
struct Vec216 { Elem216 *m_start; Elem216 *m_finish; Elem216 *m_end; };
static __forceinline unsigned VecSize(Vec216 *v) { return v->m_finish - v->m_start; }
static __forceinline Elem216 &VecAt(Vec216 *v, int i) { return v->m_start[i]; }
class Player;
class Object;
class Image;
class UnitRevivalEntry { public: void *getThingTemplate(); int revivalEntryCalcTimeToBuild(const Player *player, Object *producer); int revivalEntryCalcCostToBuild(const Player *player, Object *producer); const Image *calcButtonImage(int value); };
class Rva0037E421 {
    int m_00;
    Vec216 m_vec;
public:
    void *rva0037E421(int index);
    unsigned char rva0037E7BC(int index);
    void *rva0037E451(int key);
    unsigned char rva0037E7DA(int key);
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
// Linear search of the same 216-byte vector for element with m_a4 == key.
// Proven by 4 callers and the +4/+8 vector with 0xD8 stride; same class and flags.
void *Rva0037E421::rva0037E451(int key)
{
    Elem216 *p = m_vec.m_start;
    Elem216 *end = m_vec.m_finish;
    for (; p != end; ++p) {
        if (p->m_a4 == key)
            return p;
    }
    return 0;
}
// ?rva0037E7DA@Rva0037E421@@QAEEH@Z @0x0037E7DA 59B
// Chain of rva0037E451; if element missing or m_98 == -1 return 0 else set
// m_98/m_a4 to -1 via or -1, m_cc to 1.0f via movss, return 1. Proven by caller
// at 0x0049DCE7 and the shared 1.0f literal at 0x00BBB8D8; same class, /arch:SSE for movss.
unsigned char Rva0037E421::rva0037E7DA(int key)
{
    Elem216 *e = (Elem216 *)rva0037E451(key);
    if (!e)
        return 0;
    if (e->m_98 != -1) {
        e->m_98 = -1;
        e->m_a4 = -1;
        e->m_cc = 1.0f;
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
// Leaf body called by Rva0049CD4F::rva0049CD4F at 0x0049CD8E via Player+0x738 slot.
// Entry lookup via Rva0037E421::rva0037E451, controlling-player gate via
// Object::getControllingPlayer plus Rva002A9BF2 == 3, PlayerList gate via
// g_00DFEEF8 plus Rva002A8AB1, time via UnitRevivalEntry::
// revivalEntryCalcTimeToBuild with this+0x10 player, scale = min(1.0f,
// *(g_00DFEEF8+0x854)), return (int)(t*(1.0f-scale)). No donor; recipe follows
// UpgradeTemplate::rva0026EE30 precedent for (int)void* plus g_00DFEEF8 plus void* args.
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
class PlayerList
{
public:
    Player *rva002A8AB1(Rva003A2BD4M08 *);
};
class Rva002A8F24 : public PlayerList
{
};
extern Rva002A8F24 *g_00DFEEF8;
class Rva0037E6E8 : public Rva0037E421
{
public:
    Player *m_10;
    int rva0037E6E8(void *extra, void *object);
    int rva0037E649(int index, Object *object);
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
        if (g_00DFEEF8->rva002A8AB1((Rva003A2BD4M08 *)p2)) {
            float *limitPtr = (float *)((char *)g_00DFEEF8 + 0x854);
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
// calcButtonImage with this+0x10 value. Same +0x10 Int layout as
// UnitRevivalTracker::productionSystemQueueCreateUnit in UnitRevivalTracker.cpp
// which passes m_10 to calcButtonImage. Callees rowed 0x0037E421 plus pin
// 0x0037EBEA. Honest-address name: owner unknown so Rva0037EDC6 class,
// const Image* return, int index.
class Rva0037EDC6 : public Rva0037E421
{
public:
    int m_10;
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
        if (g_00DFEEF8->rva002A8AB1((Rva003A2BD4M08 *)p2)) {
            float *limitPtr = (float *)((char *)g_00DFEEF8 + 0x850);
            float scale = (1.0f > *limitPtr) ? *limitPtr : 1.0f;
            int cost = ((UnitRevivalEntry *)entry)->revivalEntryCalcCostToBuild(m_10, object);
            return (int)((float)cost * (1.0f - scale));
        }
    }
    return ((UnitRevivalEntry *)entry)->revivalEntryCalcCostToBuild(m_10, object);
}

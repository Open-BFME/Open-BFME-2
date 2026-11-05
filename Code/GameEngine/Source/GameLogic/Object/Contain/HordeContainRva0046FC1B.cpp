// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /ICode/Libraries/Include /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?update@Rva0046FC1B@@QAEHXZ, retail 0x0046FC1B..0x0046FE99 (638 B,
// plain RET): HordeContain's update reached through its UpdateModuleInterface
// secondary base (receiver = HordeContain + 0x10; WorldBuilder twin
// 0x010BE680). It records the owner's orientation history, refreshes the
// condition copy, runs the TransportContain update, re-layers the horde
// when its pathfind layer changed, then services the formation flags.
// The tail follows WorldBuilder literally: each busy exit returns
// UPDATE_SLEEP_NONE directly and the +0x111 latch is cleared by its own
// test before the combined busy check; that is what gives retail's block
// order. The class and method keep their address-derived names.
// Forward declarations of the classes whose data members are referenced by
// this function's retail accesses.
// The receiver. Retail accesses touch members at these offsets relative to ECX:
//   [-0xc]  -> producer container pointer
//   [-0x8]  -> owner Object*
//   [+0x110]..[+0x111]  -> condition/latch bytes
//   [+0x114] -> embedded WeaponTemplateSetHead (0x4c bytes = 0x13 dwords)
//   [+0x190] -> sub-object (Rva0046AB7D::rva0046AB7D called on it)
//   [+0x194] -> pointer/int member
//   [+0x19c] -> int member
//   [+0x1a0] -> map header
//   [+0x23c] -> map tree
//   [+0x290] -> int member
//   [+0x294] -> byte flag
//   [+0x2a0] -> int member
//   [+0x2bc] -> vector<ModuleData const*> begin
//   [+0x2c0] -> vector<ModuleData const*> end
//   [+0x2c8] -> vector cursor (int)
// Helper: per-instance push_back of a ModuleData pointer into the vector at
// [+0x2bc]. Defined by the game; only the ABI matters here.

// Retail: plain RET, embedded integer cursor, float history; every history
// branch continues into the full update. Earlier evidence:
// reverse/attempt_support/0x0046fc1b-20261019.md.
#include "Lib/Coord3D.h"
#include <vector>
#include <map>
namespace _STL {
template <> void vector<float>::push_back(const float &);
typedef pair<const int, void *> UpdateIntPtrPair;
typedef _Rb_tree<int, UpdateIntPtrPair, _Select1st<UpdateIntPtrPair>, less<int>, allocator<UpdateIntPtrPair> > UpdateIntPtrTree;
template <> void UpdateIntPtrTree::clear();
}
#include "../../../../Include/Common/WeaponTemplateSetHead.h"
bool Rva00045473Equal(const void *, const void *);
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };
class Object {
public:
    char pad00[0x38];
    Coord3D position;
    float orientation;
    char pad48[0x10c-0x48];
    unsigned int modelFlags[19];
    char pad158[0x258-0x158];
    AIUpdateInterface *ai;
    int rva0028B511() const;
    void setLayer(PathfindLayerEnum);
};
struct Rva002ED236Pos {
    float x,y,z;
    Rva002ED236Pos(const Coord3D &pos) { x=pos.x; y=pos.y; z=pos.z; }
    ~Rva002ED236Pos() {}
};
#include "../../../../Include/GameLogic/AIPathfind.h"
class AI;
extern AI *TheAI;
class GameLogic;
extern GameLogic *TheGameLogic;
struct UpdateLogicView { char pad00[0x40]; unsigned int frame; };
extern int BfmeLogicFramesPerSecond;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
class TransportContain : public BehaviorModule, public UpdateModuleInterface {
public: virtual UpdateSleepTime update();
};
class Rva0046E7C2 { public: void rva0046E7C2(); };
class Rva0046AB7D { public: void rva0046AB7D(); };
struct UpdateListNode { UpdateListNode *next,*prev; Object *object; };
struct UpdateList { UpdateListNode *head; };
#include "../../../../Include/GameLogic/Module/Rva0046247DPair.h"
class Rva0046247D { public: void rva0046247D(Rva0046247DPair &); };
class HordeContain {
public:
    void rva0046E740(int);
#define V(n) virtual void slot##n();
    V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
    V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30)
    virtual bool slot31();
    V(32) V(33) V(34) V(35)
#undef V
    void rva0046D738();
    void rva0046AA85();
    void rva0046A10D();
};
class Rva0046FC1B {
    char pad00[0x2bc];
    _STL::vector<float> m_history;
    int m_cursor;
public: int update();
};
int Rva0046FC1B::update()
{
    char *self = (char *)this;
    int count = *(int *)(*(char **)(self-0xc)+0x260);
    if (count > 0) {
        if (m_history.size() < (unsigned int)count) {
            float angle = (*(Object **)(self-8))->orientation;
            m_history.push_back(angle);
        } else {
            m_history[m_cursor++] = (*(Object **)(self-8))->orientation;
            if (m_cursor >= count)
                m_cursor = 0;
        }
    }
    if (*(unsigned char *)(self+0x294) == 1) {
        ((Rva0046E7C2 *)(self-0x10))->rva0046E7C2();
        return BfmeLogicFramesPerSecond * 2;
    }
    bool changed = false;
    WeaponTemplateSetHead flags(*(WeaponTemplateSetHead *)&(*(Object **)(self-8))->modelFlags);
    if (!Rva00045473Equal(self+0x114, &flags)) {
        changed = true;
        *(WeaponTemplateSetHead *)(self+0x114) = flags;
    }
    int result = ((TransportContain *)(self-0x10))->TransportContain::update();
    Object *owner = *(Object **)(self-8);
    AIUpdateInterface *ai = owner->ai;
    if (!ai)
        return result;
    if (*(int *)(self+0x290))
        ((HordeContain *)(self-0x10))->rva0046D738();
    if (changed)
        ((HordeContain *)(self-0x10))->rva0046AA85();
    if (!ai->isMoving() && !*(int *)(self+0x290)) {
        PathfindLayerEnum layer = (*(Pathfinder **)((char *)TheAI+0x10))->rva002ED236(owner, owner->position);
        if ((int)layer != owner->rva0028B511()) {
            owner->setLayer(layer);
            Rva0046247DPair items;
            ((Rva0046247D *)(self-0x10))->rva0046247D(items);
            for (UpdateListNode *node=((UpdateList *)items.m04)->head->next; node!=((UpdateList *)items.m04)->head; node=node->next) {
                Object *member = node->object;
                member->setLayer((*(Pathfinder **)((char *)TheAI+0x10))->rva002ED236(member, member->position));
            }
            *(bool *)(self+0x110) = true;
        }
    } else {
        *(bool *)(self+0x110) = true;
        ((Rva0046AB7D *)(self+0x190))->rva0046AB7D();
        *(int *)(self+0x2a0) = 0;
    }
    HordeContain *horde = (HordeContain *)(self-0x10);
    horde->rva0046E740(0);
    if (((UpdateLogicView *)TheGameLogic)->frame % (unsigned int)BfmeLogicFramesPerSecond == 0 && horde->slot31())
        return UPDATE_SLEEP_NONE;
    if (*(bool *)(self+0x110) || *(int *)(self+0x194) != 0 || *(int *)(self+0x1a0)) {
        *(bool *)(self+0x110) = false;
        if (*(int *)(self+0x1a0) && *(int *)(self+0x19c) == 0) {
            *(int *)(self+0x1a0) = 0;
            ((_STL::UpdateIntPtrTree *)(self+0x23c))->clear();
            *(bool *)(self+0x111) = true;
        }
        horde->slot35();
        if (!*(bool *)(self+0x110))
            *(bool *)(self+0x111) = false;
        if (*(bool *)(self+0x110) || *(int *)(self+0x194) != 0)
            return UPDATE_SLEEP_NONE;
    }
    if (((UpdateLogicView *)TheGameLogic)->frame % (unsigned int)BfmeLogicFramesPerSecond == 0)
        horde->rva0046A10D();
    return result;
}

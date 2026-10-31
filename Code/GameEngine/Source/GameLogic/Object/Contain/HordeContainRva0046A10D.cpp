// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva0046A10D@HordeContain@@QAEXXZ, retail 0x0046A10D..0x0046A2A7 (410 B,
// RET0, ebp frame 0x28). Target evidence: the +0x08 owner, +0x120/+0x121
// flags, +0x290 frame stamp (TheGameLogic +0x40), +0x294 pending flag and the +0x11C interface's
// slot 7 establish a HordeContain method; its name stays address-derived.
// Unless the owner's AI (+0x258) slot 111 holds (then the logic frame
// is stamped), a pending update older than three times the
// interval at 0x009BA4E4 clears the flag, and a stationary owner re-places
// its members: each member's 0x0028AD32 runs, TheAI's pathfinder (+0x10)
// adjusts the owner's position (rowed 0x002FCFCF), a correction of 10..150
// units is applied through Thing::setPosition, then each member is placed at
// the slot-7 position with the owner's layer (0x0028ACEE / 0x0028B511).
// The member list comes from the rowed 26-byte descriptor 0x0046247D, defined
// below as the same select-any noinline copy its home unit and other callers
// use: with its body visible cl gives retail's EBX/EDI roles (receiver in EBX,
// AI pointer and both list walks in EDI). The correction is formed as BFME 1's
// HordeContain release movement does (copy position, subtract the original).
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Object;
class LocomotorSet {};
class Pathfinder
{
public:
    bool AdjustDestination(Object *object,
        const LocomotorSet &locomotorSet,
        Coord3D *destination,
        const Coord3D *groupDestination);
};
template <int N> class Rva0046A10DAISlots : public Rva0046A10DAISlots<N - 1>
{
public:
    virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0046A10DAISlots<0> {};
class AIUpdateInterfaceSlots : public Rva0046A10DAISlots<110>
{
public:
    virtual bool gap110() = 0;
    virtual bool slot111() = 0;
};
class AIUpdateInterface : public AIUpdateInterfaceSlots
{
public:
    bool isMoving() const;
    const LocomotorSet &hordeLocomotorSet() const
    {
        return *(const LocomotorSet *)((const char *)this + 0x1CC);
    }
};
class Object
{
public:
    unsigned char m_pad000[0x38];
    Coord3D m_position;
    unsigned char m_pad044[0x258 - 0x44];
    AIUpdateInterface *m_ai;
    const Coord3D *getPosition() const { return &m_position; }
    void rva0028AD32();
    int rva0028B511() const;
    void rva0028ACEE(int position, int layer);
};
#include "../../../Common/Thing/thing.h"
struct Rva0046A10DListNode
{
    Rva0046A10DListNode *next;
    Rva0046A10DListNode *previous;
    Object *object;
};
struct HordeMemberList
{
    Rva0046A10DListNode *sentinel;
};
struct Rva0046247DPair
{
    void *m00;
    HordeMemberList *m04;
};
class Rva0046247D
{
public:
    void rva0046247D(Rva0046247DPair &pair);
};
__declspec(noinline) inline void Rva0046247D::rva0046247D(Rva0046247DPair &result)
{
	void *base = this;
	char *field = (char *)base + 0x20;
	result.m00 = base ? field : 0;
	result.m04 = (HordeMemberList *)((char *)base + 0x54);
}
class TransportContain
{
public:
    virtual void primaryAnchor() = 0;
    unsigned char m_pad004[4];
    Object *m_object;
    unsigned char m_pad00C[0x11C - 0x0C];
};
template <int N> class Rva0046BB38Slots : public Rva0046BB38Slots<N - 1>
{
public:
    virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0046BB38Slots<0> {};
class Rva0046BB38Iface11C : public Rva0046BB38Slots<7>
{
public:
    virtual Coord3D slot7(Object *object, float *angle) = 0;
};
class HordeContain : public TransportContain, public Rva0046BB38Iface11C
{
public:
    void rva0046A10D();
    bool m_120;
    bool m_121;
    unsigned char m_pad122[0x290 - 0x122];
    unsigned int m_290;
    bool m_294;
};
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva0046A10DFrameView
{
    unsigned char m_pad00[0x40];
    unsigned int m_frame;
};
// Logic frames per second, the data row at 0x009BA4E4 (ColdGlobalDwordGetters.cpp).
extern int BfmeLogicFramesPerSecond;
class AI;
extern AI *TheAI;

void HordeContain::rva0046A10D()
{
    Object *owner = m_object;
    AIUpdateInterface *ai = owner->m_ai;
    if (ai->slot111())
    {
        m_290 = ((Rva0046A10DFrameView *)TheGameLogic)->m_frame;
        return;
    }
    if (!m_294)
        return;
    if (m_290 + BfmeLogicFramesPerSecond * 3 >= ((Rva0046A10DFrameView *)TheGameLogic)->m_frame)
        return;
    m_294 = false;
    m_121 = true;
    if (ai->isMoving())
        return;
    m_120 = true;
    Coord3D original;
    original.x = owner->m_position.x;
    original.y = owner->m_position.y;
    original.z = owner->m_position.z;
    Rva0046247DPair pair;
    ((Rva0046247D *)this)->rva0046247D(pair);
    for (Rva0046A10DListNode *it = pair.m04->sentinel->next;
        it != pair.m04->sentinel; it = it->next)
        it->object->rva0028AD32();
    Pathfinder *pathfinder =
        *(Pathfinder **)((char *)TheAI + 0x10);
    pathfinder->AdjustDestination(owner, ai->hordeLocomotorSet(), &original, 0);
    {
        Coord3D delta;
        delta.x = owner->m_position.x;
        delta.y = owner->m_position.y;
        delta.z = owner->m_position.z;
        delta.x -= original.x;
        delta.y -= original.y;
        delta.z -= original.z;
        if (delta.length() > 10.0f && delta.length() < 150.0f)
            ((Thing *)owner)->setPosition(&original);
    }
    for (Rva0046A10DListNode *it = pair.m04->sentinel->next;
        it != pair.m04->sentinel; it = it->next)
    {
        Object *member = it->object;
        float angle = 0.0f;
        Coord3D position = slot7(member, &angle);
        member->rva0028ACEE((int)&position, owner->rva0028B511());
    }
}


#pragma once

// Shared accessed prefixes from the matched traversal, nemesis and contain bodies.
// Traversal proves contain-head +0x10; nemesis methods prove ID/time +0x20/+0x24.
// Object fields retain their existing target offsets; complete types are unknown.

#include <list>
#include "../GameLogicObjectLookupView.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

class Object;
class Player;
class BodyModuleInterface;

// Keep the declaration before its intrinsic pragma when the TU composer hoists
// preprocessor lines. isValidContainerFor uses this existing scheduling barrier.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum ObjectStatusTypes
{
    OBJECT_STATUS_26 = 0x26
};

typedef void (__cdecl *ContainIterateFunc)(Object *object, void *userData);

struct TunnelContainedNode
{
    TunnelContainedNode *m_next;
    TunnelContainedNode *m_prev;
    Object *m_object;
};

// Retail C63230 is the secondary counter interface at primary+4.
// Its source identity is not established; retain a neutral local view.
class TunnelCounter
{
public:
    TunnelCounter() {}
    virtual void rva004F5391(bool) = 0;
};

typedef _STL::list<Object *> ContainedItemsList;

// Primary vtable C63234 (slot 2 returns "TunnelTracker"), secondary C63230.
// The constructor 0x004F55A0 and destructor 0x004F561D prove the lists at
// +0x08/+0x10/+0x14 and the words +0x0C and +0x18..+0x24; xfer 0x004F579C
// orders them as Zero Hour's m_tunnelIDs, m_containList, m_xferContainList,
// m_containListSize and m_tunnelCount, then BFME 2's nemesis ID and time.
class TunnelTracker : public Snapshot, public TunnelCounter
{
public:
    TunnelTracker();
    virtual void rva004F5391(bool);
    int getContainMax() const;
    bool isValidContainerFor(Object *object, bool flag);
    void removeFromContain(ObjectID value, int dummy);
    bool isInContainer(ObjectID value);
    void addToContainList(Object *object);
    void iterateContained(ContainIterateFunc func, void *userData, bool reverse);
    void healObjects(float frames);
    static void healObject(Object *object, void *frames);
    Object *getCurNemesis();
    void updateNemesis(const Object *target);
protected:
    virtual ~TunnelTracker();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
private:
    // The contain list's sentinel node, walked directly by iterateContained.
    TunnelContainedNode *containHead() const { return (TunnelContainedNode *)m_containList._M_node._M_data; }
    _STL::list<int> m_tunnelIDs; // +0x08
    unsigned int m_counter; // +0x0C, rva004F5391
    ContainedItemsList m_containList; // +0x10
    _STL::list<int> m_xferContainList; // +0x14
    int m_containListSize; // +0x18
    unsigned int m_tunnelCount; // +0x1C
    int m_curNemesisID; // +0x20
    unsigned int m_nemesisTimestamp; // +0x24
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	BodyModuleInterface *getBodyModule() const { return m_body; }
	void rva0028FB6F(void *param);
	bool rva002943B2(const Player *viewer);
	bool isEffectivelyDead() const { return (m_deadFlag & 1) != 0; }
	int getID() const { return m_id; }
	void onContainedBy(Object *container);
	void rva0028BAC0(); // 0x0028BAC0
	Drawable *getDrawable() const;
	void leaveGroup();
	// The tunnel this object is contained by (+0x274).
	const Object *tunnelContainer() const { return (const Object *)m_274; }
	char m_pad00[4];
	void *m_template;
	char m_pad08[0x74 - 8];
	int m_id;
	char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body; // +0x254, healing callback
	char m_pad258[0x274 - 0x258];
	void *m_274;
	char m_pad278[4];
	unsigned int m_containedByFrame; // +0x27C, healing callback
	char m_pad280[0x438 - 0x280];
	unsigned char m_deadFlag;
};

// Shared accessed prefix: getContainMax and isValidContainerFor read +0xA98.
class GlobalData
{
public:
    char m_pad00[0xA98];
    int m_maxTunnelCapacity;
};


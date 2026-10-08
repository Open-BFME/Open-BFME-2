// ?rva0046A10D@HordeContain@@QAEXXZ
// partial score=0.94 date=2026-10-08
// cl: /DNDEBUG /MD
//
// Target evidence: the existing ModuleFactory callback pin and its registry
// dispatch establish this as a three-argument cdecl callback. At 0x00469B9F it
// forwards those arguments to the sibling callback 0x00467564, then walks the
// four-byte range beginning at argument 1 +0x218 and ending at +0x21C. Each
// element address is passed to the rowed ThingFactory::findTemplate through
// TheThingFactory (VA 0x00DFF000); a non-null result receives arguments 2 and 3
// at 0x0033CF34. The range element type and the final callee's target identity
// remain unresolved.
//
// The `Rva0020AA00Target::notify` spelling below is carried by the pre-existing
// 0x0033CF34 donor pin. It supplies the call ABI and symbol binding only; this
// caller does not establish that class or method's target identity.

class AsciiString;
class ThingTemplate;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

void __cdecl ModuleFactoryHookAt00467564(void *owner, int value, void *context);

class Rva0020AA00Target
{
public:
	void notify(int value, int context);
};

class ModuleFactoryHookRange
{
public:
	unsigned char m_pad000[0x218];
	unsigned char *m_begin;
	unsigned char *m_end;
};

class Rva002CA9CA
{
public:
	void rva002CAC6E(int value, int context);
};

struct ModuleFactoryStringListNode
{
	ModuleFactoryStringListNode *m_next;
	ModuleFactoryStringListNode *m_previous;
};

struct GameLODManagerHookView
{
	unsigned char m_pad000[0x1774];
	int m_1774;
};

class GameLODManager;
extern GameLODManager *TheGameLODManager;

struct AIHookInnerView
{
	unsigned char m_pad000[0xBB];
	unsigned char m_BB;
};

struct AIHookView
{
	unsigned char m_pad000[0x18];
	AIHookInnerView *m_18;
};

class AI;
extern AI *TheAI;

// ?ModuleFactoryHookAt00467564@@YAXPAXH0@Z
// Target evidence: the TransportContain registration at ModuleFactory::init
// (0x00257CB8) supplies this three-argument callback. Its body reads the
// eight-byte list through module-data +0xA4, resolves each stored AsciiString
// through TheThingFactory, and calls the rowed 0x0033CF34 target with the
// callback integer and a byte initialized from the context. A second target
// gate reads GameLODManager +0x1774, the template bytes +0x109/+0x113, and
// TheAI +0x18/+0xBB. If module-data +0x144 is non-null, retail also calls
// 0x002CAC6E with the original integer and context.
//
// Donor evidence: GeneralsMD TransportContainModuleData::InitialPayload
// establishes the payload-name role in this subsystem. The donor stores one
// name/count pair; BFME2's +0xA4 list and eight-byte elements come from target
// bytes and the matched module-data constructor, so the donor layout is not
// copied here. The 0x0033CF34 pin supplies a callable name/ABI only; its target
// identity and the meaning of the byte tests remain unresolved.
void __cdecl ModuleFactoryHookAt00467564(void *owner, int value, void *context)
{
	unsigned char lowDetailPayload = 0;
	GameLODManagerHookView *lod = (GameLODManagerHookView *)TheGameLODManager;
	if (lod && lod->m_1774 < 3)
		lowDetailPayload = 1;

	ModuleFactoryStringListNode *head =
		*(ModuleFactoryStringListNode **)((char *)owner + 0xA4);
	ModuleFactoryStringListNode *entry = head->m_next;
	if (entry != head) {
		do {
			const ThingTemplate *thingTemplate =
				TheThingFactory->findTemplate(*(const AsciiString *)(entry + 1));
			if (thingTemplate) {
				unsigned char notifyContext = *(unsigned char *)context;
				const unsigned char *templateBytes =
					(const unsigned char *)thingTemplate;
				AIHookView *ai = (AIHookView *)TheAI;
				if (lowDetailPayload && !(templateBytes[0x113] & 4)
					&& !(templateBytes[0x109] & 4)
					&& ai->m_18->m_BB)
					notifyContext = 1;
				((Rva0020AA00Target *)thingTemplate)->notify(
					value, (int)&notifyContext);
			}
			entry = entry->m_next;
		} while (entry != *(ModuleFactoryStringListNode **)((char *)owner + 0xA4));
	}

	Rva002CA9CA *extra = *(Rva002CA9CA **)((char *)owner + 0x144);
	if (extra)
		extra->rva002CAC6E(value, (int)context);
}

void __cdecl ModuleFactoryHookAt00469B9F(void *owner, int value, void *context)
{
	ModuleFactoryHookAt00467564(owner, value, context);

	ModuleFactoryHookRange *range = (ModuleFactoryHookRange *)owner;
	unsigned char *element = range->m_begin;
	while (element != range->m_end) {
		const ThingTemplate *thingTemplate =
			TheThingFactory->findTemplate(*(const AsciiString *)element);
		if (thingTemplate)
			((Rva0020AA00Target *)thingTemplate)->notify(value, (int)context);
		element += 4;
	}
}

// cl: /DNDEBUG /MD
// The target's +0x08 owner, +0x120 flags, +0x290 frame, and +0x11C slot-7
// access establish a HordeContain method. Its specific name remains the RVA.
struct Coord3D
{
    float x, y, z;
};
class Object;
class LocomotorSet {};
class Pathfinder
{
public:
    bool adjustDestination(Object *object,
        const LocomotorSet &locomotorSet,
        Coord3D *destination,
        const Coord3D *groupDestination);
};
class Rva0046A10DSlotZero {};
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
    const LocomotorSet &getLocomotorSet() const
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
    void rva0028ACEE(const Coord3D *position, int layer);
};
class Thing
{
public:
    void setPosition(const Coord3D *position);
};
class Rva0055A627Difference
{
public:
    float x, y, z;
    float length() const;
};
struct Rva0046A10DListNode
{
    Rva0046A10DListNode *next;
    Rva0046A10DListNode *previous;
    Object *object;
};
struct Rva0046A10DList
{
    Rva0046A10DListNode *sentinel;
};
struct Rva0046247DPair
{
    void *m00;
    Rva0046A10DList *m04;
};
class Rva0046247D
{
public:
    void *rva0046247D(Rva0046247DPair &pair);
};
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
class GlobalData;
extern GlobalData *TheWritableGlobalData;
extern const int g_009BA4E4;
extern AI *TheAI;

void HordeContain::rva0046A10D()
{
    Object *owner = m_object;
    AIUpdateInterface *ai = owner->m_ai;
    if (ai->slot111())
    {
        m_290 = *(unsigned int *)((char *)TheWritableGlobalData + 0x40);
        return;
    }
    if (!m_294)
        return;
    if (m_290 + g_009BA4E4 * 3 >= *(unsigned int *)((char *)TheWritableGlobalData + 0x40))
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
    pathfinder->adjustDestination(owner, ai->getLocomotorSet(), &original, 0);
    {
        Rva0055A627Difference delta;
        delta.x = owner->m_position.x - original.x;
        delta.y = owner->m_position.y - original.y;
        delta.z = owner->m_position.z - original.z;
        if (delta.length() > 10.0f && delta.length() < 150.0f)
            ((Thing *)owner)->setPosition(&original);
    }
    Rva0046BB38Iface11C *iface = this;
    for (Rva0046A10DListNode *it = pair.m04->sentinel->next;
        it != pair.m04->sentinel; it = it->next)
    {
        Object *member = it->object;
        float angle = 0.0f;
        Coord3D position = iface->slot7(member, &angle);
        member->rva0028ACEE(&position, owner->rva0028B511());
    }
}


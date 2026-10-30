// stlport
// cl: /O1 /Ob1 /d2inlS100 /D_STLP_USE_STATIC_LIB /G7 /arch:SSE /DNDEBUG /MD /EHsc /I.
// Retail: 0x0027893E..0x00278C29 (747 B). WB twin: 0x00CA3700.
// Target offsets are measured from retail; KindOf's 218-bit size has ledger
// support. ZH BitFlags supplies the checked-test semantic guide only.
// Evidence: reverse/attempt_support/drawable-shroud-recovery-20261023/readme.md
#include <bitset>
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Player;
class Drawable;

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int kind) const
	{ return (((const unsigned char *)&m_kindOf)[kind >> 3] & (1 << (kind & 7))) != 0; }
	__forceinline bool testKindInView(int kind) const
	{ return m_kindOf.test(kind); }
	char m_pad000[0x108];
	std::bitset<218> m_kindOf; // +0x108
	char m_pad124[0x59C - 0x124];
	int m_sightedEvent; // +0x59C
	int m_sightedEventAlt; // +0x5A0
	int m_revealedEvent; // +0x5A4
	int m_shroudedEvent; // +0x5A8
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

enum EvaEventID
{
	EVA_EVENT_INVALID = -1
};

class Eva
{
public:
	bool reportEvaEvent(EvaEventID event, const Coord3D *position, const Coord3D *position2);
};
extern Eva *TheEva;

struct ModuleData
{
	char pad[0x4C];
	int m_campSightedEvent; // +0x4C
};

#include "../../Include/Common/Module.h"

// Partial storage view: the canonical base and observed castle member at +0x18.
class Rva0027893EModuleView : public Module
{
public:
	using Module::m_moduleData;
	char pad08[0x18 - 0x08];
	ObjectID m_castleID; // +0x18
};

class Rva003974CE
{
public:
	int apply(int (*func)(Object *obj, int arg), int arg);
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

class Rva004A1828Holder
{
public:
	virtual ObjectID getID();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual bool isReady();
};
struct Rva004A1828Owner;
int Rva004A1828Get(Rva004A1828Owner *owner);

class Object
{
	friend class Drawable;
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	bool rva00294471(void *player, int arg);
	Player *getControllingPlayer() const;
	Drawable *getDrawable() const;
protected:
	Module *findModule(NameKeyType key) const;
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	char m_pad44[0x438 - 0x44];
	unsigned char m_privateStatus; // +0x438
};

class Player
{
public:
	int iterateObjects(int (*func)(Object *obj, void *userData), void *userData) const;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }
private:
	char m_pad000[0x10];
	Player *m_localPlayer; // +0x10
};
extern PlayerList *ThePlayerList;

class Rva00270260
{
public:
	bool rva00270260();
};

class Rva002706A8
{
public:
	void rva002706A8();
};

int rva00272A6A(Object *obj, void *userData);
int rva002706F0(Object *obj, int arg);

class Drawable
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *rva00272AD5();
private:
	void onComingOutOfShroud();
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0xFC - 0x08];
	Object *m_object; // +0xFC
	char m_pad100[0x114 - 0x100];
	unsigned int m_status; // +0x114
	unsigned char m_pad118[0x445 - 0x118];
	bool m_sightReported; // +0x445
	bool m_useAltSightedEvent; // +0x446
};

struct SightedEventData
{
	Drawable *drawable;
	int event;
};

void Drawable::onComingOutOfShroud()
{
	const ThingTemplate *thingTemplate = m_template;

	Object *obj = m_object;

	Player *localPlayer = ThePlayerList ? ThePlayerList->getLocalPlayer() : 0;
	if (!thingTemplate || !obj || !localPlayer || !TheGameLogic || TheGameLogic->getFrame() <= 5)
		return;

	if (obj->rva00294471(localPlayer, 1)) {
		if (!obj->isEffectivelyDead() && thingTemplate->m_sightedEvent != -1 && !thingTemplate->testKindInView(47) && !m_sightReported) {
			Rva004A1828Holder *holder = (Rva004A1828Holder *)Rva004A1828Get((Rva004A1828Owner *)obj);
			bool skip;
			if (holder && holder->isReady()) {
				skip = false;
			} else {
				Player *controller = obj->getControllingPlayer();
				if (controller) {
					int dataEvent = thingTemplate->m_sightedEvent;
					SightedEventData data;
					data.drawable = this;
					data.event = dataEvent;
					if (controller->iterateObjects(rva00272A6A, &data) == 1)
						skip = false;
					else
						skip = true;
				} else {
					skip = true;
				}
			}
			if (!skip) {
				Object *nearest = ((Drawable *)obj)->rva00272AD5();
				if (nearest) {
					int event = thingTemplate->m_sightedEvent;
					if (m_useAltSightedEvent && thingTemplate->m_sightedEventAlt != -1)
						event = thingTemplate->m_sightedEventAlt;
					if (TheEva->reportEvaEvent((EvaEventID)event, nearest->getPosition(), obj->getPosition()) && holder && holder->isReady()) {
						m_sightReported = true;
						Object *holderObject = TheGameLogic->findObjectByID(holder->getID());
						if (holderObject) {
							Drawable *draw = holderObject->getDrawable();
							if (draw)
								((Rva002706A8 *)draw)->rva002706A8();
						}
					}
				}
			}
		}

		int mask80 = 0x80;

		if ((((const unsigned char *)&thingTemplate->m_kindOf)[0] & mask80) && !(m_status & 0x40)) {
			static NameKeyType key_CastleMemberBehavior = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
			Module *member;
			// Equivalent paths preserve VC7.1 allocation costs before tail merging.
			if (m_useAltSightedEvent)
				member = obj->findModule(key_CastleMemberBehavior);
			else
				member = obj->findModule(key_CastleMemberBehavior);
			if (member) {
				Object *castle = TheGameLogic->findObjectByID(((Rva0027893EModuleView *)member)->m_castleID);
				if (castle) {
					Module *castleBehavior = castle->findModule(CastleBehavior::rva0003955DA());
					if (castleBehavior) {
						int event = ((Rva0027893EModuleView *)castleBehavior)->m_moduleData->m_campSightedEvent;
						if (event != -1) {
							Drawable *castleDraw = castle->getDrawable();
							if (castleDraw) {
								if (!(castleDraw->m_status & 0x40)) {
									Object *nearest = ((Drawable *)obj)->rva00272AD5();
									if (nearest)
										TheEva->reportEvaEvent((EvaEventID)event, nearest->getPosition(), obj->getPosition());
								}
								((Rva003974CE *)castleBehavior)->apply(rva002706F0, 0);
							}
						}
					}
				}
			}
		}

		if (!(m_status & mask80) && !obj->isEffectivelyDead()) {
			m_status |= mask80;
			int event = thingTemplate->m_revealedEvent;
			if (event != -1) {
				Object *nearest = ((Drawable *)obj)->rva00272AD5();
				if (nearest)
					TheEva->reportEvaEvent((EvaEventID)event, nearest->getPosition(), obj->getPosition());
			}
		}
	} else {
		if (((Rva00270260 *)this)->rva00270260())
			return;
		int mask80 = 0x80;
		if (!(m_status & mask80) && !obj->isEffectivelyDead()) {
			m_status |= mask80;
			int event = thingTemplate->m_shroudedEvent;
			if (event != -1) {
				Object *nearest = ((Drawable *)obj)->rva00272AD5();
				if (nearest)
					TheEva->reportEvaEvent((EvaEventID)event, nearest->getPosition(), obj->getPosition());
			}
		}
	}
}

// Native 0x272A6A callback retains its original independent target evidence.
struct BfmeDrawableSightedView
{
	char pad000[0x440];
	unsigned char obscured;
};

int rva00272A6A(Object *object, void *userData)
{
    if (!object) goto reject;
    Drawable *drawable = object->getDrawable();
    SightedEventData *context = (SightedEventData *)userData;
    if (drawable == context->drawable || !drawable ||
        ((BfmeDrawableSightedView *)drawable)->obscured) goto reject;
    const ThingTemplate *thingTemplate = drawable->getTemplate();
    if (!thingTemplate || thingTemplate->m_sightedEvent != context->event ||
        object->isEffectivelyDead()) goto reject;
    if (!object->rva00294471(ThePlayerList->getLocalPlayer(), 1)) goto reject;
    if (object->getTemplate()->isKindOf(47)) goto reject;
    return 0;
reject:
    return 1;
}

// Native2706F0..27070C: complete28B cdecl callback; its address is passed
// by the native onComingOutOfShroud body at278B90 to the member iterator.
// Existing72B owner2706A8 ends immediately before it; rowed74B27070C
// begins immediately after it. The callback sets the drawable status bit40
// and returns1. Its original name and the unused second argument are unknown.
struct BfmeDrawableStatus114View
{
    char pad000[0x114];
    unsigned int status;
};
int rva002706F0(Object *object, int unused)
{
    if (object)
    {
        Drawable *drawable = object->getDrawable();
        if (drawable)
            ((BfmeDrawableStatus114View *)drawable)->status |= 0x40;
    }
    return 1;
}

// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/GameEngine/Source/Common
// ?update@PropagandaTowerBehavior@@UAE?AW4UpdateSleepTime@@XZ
// Retail 0x00481C0C..0x00481D4C, 320 bytes. Reference: Zero Hour
// GeneralsMD PropagandaTowerBehavior.cpp update, BFME1 revision 575ba2b04.
// Target vtable/neighbour class evidence: pool key, ctor and slot13
// removeAllInfluence / slot14 doScan. Native entry is the +0x10 update
// interface: module data at this-0x0C, owner at this-8, frame at this+0x14,
// tracker list at this+0x18; its primary vtable starts at this-0x10.
// Target Object disability+0x1C8, containment+0x274, dead byte+0x438,
// and template kind word+0x10C are established by this body's accesses.
// Kind bit meanings are kept unspecified. Splitting its four-bit mask
// into low-byte and high-byte groups reproduces retail's test cl/test ch.
#include "Common/Snapshot.h"
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
class Player;
class UpgradeTemplate;
class Rva0028ADECmpBoolField;
class FXList;
class MultiIniFieldParse;
class ModuleData;
class Thing;
class BodyModule;
typedef unsigned int UnsignedInt;
extern GameLogic *TheGameLogic;

enum ObjectStatusTypes { STATUS_BUILDING = 2, STATUS_SOLD = 19 };

template <int N> class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, int);
	bool any() const;
	bool test(const void *) const;
	unsigned words[1];
};

struct ObjectTemplate
{
	char pad[0x10c];
	unsigned kind;
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes) const;
	Player *getControllingPlayer() const;
	bool hasUpgrade(const UpgradeTemplate *upgrade) const;
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	bool attemptHealingFromSoleBenefactor(float amount, const Object *source, UnsignedInt extra);
	// Retail keeps the whole 32-bit flag word live in eax across the test and the
	// set: `mov eax,[esi+0x380]` / `mov ecx,eax` / `shr ecx,8` / `test cl,1` /
	// `jne skip` / `or ah,0x1` / `mov [esi+0x380],eax`. Two facts pin the source:
	// the read-modify-write is on the WORD (a byte-view accessor collapses the
	// block to 195-216B because it drops the shared reload), and the OR is a 2-byte
	// in-place or on `ah` (an `int` shift of the word materialises
	// `or eax,0x100`, 5B, twice in this body).
	bool testWeaponBonusCondition(int bit) const
	{
		return (m_flags380 & (1 << (bit + 8))) != 0;
	}
	void setWeaponBonusCondition(int bit)
	{
		m_flags380 |= (1 << (bit + 8));
	}

	char p00[4];
	ObjectTemplate *tmpl; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos; // +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	char m_pad078[0x1c8 - 0x78];
	BitFlags<11> disabled; // +0x1C8
	char m_pad1cc[0x254 - 0x1cc];
	BodyModule *m_body; // +0x254
	char m_pad258[0x274 - 0x258];
	Object *containedBy; // +0x274
	char m_pad278[0x380 - 0x278];
	UnsignedInt m_flags380; // +0x380
	char m_pad384[0x438 - 0x384];
	unsigned char dead; // +0x438
	char m_pad439[0x484 - 0x439];
};

class __declspec(novtable) PropagandaTowerBehaviorModuleData : public Snapshot
{
public:
	virtual ~PropagandaTowerBehaviorModuleData();
	int m_unused04;
	float m_radius;
	int m_delayBetweenUpdates;
	float m_healPercentEachSecond;
	const FXList *m_pulseFX;
	AsciiString m_upgradeRequired;
	float m_upgradedHealPercentEachSecond;
	const FXList *m_upgradedPulseFX;
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class ObjectTracker
{
public:
	ObjectTracker() : objectID(INVALID_OBJECT_ID), next(0) {}
	virtual ~ObjectTracker() {}
	ObjectID objectID; // +0x04
	ObjectTracker *next; // +0x08
};

enum NameKeyType { NK_UNKNOWN = 0 };

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum SleepyUpdatePhase { PHASE_NORMAL = 2 };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *, const ModuleData *);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	void setWakeFrame(Object *, UpdateSleepTime);
	virtual SleepyUpdatePhase getUpdatePhase() const;
private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class PropagandaTowerBehaviorIface
{
public:
	virtual void slot();
};

class PropagandaTowerBehavior : public UpdateModule, public PropagandaTowerBehaviorIface
{
public:
	PropagandaTowerBehavior(Thing *, const ModuleData *);
	virtual ~PropagandaTowerBehavior();
	virtual UpdateSleepTime update();
protected:
	virtual void xfer(Xfer *xfer);
	virtual void removeAllInfluence();
	virtual void doScan();
	virtual void effectLogic(Object *obj, bool giving, const PropagandaTowerBehaviorModuleData *modData);
private:
	const PropagandaTowerBehaviorModuleData *getPropagandaTowerBehaviorModuleData() const
	{
		return (const PropagandaTowerBehaviorModuleData *)m_moduleData;
	}
	unsigned int m_lastScanFrame; // +0x24
	ObjectTracker *m_insideList;	// +0x28
	const UpgradeTemplate *m_upgradeRequired;	// +0x2C
public:
	virtual NameKeyType getModuleNameKey() const;
};

UpdateSleepTime PropagandaTowerBehavior::update()
{
	const PropagandaTowerBehaviorModuleData *modData = getPropagandaTowerBehaviorModuleData();
	Object *self = m_object;
	if (self->testStatus(STATUS_BUILDING))
		return UPDATE_SLEEP_NONE;
	if (self->testStatus(STATUS_SOLD)) {
		removeAllInfluence();
		return UPDATE_SLEEP_FOREVER;
	}
	if (self->dead & 1)
		return UPDATE_SLEEP_FOREVER;
	if (self->disabled.any()) {
		BitFlags<11> allButHeld(BitFlags<11>::kInit, 3);
		allButHeld.words[0] = ~allButHeld.words[0];
		if (allButHeld.test(&self->disabled)) {
			removeAllInfluence();
			return UPDATE_SLEEP_NONE;
		}
	}
	if (self->containedBy && self->containedBy->containedBy) {
		removeAllInfluence();
		return UPDATE_SLEEP_NONE;
	}
	unsigned currentFrame = TheGameLogic->getFrame();
	if (currentFrame - m_lastScanFrame >= modData->m_delayBetweenUpdates) {
		doScan();
		m_lastScanFrame = currentFrame;
	}
	ObjectTracker *prev = 0;
	for (ObjectTracker *curr = m_insideList, *next; curr; curr = next) {
		next = curr->next;
		Object *obj = TheGameLogic->findObjectByID(curr->objectID);
		if (obj && ((obj->tmpl->kind & 0xa0) || (obj->tmpl->kind & 0x300))) {
			effectLogic(obj, true, getPropagandaTowerBehaviorModuleData());
			prev = curr;
		} else {
			if (prev)
				prev->next = next;
			else
				m_insideList = next;
			::delete curr;
		}
	}
	return UPDATE_SLEEP_NONE;
}

// cl: /O1 /DNDEBUG /MD
// MonsterDockUpdate overrides (vtables installed by the matched ctor
// 0x004A139A: primary 0x00C51D74, DockUpdateInterface at +0x20 0x00C51D18).
// Interface slot names follow the Zero Hour DockUpdateInterface order, which
// the rowed base entries pin down in BFME2 too (slot 2 advanceApproachPosition,
// 3 isClearToEnter, 4 isClearToAdvance, 15 setDockOpen); the base bodies the
// overrides call agree with that order: 0x00589AB1 (slot 8) sets the
// approach-reached bit of the docker's approach index, 0x00589DDD (slot 9)
// sets the docking-active model conditions on both Objects and marks the
// docker inside, 0x00589E77 (slot 13) frees the docker's approach slot and
// active-docker ID. Interface overrides take the +0x20 subobject this
// ([this-0x18] is the Object at +0x08).
//
// Retail 0x004A0E47 (5 bytes), primary slot 1: tail call to
// DockUpdate::loadPostProcess 0x00589909 (reloads the dock positions when the
// byte at +0x50 is set, then tail-jumps UpdateModule::loadPostProcess). The
// same body is the slot-1 entry of SupplyCenterDockUpdate (0x00C51BDC) and
// RepairDockUpdate (0x00C51C80): identical code folded to one copy.
// Retail 0x004A159E (114 bytes), slot 8 onApproachReached.
// Retail 0x004A14A6 (28 bytes), slot 9 onEnterReached.
// Retail 0x004A17C1 (103 bytes), slot 11 onExitReached.
// Retail 0x004A13EA (10 bytes), slot 15 setDockOpen: MonsterDockUpdate keeps
// its own open flag at +0x88 (interface +0x68); slot 14 0x004A13E6 reads it.
//
// Model-condition bits: word array at Object +0x10C, bit = word*32 + bit, the
// notifier 0x0028AE6D runs only when the bit changed (see
// MonsterDockUpdateRva004A1610.cpp).

class Drawable;
class Rva0010CConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[20];
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_03 = 3,
	OBJECT_STATUS_3C = 0x3c
};
enum DisabledType
{
	DISABLED_03 = 3
};
enum DamageType
{
	DAMAGE_08 = 8
};
enum DeathType
{
	DEATH_09 = 9
};
class Thing
{
public:
	Drawable *getDrawable() const;
};
class Object : public Thing
{
public:
	void rva0028AE6D();
	void setStatus(ObjectStatusTypes status, bool set);
	void setDisabled(DisabledType type);
	bool clearDisabled(DisabledType type);
	void kill(DamageType damageType, DeathType deathType);
	unsigned char m_pad000[0x10C];
	Rva0010CConditionBits m_conditionBits; // +0x10C
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
class Drawable
{
public:
	void rva00272A02(bool on);
};
class GameLogic
{
public:
	void deselectObject(Object *obj, unsigned int playerMask, int affectClient);
};
extern GameLogic *TheGameLogic;

class Coord3D;
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	virtual void loadPostProcess();
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};
class DockUpdateInterface
{
public:
	virtual bool isClearToApproach(const Object *docker) const = 0;
	virtual bool reserveApproachPosition(Object *docker, Coord3D *position, int *index) = 0;
	virtual bool advanceApproachPosition(Object *docker, Coord3D *position, int *index) = 0;
	virtual bool isClearToEnter(const Object *docker) const = 0;
	virtual bool isClearToAdvance(const Object *docker, int dockerIndex) const = 0;
	virtual void getEnterPosition(Object *docker, Coord3D *position) = 0;
	virtual void getDockPosition(Object *docker, Coord3D *position) = 0;
	virtual void getExitPosition(Object *docker, Coord3D *position) = 0;
	virtual void onApproachReached(Object *docker) = 0;
	virtual void onEnterReached(Object *docker) = 0;
	virtual void onDockReached(Object *docker) = 0;
	virtual void onExitReached(Object *docker) = 0;
	virtual bool action(Object *docker, Object *drone) = 0;
	virtual void cancelDock(Object *docker) = 0;
	virtual bool isDockOpen() = 0;
	virtual void setDockOpen(bool open) = 0;
};
class DockUpdate : public UpdateModule, public DockUpdateInterface
{
protected:
	virtual void loadPostProcess();
public:
	virtual void onApproachReached(Object *docker);
	virtual void onEnterReached(Object *docker);
	virtual void cancelDock(Object *docker);
protected:
	unsigned char m_pad24[0x88 - 0x24];
};
class MonsterDockUpdate : public DockUpdate
{
protected:
	virtual void loadPostProcess();
public:
	virtual void onApproachReached(Object *docker);
	virtual void onEnterReached(Object *docker);
	virtual void onExitReached(Object *docker);
	virtual void setDockOpen(bool open);
private:
	bool m_dockOpen; // +0x88
};

void MonsterDockUpdate::loadPostProcess()
{
	DockUpdate::loadPostProcess();
}

void MonsterDockUpdate::onApproachReached(Object *docker)
{
	DockUpdate::onApproachReached(docker);
	Object *self = m_object;
	TheGameLogic->deselectObject(docker, 0xfffff, 1);
	self->setStatus(OBJECT_STATUS_03, true);
	self->setStatus(OBJECT_STATUS_3C, true);
	docker->setStatus(OBJECT_STATUS_03, true);
	docker->setStatus(OBJECT_STATUS_3C, true);
	setModelConditionBit(m_object, 9 * 32 + 17);
}

void MonsterDockUpdate::onEnterReached(Object *docker)
{
	m_object->setDisabled(DISABLED_03);
	DockUpdate::onEnterReached(docker);
}

void MonsterDockUpdate::onExitReached(Object *docker)
{
	DockUpdate::cancelDock(docker);
	Object *self = m_object;
	getExitPosition(docker, 0);
	self->setStatus(OBJECT_STATUS_03, false);
	self->clearDisabled(DISABLED_03);
	docker->setStatus(OBJECT_STATUS_03, false);
	docker->setStatus(OBJECT_STATUS_3C, false);
	docker->getDrawable()->rva00272A02(true);
	self->kill(DAMAGE_08, DEATH_09);
}

void MonsterDockUpdate::setDockOpen(bool open)
{
	m_dockOpen = open;
}

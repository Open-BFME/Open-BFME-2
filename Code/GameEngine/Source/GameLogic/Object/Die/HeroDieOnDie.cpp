// cl: /DNDEBUG /MD
//
// HeroDie::onDie, retail 0x004C236A (31 bytes): slot 0 of the class's +0x10
// die-module interface vftable 0x00C5C424 (stored by the matched ctor
// 0x004C2324), so `this` is that subobject (module data at -0x0C, Object at
// -0x08). Runs the static callback 0x004C2299 (48 bytes) over every Object
// of the dying hero's controlling Player with the module data's +0x38
// special-power template: each Object that has a module for that power
// (the pinned Object::getSpecialPowerModule) gets its ready frame set to the
// current frame (interface slot 8, setReadyFrame in the Zero Hour order;
// TheGameLogic +0x40 is the frame). The callback returns 1 to continue
// iteration, matching the native int callback and int result proved by
// PlayerTeamPrototypeQueries.cpp at RVA 0x002AB08B.
class Object;
class DamageInfo;
class SpecialPowerTemplate;
class ModuleData;

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void setReadyFrame(unsigned int frame) = 0;
};

class Player
{
public:
	int iterateObjects(int (*func)(Object *, void *), void *userData) const;	// 0x002AB08B
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *spTemplate) const;	// 0x0028BB9E
};

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	unsigned int m_frame;		// +0x40
};
extern GameLogic *TheGameLogic;

struct HeroDieModuleData
{
	unsigned char m_pad00[0x38];
	const SpecialPowerTemplate *m_specialPowerTemplate;	// +0x38
};

class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

class DieModule : public ModuleBase, public BehaviorModuleInterface, public DieModuleInterface
{
};

class HeroDie : public DieModule
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
private:
	static int rva004C2299(Object *obj, void *userData);
};

int HeroDie::rva004C2299(Object *obj, void *userData)
{
	const SpecialPowerTemplate *spTemplate = (const SpecialPowerTemplate *)userData;
	if (obj && spTemplate)
	{
		SpecialPowerModuleInterface *sp = obj->getSpecialPowerModule(spTemplate);
		if (sp)
			sp->setReadyFrame(TheGameLogic->getFrame());
	}
	return 1;
}

void HeroDie::onDie(const DamageInfo *damageInfo)
{
	const HeroDieModuleData *data = (const HeroDieModuleData *)m_moduleData;
	Player *player = m_object->getControllingPlayer();
	player->iterateObjects(rva004C2299,
		(void *)data->m_specialPowerTemplate);
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModuleFactory's create proc 0x0011E0B0 allocates 0x30 and
// reaches this body, which identifies AudioLoopUpgrade.
//
// Four vftable slots: the UpdateModule base is inline (+0x0C/+0x10 and the
// three member inits), the UpgradeMux base at +0x20 is a real call to the
// independently matched constructor ILT 0x0003D24E, and the interface base at
// +0x28 is inline. The most-derived class then overwrites all four.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class ALU_DeepBase
{
public:
	ALU_DeepBase(Thing *, const ModuleData *);
	virtual ~ALU_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class ALU_Iface1 { public: virtual void slot() = 0; };
class ALU_Iface2 { public: virtual void slot() = 0; };

// The base is retail's UpdateModule: its constructor (0x00253390),
// destructor and setWakeFrame are rowed elsewhere, so they are declared,
// never defined here.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class UpgradeMux
{
public:
	UpgradeMux();
	// Rowed: slot 0 of retail's UpgradeMux table 0x00C5FF10 and of this class's 0x00C58C70.
	virtual bool isAlreadyUpgraded() const;

private:
	bool m_upgradeExecuted;
};

// Slot 0 of the interface table 0x00C1C780 is __purecall.
class ALU_Iface4 { public: virtual void rva004B7E3C(int) = 0; };

class AudioLoopUpgrade : public UpdateModule,
	public UpgradeMux,
	public ALU_Iface4
{
public:
	AudioLoopUpgrade(Thing *, const ModuleData *);
	// Rowed in AudioLoopUpgradeRva004B7E3C.cpp: slot 0 of retail's table 0x00C58C68.
	virtual void rva004B7E3C(int);

private:
	int m_x2c;
};

// ??0AudioLoopUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
AudioLoopUpgrade::AudioLoopUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData), UpgradeMux()
{
	m_x2c = 1;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

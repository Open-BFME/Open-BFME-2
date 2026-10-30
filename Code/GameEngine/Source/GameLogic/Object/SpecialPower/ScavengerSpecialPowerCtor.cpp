// cl: /DNDEBUG /MD
//
// ??0ScavengerSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C4353, 46 bytes.
// ScavengerSpecialPower behavior ctor over the pinned SpecialPowerModule
// intermediate base (0x493C5A, thing plus data): re-stores the primary
// vtable slot and the +0x0C/+0x10 secondary slots, then zeroes the byte at
// +0x34. The rowed name getter
// at 0x4C43BC proves the class; the rowed instance factory 0x251D94 is the
// sole raw caller. Row supersedes the ctor pin.

enum NameKeyType;
class Object;
class Thing;
class ModuleData;


// SpecialPowerModule at RVA 0x00493C5A takes Thing* and ModuleData*.
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
protected:
	unsigned char m_pad14[0x34 - 0x14];
};

class ScavengerSpecialPower : public SpecialPowerModule
{
public:
	ScavengerSpecialPower(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;

private:
	bool m_34; // +0x34
};

// ??0ScavengerSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C4353
ScavengerSpecialPower::ScavengerSpecialPower(Thing *thing, const ModuleData *moduleData)
	: SpecialPowerModule(thing, moduleData)
{
	m_34 = 0;
}

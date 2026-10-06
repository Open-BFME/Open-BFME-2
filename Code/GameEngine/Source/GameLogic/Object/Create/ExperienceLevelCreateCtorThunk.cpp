// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ExperienceLevelCreate module ctor.
// Out-of-line base MI, then three most-derived vtbls at +0/+0xC/+0x10.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class ExperienceLevelCreateIface1
{
public:
	virtual void experienceLevelCreateIface1Anchor();
};

class ExperienceLevelCreateIface2
{
public:
	virtual void experienceLevelCreateIface2Anchor();
};

class ExperienceLevelCreateBase : public BehaviorModule,
	public ExperienceLevelCreateIface1,
	public ExperienceLevelCreateIface2
{
public:
	ExperienceLevelCreateBase(Thing *thing, const ModuleData *moduleData);
};

class ExperienceLevelCreate : public ExperienceLevelCreateBase
{
public:
	ExperienceLevelCreate(Thing *thing, const ModuleData *moduleData);
};

// ??0ExperienceLevelCreate@@QAE@PAVThing@@PBVModuleData@@@Z
ExperienceLevelCreate::ExperienceLevelCreate(Thing *thing, const ModuleData *moduleData)
	: ExperienceLevelCreateBase(thing, moduleData)
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?experienceLevelCreateIface2Anchor@ExperienceLevelCreateIface2@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?experienceLevelCreateIface1Anchor@ExperienceLevelCreateIface1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

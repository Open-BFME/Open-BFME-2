// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SupplyCenterDockUpdate module ctor.
// Out-of-line base MI, then four most-derived vtbls at +0/+0xC/+0x10/+0x20.

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

class SupplyCenterDockUpdateIface1
{
public:
	virtual void supplyCenterDockUpdateIface1Anchor();
};

class SupplyCenterDockUpdateIface2
{
public:
	virtual void supplyCenterDockUpdateIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class SupplyCenterDockUpdateIface3
{
public:
	virtual void supplyCenterDockUpdateIface3Anchor();
};

class SupplyCenterDockUpdateBase : public BehaviorModule,
	public SupplyCenterDockUpdateIface1,
	public SupplyCenterDockUpdateIface2,
	public SupplyCenterDockUpdateIface3
{
public:
	SupplyCenterDockUpdateBase(Thing *thing, const ModuleData *moduleData);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterDockUpdate.h
class SupplyCenterDockUpdate : public SupplyCenterDockUpdateBase
{
public:
	SupplyCenterDockUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0SupplyCenterDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SupplyCenterDockUpdate::SupplyCenterDockUpdate(Thing *thing, const ModuleData *moduleData)
	: SupplyCenterDockUpdateBase(thing, moduleData)
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?supplyCenterDockUpdateIface2Anchor@SupplyCenterDockUpdateIface2@@UAEXXZ=?update@SupplyCenterDockUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?supplyCenterDockUpdateIface1Anchor@SupplyCenterDockUpdateIface1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?supplyCenterDockUpdateIface3Anchor@SupplyCenterDockUpdateIface3@@UAEXXZ=?isClearToApproach@DockUpdate@@UBE_NPBVObject@@@Z")

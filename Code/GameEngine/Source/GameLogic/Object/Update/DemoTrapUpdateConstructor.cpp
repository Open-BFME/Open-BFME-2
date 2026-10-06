// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib

// Module-constructor family shape: an out-of-line ObjectModule base call
// (pinned at 0x000170E4), then UpdateModule's constructor inlined -- its two
// vtables at 0x0c and 0x10 then its three members -- then this class's own
// three vtables.
//
// Here every member store precedes the vtable stores, so the members are plain
// and the vptr stores sink past the whole run. MSVC groups by value: the zeros
// at 0x14, 0x20 and 0x24 first, then the two -1s at 0x18 and 0x1c.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);

	virtual void objectModuleAnchor();		///< vptr at 0x00

	void *m_04;
	void *m_08;								///< ends at 0x0c
};

class BehaviorInterface
{
public:
	virtual void behaviorAnchor() = 0;		///< vptr at 0x0c
};

class UpdateInterface
{
public:
	virtual void updateAnchor() = 0;		///< vptr at 0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule,
	public BehaviorInterface, public UpdateInterface
{
public:
	// Defined once, out of line, in UpdateModuleCtor.cpp (retail 0x00253390): derived
	// ctors call it, and a copy here would offer the link a second, non-retail body.
	UpdateModule(Thing *thing, const ModuleData *moduleData);

	virtual void behaviorAnchor();
	virtual void updateAnchor();

	int m_nextCallFrameAndPhase;			///< 0x14
	int m_indexInLogic;						///< 0x18
	int m_updateState;						///< 0x1c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DemoTrapUpdate.h
class DemoTrapUpdate : public UpdateModule
{
public:
	DemoTrapUpdate(Thing *, const ModuleData *);

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();

	int m_value20;							///< 0x20
	bool m_flag24;							///< 0x24
};

// ??0DemoTrapUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DemoTrapUpdate::DemoTrapUpdate( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
	m_value20 = 0;
	m_flag24 = false;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorAnchor@DemoTrapUpdate@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?objectModuleAnchor@DemoTrapUpdate@@UAEXXZ=??_GRva00495916@@UAEPAXI@Z")

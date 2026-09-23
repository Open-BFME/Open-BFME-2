// cl: /O1 /Oy- /DNDEBUG /MD
// stlport
//
// ??0MineshaftPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00373096, 96 bytes. Behavior-side ctor over the rowed
// UpdateModule base (0x253390, 61B): two derived interfaces at +0x20/+0x24
// (their stores overwrite the re-stored inherited values, UpdateModule
// double-store precedent), the implicit _STL::vector<int> member at +0x28
// builds through the folded Vector_base at 0x211E58 (int spelling reuses
// the existing pin; ProductionQueueHordeContain precedent: only compiler
// stores split setup/call), then the trailing int/byte/byte. Framed via
// /Oy- (the 1-byte allocator temp lives at [ebp+0xF]); no /GX so no EH
// prolog draws. Class size 0x3C proven by the rowed instance factory
// (news 0x3C, sole caller at 0x24B625). Row supersedes the ctor pin.

#include <vector>

class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual void update();
};

class MineshaftPortalInterfaceA
{
public:
	virtual void ifaceA() = 0;
};

class MineshaftPortalInterfaceB
{
public:
	virtual void ifaceB() = 0;
};

class MineshaftPortalBehaviour : public UpdateModule, public MineshaftPortalInterfaceA, public MineshaftPortalInterfaceB
{
public:
	MineshaftPortalBehaviour(Thing *thing, const ModuleData *moduleData);

private:
	_STL::vector<int> m_items28;
	int m_count34;
	unsigned char m_flag38;
	unsigned char m_mode39;
	unsigned char m_pad3A[2];
};

// ??0MineshaftPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z @0x00373096
MineshaftPortalBehaviour::MineshaftPortalBehaviour(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_count34 = 0;
	m_flag38 = 0;
	m_mode39 = 1;
}

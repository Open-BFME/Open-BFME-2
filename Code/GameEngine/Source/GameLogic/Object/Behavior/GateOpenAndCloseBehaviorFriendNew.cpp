// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GateOpenAndCloseBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E28B, 65 bytes. Dedicated TU: retail news 0x4C and runs the
// pinned behavior ctor (0x49889C, MI over UpdateModule plus members) with the
// Thing plus ModuleData args, then returns the new behavior as the secondary
// Module interface at +4 through a null-safe derived-to-base conversion
// (retail neg-sbb-and). Operator new and __EH_prolog resolve via their rows.
// Recipe: DestroyEnvironmentUpdateFriendNew.cpp with an MI second base.
// Class identity is the GateOpenAndCloseBehavior pool key (rowed at 0x498857)
// beside the behavior ctor in the 0x4988xx cluster; the ModuleData triple is
// rowed at 0x498E2E/0x253F0E/0x253F1F.

class Thing;
class ModuleData;

class Module
{
public:
	virtual ~Module();
};

class PrimaryModuleBase
{
public:
	virtual ~PrimaryModuleBase();
};

class GateOpenAndCloseBehavior : public PrimaryModuleBase, public Module
{
public:
	GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_pad[0x4C - 8];
};

// ?friend_newModuleInstance@GateOpenAndCloseBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GateOpenAndCloseBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return new GateOpenAndCloseBehavior(thing, moduleData);
}

// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@InheritUpgradeCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250C8B, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B9428. Class identity is the
// "InheritUpgradeCreate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class InheritUpgradeCreate
{
public:
	InheritUpgradeCreate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@InheritUpgradeCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *InheritUpgradeCreate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new InheritUpgradeCreate(thing, moduleData));
}

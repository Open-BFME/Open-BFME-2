// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SpecialPowerModule@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024DC54, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x493C5A. Class identity is the
// "SpecialPowerModule" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SpecialPowerModule
{
public:
	SpecialPowerModule(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@SpecialPowerModule@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpecialPowerModule::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SpecialPowerModule(thing, moduleData));
}

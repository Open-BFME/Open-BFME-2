// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FellBeastSwoopPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002523B3, 59 bytes. Dedicated TU: retail news 0x8C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C6C1E. Class identity is the
// "FellBeastSwoopPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FellBeastSwoopPower
{
public:
	FellBeastSwoopPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x8C];
};

// ?friend_newModuleInstance@FellBeastSwoopPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FellBeastSwoopPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FellBeastSwoopPower(thing, moduleData));
}

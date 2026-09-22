// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@OCLSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251B52, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C30D8. Class identity is the
// "OCLSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class OCLSpecialPower
{
public:
	OCLSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@OCLSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *OCLSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new OCLSpecialPower(thing, moduleData));
}

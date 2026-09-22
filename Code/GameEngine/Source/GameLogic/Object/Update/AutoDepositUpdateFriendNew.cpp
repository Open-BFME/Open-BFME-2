// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AutoDepositUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E4ED, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x49A20F. Class identity is the
// "AutoDepositUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AutoDepositUpdate
{
public:
	AutoDepositUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@AutoDepositUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AutoDepositUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AutoDepositUpdate(thing, moduleData));
}

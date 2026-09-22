// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GrabPassengerSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252050, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C4FA4. Class identity is the
// "GrabPassengerSpecialPower" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class GrabPassengerSpecialPower
{
public:
	GrabPassengerSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@GrabPassengerSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GrabPassengerSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new GrabPassengerSpecialPower(thing, moduleData));
}

// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GarrisonUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002502A6, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B5839. Class identity is the
// "GarrisonUpgrade" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class GarrisonUpgrade
{
public:
	GarrisonUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@GarrisonUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GarrisonUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new GarrisonUpgrade(thing, moduleData));
}

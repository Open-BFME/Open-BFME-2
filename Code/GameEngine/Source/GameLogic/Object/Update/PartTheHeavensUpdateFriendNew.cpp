// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PartTheHeavensUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F4C5, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4AC998. Class identity is the
// "PartTheHeavensUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class PartTheHeavensUpdate
{
public:
	PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@PartTheHeavensUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PartTheHeavensUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PartTheHeavensUpdate(thing, moduleData));
}

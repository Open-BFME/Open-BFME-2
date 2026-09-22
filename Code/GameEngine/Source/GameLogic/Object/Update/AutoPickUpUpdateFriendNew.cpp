// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AutoPickUpUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E061, 56 bytes. Dedicated TU: retail news 0x2C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x495D31. Class identity is the
// "AutoPickUpUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AutoPickUpUpdate
{
public:
	AutoPickUpUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2C];
};

// ?friend_newModuleInstance@AutoPickUpUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AutoPickUpUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AutoPickUpUpdate(thing, moduleData));
}

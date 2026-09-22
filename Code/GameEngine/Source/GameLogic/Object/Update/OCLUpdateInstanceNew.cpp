// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@OCLUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E59B, 56 bytes. Dedicated TU: retail news 0x2C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x49B381. Class identity is the
// "OCLUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class OCLUpdate
{
public:
	OCLUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2C];
};

// ?friend_newModuleInstance@OCLUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *OCLUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new OCLUpdate(thing, moduleData));
}

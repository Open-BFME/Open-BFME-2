// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ProneUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E8E0, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x49FF06. Class identity is the
// "ProneUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ProneUpdate
{
public:
	ProneUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@ProneUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ProneUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ProneUpdate(thing, moduleData));
}

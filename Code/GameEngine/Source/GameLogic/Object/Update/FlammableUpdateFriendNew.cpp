// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FlammableUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D030, 56 bytes. Dedicated TU: retail news 0x50 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x48C64F. Class identity is the
// "FlammableUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FlammableUpdate
{
public:
	FlammableUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x50];
};

// ?friend_newModuleInstance@FlammableUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FlammableUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FlammableUpdate(thing, moduleData));
}

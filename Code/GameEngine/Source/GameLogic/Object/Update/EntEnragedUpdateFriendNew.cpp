// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@EntEnragedUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FB47, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B2516. Class identity is the
// "EntEnragedUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class EntEnragedUpdate
{
public:
	EntEnragedUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@EntEnragedUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *EntEnragedUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new EntEnragedUpdate(thing, moduleData));
}

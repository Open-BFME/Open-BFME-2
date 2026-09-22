// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RadiateFearUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E6B0, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x49C106. Class identity is the
// "RadiateFearUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RadiateFearUpdate
{
public:
	RadiateFearUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@RadiateFearUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RadiateFearUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RadiateFearUpdate(thing, moduleData));
}

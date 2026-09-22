// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PillageModule@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C77B, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x484F0D. Class identity is the
// "PillageModule" literal ModuleFactory registers alongside this stub and the
// PillageModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class PillageModule
{
public:
	PillageModule(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@PillageModule@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PillageModule::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PillageModule(thing, moduleData));
}

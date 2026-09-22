// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@OilSpillUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CFA7, 56 bytes. Dedicated TU: retail news 0x38 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x48C1F7. Class identity is the
// "OilSpillUpdate" literal ModuleFactory registers alongside this stub and the
// OilSpillUpdateModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class OilSpillUpdate
{
public:
	OilSpillUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x38];
};

// ?friend_newModuleInstance@OilSpillUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *OilSpillUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new OilSpillUpdate(thing, moduleData));
}

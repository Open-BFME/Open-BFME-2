// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GeometryUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025060A, 56 bytes. Dedicated TU: retail news 0x20 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B6A5E. Class identity is the
// "GeometryUpgrade" literal ModuleFactory registers alongside this stub and the
// GeometryUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class GeometryUpgrade
{
public:
	GeometryUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x20];
};

// ?friend_newModuleInstance@GeometryUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GeometryUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new GeometryUpgrade(thing, moduleData));
}

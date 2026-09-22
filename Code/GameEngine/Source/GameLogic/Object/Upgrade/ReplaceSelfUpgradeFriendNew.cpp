// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ReplaceSelfUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250696, 56 bytes. Dedicated TU: retail news 0x20 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B7045. Class identity is the
// "ReplaceSelfUpgrade" literal ModuleFactory registers alongside this stub and the
// ReplaceSelfUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ReplaceSelfUpgrade
{
public:
	ReplaceSelfUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x20];
};

// ?friend_newModuleInstance@ReplaceSelfUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ReplaceSelfUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ReplaceSelfUpgrade(thing, moduleData));
}

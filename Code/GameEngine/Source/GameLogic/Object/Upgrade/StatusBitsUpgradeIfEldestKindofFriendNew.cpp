// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StatusBitsUpgradeIfEldestKindof@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250076, 56 bytes. Dedicated TU: retail news 0x20 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B4A32. Class identity is the
// "StatusBitsUpgradeIfEldestKindof" literal ModuleFactory registers alongside this stub and the
// StatusBitsUpgradeIfEldestKindofModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class StatusBitsUpgradeIfEldestKindof
{
public:
	StatusBitsUpgradeIfEldestKindof(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x20];
};

// ?friend_newModuleInstance@StatusBitsUpgradeIfEldestKindof@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *StatusBitsUpgradeIfEldestKindof::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StatusBitsUpgradeIfEldestKindof(thing, moduleData));
}

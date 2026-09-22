// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CommandPointsUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002508EE, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B8661. Class identity is the
// "CommandPointsUpgrade" literal ModuleFactory registers alongside this stub and the
// CommandPointsUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CommandPointsUpgrade
{
public:
	CommandPointsUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@CommandPointsUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CommandPointsUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CommandPointsUpgrade(thing, moduleData));
}

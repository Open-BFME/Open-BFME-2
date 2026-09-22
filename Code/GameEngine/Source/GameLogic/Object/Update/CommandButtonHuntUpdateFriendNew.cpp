// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CommandButtonHuntUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024DF4F, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4952CF. Class identity is the
// "CommandButtonHuntUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CommandButtonHuntUpdate
{
public:
	CommandButtonHuntUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@CommandButtonHuntUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CommandButtonHuntUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CommandButtonHuntUpdate(thing, moduleData));
}

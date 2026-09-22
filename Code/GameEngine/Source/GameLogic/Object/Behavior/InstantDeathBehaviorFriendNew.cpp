// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@InstantDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B1DB, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x45CF55. Class identity is the
// "InstantDeathBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class InstantDeathBehavior
{
public:
	InstantDeathBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@InstantDeathBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *InstantDeathBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new InstantDeathBehavior(thing, moduleData));
}

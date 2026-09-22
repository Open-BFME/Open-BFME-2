// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CivilianSpawnUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BF24, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x47F9D4. Class identity is the
// "CivilianSpawnUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CivilianSpawnUpdate
{
public:
	CivilianSpawnUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@CivilianSpawnUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CivilianSpawnUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CivilianSpawnUpdate(thing, moduleData));
}

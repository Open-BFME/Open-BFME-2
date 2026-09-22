// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@MissileUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EF65, 59 bytes. Dedicated TU: retail news 0xD0 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4A75B9. Class identity is the
// "MissileUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class MissileUpdate
{
public:
	MissileUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xD0];
};

// ?friend_newModuleInstance@MissileUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *MissileUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new MissileUpdate(thing, moduleData));
}

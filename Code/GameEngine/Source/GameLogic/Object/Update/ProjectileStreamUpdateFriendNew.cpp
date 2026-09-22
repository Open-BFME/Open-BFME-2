// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ProjectileStreamUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FC59, 59 bytes. Dedicated TU: retail news 0x8C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x33EE25. Class identity is the
// "ProjectileStreamUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ProjectileStreamUpdate
{
public:
	ProjectileStreamUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x8C];
};

// ?friend_newModuleInstance@ProjectileStreamUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ProjectileStreamUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ProjectileStreamUpdate(thing, moduleData));
}

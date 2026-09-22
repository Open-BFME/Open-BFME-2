// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@LifetimeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E36B, 56 bytes. Dedicated TU: retail news 0x2C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x3A4B58. Class identity is the
// "LifetimeUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class LifetimeUpdate
{
public:
	LifetimeUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2C];
};

// ?friend_newModuleInstance@LifetimeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LifetimeUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new LifetimeUpdate(thing, moduleData));
}

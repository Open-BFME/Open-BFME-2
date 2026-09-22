// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StrafeAreaUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D6FF, 56 bytes. Dedicated TU: retail news 0x48 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x3A4D23. Class identity is the
// "StrafeAreaUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class StrafeAreaUpdate
{
public:
	StrafeAreaUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x48];
};

// ?friend_newModuleInstance@StrafeAreaUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *StrafeAreaUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StrafeAreaUpdate(thing, moduleData));
}

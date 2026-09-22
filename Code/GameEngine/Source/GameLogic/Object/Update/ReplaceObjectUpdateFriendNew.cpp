// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ReplaceObjectUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FCAF, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4B2987. Class identity is the
// "ReplaceObjectUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ReplaceObjectUpdate
{
public:
	ReplaceObjectUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@ReplaceObjectUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ReplaceObjectUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ReplaceObjectUpdate(thing, moduleData));
}

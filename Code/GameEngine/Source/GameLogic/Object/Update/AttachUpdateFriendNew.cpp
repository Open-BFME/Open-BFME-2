// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AttachUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D89A, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x491A0F. Class identity is the
// "AttachUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AttachUpdate
{
public:
	AttachUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@AttachUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AttachUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AttachUpdate(thing, moduleData));
}

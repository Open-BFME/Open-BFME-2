// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@EvaAnnounceClientCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252A50, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C99D4. Class identity is the
// "EvaAnnounceClientCreate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class EvaAnnounceClientCreate
{
public:
	EvaAnnounceClientCreate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@EvaAnnounceClientCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *EvaAnnounceClientCreate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new EvaAnnounceClientCreate(thing, moduleData));
}

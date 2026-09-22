// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ShareExperienceBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BFAD, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x47FEED. Class identity is the
// "ShareExperienceBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ShareExperienceBehavior
{
public:
	ShareExperienceBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@ShareExperienceBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ShareExperienceBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ShareExperienceBehavior(thing, moduleData));
}

// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AssistedTargetingUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CC11, 56 bytes. Dedicated TU: retail news 0x20 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x486E8D. Class identity is the
// "AssistedTargetingUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AssistedTargetingUpdate
{
public:
	AssistedTargetingUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x20];
};

// ?friend_newModuleInstance@AssistedTargetingUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AssistedTargetingUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AssistedTargetingUpdate(thing, moduleData));
}

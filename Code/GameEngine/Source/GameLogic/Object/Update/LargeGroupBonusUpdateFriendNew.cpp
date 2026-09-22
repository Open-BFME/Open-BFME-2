// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@LargeGroupBonusUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D407, 56 bytes. Dedicated TU: retail news 0x2C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4900B1. Class identity is the
// "LargeGroupBonusUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class LargeGroupBonusUpdate
{
public:
	LargeGroupBonusUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x2C];
};

// ?friend_newModuleInstance@LargeGroupBonusUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *LargeGroupBonusUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new LargeGroupBonusUpdate(thing, moduleData));
}

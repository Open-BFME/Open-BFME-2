// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DelayedUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FEC3, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B3C75. Class identity is the
// "DelayedUpgrade" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DelayedUpgrade
{
public:
	DelayedUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@DelayedUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DelayedUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DelayedUpgrade(thing, moduleData));
}

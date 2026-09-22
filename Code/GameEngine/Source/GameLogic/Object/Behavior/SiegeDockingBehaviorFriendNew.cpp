// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SiegeDockingBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AF24, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x45996C. Class identity is the
// "SiegeDockingBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SiegeDockingBehavior
{
public:
	SiegeDockingBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@SiegeDockingBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SiegeDockingBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SiegeDockingBehavior(thing, moduleData));
}

// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SiegeAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024D490, 59 bytes. Dedicated TU: retail news 0x3E4 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x490506. Class identity is the
// "SiegeAIUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SiegeAIUpdate
{
public:
	SiegeAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x3E4];
};

// ?friend_newModuleInstance@SiegeAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SiegeAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SiegeAIUpdate(thing, moduleData));
}

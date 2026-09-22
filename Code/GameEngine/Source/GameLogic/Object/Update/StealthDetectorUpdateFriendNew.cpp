// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@StealthDetectorUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024EBB5, 56 bytes. Dedicated TU: retail news 0x20 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4A2CB9. Class identity is the
// "StealthDetectorUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class StealthDetectorUpdate
{
public:
	StealthDetectorUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x20];
};

// ?friend_newModuleInstance@StealthDetectorUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *StealthDetectorUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new StealthDetectorUpdate(thing, moduleData));
}

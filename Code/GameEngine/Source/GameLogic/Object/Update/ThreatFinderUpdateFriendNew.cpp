// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ThreatFinderUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FBD0, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x3ECCA2. Class identity is the
// "ThreatFinderUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ThreatFinderUpdate
{
public:
	ThreatFinderUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@ThreatFinderUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ThreatFinderUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ThreatFinderUpdate(thing, moduleData));
}

// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AODHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BB25, 59 bytes. Dedicated TU: retail news 0x8E0 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x47B3DB. Class identity is the
// "AODHordeContain" literal ModuleFactory registers alongside this stub and the
// AODHordeContainModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AODHordeContain
{
public:
	AODHordeContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x8E0];
};

// ?friend_newModuleInstance@AODHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AODHordeContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AODHordeContain(thing, moduleData));
}

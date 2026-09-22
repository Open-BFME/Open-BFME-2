// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SlaughterHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C036, 59 bytes. Dedicated TU: retail news 0x9EC (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x48034E. Class identity is the
// "SlaughterHordeContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SlaughterHordeContain
{
public:
	SlaughterHordeContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x9EC];
};

// ?friend_newModuleInstance@SlaughterHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SlaughterHordeContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SlaughterHordeContain(thing, moduleData));
}

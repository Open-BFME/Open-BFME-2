// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HordeTransportContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B9CC, 59 bytes. Dedicated TU: retail news 0x128 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x477003. Class identity is the
// "HordeTransportContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HordeTransportContain
{
public:
	HordeTransportContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x128];
};

// ?friend_newModuleInstance@HordeTransportContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeTransportContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HordeTransportContain(thing, moduleData));
}

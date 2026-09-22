// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SiegeEngineContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BBB4, 59 bytes. Dedicated TU: retail news 0x138 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x47C21E. Class identity is the
// "SiegeEngineContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SiegeEngineContain
{
public:
	SiegeEngineContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x138];
};

// ?friend_newModuleInstance@SiegeEngineContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SiegeEngineContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SiegeEngineContain(thing, moduleData));
}

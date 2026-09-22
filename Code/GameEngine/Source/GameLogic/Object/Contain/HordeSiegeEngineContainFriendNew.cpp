// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HordeSiegeEngineContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BC43, 59 bytes. Dedicated TU: retail news 0x144 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x47D247. Class identity is the
// "HordeSiegeEngineContain" literal ModuleFactory registers alongside this stub and the
// HordeSiegeEngineContainModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HordeSiegeEngineContain
{
public:
	HordeSiegeEngineContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x144];
};

// ?friend_newModuleInstance@HordeSiegeEngineContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeSiegeEngineContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HordeSiegeEngineContain(thing, moduleData));
}

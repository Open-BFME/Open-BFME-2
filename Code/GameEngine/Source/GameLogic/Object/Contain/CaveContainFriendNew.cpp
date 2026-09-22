// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CaveContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B797, 59 bytes. Dedicated TU: retail news 0x10C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x466630. Class identity is the
// "CaveContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CaveContain
{
public:
	CaveContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10C];
};

// ?friend_newModuleInstance@CaveContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CaveContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CaveContain(thing, moduleData));
}

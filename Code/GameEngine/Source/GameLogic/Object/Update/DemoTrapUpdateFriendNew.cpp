// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DemoTrapUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024DFD8, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4959B1. Class identity is the
// "DemoTrapUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DemoTrapUpdate
{
public:
	DemoTrapUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@DemoTrapUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DemoTrapUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DemoTrapUpdate(thing, moduleData));
}

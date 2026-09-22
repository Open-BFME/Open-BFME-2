// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RiderChangeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BD28, 59 bytes. Dedicated TU: retail news 0x148 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x47E268. Class identity is the
// "RiderChangeContain" literal ModuleFactory registers alongside this stub and the
// RiderChangeContainModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RiderChangeContain
{
public:
	RiderChangeContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x148];
};

// ?friend_newModuleInstance@RiderChangeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RiderChangeContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RiderChangeContain(thing, moduleData));
}

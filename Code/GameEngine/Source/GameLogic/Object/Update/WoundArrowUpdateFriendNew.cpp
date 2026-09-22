// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@WoundArrowUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252309, 59 bytes. Dedicated TU: retail news 0x8C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C6905. Class identity is the
// "WoundArrowUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class WoundArrowUpdate
{
public:
	WoundArrowUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x8C];
};

// ?friend_newModuleInstance@WoundArrowUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *WoundArrowUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new WoundArrowUpdate(thing, moduleData));
}

// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@TransportContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B861, 59 bytes. Dedicated TU: retail news 0x11C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x468559. Class identity is the
// "TransportContain" literal ModuleFactory registers alongside this stub and the
// TransportContainModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class TransportContain
{
public:
	TransportContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x11C];
};

// ?friend_newModuleInstance@TransportContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TransportContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TransportContain(thing, moduleData));
}

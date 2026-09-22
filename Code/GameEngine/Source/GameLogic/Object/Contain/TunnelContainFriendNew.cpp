// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@TunnelContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024BCED, 59 bytes. Dedicated TU: retail news 0x9E8 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x47DBF7. Class identity is the
// "TunnelContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class TunnelContain
{
public:
	TunnelContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x9E8];
};

// ?friend_newModuleInstance@TunnelContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TunnelContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TunnelContain(thing, moduleData));
}

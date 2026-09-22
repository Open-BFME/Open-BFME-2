// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GloriousChargeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F5E0, 59 bytes. Dedicated TU: retail news 0x94 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4AD680. Class identity is the
// "GloriousChargeUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class GloriousChargeUpdate
{
public:
	GloriousChargeUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x94];
};

// ?friend_newModuleInstance@GloriousChargeUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GloriousChargeUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new GloriousChargeUpdate(thing, moduleData));
}

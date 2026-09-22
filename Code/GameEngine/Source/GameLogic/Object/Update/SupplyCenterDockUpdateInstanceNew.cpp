// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SupplyCenterDockUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E9D9, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4A0DC7. Class identity is the
// "SupplyCenterDockUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SupplyCenterDockUpdate
{
public:
	SupplyCenterDockUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@SupplyCenterDockUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SupplyCenterDockUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SupplyCenterDockUpdate(thing, moduleData));
}

// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SupplyCenterCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250A99, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B8D81. Class identity is the
// "SupplyCenterCreate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SupplyCenterCreate
{
public:
	SupplyCenterCreate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@SupplyCenterCreate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SupplyCenterCreate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SupplyCenterCreate(thing, moduleData));
}

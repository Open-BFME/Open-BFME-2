// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CallHelpOnDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250F25, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4BB43C. Class identity is the
// "CallHelpOnDamage" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CallHelpOnDamage
{
public:
	CallHelpOnDamage(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@CallHelpOnDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CallHelpOnDamage::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CallHelpOnDamage(thing, moduleData));
}

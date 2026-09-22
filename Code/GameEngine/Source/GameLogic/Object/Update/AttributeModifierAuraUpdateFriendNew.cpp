// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AttributeModifierAuraUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E624, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x49B560. Class identity is the
// "AttributeModifierAuraUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AttributeModifierAuraUpdate
{
public:
	AttributeModifierAuraUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@AttributeModifierAuraUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AttributeModifierAuraUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AttributeModifierAuraUpdate(thing, moduleData));
}

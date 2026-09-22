// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AttributeModifierUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025059A, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B6740. Class identity is the
// "AttributeModifierUpgrade" literal ModuleFactory registers alongside this stub and the
// AttributeModifierUpgradeModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AttributeModifierUpgrade
{
public:
	AttributeModifierUpgrade(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@AttributeModifierUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AttributeModifierUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AttributeModifierUpgrade(thing, moduleData));
}

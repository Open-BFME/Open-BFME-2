// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DeflectSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002520DC, 56 bytes. Dedicated TU: retail news 0x40 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C545D. Class identity is the
// "DeflectSpecialPower" literal ModuleFactory registers alongside this stub and the
// DeflectSpecialPowerModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DeflectSpecialPower
{
public:
	DeflectSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x40];
};

// ?friend_newModuleInstance@DeflectSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DeflectSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DeflectSpecialPower(thing, moduleData));
}

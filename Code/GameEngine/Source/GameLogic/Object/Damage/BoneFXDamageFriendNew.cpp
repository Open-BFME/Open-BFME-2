// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BoneFXDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250D17, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4B979C. Class identity is the
// "BoneFXDamage" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BoneFXDamage
{
public:
	BoneFXDamage(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@BoneFXDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BoneFXDamage::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BoneFXDamage(thing, moduleData));
}

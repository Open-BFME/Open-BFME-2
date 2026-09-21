// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PlayerHealSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025258F, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8) and
// runs the rowed behavior ctor (0x004C7E7E, Rva00493C5A base plus vtable
// re-stores) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// InvisibilityUpdateFriendNew.cpp. Class identity is the PlayerHeal retail
// cluster (pool key rowed at 0x004C7EFB, ModuleData triple rowed at
// 0x004C7E63/0x002525C7/0x004C803A-pin, behavior ctor rowed at 0x004C7E7E).
class Thing;
class ModuleData;
class Module;

class PlayerHealSpecialPower
{
public:
	PlayerHealSpecialPower(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@PlayerHealSpecialPower@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PlayerHealSpecialPower::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PlayerHealSpecialPower(thing, moduleData));
}

// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BloodthirstyUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024A7B0, 56 bytes. Dedicated TU: retail news 0x30 (push-imm8) and
// runs the rowed behavior ctor (0x0044E0AA, UpdateModule base plus explicit
// secondary installs) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// PlayerHealSpecialPowerFriendNew.cpp. Class identity is the Bloodthirsty
// retail cluster (pool key rowed at 0x0044E054, ModuleData triple rowed at
// 0x0044E099/0x0024A7E8/0x0044E2AC, behavior ctor rowed at 0x0044E0AA).
class Thing;
class ModuleData;
class Module;

class BloodthirstyUpdate
{
public:
	BloodthirstyUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x30];
};

// ?friend_newModuleInstance@BloodthirstyUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BloodthirstyUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BloodthirstyUpdate(thing, moduleData));
}

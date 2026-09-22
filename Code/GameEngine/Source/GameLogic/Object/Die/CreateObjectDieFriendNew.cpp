// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CreateObjectDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C889, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8) and
// runs the rowed behavior ctor (0x00485A96, Rva0045CEBDUpdate base plus
// vtable re-stores) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// PlayerHealSpecialPowerFriendNew.cpp. Identity: ModuleFactory registers
// this factory under "CreateObjectDie" (with data factory 0x0024C8C1);
// formerly misnamed CreateObjectDieIfEldestKindof, whose registered
// factories are 0x0024C912/0x0024C94A.
class Thing;
class ModuleData;
class Module;

class CreateObjectDie
{
public:
	CreateObjectDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@CreateObjectDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CreateObjectDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CreateObjectDie(thing, moduleData));
}

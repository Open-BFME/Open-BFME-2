// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CreateObjectDieIfEldestKindof@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C889, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8) and
// runs the rowed behavior ctor (0x00485A96, Rva0045CEBDUpdate base plus
// vtable re-stores) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// PlayerHealSpecialPowerFriendNew.cpp. Class identity is the
// CreateObjectDieIfEldestKindof retail cluster (pool key rowed at 0x00485A2F,
// ModuleData triple rowed at 0x00485A74/0x0024C8C1/0x00485D88-pin, behavior
// ctor rowed at 0x00485A96).
class Thing;
class ModuleData;
class Module;

class CreateObjectDieIfEldestKindof
{
public:
	CreateObjectDieIfEldestKindof(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@CreateObjectDieIfEldestKindof@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CreateObjectDieIfEldestKindof::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CreateObjectDieIfEldestKindof(thing, moduleData));
}

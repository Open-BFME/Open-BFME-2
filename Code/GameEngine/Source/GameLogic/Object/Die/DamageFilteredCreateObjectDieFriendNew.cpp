// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DamageFilteredCreateObjectDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C99B, 56 bytes. Dedicated TU: retail news 0x20 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x485F87. Class identity is the
// "DamageFilteredCreateObjectDie" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DamageFilteredCreateObjectDie
{
public:
	DamageFilteredCreateObjectDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x20];
};

// ?friend_newModuleInstance@DamageFilteredCreateObjectDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DamageFilteredCreateObjectDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DamageFilteredCreateObjectDie(thing, moduleData));
}

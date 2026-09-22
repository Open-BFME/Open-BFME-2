// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CreateObjectDieIfEldestKindof@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C912, 56 bytes. Dedicated TU: retail news 0x18 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x485B4B. Class identity is the
// "CreateObjectDieIfEldestKindof" literal ModuleFactory registers alongside this stub and the
// CreateObjectDieIfEldestKindofModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CreateObjectDieIfEldestKindof
{
public:
	CreateObjectDieIfEldestKindof(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x18];
};

// ?friend_newModuleInstance@CreateObjectDieIfEldestKindof@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CreateObjectDieIfEldestKindof::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CreateObjectDieIfEldestKindof(thing, moduleData));
}

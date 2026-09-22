// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CreateCrateDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C851, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4854F0. Class identity is the
// "CreateCrateDie" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CreateCrateDie
{
public:
	CreateCrateDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@CreateCrateDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CreateCrateDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CreateCrateDie(thing, moduleData));
}

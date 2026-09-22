// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DestroyDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CA70, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x48650E. Class identity is the
// "DestroyDie" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class DestroyDie
{
public:
	DestroyDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@DestroyDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DestroyDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DestroyDie(thing, moduleData));
}

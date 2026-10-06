// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@DestroyEnvironmentUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F43C, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8) and
// runs the rowed Update ctor (0x4AC63A, UpdateModule base plus next-frame plus
// flags) with the Thing plus ModuleData args. Operator new and __EH_prolog
// resolve via their rows. Recipe: PrisonDockUpdateFriendNew.cpp. Class
// identity is the DestroyEnvironmentUpdate retail cluster (pool key rowed at
// 0x4AC686, ModuleData triple rowed at 0x4AC615/0x4AC629/0x24F474).

class Thing;
class ModuleData;
class Module;

class DestroyEnvironmentUpdate
{
public:
	DestroyEnvironmentUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@DestroyEnvironmentUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *DestroyEnvironmentUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new DestroyEnvironmentUpdate(thing, moduleData));
}

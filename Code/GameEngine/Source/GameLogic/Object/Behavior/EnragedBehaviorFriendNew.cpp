// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@EnragedBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024AD89, 56 bytes. Dedicated TU: retail news 0x24 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x458FA3. Class identity is the
// "EnragedBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class EnragedBehavior
{
public:
	EnragedBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x24];
};

// ?friend_newModuleInstance@EnragedBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *EnragedBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new EnragedBehavior(thing, moduleData));
}

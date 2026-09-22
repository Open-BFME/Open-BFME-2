// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ReflectDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250D8A, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4BABB4. Class identity is the
// "ReflectDamage" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class ReflectDamage
{
public:
	ReflectDamage(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@ReflectDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ReflectDamage::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ReflectDamage(thing, moduleData));
}

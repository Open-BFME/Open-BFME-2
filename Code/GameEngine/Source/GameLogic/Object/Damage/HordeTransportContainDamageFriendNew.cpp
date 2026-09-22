// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HordeTransportContainDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250E9C, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4BB130. Class identity is the
// "HordeTransportContainDamage" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HordeTransportContainDamage
{
public:
	HordeTransportContainDamage(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@HordeTransportContainDamage@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HordeTransportContainDamage::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HordeTransportContainDamage(thing, moduleData));
}

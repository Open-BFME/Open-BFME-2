// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@SymbioticStructuresBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00251520, 59 bytes. Dedicated TU: retail news 0x10C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C0AF1. Class identity is the
// "SymbioticStructuresBody" literal ModuleFactory registers alongside this stub and the
// SymbioticStructuresBodyModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class SymbioticStructuresBody
{
public:
	SymbioticStructuresBody(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10C];
};

// ?friend_newModuleInstance@SymbioticStructuresBody@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SymbioticStructuresBody::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new SymbioticStructuresBody(thing, moduleData));
}

// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CrushDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024CA38, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4862E1. Class identity is the
// "CrushDie" literal ModuleFactory registers alongside this stub and the
// CrushDieModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CrushDie
{
public:
	CrushDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@CrushDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CrushDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CrushDie(thing, moduleData));
}

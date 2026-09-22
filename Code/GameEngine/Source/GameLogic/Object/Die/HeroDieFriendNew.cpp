// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@HeroDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025185B, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4C2324. Class identity is the
// "HeroDie" literal ModuleFactory registers alongside this stub and the
// SpecialPowerCompletionDieModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class HeroDie
{
public:
	HeroDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@HeroDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *HeroDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new HeroDie(thing, moduleData));
}

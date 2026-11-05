// cl: /O1 /GX /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?friend_newModuleInstance@SpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024A847, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x44EF5E. Class identity is the
// "SpecialAbilityUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

// The rowed owner spelling of the 0x88 constructor (0x44EF5E); the row's own
// class name stays on friend_newModuleInstance.
class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@SpecialAbilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *SpecialAbilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new Rva0044EF5E(thing, moduleData));
}

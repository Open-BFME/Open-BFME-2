// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DStreakDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00064F0F, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0xD02A7. Class identity is the
// "W3DStreakDraw" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

#include "../../../../../Include/W3DDevice/GameClient/Drawable/Draw/W3DStreakDraw.h"

// ?friend_newModuleInstance@W3DStreakDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DStreakDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DStreakDraw(thing, moduleData));
}

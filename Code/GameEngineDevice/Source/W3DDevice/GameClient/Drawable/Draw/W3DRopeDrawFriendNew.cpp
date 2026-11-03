// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@W3DRopeDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "W3DRopeDraw"
// (addModule pairs the name with it). news 0x54 and runs the declared-only
// module ctor, pinned at 0x000CA752.

class Thing;
class ModuleData;
class Module;

#include "../../../../../Include/W3DDevice/GameClient/Module/W3DRopeDrawClass.h"

// ?friend_newModuleInstance@W3DRopeDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DRopeDraw::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new W3DRopeDraw(thing, moduleData));
}

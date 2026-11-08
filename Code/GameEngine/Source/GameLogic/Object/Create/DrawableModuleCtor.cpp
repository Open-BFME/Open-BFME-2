// cl: /Oy- /DNDEBUG /MD /GX /Oi-
//
// ??0DrawableModule@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x00306B19
// (108B). Dedicated TU (its base-callers 0xB19A1/0x252B68/0x362EC7 live in
// other TUs, so this body cannot live with any of them).
//
// Identity evidence (converging, cf. commit note):
//  - BFME1 reference (reference/open-bfme-1/.../Thing/Module.cpp,
//    retained as an unrowed definition there) has exactly one other ctor of this shape:
//    DrawableModule with AsDrawable(thing) in place of AsObject.
//  - Retail calls Thing slot 0x10 here vs slot 8 in the landed ObjectModule
//    twin (AsObject, proven) -- a different AsX helper as the donor demands.
//  - Called as a base by 0xB19A1 (the 12B intermediate behind the
//    client-side LaserUpdate/AnimatedParticleSysBone updates), mirroring how
//    BehaviorModule calls the landed ObjectModule on the logic side.
//  - Adjacent address with sequential vtables (ObjectModule 0xC07E1C,
//    DrawableModule 0xC07E54).
// Same three BFME2 deltas as the ObjectModule twin: slim Module view,
// filler/THROW idiom (same literal, same throw-info address), NDEBUG
// AsDrawable ternary.

class ModuleData;
class Object;
class Drawable;
class Player;
typedef int Bool;

// Retail inlines this existing friend helper at the constructor call site.
class Thing;
__forceinline Drawable *AsDrawable(Thing *thing);
#include "../../../Common/Thing/thing.h"

#include "../../../../Include/Common/DrawableModule.h"

#include "../../../../Include/Common/INI/FieldParse.h"


// ??0DrawableModule@@QAE@PAVThing@@PBVModuleData@@@Z
DrawableModule::DrawableModule(Thing *thing, const ModuleData *moduleData)
	: Module(moduleData)
{
	if (!moduleData) {
		throw INIException(3, "module data may not be null\n");
	}
	m_drawable = AsDrawable(thing);
}

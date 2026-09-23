// cl: /O1 /DNDEBUG /MD
//
// ??0W3DTreeDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000CEB4D,
// 28 bytes. Behavior-side ctor completing the W3DTreeDraw file-unit
// (ModuleData proc/factory/dtor rowed at 0xCED03/0x64C0B/0xCECA6 with the
// ModuleData ctor pinned at 0xCEBBF; behavior instance factory rowed at
// 0x64BD3 news 0xC with this ctor as sole raw caller; name getter rowed at
// 0xCEB69 returning the W3DTreeDraw literal).
//
// Shape: frameless single-base ctor over the rowed DrawModule base 0xB19A1
// (opaque ClientUpdate intermediate, human-readable pin) with the derived
// vtable stored explicitly in the body via pointer cast after the base call
// (Defector precedent: the base size is unknown, so an explicit member would
// misplace the store; no virtuals are declared anywhere so no vtable is
// emitted here; the immediate is DIR32-masked in comparison). Zero new pins
// (base resolves via the existing DrawModule pin).

class Thing;
class ModuleData;

class DrawModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
};

class W3DTreeDraw : public DrawModule
{
public:
	W3DTreeDraw(Thing *thing, const ModuleData *moduleData);
};

// ??0W3DTreeDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0x000CEB4D
W3DTreeDraw::W3DTreeDraw(Thing *thing, const ModuleData *moduleData) :
	DrawModule(thing, moduleData)
{
	*(unsigned int *)this = 0x00BCCCF8;
}

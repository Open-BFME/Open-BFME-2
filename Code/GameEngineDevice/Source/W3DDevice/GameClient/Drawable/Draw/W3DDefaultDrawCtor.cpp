// cl: /O1 /DNDEBUG /MD
//
// ??0W3DDefaultDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000B21B3,
// 28 bytes. Draw-side ctor completing the W3DDefaultDraw file-unit (name
// getter rowed at 0xB2214 returning the W3DDefaultDraw literal; pool key
// rowed at 0xB21CF; behavior instance factory rowed at 0x64863 news 0xC with
// this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the DrawModule base 0xB19A1 with the
// derived vtable stored explicitly in the body via pointer cast after the
// base call (W3DTreeDraw precedent: no virtuals are declared anywhere so no
// vtable is emitted here; the immediate is DIR32-masked in comparison). Zero
// new pins (base resolves via the existing DrawModule pin). Row supersedes
// the ctor pin.

class Thing;
class ModuleData;

class DrawModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
};

class W3DDefaultDraw : public DrawModule
{
public:
	W3DDefaultDraw(Thing *thing, const ModuleData *moduleData);
};

// ??0W3DDefaultDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0xB21B3
W3DDefaultDraw::W3DDefaultDraw(Thing *thing, const ModuleData *moduleData) :
	DrawModule(thing, moduleData)
{
	*(unsigned int *)this = 0x00BC98B0;
}

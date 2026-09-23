// cl: /O1 /DNDEBUG /MD
//
// ??0W3DQuadrupedDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000CA0A4,
// 42 bytes. Draw-side ctor completing the W3DQuadrupedDraw file-unit (name
// getter rowed at 0xCA113 returning the W3DQuadrupedDraw literal; pool key
// rowed at 0xCA0CE; ModuleData pair with ctor rowed at 0x651C2; behavior
// instance factory rowed at 0x649B3 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the W3DScriptedModelDraw base
// 0xC0DD8 with the derived vtable slots stored explicitly in the body via
// pointer casts after the base call (W3DTreeDraw precedent: no virtuals are
// declared anywhere so no vtable is emitted here; the immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the existing
// W3DScriptedModelDraw pin). Row supersedes the ctor pin.

class Thing;
class ModuleData;

class W3DScriptedModelDraw
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);
};

class W3DQuadrupedDraw : public W3DScriptedModelDraw
{
public:
	W3DQuadrupedDraw(Thing *thing, const ModuleData *moduleData);
};

// ??0W3DQuadrupedDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0xCA0A4
W3DQuadrupedDraw::W3DQuadrupedDraw(Thing *thing, const ModuleData *moduleData) :
	W3DScriptedModelDraw(thing, moduleData)
{
	*(unsigned int *)this = 0x00BCBC40;
	*(unsigned int *)((char *)this + 0x0C) = 0x00BCBB78;
	*(unsigned int *)((char *)this + 0x10) = 0x00BCA08C;
}

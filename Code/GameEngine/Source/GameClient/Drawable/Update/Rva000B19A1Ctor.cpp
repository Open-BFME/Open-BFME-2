// cl: /MD /DNDEBUG
//
// ??0DrawModule@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x000B19A1
// (28B). Dedicated TU (its base, DrawableModule 0x306B19, lives in the
// Create TU).
//
// Frameless leaf: DrawableModule base call, then the vtable at VA 0x00BC9690,
// the address every unit that binds DrawModule's vtable reaches
// (reverse/data_ledger.csv: ??_7DrawModule@@6B@). Its callers are DrawModule
// subclasses' ctors -- W3DPropDraw, W3DBuffDraw, W3DDebrisDraw, W3DTreeDraw,
// W3DDefaultDraw, W3DBoatWakeModelDraw, W3DRopeDraw and W3DLightDraw spell it
// DrawModule::DrawModule -- plus W3DTornadoDraw 0xD181D and
// W3DProjectileStreamDraw 0xD1370. W3DPropDraw.cpp and W3DRopeDrawCtor.cpp compile
// Zero Hour's inline DrawModule ctor to these same 28 bytes. Formerly rowed as
// the address-named Rva000B19A1.

class Thing;
class ModuleData;

class DrawableModule
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawableModule();
};

class DrawModule : public DrawableModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawModule();
};

// ??0DrawModule@@QAE@PAVThing@@PBVModuleData@@@Z
DrawModule::DrawModule(Thing *thing, const ModuleData *moduleData)
	: DrawableModule(thing, moduleData)
{
}

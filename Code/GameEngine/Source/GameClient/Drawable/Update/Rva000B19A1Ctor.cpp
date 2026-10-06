// cl: /MD /DNDEBUG
//
// ??0Rva000B19A1@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x000B19A1
// (26B). Dedicated TU (its base-callers live elsewhere; its own base,
// DrawableModule 0x306B19, lives in the Create TU).
//
// Opaque ClientUpdate-derived intermediate base ctor (frameless leaf:
// base call plus vtable 0xBC9690); called this-only with
// (Thing,ModuleData) by AnimatedParticleSysBoneClientUpdate 0xD181D and
// LaserUpdate 0xCA752. Pin-to-row upgrade; identity still unproven.

class Thing;
class ModuleData;

class DrawableModule
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawableModule();
};

class Rva000B19A1 : public DrawableModule
{
public:
	Rva000B19A1(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva000B19A1();
};

// ??0Rva000B19A1@@QAE@PAVThing@@PBVModuleData@@@Z
Rva000B19A1::Rva000B19A1(Thing *thing, const ModuleData *moduleData)
	: DrawableModule(thing, moduleData)
{
}

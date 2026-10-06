// cl: /MD /DNDEBUG
//
// ??0Rva00362EC7@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x00362EC7
// (26B). Dedicated TU (its base-callers live elsewhere; its own base,
// DrawableModule 0x306B19, lives in the Create TU).
//
// Opaque intermediate base ctor (frameless leaf:
// base call plus vtable 0xC170A4); called this-only with
// (Thing,ModuleData) by CommandButtonHuntUpdate. Pin-to-row upgrade;
// identity still unproven.

class Thing;
class ModuleData;

class DrawableModule
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawableModule();
};

class Rva00362EC7 : public DrawableModule
{
public:
	Rva00362EC7(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00362EC7();
};

// ??0Rva00362EC7@@QAE@PAVThing@@PBVModuleData@@@Z
Rva00362EC7::Rva00362EC7(Thing *thing, const ModuleData *moduleData)
	: DrawableModule(thing, moduleData)
{
}

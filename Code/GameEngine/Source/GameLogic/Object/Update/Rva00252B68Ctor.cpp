// cl: /MD /DNDEBUG
//
// ??0Rva00252B68@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x00252B68
// (26B). Dedicated TU (its base-callers live elsewhere; its own base,
// DrawableModule 0x306B19, lives in the Create TU).
//
// Opaque intermediate base ctor (frameless leaf:
// base call plus vtable 0xBEFE48); called this-only with
// (Thing,ModuleData) by 6 module-ctor callers incl
// QueueProductionExitUpdate and BattlePlanUpdate. Pin-to-row upgrade;
// identity still unproven.

class Thing;
class ModuleData;

class DrawableModule
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawableModule();
};

class Rva00252B68 : public DrawableModule
{
public:
	Rva00252B68(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00252B68();
};

// ??0Rva00252B68@@QAE@PAVThing@@PBVModuleData@@@Z
Rva00252B68::Rva00252B68(Thing *thing, const ModuleData *moduleData)
	: DrawableModule(thing, moduleData)
{
}

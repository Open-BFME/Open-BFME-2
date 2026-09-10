// ??0DrawableModule@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.9 date=2026-09-10
// cl: /O1 /DNDEBUG /MD
//
// DrawableModule::DrawableModule, retail 0x006DCD20, 40 bytes.
// Dedicated TU so Module.cpp cannot see this body. Installs the vtable,
// calls the Thing* helper, then forces module flags at +4 to include 0x10.

class Thing;
class ModuleData;

class DrawableModule
{
	virtual void unused();
	int flags;
	void initThing(Thing *thing);

public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
};

DrawableModule::DrawableModule(Thing *thing, const ModuleData *)
{
	Thing *t = thing;
	initThing(t);
	flags = (flags & 0xFE000011) | 0x10;
}

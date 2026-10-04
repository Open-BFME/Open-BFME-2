// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ??0DrawableModule@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x00306B19
// (108B). Dedicated TU (its base-callers 0xB19A1/0x252B68/0x362EC7 live in
// other TUs, so this body cannot live with any of them).
//
// Identity evidence (converging, cf. commit note):
//  - BFME1 reference (reference/open-bfme-1/.../Thing/Module.cpp,
//    present-unmatched there) has exactly one other ctor of this shape:
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

class Thing
{
public:
	virtual void opaqueSlot0(); // slot 0 (unproven)
	virtual void opaqueSlot4(); // slot 4 (unproven)
	virtual Object *asObjectMeth(); // slot 8 (BFME1 name; proven by ObjectModule twin)
	virtual void opaqueSlotC(); // slot 0xC (unproven)
	virtual Drawable *asDrawableMeth(); // slot 0x10 (BFME1 name, position from retail)
};

// Friend-style helper matching BFME1 Thing.h: null-guarded virtual dispatch.
static Drawable *AsDrawable(Thing *thing) { return thing ? thing->asDrawableMeth() : 0; }

class Module
{
public:
	Module(const ModuleData *moduleData) : m_moduleData(moduleData) {}
	~Module();

protected:
	const ModuleData *m_moduleData; // +0
};

class DrawableModule : public Module
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~DrawableModule();
public:
	virtual void onCapture(Player *oldOwner, Player *newOwner) {}
	virtual void onDisabledEdge(Bool nowDisabled) {}

private:
	Drawable *m_drawable; // +4
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};


// ??0DrawableModule@@QAE@PAVThing@@PBVModuleData@@@Z
DrawableModule::DrawableModule(Thing *thing, const ModuleData *moduleData)
	: Module(moduleData)
{
	if (!moduleData) {
		throw INIException(3, "module data may not be null\n");
	}
	m_drawable = AsDrawable(thing);
}

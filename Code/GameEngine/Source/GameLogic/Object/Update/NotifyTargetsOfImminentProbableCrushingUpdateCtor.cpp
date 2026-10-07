// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ??0NotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00253E64, 40 bytes. Behavior-side ctor completing the
// NotifyTargetsOfImminentProbableCrushingUpdate file-unit (poolkey rowed at
// 0x253E8E, name getter rowed at 0x253ED3, behavior instance factory rowed
// at 0x255207 news 0x34 with this ctor as sole raw caller; the Horde twin
// keeps its own poolkey 0x253DB2, factory 0x2551CF and pinned ctor 0x253D88).
//
// Shape: frameless single-base ctor over the rowed UpdateModule base
// 0x253390 with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed UpdateModule spelling).

extern "C" const void *const vtbl_00BEFF90[];  // folded, 80 classes; via ??_7AIGateUpdate@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00BEFF90=??_7AIGateUpdate@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00BF1860[];  // ??_7Rva00253EF5@@6BRva00253EF5_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00BF1860=??_7Rva00253EF5@@6BRva00253EF5_B2@@@")
extern "C" const void *const vtbl_00BF186C[];  // ??_7Rva00253EF5@@6BRva0024A797@@@
#pragma comment(linker, "/alternatename:_vtbl_00BF186C=??_7Rva00253EF5@@6BRva0024A797@@@")

class Thing;
class ModuleData;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
};

class NotifyTargetsOfImminentProbableCrushingUpdate : public UpdateModule
{
public:
	NotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0NotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00253E64
NotifyTargetsOfImminentProbableCrushingUpdate::NotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BF186C);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)vtbl_00BEFF90);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00BF1860);
}

// Native list merge4CEB14 calls this comparator; sort4CEB76 calls that
// merge, and wrapper4CED15 calls the sort. The wrapper's caller4CEDB8 is
// adjacent to the module update4CEE1A, which suggests this subsystem home.
// Native origin0/4 and input positions38/3C prove squared-distance ordering;
// the original comparator class name and module association remain uncertain.
struct Rva004CEAB7Position { char pad[0x38]; float x,y; };
class Rva004CEAB7 {
public:
 bool rva004CEAB7(void *,void *);
 float x,y,z;
};
bool Rva004CEAB7::rva004CEAB7(void *a,void *b)
{
 const Rva004CEAB7Position *left=(const Rva004CEAB7Position *)a;
 const Rva004CEAB7Position *right=(const Rva004CEAB7Position *)b;
 float centerX=x;
 float centerY=y;
 float otherX=centerX;
 float otherY=centerY;
 centerY-=left->y;
 centerX-=left->x;
 otherX-=right->x;
 otherY-=right->y;
 float len1=centerY*centerY+centerX*centerX;
 float len2=otherY*otherY+otherX*otherX;
 if (len1<len2) return true;
 return false;
}

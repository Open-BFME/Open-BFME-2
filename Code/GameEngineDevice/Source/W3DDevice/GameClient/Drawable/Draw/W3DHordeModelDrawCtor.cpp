// cl: /O1 /DNDEBUG /MD
//
// ??0W3DHordeModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00078A82,
// 68 bytes. Behavior-side ctor completing the W3DHordeModelDraw file-unit
// (instance factory rowed at 0x64E80 news 0x2F0+ with this ctor as sole raw
// caller; ModuleData proc/factory rowed at 0x793E5/0x64EBB; pool key rowed at
// 0x78B38; name getter rowed at 0x78B7D returning the W3DHordeModelDraw
// literal; ModuleData ctor pinned at 0x789E3).
//
// Shape: frameless single-base ctor over the pinned W3DScriptedModelDraw base
// 0xC0DD8 (factory-evidenced (Thing*;ModuleData*) ctor) with the derived
// vtable plus its two shared member-subobject vtables stored explicitly in
// the body via pointer casts after the member zeros (Defector precedent: no
// virtuals are declared anywhere so no vtable is emitted here; the
// immediates are DIR32-masked in comparison). The three trailing members at
// +0x2E8 are zeroed from the init list, which the compiler emits before the
// body statements, matching retail order. The global counter bump closes the
// body. Zero new pins (base resolves via the existing pin).

extern "C" const void *const vtbl_00BCA08C[];  // folded, 5 classes; via ??_7Rva000CA119@@6BRva000CA119_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00BCA08C=??_7Rva000CA119@@6BRva000CA119_B2@@@")
extern "C" const void *const vtbl_00BCC588[];  // folded, 3 classes; via ??_7W3DTankDraw@@6BDrawInterfaceA@@@
#pragma comment(linker, "/alternatename:_vtbl_00BCC588=??_7W3DTankDraw@@6BDrawInterfaceA@@@")
extern const void *const g_00BC68F0[];

class Thing;
class ModuleData;

class W3DScriptedModelDraw
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);

private:
	// W3DHordeModelDraw's own first member is at +0x2E8, so this is what
	// sits before it. Only its size is claimed (BFME1 donor has 0x27C of
	// base here; BFME2 retail proves 0x2E8).
	unsigned char m_unmodelled[0x2E8];
};

class W3DHordeModelDraw : public W3DScriptedModelDraw
{
public:
	W3DHordeModelDraw(Thing *thing, const ModuleData *moduleData);

private:
	int m_unmodelled2E8;	// +0x2E8
	int m_unmodelled2EC;	// +0x2EC
	int m_unmodelled2F0;	// +0x2F0
};

// The counter the constructor bumps. Nothing in the image names it; it is
// reached by what this body does to it.
extern int TheW3DHordeModelDrawCount;	// 0x00DE1FB4
// TheW3DHordeModelDrawCount: VA 0xde1fb4 (zero-filled .bss).
int TheW3DHordeModelDrawCount;

// ??0W3DHordeModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0x00078A82
W3DHordeModelDraw::W3DHordeModelDraw(Thing *thing, const ModuleData *moduleData) :
	W3DScriptedModelDraw(thing, moduleData),
	m_unmodelled2E8(0), m_unmodelled2EC(0), m_unmodelled2F0(0)
{
	*(unsigned int *)this = ((unsigned int)g_00BC68F0);
	*(unsigned int *)((char *)this + 0x0C) = ((unsigned int)vtbl_00BCC588);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00BCA08C);
	++TheW3DHordeModelDrawCount;
}

// cl: /O1 /DNDEBUG /MD
//
// ??0W3DSupplyDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000CAE43,
// 56 bytes. Draw-side ctor completing the W3DSupplyDraw file-unit (name
// getter rowed at 0xCAEC0 returning the W3DSupplyDraw literal; pool key rowed
// at 0xCAE7B; ModuleData pair with ctor rowed at 0xCAF17; behavior instance
// factory rowed at 0x64A26 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the W3DScriptedModelDraw base
// 0xC0DD8 with an or-flags word and a zero word plus the derived vtable
// slots stored explicitly in the body via pointer casts after the base call
// (W3DTreeDraw precedent: no virtuals are declared anywhere so no vtable is
// emitted here; the immediates are DIR32-masked in comparison). Zero new pins
// (base resolves via the existing W3DScriptedModelDraw pin). Row supersedes
// the ctor pin.

class Thing;
class ModuleData;

class W3DScriptedModelDraw
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_pad[0x2E8];
};

class W3DSupplyDraw : public W3DScriptedModelDraw
{
public:
	W3DSupplyDraw(Thing *thing, const ModuleData *moduleData);

private:
	int m_flags2E8;
	int m_2EC;
};

// ??0W3DSupplyDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0xCAE43
W3DSupplyDraw::W3DSupplyDraw(Thing *thing, const ModuleData *moduleData) :
	W3DScriptedModelDraw(thing, moduleData)
{
	m_flags2E8 |= -1;
	m_2EC = 0;
	*(unsigned int *)this = 0x00BCBFC0;
	*(unsigned int *)((char *)this + 0x0C) = 0x00BCBEF8;
	*(unsigned int *)((char *)this + 0x10) = 0x00BCA08C;
}

// cl: /O1 /DNDEBUG /MD /GX
//
// ??0GloriousChargeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004AD680,
// 116 bytes. Behavior-side ctor (poolkey rowed; ModuleData ctor rowed;
// factory news fits).
//
// Shape follows the ArrowStormUpdate behavior precedent over the opaque
// Rva0044EF5E base: declared-only base dtor for the single EH state plus
// explicit derived vtable installs plus freelist-node member at +0x88 via
// pinned 0x29FB3B init with the shared ebp+0xF context idiom plus pool reset
// via 0x26549E alias pin. Tail is direct and-imm plus mov-byte (no zero
// register). Zero new pins (all callees rowed/pinned).

class Thing;
class ModuleData;

class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	~Rva0044EF5E();
private:
	char m_pad[0x88];
};

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
};

class GloriousChargeUpdate : public Rva0044EF5E
{
public:
	GloriousChargeUpdate(Thing *thing, const ModuleData *moduleData);
private:
	Rva0029FB3BMember m_88;
	int m_8C;
	unsigned char m_90;
};

// ??0GloriousChargeUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004AD680
GloriousChargeUpdate::GloriousChargeUpdate(Thing *thing, const ModuleData *moduleData) :
	Rva0044EF5E(thing, moduleData)
{
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x88);
	void *context = (void *)((char *)&moduleData + 3);
	*(const void **)this = (const void *)0x00C55118;
	*(const void **)((char *)this + 0x0C) = (const void *)0x00C4D640;
	*(const void **)((char *)this + 0x10) = (const void *)0x00C55108;
	*(const void **)((char *)this + 0x20) = (const void *)0x00C552A4;
	member->init(context);
	m_8C &= 0;
	m_90 = 0;
	member->reset();
}

// cl: /O1 /DNDEBUG /MD
//
// ??0DelayedDeathBody@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C15B9,
// 54 bytes. Behavior-side ctor completing the DelayedDeathBody file-unit
// (ModuleData factory rowed at 0x2515E7 news 0x104 with this pinned 2-arg
// ctor; poolkey rowed at 0x4C161D).
//
// Shape: frameless single-base ctor over the rowed RespawnBody base 0x4C12EB
// (RespawnBodyCtorThunk donor spelling, human-readable row) with three
// explicit vtable stores at +0/+0x0C/+0x10 via byte-wise pointer casts
// (Defector precedent: explicit stores, no virtuals declared anywhere so no
// vtable is emitted here; all three immediates are DIR32-masked in
// comparison) plus two byte zeros at +0x100/+0x101. Flat classes throughout
// keep the body frameless. Factory news 0x104 fits the +0x100 tail (base
// 0x100 plus 4). Zero new pins (base resolves via the existing RespawnBody
// row).

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

class RespawnBody
{
public:
	RespawnBody(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	int m_pad04;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x100 - 0x14];
};

class DelayedDeathBody : public RespawnBody
{
public:
	DelayedDeathBody(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_b100;
	unsigned char m_b101;
	unsigned char m_pad102[2];
};

// ??0DelayedDeathBody@@QAE@PAVThing@@PBVModuleData@@@Z @0x004C15B9
DelayedDeathBody::DelayedDeathBody(Thing *thing, const ModuleData *moduleData) :
	RespawnBody(thing, moduleData)
{
	*(unsigned int *)this = (unsigned int)&s_vtable;
	*(unsigned int *)((char *)this + 0xC) = (unsigned int)&s_secondary0C;
	*(unsigned int *)((char *)this + 0x10) = (unsigned int)&s_secondary10;
	m_b100 = 0;
	m_b101 = 0;
}

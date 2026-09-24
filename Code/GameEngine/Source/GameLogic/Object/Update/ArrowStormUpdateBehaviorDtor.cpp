// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
//
// ??1ArrowStormUpdate@@UAE@XZ, retail 0x004907C0, 49 bytes. Virtual dtor
// shard: ctor TU keeps its verified shape untouched (adding a dtor decl
// there would perturb it), so the class is re-declared here with the ctor
// declared-only and only the dtor defined.
//
// Shape mirrors the ctor: explicit 4 vtable installs (0xC4D700 primary plus
// 0xC4D640/0xC4DEE8/0xC4D61C secondaries) plus freelist-node member at +0x88
// via pool-free 0x268902 pin plus implicit Rva0044EF5E base-dtor tail call.
// Unlike the GloriousCharge/RousingSpeech/DamageField siblings there is NO
// separate reset() call: retail has a single call (lea ecx,[esi+0x88] then
// call 0x268902), and 0x268902 itself calls reset (0x26549E) internally.
//
// Identity proof (upgrades opaque Rva004907C0): ArrowStorm's primary vtable
// 0xC4D700 (installed by the rowed ctor) has slot0 = ??_G at 0x490A58, and
// that ??_G calls 0x4907C0. The 4 installs match the ctor's 4 installs.
// Zero new pins (base dtor via ??1Rva0044EF5E pin, pool-free via Rva00268902
// pin, operator delete rowed).
//
// LEVERS (sibling-proven): (1) base dtor declared VIRTUAL (true UAE spelling,
// shares vfptr so base stays at +0; non-virtual base pushes to +4 with a
// this-adjust). (2) NO explicit base call (explicit doubles with the
// implicit one). (3) /GX- (retail dtor is frameless with no EH prologue;
// /GX adds cookie+frame+states).

class Thing;
class ModuleData;

class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();
private:
	char m_pad[0x88];
};

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
};

class PoolMember
{
public:
	void Rva00268902();
};

class ArrowStormUpdate : public Rva0044EF5E
{
public:
	ArrowStormUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~ArrowStormUpdate();
private:
	Rva0029FB3BMember m_88;
	int m_8C;
	int m_90;
	int m_94;
	unsigned char m_98;
};

void deleteArrowStormUpdate(ArrowStormUpdate *p)
{
	delete p;
}

// ??1ArrowStormUpdate@@UAE@XZ @0x004907C0
ArrowStormUpdate::~ArrowStormUpdate()
{
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x88);
	*(const void **)this = (const void *)0x00C4D700;
	*(const void **)((char *)this + 0x0C) = (const void *)0x00C4D640;
	*(const void **)((char *)this + 0x10) = (const void *)0x00C4DEE8;
	*(const void **)((char *)this + 0x20) = (const void *)0x00C4D61C;
	((PoolMember *)member)->Rva00268902();
}

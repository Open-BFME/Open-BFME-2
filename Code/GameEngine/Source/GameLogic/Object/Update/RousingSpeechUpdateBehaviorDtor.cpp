// cl: /O1 /DNDEBUG /MD /GX- /arch:SSE
//
// ??1RousingSpeechUpdate@@UAE@XZ, retail 0x004ACE96, 60 bytes. Virtual dtor
// shard: ctor TU keeps its verified shape untouched (adding a dtor decl
// there would perturb it), so the class is re-declared here with the ctor
// declared-only and only the dtor defined.
//
// Shape mirrors the ctor: explicit 4 vtable installs plus freelist-node
// member at +0x88 via pinned reset plus pool-free via 0x268902 pin plus
// implicit base-dtor tail call. Zero new pins (all callees rowed/pinned).
//
// LEVERS (probe-proven): (1) base dtor declared VIRTUAL (true UAE spelling,
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

class RousingSpeechUpdate : public Rva0044EF5E
{
public:
	RousingSpeechUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~RousingSpeechUpdate();
private:
	Rva0029FB3BMember m_88;
	int m_8C;
	unsigned char m_90;
	float m_94;
	float m_98;
};

// ??1RousingSpeechUpdate@@UAE@XZ @0x004ACE96
RousingSpeechUpdate::~RousingSpeechUpdate()
{
	Rva0029FB3BMember *member = (Rva0029FB3BMember *)((char *)this + 0x88);
	*(const void **)this = (const void *)0x00C54FE8;
	*(const void **)((char *)this + 0x0C) = (const void *)0x00C4D640;
	*(const void **)((char *)this + 0x10) = (const void *)0x00C54FD8;
	*(const void **)((char *)this + 0x20) = (const void *)0x00C552A4;
	member->reset();
	((PoolMember *)member)->Rva00268902();
}

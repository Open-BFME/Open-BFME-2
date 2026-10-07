// cl: /MD
// ??1Rva005E3258@@UAE@XZ @0x005E3258 14B
// Virtual dtor storing vtable 0x00877BB4 then tail-jmping to member clear
// 0x005E30CE at +4. Layout from retail add ecx 4: Rva005E30CE subobject at +4.
// Caller 0x005E3271 plus chain from 0x005E30CE. Precedent SubtitleEntry 14B tail-jmp.
// Evidence: chain lane; vtable g_00C77BB4; callee rowed.
// The 77B constructor at 0x005E3463 stores this same vtable, allocates 0x34
// bytes, and calls 0x005E328A with this plus its three pointer-sized args.
// Retail data xrefs tie 0x00877BB4 to this dtor/constructor and 0x00877BC0 to
// the inner initializer. The latter's object identity stays address-derived.
class Rva005E328AInner
{
public:
	Rva005E328AInner(void *owner, void *a, void *b, void *c);
	char m_opaque[0x34];
};

class Rva005E30CE
{
public:
	void rva005E30CE();
	void *m_ptr;
};

extern const void *const g_00C77BB4[];

class Rva005E3258
{
public:
	Rva005E3258(void *a, void *b, void *c);
	virtual ~Rva005E3258();
private:
	Rva005E30CE m_04;
};

Rva005E3258::Rva005E3258(void *a, void *b, void *c)
{
	m_04.m_ptr = new Rva005E328AInner(this, a, b, c);
}

Rva005E3258::~Rva005E3258()
{
	m_04.rva005E30CE();
}

// cl: /O2
// 0x007FA990: thiscall constructor. A secondary-base vptr lands at +4,
// then the most-derived vptrs at +0 and +4, then four 16-byte cells at +8
// through a walking pointer, then the argument and trailing zeros.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

class Rva007FA990Base0
{
public:
	virtual void v0();
};

class Rva007FA990Base4
{
public:
	virtual void v4() = 0;
};

struct Rva007FA990Cell
{
	void *a;
	void *b;
	void *c;
	void *d;

	Rva007FA990Cell() throw()
	{
		a = 0;
		b = 0;
		c = 0;
		d = 0;
	}
};

class Rva007FA990 : public Rva007FA990Base0, public Rva007FA990Base4
{
public:
	Rva007FA990(void *arg) throw();
	virtual void v0();
	virtual void v4();

private:
	Rva007FA990Cell m_cells[4];
	void *m_48;
	void *m_4C;
	unsigned char m_50;
	char m_pad51[0x3F];
	unsigned char m_90;
	char m_pad91[0x3F];
	void *m_D0;
	void *m_D4;
};

Rva007FA990::Rva007FA990(void *arg) throw()
{
	m_4C = arg;
	m_48 = 0;
	m_50 = 0;
	m_90 = 0;
	m_D4 = 0;
	m_D0 = 0;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?v4@Rva007FA990@@UAEXXZ=?bfmeFlushVQB@BfmeHubVQB@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?v0@Rva007FA990@@UAEXXZ=?bfmeKillVF@BfmeThingVF@@QAEPAXH@Z")
#pragma comment(linker, "/alternatename:?v0@Rva007FA990Base0@@UAEXXZ=?bfmeKillVF@BfmeThingVF@@QAEPAXH@Z")

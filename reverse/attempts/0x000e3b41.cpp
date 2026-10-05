// ??1Rva000E3B41@@UAE@XZ
// partial score=0.8 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva000E3B41@@UAE@XZ @0x000E3B41 (152B): virtual dtor of the opaque
// 0x3940-byte 4-vtable RenderObj-derived class (base ctor 0x006C9CF calls
// RenderObjClass::ctor 0x0013BF00; vftables 0xBCE788/+0, 0xBCE784/+8,
// 0xBCE77C/+0xC4, 0xBCE76C/+0xC8). Layout read from the dtor stores: base0
// (+0, dtor pinned 0x6D0D7), big base1 (+8..+0xC4), base2 (+0xC4),
// base3 (+0xC8). Dtor resets vftables, runs the shutdown method 0xE14C4,
// clears global 0xDEBC5C, releases the intrusive ref at +0x3938 (dec +4,
// virtual slot 0), frees +0x38C4 start via free 0x30830, destroys the
// +0x38B4 member (rowed ??1Rva0008B470, believed to be ~ObjectCreationList:
// its 19B ctor 0x1F81BF inits a _Vector_base at +0) and base0. Sibling
// init @0x000E3BFE takes a byte, re-stores the vftables, re-inits members
// and publishes this at 0xDEBC5C. Identity unproven (terrain-render width
// class is one hypothesis); address-derived names, opaque views.
struct RvaE3B0
{
	virtual ~RvaE3B0();
	char m_pad04[4];
};

struct RvaE3B1
{
	virtual void rvaE3B1();
	char m_pad04[0xB8];
};

struct RvaE3B2
{
	virtual void rvaE3B2();
};

struct RvaE3B3
{
	virtual void rvaE3B3();
};

struct Rva0008B470
{
	~Rva0008B470();
	char m_pad00[12];
};

struct RvaE3VecBase
{
	void *m_start;
	void *m_finish;
	void *m_end;
};

struct RvaE3Coord
{
	int x;
	int y;
};

struct RvaE3Ref
{
	virtual void release();
	int m_refs;
};

struct RvaE3PadA
{
	~RvaE3PadA() {}
	char m_pad;
};

struct RvaE3PadB
{
	~RvaE3PadB() {}
	char m_pad;
};

extern "C" void __cdecl free(void *block);

extern int g_Va00DEBC5C;

class Rva000E3B41 : public RvaE3B0, public RvaE3B1, public RvaE3B2, public RvaE3B3
{
public:
	virtual ~Rva000E3B41();
	void rva000E14C4();

private:
	char m_padCC[0x3884 - 0xCC];
	void *m_3884;
	char m_pad3888[0x38B4 - 0x3888];
	Rva0008B470 m_38B4;
	char m_38C0;
	char m_pad38C1[3];
	RvaE3VecBase m_38C4;
	RvaE3Coord m_38D0[12];
	char m_3930;
	char m_pad3931[3];
	int m_3934;
	RvaE3Ref *m_3938;
	RvaE3PadA m_padA;
	RvaE3PadB m_padB;
};

Rva000E3B41::~Rva000E3B41()
{
	rva000E14C4();
	g_Va00DEBC5C &= 0;
	RvaE3Ref *p = m_3938;
	if (p)
	{
		if (--p->m_refs == 0)
			p->release();
	}
	void *vecStart = m_38C4.m_start;
	if (vecStart)
		free(vecStart);
}

// cl: /O1 /DNDEBUG /MD
// Dump lane range 13: ??0Rva002EAB6F @0x002EAB6F 127B. 8-arg constructor:
// m0 plus the 0x10-byte Rva002E8BCF member at +0x4 are member-initialized
// (the member-init emits the in-place lea+call with no null check and no
// unwind funclet, which placement new cannot reproduce), then the body
// stores the remaining args and gates the rowed 0x0006E009 dword getter
// on Object+0x258. Identity otherwise unproven; names address-derived.
struct Rva002E8BCFSrc
{
	char _00[0x10];
	int m10;
	char _14;
	bool m15;
};

class Rva002E8BCF
{
public:
	Rva002E8BCF(Rva002E8BCFSrc const *src, bool a, int b, bool c);
	int m0;
	bool m4;
	bool m5;
	int m8;
	bool mC;
};

struct Rva002EAB6FInner
{
	char _00[0x56C];
	int m_56C;
	char _570[0x634 - 0x570];
	unsigned char m_634;
};

class Object
{
public:
	bool rva0028AFBB() const;
	char _00[4];
	Rva002EAB6FInner *m_04;
	char _08[0x258 - 8];
	void *m_258;
};

class Rva0006E009DwordField
{
public:
	int get() const;
};

static unsigned char Rva002EAB6FFlag(const Object *obj)
{
	return obj->m_04->m_634;
}

static int Rva002EAB6FCount(const Object *obj)
{
	return obj->m_04->m_56C;
}

class Rva002EAB6F
{
public:
	Rva002EAB6F(int a1, Rva002E8BCFSrc const *src, unsigned char a3, int a4, Object *obj, unsigned char a6, int a7, int a8);
	int m0;
	Rva002E8BCF m4;
	unsigned char m14;
	unsigned char m15;
	int m18;
	Object *m1C;
	int m20;
	int m24;
	char _28[8];
	int m30;
};

Rva002EAB6F::Rva002EAB6F(int a1, Rva002E8BCFSrc const *src, unsigned char a3, int a4, Object *obj, unsigned char a6, int a7, int a8)
	: m0(a1),
	m4(src,
		Rva002EAB6FFlag(obj) == 0,
		Rva002EAB6FCount(obj) - 1,
		obj->rva0028AFBB())
{
	m14 = a3;
	m15 = a6;
	m18 = a4;
	m20 = a7;
	m1C = obj;
	m30 = a8;
	m24 = obj->m_258 ? ((Rva0006E009DwordField *)obj->m_258)->get() : 0;
}

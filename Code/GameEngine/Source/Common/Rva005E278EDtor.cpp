// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva005E278E@@UAE@XZ @0x005E278E 173B (the pin keeps the opaque spelling).
// Three-base object dtor in the family of Rva005E29CDDtor.cpp: when the +0x18
// reference is held and the +0x10 owner's slot-3 getter (folded forwarder
// 0x005CB265, owner+0x10) still answers it, that object is told through
// 0x005CB260; the build-plot-like object the rowed 0x005E2138 hands back is
// destroyed through its virtual slot 0 (flag 0); the listener base at +0xC is
// dropped from the list at owner+0x0C+0x170[+0x14] through the rowed erase
// 0x002B7250; the +0x18 reference holder releases and the three inline base
// dtors restore their vtables. Identity of the class is unproven.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva004F6966
{
public:
	Rva004F6966() : m_ptr(0) {}
	~Rva004F6966()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
	void *m_ptr;
};

struct Rva005E278EItem
{
	char m_pad[8];
	Rva002B7250 m_holder;
};
struct Rva005E278ERegion
{
	char m_pad[0x170];
	Rva005E278EItem **m_170;
};
struct Rva005E278EOwner
{
	char m_pad[0x0C];
	Rva005E278ERegion *m_0C;
	Rva005CB265 *m_10;
};

class Rva005E278EPlot
{
public:
	virtual ~Rva005E278EPlot();
};

class Rva005E278E;
class Rva005E2138
{
public:
	void *rva005E2138();
};

class Rva005E278EBase0
{
public:
	virtual ~Rva005E278EBase0() {}
private:
	int m_04;
};
class Rva005E278EBase8
{
public:
	virtual ~Rva005E278EBase8() {}
};
class Rva005E278EBaseC
{
public:
	virtual ~Rva005E278EBaseC() {}
};

class Rva005E278E : public Rva005E278EBase0, public Rva005E278EBase8, public Rva005E278EBaseC
{
public:
	virtual ~Rva005E278E();
private:
	Rva005E278EOwner *m_10;
	int m_14;
	Rva004F6966 m_18;
};

Rva005E278E::~Rva005E278E()
{
	void *current = m_18.m_ptr;
	if (current)
	{
		if (m_10->m_10->Rva005CB265::rva005CB265() == (int)current)
			((Rva005CB260 *)m_10->m_10)->rva005CB260();
	}
	((Rva005E278EPlot *)((Rva005E2138 *)this)->rva005E2138())->~Rva005E278EPlot();
	Rva005E278EItem *item = m_10->m_0C->m_170[m_14];
	item->m_holder.rva002B7250((CreateAHeroData *)static_cast<Rva005E278EBaseC *>(this));
}

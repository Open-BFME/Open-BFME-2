// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva005770F7@@UAE@XZ @0x005770F7 142B (the pin keeps the opaque spelling).
// Sibling of Rva00576C4BDtor.cpp (same 0x005CD1A9 / 0x005CD651 / 0x005CD7DA
// members and ptr-chase getters 0x00328A83 + 0x0042D6AE): when the flag at
// +0x38 is set the object reached through the +0x0C record is told through
// its slot 3; then the +0x28 member, the +0x18 and +0x14 wrapped members, the
// +4 base (virtual dtor 0x005CD1A9 out of line) and the empty first base
// unwind. Identity of the class is unproven.
class Rva00328A83PtrChaseField
{
public:
	int get() const;
};
class Rva0042D6AEPtrChaseField
{
public:
	int get() const;
};
class VirtObj005770F7
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
};
struct Inner005770F7
{
	char m_pad[4];
	Rva00328A83PtrChaseField *m_p;
};
class Rva0057702E
{
public:
	void rva0057702E();
	int m_data;
};
struct Wrap1005770F7
{
	~Wrap1005770F7() { m_m.rva0057702E(); }
	Rva0057702E m_m;
};
class Rva005CD7DA
{
public:
	void rva005CD7DA();
	int m_data[4];
};
struct Wrap2005770F7
{
	~Wrap2005770F7() { m_m.rva005CD7DA(); }
	Rva005CD7DA m_m;
};
class Rva005CD651
{
public:
	virtual ~Rva005CD651();
	char m_pad[12];
};
class Rva005CD1A9
{
public:
	virtual ~Rva005CD1A9();
	void *m_ptr;
};
class Base0_005770F7
{
public:
	virtual ~Base0_005770F7() {}
};
class Rva005770F7 : public Base0_005770F7, public Rva005CD1A9
{
public:
	virtual ~Rva005770F7();
private:
	Inner005770F7 *m_s;
	int m_10;
	Wrap1005770F7 m_14;
	Wrap2005770F7 m_18;
	Rva005CD651 m_28;
	bool m_flag38;
};
Rva005770F7::~Rva005770F7()
{
	if (m_flag38) {
		int v1 = m_s->m_p->get();
		int v2 = ((Rva0042D6AEPtrChaseField *)v1)->get();
		if (v2)
			((VirtObj005770F7 *)v2)->f3();
	}
}

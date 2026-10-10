// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva005CE4FA@@UAE@XZ @0x005CE4FA 185B (the pin keeps the opaque spelling).
// Two-base object dtor (first base Rva005E67FE with its dtor called out of
// line, second base at +8 with an inline vtable restore). When the +0x18
// object's const getter 0x004E0625 answers non-zero it drops the +8 base from
// that object's list at +8 (rowed erase 0x002B7250), tells the objects the
// ptr-chase getters 0x0042D6FD / 0x0042D703 / 0x0042D69D reach from +0x10
// through their slots 4, 10 and 2(5), calls 0x004E0750 on the +0x18 object and
// clears the back reference at +0x20+0xC; then the +0x1C owning pointer
// (0x005CE21C) resets. Identity of the class is unproven.
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
class Rva004E0625
{
public:
	int rva004E0625() const;
};
class Rva004E0750
{
public:
	void rva004E0750() const;
};
struct Rva005CE4FATarget
{
	char m_pad[8];
	Rva002B7250 m_holder;
};
class Rva0042D6FDPtrChaseField { public: int get() const; };
class Rva0042D703PtrChaseField { public: int get() const; };
class Rva0042D69DPtrChaseField { public: int get() const; };
class VirtObj005CE4FA
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2(int arg);
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
};
class Rva005E893E;
class Rva005CE21C
{
public:
	void clear();
	Rva005E893E *m_ptr;
};
struct WrapClear005CE4FA
{
	~WrapClear005CE4FA() { m_c.clear(); }
	Rva005CE21C m_c;
};
struct Rva005CE4FAAux
{
	char m_pad[0x0C];
	int m_0C;
};
class Rva005E67FE
{
public:
	virtual ~Rva005E67FE();
private:
	int m_04;
};
class Rva005CE4FABase8
{
public:
	virtual ~Rva005CE4FABase8() {}
};
class Rva005CE4FA : public Rva005E67FE, public Rva005CE4FABase8
{
public:
	virtual ~Rva005CE4FA();
private:
	int m_0C;
	Rva0042D6FDPtrChaseField *m_10;
	int m_14;
	Rva004E0625 *m_18;
	WrapClear005CE4FA m_1C;
	Rva005CE4FAAux *m_20;
};
Rva005CE4FA::~Rva005CE4FA()
{
	if (m_18->rva004E0625())
	{
		((Rva005CE4FATarget *)m_18)->m_holder.rva002B7250((CreateAHeroData *)static_cast<Rva005CE4FABase8 *>(this));
		VirtObj005CE4FA *o = (VirtObj005CE4FA *)m_10->get();
		if (o)
			o->f4();
		o = (VirtObj005CE4FA *)((Rva0042D703PtrChaseField *)m_10)->get();
		if (o)
			o->f10();
		o = (VirtObj005CE4FA *)((Rva0042D69DPtrChaseField *)m_10)->get();
		if (o)
			o->f2(5);
		((Rva004E0750 *)m_18)->rva004E0750();
		if (m_20)
			m_20->m_0C = 0;
	}
}

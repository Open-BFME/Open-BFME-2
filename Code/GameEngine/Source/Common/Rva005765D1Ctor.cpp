// cl: /O1 /EHsc /MD
// ??0Rva005765D1@@QAE@PAXHH@Z @0x005765D1 90B: ctor stores vtable 0x0086E7A4 at +0 plus arg1 at +8 over base Rva005D19F8(a,b), then ptr-chase getters with virtual call. Evidence: retail mov stores plus vtable imm plus ret 12 plus base call 0x005D19F8 plus getters 0x00328A83/0x0042D697 plus virtual 0x005CC208 plus caller 0x00576A9F chain; prev Disp0DwordImmSetters next Rva005766B3Ctor.
class Rva00328A83PtrChaseField
{
public:
	int get() const;
};
class Rva0042D697PtrChaseField
{
public:
	int get() const;
};
class Rva005CC208
{
public:
	virtual void rva005CC208_slot0();
	virtual void rva005CC208_slot1();
	virtual void rva005CC208_slot2();
	virtual void rva005CC208();
};
class Rva005D19F8
{
public:
	Rva005D19F8(int a, int b);
	virtual ~Rva005D19F8();
private:
	void *m_04;
};
struct Rva005765D1Mid
{
	char m_pad[4];
	const Rva00328A83PtrChaseField *m_04;
};
struct Rva005765D1Outer
{
	char m_pad[0x10];
	const Rva005765D1Mid *m_10;
};
class Rva005765D1 : public Rva005D19F8
{
public:
	Rva005765D1(void *p, int a, int b);
	virtual ~Rva005765D1();
private:
	void *m_08;
};
Rva005765D1::Rva005765D1(void *p, int a, int b)
	: Rva005D19F8(a, b), m_08(p)
{
	const Rva005765D1Outer *o = (const Rva005765D1Outer *)p;
	int v1 = o->m_10->m_04->get();
	const Rva0042D697PtrChaseField *p2 = (const Rva0042D697PtrChaseField *)v1;
	int v2 = p2->get();
	if (v2) {
		Rva005CC208 *p3 = (Rva005CC208 *)v2;
		p3->Rva005CC208::rva005CC208();
	}
}

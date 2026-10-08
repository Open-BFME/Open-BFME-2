// cl: /EHsc /MD
// ??1Rva00576C4B@@UAE@XZ @0x00576C4B 186B: virtual dtor unregistering listener base at +0xC via rowed erase 0x002B7250 then conditional ptr-chase release then member teardown. Evidence: three vtable stores plus base restores 0x0086E7F0/0x0086E7E8/0x0086E7E4 to 0x007DBA74/0x0086E788; erase caller plus deleting-dtor caller at 0x00576DD5; callees all rowed.
class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
class Rva002BA8F1Logic
{
public:
	char m_pad[0x5c];
	Rva002B7250 m_holder;
};

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
class VirtObj00576C4B
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
};
struct Inner00576C4B
{
	char m_pad[4];
	Rva00328A83PtrChaseField *m_p;
};
class Rva000AD6F4
{
public:
	void clear();
	void *m_ptr;
};
class Rva005CD7DA
{
public:
	void rva005CD7DA();
	int m_data[4];
};
struct WrapClear00576C4B
{
	~WrapClear00576C4B() { m_c.clear(); }
	Rva000AD6F4 m_c;
};
struct Wrap2000576C4B
{
	~Wrap2000576C4B() { m_m.rva005CD7DA(); }
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
class Base0_00576C4B
{
public:
	virtual ~Base0_00576C4B() {}
};
class Listener00576C4B
{
public:
	virtual ~Listener00576C4B() {}
	Inner00576C4B *m_s;
	char m_pad[8];
};
class Rva00576C4B : public Base0_00576C4B, public Rva005CD1A9, public Listener00576C4B
{
public:
	virtual ~Rva00576C4B();
private:
	WrapClear00576C4B m_1c;
	Wrap2000576C4B m_20;
	Rva005CD651 m_30;
	WrapClear00576C4B m_40;
	bool m_flag44;
};
Rva00576C4B::~Rva00576C4B()
{
	(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_holder.rva002B7250((CreateAHeroData *)(Listener00576C4B *)this);
	if (m_flag44) {
		int v1 = m_s->m_p->get();
		int v2 = ((Rva0042D6AEPtrChaseField *)v1)->get();
		if (v2)
			((VirtObj00576C4B *)v2)->f3();
	}
}

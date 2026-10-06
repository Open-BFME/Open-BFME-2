// cl: /MD /EHsc
// ??1Rva00517397@@UAE@XZ @0x00517397 52B
// Dtor releasing TargetRef holder at +8 via rowed fastcall 0x0007DEEF then
// storing base vtable 0x007C6F20 via empty inline base dtor. Derived adds no
// new virtuals so only the base store remains. Deleting dtor caller at
// 0x0051737B news nothing and deletes via rowed operator delete.
// Same recipe as Rva006003FCDtor.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva00517397Holder08
{
	TargetRef00217D4C *m_ptr;
	~Rva00517397Holder08() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class Rva00517397Base
{
public:
	__forceinline ~Rva00517397Base() {}
	virtual void keep() {}
};

class __declspec(novtable) Rva00517397 : public Rva00517397Base
{
public:
	virtual ~Rva00517397();

private:
	int m_pad04;
	Rva00517397Holder08 m_08;
};

Rva00517397::~Rva00517397()
{
}

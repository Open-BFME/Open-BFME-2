// cl: /MD /EHsc
// ??1Rva0059B072@@UAE@XZ @0x0059B072 (107B)
// Virtual dtor storing derived vtable 0x00870E6C then releasing members at
// +0x24 via virtual slot0 plus operator delete, +0x20 via rowed fastcall
// ReleaseTreeHintRef 0x0007DEEF, +8 embedded at +0xAC via same Release,
// then storing base vtable 0x007C6F20 via empty inline base dtor.
// Same recipe as Rva006003FCDtor dual-vtable plus Rva00517397Dtor holders.
// Evidence: deleting dtor caller 0x0059B132; unlock lane.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Slot00259B072
{
	virtual void *slot0(int arg);
};

struct Holder24_0059B072
{
	Slot00259B072 *m_ptr;
	__forceinline ~Holder24_0059B072()
	{
		if (m_ptr)
			::operator delete(m_ptr->slot0(0));
	}
};

struct Holder20_0059B072
{
	TargetRef00217D4C *m_ptr;
	~Holder20_0059B072()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

struct Obj08_0059B072
{
	char m_pad[0xac];
	TargetRef00217D4C m_ref;
};

struct Holder08_0059B072
{
	Obj08_0059B072 *m_ptr;
	~Holder08_0059B072()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ref);
	}
};

class Rva0059B072Base
{
public:
	__forceinline ~Rva0059B072Base() {}
	virtual void keep() {}
};

class Rva0059B072 : public Rva0059B072Base
{
public:
	virtual ~Rva0059B072();

private:
	int m_pad04;
	Holder08_0059B072 m_08;
	char m_pad0C[0x14];
	Holder20_0059B072 m_20;
	Holder24_0059B072 m_24;
};

Rva0059B072::~Rva0059B072()
{
}

// cl: /O1 /G7 /arch:SSE /MD /EHsc
// ??1LivingWorldAutoResolveUnit@@UAE@XZ @0x0059B072 (107B)
// WB14D5A60 and retail256B ctor59B1EC installC70E6C; that complete
// one-slot table points to scalar destructor59B132, which calls59B072.
// The real8B ref base Rva0007DF07 has a virtual destructor as its sole
// slot. This replaces the old dummy keep() plus separate destructor slot.
// Native ctor proves52B full extent and the trailing army/template/player
// fields28/2C/30; their storage stays opaque in this cleanup-only view.
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

class Rva0007DF07
{
public:
	virtual ~Rva0007DF07() {}
 int references;
};

class LivingWorldAutoResolveUnit : public Rva0007DF07
{
public:
	virtual ~LivingWorldAutoResolveUnit();

private:
	Holder08_0059B072 m_08;
	char m_pad0C[0x14];
	Holder20_0059B072 m_20;
	Holder24_0059B072 m_24;
 char unknown28[0xC];
};

LivingWorldAutoResolveUnit::~LivingWorldAutoResolveUnit()
{
}

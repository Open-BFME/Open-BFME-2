// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// stlport
// ??0Rva00220CD4@@QAE@XZ @0x00220C74 96B: ctor of Rva00220CD4 (vtable 0x007E6A84).
// Base via rowed baseConstruct 0x001B4E63, member +0xC via pinned 0x003623E5,
// vector<BfmeE16> +0x10 via rowed Vector_base 0x00211E58, setName("ArmySummaryDescription")
// via 0x00037BA0+0x0006F3CC. Size 0x1C proven by new 0x1C in 0x00220DCD. Neighbours
// Rva00220C56Dtor/Rva00220CD4Dtor share /O1 /MD /EHsc. Dtor rowed at 0x00220CD4,
// deleting dtor at 0x00220F71 slot 0 of same vtable.
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


struct BfmeE16 { float x; float y; float z; float w; };

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
private:
	unsigned m_unknown;
};

// SubsystemInterface with the 14 virtual slots of its retail vtable 0x00BD77A0,
// spelled as reference/shims/subsystem_bfme2/subsystem_interface.h does (ctor
// 0x001B4E63 / dtor 0x001B4E74 rowed as ??0/??1SubsystemInterface), so the
// derived vtable below gets the retail 14-slot shape.
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad() {}
	virtual bool vslot04(int) { return false; }
	virtual bool vslot05() { return false; }
	virtual int vslot06() { return 0; }
	virtual void vslot07(int) {}
	virtual void vslot08() {}
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual bool vslot11(int) { return false; }
	virtual void vslot12() {}
	virtual void vslot13(int) {}
	void setName(AsciiString name);

private:
	char m_flag;
	int m_value;
};

class Rva00220CD4 : public SubsystemInterface
{
public:
	Rva00220CD4();
	virtual ~Rva00220CD4();
	// Retail vtable 0x007E6A84 slots 1/9/10 (init/reset/update) are the folded
	// empty body at 0x000B3FD0.
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
private:
	Rva003623E5Member m_member0C;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec10;
};

Rva00220CD4::Rva00220CD4()
	: m_vec10(_STL::allocator<BfmeE16>())
{
	setName("ArmySummaryDescription");
}

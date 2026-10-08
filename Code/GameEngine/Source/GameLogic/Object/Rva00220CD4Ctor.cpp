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

class __declspec(novtable) BFME2NativeNetwork
{
public:
	__forceinline BFME2NativeNetwork() { baseConstruct(); }
	virtual ~BFME2NativeNetwork() { _ReadWriteBarrier(); }
	void baseConstruct();
private:
	virtual void unused() = 0;
	char m_flag;
	int m_value;
};

class SubsystemInterface : public BFME2NativeNetwork
{
public:
	SubsystemInterface();	// out of line: retail 0x001B4E63, defined by SubsystemInterface.cpp
	~SubsystemInterface();	// out of line: retail 0x001B4E74, defined by SubsystemInterface.cpp
	void setName(AsciiString name);
};

class Rva00220CD4 : public SubsystemInterface
{
public:
	Rva00220CD4();
private:
	Rva003623E5Member m_member0C;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec10;
};

Rva00220CD4::Rva00220CD4()
	: m_vec10(_STL::allocator<BfmeE16>())
{
	setName("ArmySummaryDescription");
}

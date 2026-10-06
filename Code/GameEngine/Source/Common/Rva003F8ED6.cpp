// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva003F8ED6@@UAE@XZ @0x003F8ED6 85B.
// Virtual dtor over vector<AsciiString> at +0xC, AsciiString at +0x18
// and TargetRef holder at +0x1C; empty body with EH for the calls.
// Evidence: unlock lane; callees rowed Release 0x0007DEEF plus
// releaseBuffer 0x00036410 plus vector dtor 0x0002CC70; caller at
// 0x003F9062; unblocks 0x003F905F; same 3-call EH shape as Rva001EC349.
#include <vector>

#include "ascii_string.h"


struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TargetRefHolder1C
{
	TargetRef00217D4C *m_ptr;
	~TargetRefHolder1C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

struct Base003F8ED6
{
	virtual ~Base003F8ED6() {}
private:
	char m_pad04[8];
};

class Rva003F8ED6 : public Base003F8ED6
{
public:
	virtual ~Rva003F8ED6();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_0C;
	AsciiString m_18;
	TargetRefHolder1C m_1C;
};

Rva003F8ED6::~Rva003F8ED6()
{
}

void *operator new(unsigned int size);
void operator delete(void *p);

// Anchor: new/delete emits the scalar deleting dtor COMDAT for
// ??_GRva003F8ED6@@UAEPAXI@Z at 0x003F905F. Operator new/delete resolve
// to their rows at 0x0002FDA0/0x0002FD60.
void Rva003F8ED6_Anchor()
{
	Rva003F8ED6 *p = new Rva003F8ED6;
	delete p;
}

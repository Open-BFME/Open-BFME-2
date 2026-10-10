// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ??1Rva00414B40@@UAE@XZ, retail 0x00414B40, 73 bytes.
// ModuleData-style dtor: vector<Rva00414BDBElement> at +0x10 via rowed 0x00414721,
// restores Snapshot secondary vtable 0x00BBB554 at +0x0C, then base SubsystemInterface 0x001B4E74.
// Precedent Rva00414932Dtor (novtable Snapshot BBB554 plus vector); caller is ??_G at 0x00414B24.
#include <vector>

#include "ascii_string.h"
#include "Common/Snapshot.h"

struct Rva00414BDBElement { ~Rva00414BDBElement(); };

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class __declspec(novtable) Rva00414B40 : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Rva00414B40();
private:
	_STL::vector<Rva00414BDBElement, _STL::allocator<Rva00414BDBElement> > m_vec10;
};

Rva00414B40::~Rva00414B40()
{
}

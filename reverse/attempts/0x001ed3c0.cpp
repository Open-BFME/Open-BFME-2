// ??0Rva001ED41B@@QAE@XZ
// partial score=0.9 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva001ED41B@@QAE@XZ, retail 0x001ED3C0..0x001ED413 (83 bytes, EH).
// Constructor of the subsystem whose vtable 0x00BDF260 the deleting
// destructor 0x001ED41B names Rva001ED41B: the canonical Snapshot at +0
// (the unwinding target is the rowed Snapshot destructor), SubsystemInterface
// at +4 under vftable 0x00BDF228 (rowed ctor 0x001B4E63), a word at +0x10
// and an empty vector at +0x14. Class name address-derived; the vector
// element is a 4-byte stand-in.
#include <vector>
#include "Common/Snapshot.h"

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
private:
	char m_pad04[0x0C - 0x04];
};

class Rva001ED41B : public Snapshot, public SubsystemInterface
{
public:
	Rva001ED41B();
	virtual ~Rva001ED41B();
private:
	int m_10;
	_STL::vector<int> m_14;
};

Rva001ED41B::Rva001ED41B()
	: m_10(0)
{
}

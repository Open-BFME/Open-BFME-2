// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva003B923B@@QAE@XZ, retail 0x003B90DB..0x003B9124 (73 bytes, no EH).
// Constructor of the subsystem whose vtable 0x00C1FB04 (deleting
// destructor 0x003B923B) sits over SubsystemInterface (rowed ctor
// 0x001B4E63) and, at +0x0C, the canonical Snapshot (final vftable 0x00C1FAF4):
// a word at +0x10, two empty vectors at +0x14 / +0x20 and two flags at
// +0x2C / +0x2D. Class name address-derived; the vector elements are 4-byte
// stand-ins.
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

class Rva003B923B : public SubsystemInterface, public Snapshot
{
public:
	Rva003B923B();
	virtual ~Rva003B923B();
private:
	int m_10;
	_STL::vector<int> m_14;
	_STL::vector<int> m_20;
	bool m_2C;
	bool m_2D;
};

Rva003B923B::Rva003B923B()
	: m_10(0), m_2C(false), m_2D(false)
{
}

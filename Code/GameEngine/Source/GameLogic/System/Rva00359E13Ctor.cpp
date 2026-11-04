// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include /Ireference/shims/moduledata
// stlport
//
// ??0Rva00359E13@@QAE@XZ, retail 0x00359E13, 122 bytes; caller 0x0024408B.
// Target evidence: the EH funclets unwind a first base at +0 through the
// shared vptr-only interface dtor 0x0049B47C (vtable 0x00BBB554) and the
// rowed vector-plus-flags base at +4 (ctor 0x00330757, teardown 0x0007FAB3);
// the ctor never stores the interface vptr, so that base is novtable. The
// WorldBuilder twin (0xE5FA60) shows a list<Coord3D> at +0x14, a 24-byte
// two-Coord3D region at +0x1C zeroed lo then hi, then +0x34, +0x38, +0x3C,
// +0x18 and +0x40 cleared in that order. Class names are address-derived.
#include <list>
#include <vector>

#include "Lib/Region3D.h"
#include "Lib/BfmeE16.h"
// vector<BfmeE16>'s destructor is needed here only for this constructor's unwind;
// declared only, so this unit emits no differing copy of it.
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

#include "../../../Include/Common/Rva00330757Member.h"

#include "Common/Snapshot.h"

class __declspec(novtable) Rva00359E13Interface
{
public:
	Rva00359E13Interface() {}
	// Retail's ctor unwind destroys this base through 0x0049B47C, the folded
	// Snapshot destructor: restore table 0x00BBB554 and return. Running the
	// canonical Snapshot destructor body emits exactly that store.
	virtual ~Rva00359E13Interface() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
};

class Rva00359E13 : public Rva00359E13Interface, public Rva00330757Member
{
public:
	Rva00359E13();

private:
	_STL::list<Coord3D> m_list; // +0x14
	float m_18;
	Region3D m_region; // +0x1C
	int m_34;
	int m_38;
	float m_3c;
	int m_40;
};

Rva00359E13::Rva00359E13()
{
	m_region.zero();
	m_34 = 0;
	m_38 = 0;
	m_3c = 0.0f;
	m_18 = 0.0f;
	m_40 = 0;
}


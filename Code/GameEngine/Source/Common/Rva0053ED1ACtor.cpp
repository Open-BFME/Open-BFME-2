// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0053ED1A@@QAE@XZ retail 0x0053ED1A 86B.
// Evidence: constructs the primary base through the pinned
// SubsystemInterface ctor 0x001B4E63 (state 0), the secondary base at +0xC
// through 0x005C6D4D, installs vtables 0x00C69464 at +0 and 0x00C6944C at
// +0xC, builds the vector at +0x48 through the pinned _Vector_base ctor
// 0x00211E58 with an allocator temporary, then zeroes +0x54 and +0x58. Slot 0
// of the +0xC vftable is a this-12 thunk to ??_G, so the secondary base leads
// with a virtual dtor; it is inline and empty, so no unwind state follows it.
// Names are generated; the vector's element type and the secondary base's
// contents are not established.
#include <vector>

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva005C6D4D
{
public:
	Rva005C6D4D();
	__declspec(dllimport) __forceinline virtual ~Rva005C6D4D() {}
private:
	char m_pad04[0x38];
};

class Rva0053ED1A : public SubsystemInterface, public Rva005C6D4D
{
public:
	Rva0053ED1A();
	virtual ~Rva0053ED1A();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void rva0053EDD2();
private:
	_STL::vector<int> m_at48;
	int m_at54;
	int m_at58;
};

Rva0053ED1A::Rva0053ED1A() : m_at54(0), m_at58(0)
{
}

class GameLogic;
extern GameLogic *TheGameLogic;
class Object;
#include "GameLogicObjectLookupView.h"
#include "../../Include/Common/Rva005C6C7B.h"
class Rva005C65F1
{
public:
	void rva005C65F1();
};

void Rva0053ED1A::rva0053EDD2()
{
	Object *obj = TheGameLogic->findObjectByID(*(ObjectID *)&m_at48);
	if (obj == 0)
		return ((Rva005C6C7B *)this)->reset();
	else
		return ((Rva005C65F1 *)this)->rva005C65F1();
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??0Rva005C6D4D@@QAE@XZ=??0Rva005C6C7B@@QAE@XZ")
#pragma comment(linker, "/alternatename:?v01@Rva0053ED1A@@UAEXXZ=??1Region2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?v02@Rva0053ED1A@@UAEXXZ=?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ")
#pragma comment(linker, "/alternatename:?v03@Rva0053ED1A@@UAEXXZ=??1Region2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?v04@Rva0053ED1A@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")

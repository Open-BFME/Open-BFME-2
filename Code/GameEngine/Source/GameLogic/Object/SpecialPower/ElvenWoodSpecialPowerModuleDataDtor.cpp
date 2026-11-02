// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??1ElvenWoodSpecialPowerModuleData@@UAE@XZ @0x004C3EC2 71B
// Elven-wood data dtor over the ctor 0x004C3DA9 layout (0x7C base plus vector
// at +0x7C plus string at +0x88 plus ints/float at +0x8C/+0x90/+0x94/+0x98 for
// 0x9C total): destroys the string at +0x88 through pinned 0x36410 then the
// RvaPair vector at +0x7C through rowed 0x4C3D4C then the SpecialPowerModuleData base
// through rowed 0x49334F. Identity: vtable 0x00C5CF38 slot 0 caller ??_G at
// 0x004C3EA6 plus ctor vptr store 0x004C3DBA plus factory 0x00251CB4 plus
// table 0x00C5D018. Shape reuses OCLSpecialPowerModuleDataDtor (same base
// plus vector plus string teardown with CashHack MALLOC flags).
#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

#define BFME_STRINGBASE_PUBLIC_DTOR
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"


struct RvaPair004C3D4C
{
	AsciiString m_key;
	int m_value;
	// The retail 0x0032C0CA loop destroys only the key at each 8-byte stride.
	// Let member destruction bind to the rowed AsciiString destructor.
	~RvaPair004C3D4C() {}
};

#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"

class __declspec(novtable) ElvenWoodSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~ElvenWoodSpecialPowerModuleData();

private:
	_STL::vector<RvaPair004C3D4C> m_elves;
	StringBase<char> m_groveObject;
	int m_numObjects;
	float m_radius;
	int m_fx;
	int m_ocl;
};

ElvenWoodSpecialPowerModuleData::~ElvenWoodSpecialPowerModuleData()
{
}

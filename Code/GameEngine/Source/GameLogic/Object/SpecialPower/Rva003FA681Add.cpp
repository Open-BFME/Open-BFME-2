// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?rva003FA681@Rva003FA681@@QAEXHABH@Z @0x003FA681 51B add Upgrades pair if science not present; calls rowed contains 0x003FA430 plus Upgrades ctor 0x003FA38C plus push_back 0x003FA5F4
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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

#include "../../../../Include/GameLogic/Module/CashHackSpecialPowerModuleData.h"

class Rva003FA430
{
public:
	bool rva003FA430(int science);
};

class Rva003FA681
{
public:
	int m_pad0;
	_STL::vector<CashHackSpecialPowerModuleData::Upgrades> m_vec;
	void rva003FA681(int science, const int &amount);
};

// bfme link decl-only begin
namespace _STL { template <> void _Construct<CashHackSpecialPowerModuleData::Upgrades,CashHackSpecialPowerModuleData::Upgrades>(CashHackSpecialPowerModuleData::Upgrades *,CashHackSpecialPowerModuleData::Upgrades const &); }
namespace _STL { template <> void vector<CashHackSpecialPowerModuleData::Upgrades,_STL::allocator<CashHackSpecialPowerModuleData::Upgrades> >::_M_insert_overflow(CashHackSpecialPowerModuleData::Upgrades *,CashHackSpecialPowerModuleData::Upgrades const &,_STL::__false_type const &,unsigned int,bool); }
namespace _STL { template <> CashHackSpecialPowerModuleData::Upgrades * allocator<CashHackSpecialPowerModuleData::Upgrades>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void vector<CashHackSpecialPowerModuleData::Upgrades,_STL::allocator<CashHackSpecialPowerModuleData::Upgrades> >::push_back(CashHackSpecialPowerModuleData::Upgrades const &); }
// bfme link decl-only end
void Rva003FA681::rva003FA681(int science, const int &amount)
{
	if (((Rva003FA430 *)this)->rva003FA430(science))
		return;
	CashHackSpecialPowerModuleData::Upgrades tmp(science, amount);
	m_vec.push_back(tmp);
}

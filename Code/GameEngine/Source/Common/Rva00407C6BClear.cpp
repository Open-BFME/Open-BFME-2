// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport46
//
// ?rva00407C6B@CreateAHeroHero@@QAEXXZ retail 0x00407C6B 20B
// Evidence: unlock lane; two Rb_tree int-int clears via twin pin clear 0x0021A917 (twin of dup); caller 0x00408C11; prev our Object 23B same /O1.
#include <map>
// bfme link decl-only begin
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::clear(); }
// Retail calls the clear rowed at 0x0021A917 (StlSweepW5Rva0021A917.cpp), a
// separate instantiation from the int-int clear at 0x0006AA1C, so the key is
// that row's element type, not int.
struct Rva0021A917Element { short words[1]; bool operator<(const Rva0021A917Element &b) const { return words[0] < b.words[0]; } };
namespace _STL { template <> void _Rb_tree<Rva0021A917Element, pair<Rva0021A917Element const, int>, _Select1st<pair<Rva0021A917Element const, int> >, less<Rva0021A917Element>, allocator<pair<Rva0021A917Element const, int> > >::clear(); }
// bfme link decl-only end

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

class CreateAHeroHero
{
public:
	void rva00407C6B();
private:
	char m_pad[0x14];
	_STL::map<Rva0021A917Element, int> m_a;
	_STL::map<Rva0021A917Element, int> m_b;
};

void CreateAHeroHero::rva00407C6B()
{
	m_a.clear();
	m_b.clear();
}

// The unit's rowed map<int,int>::clear forwarder (0x0023E995).
template void _STL::map<int, int>::clear();

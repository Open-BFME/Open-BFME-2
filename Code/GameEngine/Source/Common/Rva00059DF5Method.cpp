// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Oi /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00059DF5@Rva00059DF5@@QAEXABVAsciiString@@H@Z at 0x00059DF5 (103B).
// Guard over +0x9D4 then virtual slot 0x68 then set insert at +0xA14.
// Evidence: MilesMutexGuard ctor 0x4120E/dtor 0x4122F, virtual call [eax+0x68]
// with (AsciiString,int), set insert row 0x5897D with (idx+0xD7)*12+this
// folding base 0xA14, imul 0xC needs /G7. No callers.
#include <set>

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

#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
template <> pair<Lk6AsciiSetTree::iterator, bool> Lk6AsciiSetTree::insert_unique(const AsciiString&);
template <> Lk6AsciiSetTree::iterator Lk6AsciiSetTree::insert_unique(Lk6AsciiSetTree::iterator, const AsciiString&);
template <> _Rb_tree_node<AsciiString> *Lk6AsciiSetTree::_M_create_node(const AsciiString&);
}

#include "../../../GameEngineDevice/Include/MilesAudioDevice/MilesMutexGuard.h"

class MilesAudioManager
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void vf26(const AsciiString &a, int idx);
	virtual void rva00059DF5(const AsciiString &a, int idx);
	virtual void rva00059E5C(int idx);
private:
	char m_pad4[0x9D4 - 4];
	void *m_mutex;
	char m_pad9D8[0xA14 - 0x9D8];
	_STL::set<AsciiString> m_sets[4];
};

void MilesAudioManager::rva00059DF5(const AsciiString &asciiString, int idx)
{
	MilesMutexGuard guard(&m_mutex, 0);
	vf26(asciiString, idx);
	m_sets[idx].insert(asciiString);
}

// ?rva00059E5C@Rva00059DF5@@QAEXH@Z at 0x00059E5C (82B).
// Sibling of 0x00059DF5: guard over +0x9D4 then tree clear 0x57B4B at +0xA14.
// Evidence: same mutex/sets layout, add 0xD7 imul 0xC needs /G7, ret 4 single int.
void MilesAudioManager::rva00059E5C(int idx)
{
	MilesMutexGuard guard(&m_mutex, 0);
	m_sets[idx].clear();
}

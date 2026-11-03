// ?rva002B69A6@Rva002B69A6@@QAEXPAX@Z
// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?rva002B69A6@Rva002B69A6@@QAEXPAX@Z @0x002B69A6 94B: unlock callee of
// 0x002B77F7; vector at this+0x8c, rank at elem+0x34; clears arg via rowed
// 0x00072FE6 then inserts each element's rank into the set at arg via rowed
// 0x000BC15D. Evidence: rowed clear callee, set-int insert callee, layout from
// pinned vector pair.
//
// The span is spelled by hand over the vector's own finish/start pair, exactly
// as the rowed sibling 0x0009D9BD does: STLport size() materializes start into
// eax and counts in ecx, while retail recomputes `finish - start` in eax on
// both the entry and the loop-back edge. Keeping the difference signed keeps
// the arithmetic shift, so an unsigned-typed count is a size regression.
#include <set>
#include <vector>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
typedef _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> > Lk11RbIntSet;
template <> pair<Lk11RbIntSet::iterator, bool> Lk11RbIntSet::insert_unique(const int &);
}
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

#include "../../Include/Common/Rva00072FE6.h"

struct Rva002B69A6Elem
{
	char m_pad[0x34];
	int m_rank;
};

class Rva002B69A6
{
public:
	void rva002B69A6(void *arg);
private:
	char m_pad00[0x8c];
	_STL::vector<Rva002B69A6Elem *> m_vec;
};

// ?rva002B69A6@Rva002B69A6@@QAEXPAX@Z
void Rva002B69A6::rva002B69A6(void *arg)
{
	((Rva00072FE6 *)arg)->rva00072FE6();
	int *span = (int *)&m_vec;
	_STL::vector<Rva002B69A6Elem *> &vec = m_vec;
	for (unsigned int i = 0; i < (unsigned)((span[1] - span[0]) >> 2); ++i)
	{
		int rank = vec[i]->m_rank;
		((_STL::set<int> *)arg)->insert(rank);
	}
}

// ?rva002B69A6@Rva002B69A6@@QAEXPAX@Z
// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
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

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

class Rva00072FE6
{
public:
	void rva00072FE6();
};

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

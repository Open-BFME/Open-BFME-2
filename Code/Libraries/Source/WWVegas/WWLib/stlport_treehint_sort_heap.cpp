// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$sort_heap@PAUTreeHintRef00217D4C@@URva004F9185Cmp@@@_STL@@YAXPAUTreeHintRef00217D4C@@0URva004F9185Cmp@@@Z, retail 0x004F8162, 58 bytes.
// Public sort_heap loop over TreeHintRef calling rowed pop_heap 0x004F7AA6 then --last while more than one element.
// Evidence: chain via just-landed pop_heap 0x004F7AA6; caller 0x004F8752 in 178B unclaimed; same flags and minimal structs as landed pop_heap TU; same 58B shape as int __sort_heap 0x002082B7.
#include <algorithm>

struct TreeHintRef00217D4C
{
	void *m_ptr;
};

struct Rva004F9185Cmp
{
	bool operator()(TreeHintRef00217D4C a, TreeHintRef00217D4C b) const;
};

namespace _STL
{
	template void sort_heap<TreeHintRef00217D4C *, Rva004F9185Cmp>(TreeHintRef00217D4C *, TreeHintRef00217D4C *, Rva004F9185Cmp);
}

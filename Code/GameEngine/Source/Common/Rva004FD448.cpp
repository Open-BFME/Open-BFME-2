// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004FD448@Rva004FD448@@QAEXPBVModuleData@@@Z @0x004FD448 102B.
// Multimap<int int> insert per int plus vector<ModuleData*> push_back.
// Evidence: unlock lane unblocks 0x004FD7FB TeamDefeatCondition ParseINI;
// caller 0x004FD834 passes new 0x24 object with vector<int> at +4 in push
// and holder in ecx; map at this+0x68 via rowed insert_equal 0x004FF876;
// vector at this+0x8c via rowed push_back 0x004DFCB0; same 0x24 spacing as
// siblings 0x004FD37F 0x50/0x74 and 0x004FD3E2 0x5c/0x80; neighbours carry
// /O1 /GX /MD.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class ModuleData;

// This name is already present in the ledger as an address-derived partial
// row. 0x004FD571's REL32 call proves the target RVA used below; the helper's
// owner and semantics remain unresolved.
class Rva004FCE73
{
public:
	void rva004FD013(int key, _STL::vector<const ModuleData *> *records, int *out);
	bool rva004FCEB5(int key);
};

struct Rva004FCD49Vec {
    void *vtbl;
    _STL::vector<int> m_vec;
    int m_10;
};

class Rva004FD448 {
public:
    void rva004FD448(const ModuleData *p);
    void rva004FD571(int key, _STL::vector<const ModuleData *> *records, int *out) const;
    bool rva004FD656(int key) const;
private:
    char m_pad00[0x68];
    _STL::multimap<int, int> m_map;
    char m_pad1[0x8c - 0x68 - sizeof(_STL::multimap<int, int>)];
    _STL::vector<const ModuleData *> m_vec;
};

void Rva004FD448::rva004FD448(const ModuleData *p)
{
    if (!p)
        return;
    const _STL::vector<int> &vec = ((const Rva004FCD49Vec *)p)->m_vec;
    for (unsigned int i = 0; i < vec.size(); ++i) {
        int v = vec[i];
        m_map.insert(_STL::multimap<int, int>::value_type(v, (int)p));
    }
    m_vec.push_back(p);
}

// 0x004FD571 86B.
// Shares the +0x68 multimap field with the matched 0x004FD448 body. The target
// clears the supplied vector, obtains a const equal_range, and calls the
// address-derived 0x004FD013 helper once per mapped pointer; the helper's
// identity is still an inference carried from its partial ledger row.
void Rva004FD448::rva004FD571(int key, _STL::vector<const ModuleData *> *records, int *out) const
{
	// The target vector holds four-byte pointers. Use the already-rowed
	// vector<void *> erase body; this changes only the template spelling.
	_STL::vector<void *> *clearRecords = (_STL::vector<void *> *)records;
	clearRecords->erase(clearRecords->begin(), clearRecords->end());
    *out = 0;
    _STL::pair<_STL::multimap<int, int>::const_iterator,
        _STL::multimap<int, int>::const_iterator> range = m_map.equal_range(key);
    for (_STL::multimap<int, int>::const_iterator it = range.first; it != range.second; ++it) {
        Rva004FCE73 *candidate = (Rva004FCE73 *)(*it).second;
        candidate->rva004FD013(key, records, out);
    }
}

// Retail 0x004FD656, 67 bytes, RET 4. The +0x68 equal_range and mapped
// pointer at node +0x14 are shared with 0x004FD571. The target stops at the
// first positive native predicate; its original owner and name are unknown.
bool Rva004FD448::rva004FD656(int key) const
{
    _STL::pair<_STL::multimap<int, int>::const_iterator,
        _STL::multimap<int, int>::const_iterator> range = m_map.equal_range(key);
    for (_STL::multimap<int, int>::const_iterator it = range.first; it != range.second; ++it)
    {
        Rva004FCE73 *candidate = (Rva004FCE73 *)(*it).second;
        if (candidate->rva004FCEB5(key))
            return true;
    }
    return false;
}

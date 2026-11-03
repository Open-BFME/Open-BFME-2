// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?addTeamDefeatCondition@Scenario@LivingWorldScenario@@QAEXPBVModuleData@@@Z @0x004FD3E2 102B.
// Multimap<int int> insert per int plus vector<ModuleData*> push_back.
// Evidence: unlock lane unblocks 0x004FD77C TeamDefeatCondition ParseINI;
// caller 0x004FD7B5 passes new Rva004FCD49 0x14 with vector<int> at +4 in push
// and holder in ecx; map at this+0x5c via rowed insert_equal 0x004FF876;
// vector at this+0x80 via rowed push_back 0x004DFCB0; same 0x24 spacing as
// siblings 0x004FD37F 0x50/0x74 and 0x004FD448 0x68/0x8c; neighbours carry
// /O1 /GX /MD.
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
#include <map>

// Native int-map operations stay inline without per-unit allocator/pair copies.
namespace _STL {
typedef pair<const int,int> SVIntPair;
typedef _Rb_tree_node<SVIntPair> SVIntNode;
template<> __declspec(dllimport) __forceinline SVIntNode *allocator<SVIntNode>::allocate(size_t n, const void *) const { return n ? reinterpret_cast<SVIntNode *>(allocator<char>::allocate(n * sizeof(SVIntNode),0)) : 0; }
template<> __declspec(dllimport) __forceinline void allocator<SVIntNode>::deallocate(SVIntNode *p, size_t) const { if(p) ::free(p); }
template<> __declspec(dllimport) __forceinline SVIntNode *_STLP_alloc_proxy<SVIntNode *,SVIntNode,allocator<SVIntNode> >::allocate(size_t n) { return __stl_alloc_rebind(static_cast<allocator<SVIntNode> &>(*this), (SVIntNode *)0).allocate(n,0); }
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<SVIntNode *,SVIntNode,allocator<SVIntNode> >::deallocate(SVIntNode *p, size_t n) { __stl_alloc_rebind(static_cast<allocator<SVIntNode> &>(*this), (SVIntNode *)0).deallocate(p,n); }
template<> __declspec(dllimport) __forceinline pair<const int,int>::pair(const int &a,const int &b):first(a),second(b) {}
}


// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class ModuleData;



struct Rva004FCD49Vec {
    void *vtbl;
    _STL::vector<int> m_vec;
    int m_10;
};

#include "../../Include/Common/LivingWorldScenario.h"
class LivingWorldScenario::TeamDefeatCondition
{
public:
    bool isTeamDefeated(int team);
};

class LivingWorldScenario::Scenario {
public:
    void addTeamDefeatCondition(const ModuleData *p);
    void rva004FD533(int key, int unused, int *out) const;
    bool rva004FD613(int key) const;
private:
    char m_pad00[0x5c];
    _STL::multimap<int, int> m_map;
    char m_pad1[0x80 - 0x5c - sizeof(_STL::multimap<int, int>)];
    _STL::vector<const ModuleData *> m_vec;
};

void LivingWorldScenario::Scenario::addTeamDefeatCondition(const ModuleData *moduleData)
{
    if (!moduleData)
        return;
    const _STL::vector<int> &vec = ((const Rva004FCD49Vec *)moduleData)->m_vec;
    for (unsigned int i = 0; i < vec.size(); ++i) {
        int v = vec[i];
        m_map.insert(_STL::multimap<int, int>::value_type(v, (int)moduleData));
    }
    m_vec.push_back(moduleData);
}

void LivingWorldScenario::Scenario::rva004FD533(int key, int unused, int *out) const
{
    (void)unused;
    *out = 0;
    _STL::pair<_STL::multimap<int, int>::const_iterator, _STL::multimap<int, int>::const_iterator> r = m_map.equal_range(key);
    for (_STL::multimap<int, int>::const_iterator it = r.first; it != r.second; ++it) {
        int ptr = (*it).second;
        int v = *(int *)(ptr + 0x10);
        if (*out < v)
            *out = v;
    }
}
bool LivingWorldScenario::Scenario::rva004FD613(int key) const
{
    _STL::pair<_STL::multimap<int, int>::const_iterator, _STL::multimap<int, int>::const_iterator> r = m_map.equal_range(key);
    for (_STL::multimap<int, int>::const_iterator it = r.first; it != r.second; ++it) {
        LivingWorldScenario::TeamDefeatCondition *cand = (LivingWorldScenario::TeamDefeatCondition *)(*it).second;
        if (cand->isTeamDefeated(key))
            return true;
    }
    return false;
}

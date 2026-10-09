// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native 0007A4E6..0007A54B, nonvirtual container-owner destructor.
// Target facts: the direct first call is the existing 7A41E pruning worker;
// then reverse member teardown frees vector buffers at1C and10, destroys the
// string list at0C (799D0) and the tree at0 (79E55). Constructor7A498 confirms
// these member offsets independently. Original owner identity remains unknown.
// STLport4.5.3 vector/list/tree teardown is the semantic reference; existing
// native provider names retained. No names inferred from byte identity alone.
#include <map>
#include <algorithm>
extern "C" void __cdecl free(void *);
class Rva00079A0C {
    unsigned opaque[2];
public:
    ~Rva00079A0C();
};
class Rva000799D0 {
    void *sentinel;
public:
    void rva000799D0();
    ~Rva000799D0() { rva000799D0(); }
};
struct Rva0007A4E6VectorStorage {
    void *begin, *end, *capacity;
    ~Rva0007A4E6VectorStorage() { if (begin) free(begin); }
};
class Rva007A41E {
public:
    void rva007A41E();
};
class Rva007A4E6 {
    Rva00079A0C tree;
    unsigned opaque08;
    Rva000799D0 list;
    Rva0007A4E6VectorStorage first, second;
public:
    ~Rva007A4E6();
};
Rva007A4E6::~Rva007A4E6() {
    reinterpret_cast<Rva007A41E *>(this)->rva007A41E();
}

// Native7A41E..7A498122B: sort each node's pointer vector, delete trailing
// objects with a zero second word, and erase empty tree entries. Existing
// sort and erase owners prove all three call contracts independently.
struct Rva00078F95Item { void *opaque00; int count04; };
struct Rva00078F95Cmp {
    bool operator()(const Rva00078F95Item *, const Rva00078F95Item *) const;
};
struct Rva00079995Element { char unaccessed[12]; };
typedef _STL::_Rb_tree<int, _STL::pair<const int,Rva00079995Element>,
    _STL::_Select1st<_STL::pair<const int,Rva00079995Element> >,
    _STL::less<int>, _STL::allocator<_STL::pair<const int,Rva00079995Element> > > NativeEraseTree;
namespace _STL {
template<> void NativeEraseTree::erase(NativeEraseTree::iterator);
template<> void sort<Rva00078F95Item **,Rva00078F95Cmp>(Rva00078F95Item **,Rva00078F95Item **,Rva00078F95Cmp);
}
struct Rva0007A41ENode : _STL::_Rb_tree_node_base {
    int key;
    Rva00078F95Item **begin, **end, **capacity;
};
void Rva007A41E::rva007A41E() {
    _STL::_Rb_tree_node_base *header = *reinterpret_cast<_STL::_Rb_tree_node_base **>(this);
    Rva0007A41ENode *node = static_cast<Rva0007A41ENode *>(header->_M_left);
    while (node != header) {
        _STL::sort(node->begin,node->end,Rva00078F95Cmp());
        while (node->begin != node->end) {
            Rva00078F95Item *last = node->end[-1];
            if (last->count04 != 0) break;
            ::operator delete(last);
            --node->end;
        }
        if (node->begin == node->end) {
            _STL::_Rb_tree_node_base *next = _STL::_Rb_global<bool>::_M_increment(node);
            reinterpret_cast<NativeEraseTree *>(this)->erase(NativeEraseTree::iterator(reinterpret_cast<_STL::_Rb_tree_node<NativeEraseTree::value_type> *>(node)));
            node = static_cast<Rva0007A41ENode *>(next);
        } else {
            node = static_cast<Rva0007A41ENode *>(_STL::_Rb_global<bool>::_M_increment(node));
        }
        header = *reinterpret_cast<_STL::_Rb_tree_node_base **>(this);
    }
}

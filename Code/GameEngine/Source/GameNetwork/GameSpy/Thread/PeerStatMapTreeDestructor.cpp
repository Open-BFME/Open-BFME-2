// cl: /O1 /EHsc /MD /D_CRTIMP=
// STLport 4.5.3 _Rb_tree destructor, recovered from the named PeerThread map
// specialization. Donor structure: reference/open-bfme-1 at
// 071013b3c6f1228dfda315732197bed0fd191209, inputs/vendor/stlport/stl/_tree.h.
// Target evidence: constructor cleanup at this+0x98/+0xA4 and the matching
// PlayerStatMap lookups identify this specialization. Ghidra boundary
// 0x0038A48B..0x0038A4C2 calls its rowed clear at 0x00389A4C, then releases
// the header through 0x00030830. Only the destructor-visible layout is modeled.
// C++ linkage on free preserves the target's unwind-state transition before
// the base's header release. extern "C" free incorrectly suppresses that store.

namespace _STL {
void __cdecl free(void *block);

template<class T> class char_traits;
template<class T> class allocator {};
template<class Char, class Traits, class Alloc> class basic_string;
template<class First, class Second> struct pair;
template<class Pair> struct _Select1st;
template<class T> struct less {};
template<class Value> struct _Rb_tree_node;

// ?_Rb_tree_base::~_Rb_tree_base present-unmatched
template<class Value, class Alloc> struct _Rb_tree_base {
    _Rb_tree_node<Value> *header;
    inline ~_Rb_tree_base() {
        if (header != 0)
            free(header);
    }
};

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree : public _Rb_tree_base<Value, Alloc> {
public:
    ~_Rb_tree();
    void clear();
private:
    unsigned int nodeCount;
    Compare keyCompare;
};

typedef basic_string<char, char_traits<char>, allocator<char> > PeerStatKey;
typedef pair<const PeerStatKey, int> PeerStatValue;
typedef _Rb_tree<PeerStatKey, PeerStatValue, _Select1st<PeerStatValue>,
    less<PeerStatKey>, allocator<PeerStatValue> > PeerStatTree;

template<> PeerStatTree::~_Rb_tree() {
    clear();
}
}

// Native38A5D1..38A5D6 is a standalone JMP to the owned PlayerStatMap dtor.
// Original wrapper name and enclosing receiver type remain unknown.
typedef _STL::PeerStatTree Rva0038A5D1Tree;
struct Rva0038A5D1PeerStatCleanupForward { void cleanup(); };
void Rva0038A5D1PeerStatCleanupForward::cleanup()
{
    reinterpret_cast<Rva0038A5D1Tree *>(this)->~Rva0038A5D1Tree();
}

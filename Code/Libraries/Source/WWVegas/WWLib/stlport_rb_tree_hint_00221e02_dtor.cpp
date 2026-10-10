// cl: /O1 /EHsc /MD /D_CRTIMP=
// STLport 4.5.3 tree destructor. Semantic donor: _tree.h at BFME1
// 071013b3c6f1228dfda315732197bed0fd191209. Target 0x00221E02..0x00221E39
// calls this specialization's verified clear at 0x00221CAE, then free30830.
// The matching insertion/copy/erase chain in stlport_rb_tree_hint_00221e3a.cpp
// establishes AsciiString keys and opaque reference-counted pointer values.
// Application type remains unknown. This TU exposes only destruction's layout;
// the header base and throwing C++ allocator declaration preserve the EH store.

class AsciiString;
struct TreeHintRef00221D6B;

namespace _STL {
void __cdecl free(void *block);
template<class T> class allocator {};
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

typedef pair<const AsciiString, TreeHintRef00221D6B> HintValue;
typedef _Rb_tree<AsciiString, HintValue, _Select1st<HintValue>,
    less<AsciiString>, allocator<HintValue> > HintTree;

template<> inline HintTree::~_Rb_tree() {
    clear();
}
}

// ??1?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@_STL@@@3@@_STL@@QAE@XZ is a header inline in STLport: another unit emits a select-any copy of it, so a strong definition here was a duplicate symbol in the linked build. This anchor only makes this unit emit its copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitstlport_rb_tree_hint_00221e02_dtor@@YAXPAV?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@_STL@@@3@@_STL@@@Z present-unmatched
void bfmeEmitstlport_rb_tree_hint_00221e02_dtor(_STL::HintTree *p)
{
    p->~_Rb_tree();
}
#pragma inline_depth()

// Native221FF5 tail JMP221E02: unchanged ECX and no stack arguments.
// Existing tree type is reused; original wrapper identity is unknown.
struct Rva00221FF5TreeCleanupForward { void cleanup(); };
void Rva00221FF5TreeCleanupForward::cleanup() {
    reinterpret_cast<_STL::HintTree *>(this)->~_Rb_tree();
}

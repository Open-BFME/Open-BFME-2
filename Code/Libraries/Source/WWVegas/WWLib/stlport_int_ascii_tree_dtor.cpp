// cl: /O1 /EHs /MD /D_CRTIMP=
// STLport 4.5.3 _tree.h destructor; PeerStatMapTreeDestructor.cpp supplies
// the verified sibling compiler shape. Native Ghidra 0x2B80CE..0x2B8106
// calls the existing map<int,AsciiString> clear at 0x2B70B3, then frees its
// header through 0x30830. The call and header ownership are target facts;
// template identity follows the already recovered clear specialization.
// C++ free retains the unwind-state transition before the header release.
class AsciiString;
namespace _STL {
// Retail calls free directly (the game allocator at 0x00030830), not through
// the CRT import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

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

typedef pair<const int, AsciiString> IntAsciiValue;
typedef _Rb_tree<int, IntAsciiValue, _Select1st<IntAsciiValue>,
    less<int>, allocator<IntAsciiValue> > IntAsciiTree;

template<> IntAsciiTree::~_Rb_tree() {
    clear();
}
}

// Preserve the existing callers' address-derived spelling as a link alias.
#pragma comment(linker, "/alternatename:??1RvaVec002B80CE@@QAE@XZ=??1?$_Rb_tree@HU?$pair@$$CBHVAsciiString@@@_STL@@U?$_Select1st@U?$pair@$$CBHVAsciiString@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@QAE@XZ")

// Record-set cleanup uses the established genuine clear and owned header.
// This is the existing nontrivial destructor-only view, not a trivial map.
#include "../../../../GameEngine/Include/Common/Rva00064640Record.h"
namespace _STL {
template<class T> struct _Identity;
typedef _Rb_tree<Rva00064640Record, Rva00064640Record,
    _Identity<Rva00064640Record>, less<Rva00064640Record>,
    allocator<Rva00064640Record> > ControlPointTree;
template<> ControlPointTree::~_Rb_tree() {
    clear();
}
}

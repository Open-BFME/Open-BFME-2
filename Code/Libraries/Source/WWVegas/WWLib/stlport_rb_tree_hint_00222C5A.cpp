// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1?$pair@$$CBVAsciiString@@UTreeHintRef00222C5A@@@_STL@@QAE@XZ, retail 0x00222C5A 57 bytes.
// STLport pair<const AsciiString TreeHintRef> destructor: releases non-null mapped
// pointer through shared rowed fastcall 0x0007DEEF then AsciiString teardown 0x00036410.
// Identical to rowed 0x002175CE and 0x0022187B except EH scopetable. Callers at
// 0x00222DEF 0x00223599 0x00223FBB 0x0022409E prove the 8-byte pair layout.
// Deleting dtor 0x00222DEC in same TU calls this dtor then operator delete 0x0002FD60.
// Honest address type TreeHintRef00222C5A; application identity remains opaque.
#include <map>
template <class T> class StringBase
{
	friend class AsciiString;
	void releaseBuffer();
public:
	void *m_data;
};
class AsciiString : public StringBase<char>
{
public:
	~AsciiString() { releaseBuffer(); }
};
bool operator<(const AsciiString &, const AsciiString &);
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00222C5A {
    TargetRef00217D4C *m_ptr;
    TreeHintRef00222C5A(const TreeHintRef00222C5A &other) : m_ptr(other.m_ptr) {
        if (m_ptr) ++m_ptr->references;
    }
    __forceinline ~TreeHintRef00222C5A() {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
};
typedef _STL::pair<const AsciiString, TreeHintRef00222C5A> TreeHintPair00222C5A;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair00222C5A, _STL::_Select1st<TreeHintPair00222C5A>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair00222C5A> > TreeHint00222C5A;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
template void _STL::_Destroy<TreeHintPair00222C5A>(TreeHintPair00222C5A *);

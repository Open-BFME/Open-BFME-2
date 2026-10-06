// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Nocase AsciiString set cleanup trio for the INI macro map family:
//   ?_M_erase@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@UBfmeStringNoCaseLess@@V?$allocator@VAsciiString@@@3@@_STL@@AAEXPAU?$_Rb_tree_node@VAsciiString@@@2@@Z @0x0002C8D3 53B
//   ?clear@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@UBfmeStringNoCaseLess@@V?$allocator@VAsciiString@@@3@@_STL@@QAEXXZ @0x0002CA49 41B
//   ??1?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@UBfmeStringNoCaseLess@@V?$allocator@VAsciiString@@@3@@_STL@@QAE@XZ @0x0002CC38 56B
// Evidence: 53/41/56 sizes match the plain-less siblings 0x56CC3/0x57B4B/0x589BE;
// erase destroys the string at node+16 via rowed 0x48BA39 then frees via rowed
// 0x30830 with self-recursion on [node+0x0C] and loop on [node+8]; clear calls
// erase then resets root/extremes/count; dtor calls clear then frees the header.
// Same 4KB page as the nocase ordering 0x2C63C used by 0x2C686/0x2C908.
// Comparator BfmeStringNoCaseLess is the established nocase set comparator from
// stlport_rb_tree_insert_unique_nocase.cpp (NoCaseStringSet); erase/clear/dtor
// never call it so their bytes are comparator-independent. Flags copied from
// the proven 56B dtor TU WaypointTreeCleanup.cpp.
#include <map>
#include <set>

// class-gate: allow AsciiString Retail erase at 0x0002C8D3 calls the dtor thunk at 0x0048BA39.
class AsciiString { public: ~AsciiString(); private: char *m_text; };

bool operator<(const AsciiString &, const AsciiString &);

struct BfmeStringNoCaseLess
{
    bool operator()(const AsciiString &, const AsciiString &) const;
};

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > NoCaseSetTree;

template void NoCaseSetTree::_M_erase(NoCaseSetTree::_Link_type);
template void NoCaseSetTree::clear();
template NoCaseSetTree::~_Rb_tree();

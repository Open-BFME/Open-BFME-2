// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Semantic donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/RvaTreeInsertUniqueHint.cpp.
// BFME2 uses the established external AsciiString comparator.
#include <map>
#include <set>
// class-gate: allow AsciiString Retail tree erase at 0x00056CC3 calls the dtor thunk at 0x0048BA39.
class AsciiString { public: AsciiString(const AsciiString &); ~AsciiString(); private: char *m_text; };
bool operator<(const AsciiString &, const AsciiString &);
// Retail _M_create_node 0x0002C552 allocates 20 bytes: 16-byte links + AsciiString.
// _Construct 0x0002C485 invokes the independently established AsciiString copy at 0x000365F0.
// There is no mapped value; this is a tree with _Identity<AsciiString>.
typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> > StringSetTree;
// BFME replaces STLport allocation with a static byte allocator (RVA 0x307F0).
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

// Existing helper alias distinguishes the StringBase flavor from the Buffer flavor.
void AsciiStringCopyConstructAtRva0002C485(AsciiString *, const AsciiString &);

// Retail 0x0002C552 allocates the node, then constructs its value.
// Unlike stock STLport, this retail body has no allocation-cleanup catch path.
// ?_M_create_node@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@U?$less@VAsciiString@@@3@V?$allocator@VAsciiString@@@3@@_STL@@IAEPAU?$_Rb_tree_node@VAsciiString@@@2@ABVAsciiString@@@Z
template <>
StringSetTree::_Link_type StringSetTree::_M_create_node(const AsciiString &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<AsciiString>), 0);
    AsciiStringCopyConstructAtRva0002C485(&node->_M_value_field, value);
    return node;
}

template StringSetTree::iterator StringSetTree::insert_unique(StringSetTree::iterator, const AsciiString &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::set<AsciiString,_STL::less<AsciiString>,_STL::allocator<AsciiString> > SetExtra;
template SetExtra::iterator SetExtra::insert(SetExtra::iterator, const AsciiString &);

template StringSetTree::_Rb_tree(const StringSetTree &);

// Faction-set cleanup: player callback22D920 -> tree dtor589BE -> clear57B4B.
// Erase56CC3 destroys each string at node+16 through the proven dtor48BA39.
template void StringSetTree::_M_erase(StringSetTree::_Link_type);
template void StringSetTree::clear();

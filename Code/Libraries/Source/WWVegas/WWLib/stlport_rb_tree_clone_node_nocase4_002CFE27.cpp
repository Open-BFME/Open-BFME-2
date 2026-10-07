// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// NoCase _M_clone_node @0x002CFE27 30B: clones the source node through the
// rowed _M_create_node 0x002CFA8E (value field at source+0x10), copies the
// color byte, nulls links +8/+0xc, ret 4. Same 30B shape as the landed
// sibling 0x002CFE09 in OwnedRecord900TreeCopy.cpp; the chain packet shows
// the call into 0x002CFA8E which this session landed. Emitted via explicit
// instantiation of this one member; _M_create_node stays an external call
// resolved by its ledger row.
#include <map>

struct NoCaseTreeValue4 { public: unsigned char m_data[4]; };
class AsciiString { public: void *m_data; };
struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &left, const AsciiString &right) const;
};

// Use the complete value-copy provider at retail 0x00466EA7.
// A trivial local AsciiString view must not supply the selected pair copy.
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NoCasePairCopy;
namespace _STL {
template <> NoCasePairCopy::pair(const NoCasePairCopy &);
}

typedef _STL::_Rb_tree<AsciiString, _STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::_Select1st<_STL::pair<const AsciiString, NoCaseTreeValue4> >, BfmeStringNoCaseLess, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > > NoCaseTree4CF550;

template NoCaseTree4CF550::_Link_type NoCaseTree4CF550::_M_clone_node(NoCaseTree4CF550::_Link_type);

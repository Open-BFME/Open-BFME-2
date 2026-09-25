// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport _Construct<T> placement-copy helper for the nested hint-tree pair,
// same-shape sibling of the rowed _Construct<AsciiString> at 0x0002C485
// (45 bytes; see stlport_construct_asciistring.cpp). The body is the
// null-guarded placement-new copy delegating out-of-line to the pair's own
// rowed copy ctor, and __EH_prolog resolves via its matched row. The key is
// a two-AsciiString pair and the mapped value an opaque 16-byte payload,
// matching the retail pair encoding exactly.

#include <memory>

class AsciiString
{
public:
	AsciiString(const AsciiString &other);

private:
	char m_pad[4];
};

struct TreeOpaqueMapped0032CB55
{
	char m_body[16];
};

typedef _STL::pair<AsciiString, AsciiString> ConstructInnerPair;
typedef _STL::pair<const ConstructInnerPair, TreeOpaqueMapped0032CB55> ConstructNestedPair;

template void _STL::_Construct<ConstructNestedPair, ConstructNestedPair>(ConstructNestedPair *, const ConstructNestedPair &);

// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport _Construct<pair<const NameKeyType, FXList>> placement-copy helper.
// Retail 0x0016CC30 (29 bytes) is the null-guarded placement-new copy over
// 12 bytes (4B key + 8B value), called by the hashtable _M_new_node at
// 0x0016D670 (matched row in FXList.cpp). FXList is an 8B POD here so the
// copy inlines to three movs; the null guard comes from _Construct itself
// (AsciiString precedent in stlport_construct_asciistring.cpp).

#include <memory>

enum NameKeyType
{
	NK_NONE = 0
};

class FXList
{
public:
	int m_a;
	int m_b;
};

typedef _STL::pair<const NameKeyType, FXList> FXListPair;

template void _STL::_Construct<FXListPair, FXListPair>(FXListPair *, const FXListPair &);

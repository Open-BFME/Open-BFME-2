// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Target facts: retail 0x004650A0..0x00465122 is a 132-byte get-or-create
// body. It calls the int-key lower-bound twin at 0x00382A92, compares the
// signed key with node+0x10, constructs a key/value pair through 0x00523DB7
// on a miss, calls the hinted-insert body at 0x00464984, destroys the narrow
// string temporaries through 0x00036410, and returns node+0x14.
//
// Structural inference: this follows STLport map subscript's lower-bound,
// default-value, hinted-insert pattern. The return slot and teardown support
// a four-byte narrow-string view; the helper at 0x00523DB7 is pinned through
// a pair<const int, AsciiString> spelling. Neither the owning class nor the
// exact map specialization is established, so the exported method stays
// address-derived and AsciiString is used only as a layout-compatible view.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(T) T()
#include <map>
#include "ascii_string.h"

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef _STL::pair<const int, AsciiString> Rva004650A0Pair;
typedef _STL::map<int, AsciiString, _STL::less<int>,
	_STL::allocator<Rva004650A0Pair> > Rva004650A0Map;

class Rva004650A0 : public Rva004650A0Map
{
public:
	typedef Rva004650A0Map::iterator Iterator;
	typedef Rva004650A0Map::value_type Value;

	Iterator rva00464984(Iterator hint, const Value &value);
	AsciiString &rva004650A0(const int &key);
};

AsciiString &Rva004650A0::rva004650A0(const int &key)
{
	Iterator it = lower_bound(key);
	if (it == end() || key_comp()(key, (*it).first))
	{
		AsciiString empty;
		it = rva00464984(it, Value(key, empty));
	}
	return (*it).second;
}

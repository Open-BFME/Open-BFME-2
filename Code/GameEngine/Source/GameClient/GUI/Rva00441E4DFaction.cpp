// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00441E4DFaction@@YA_NPAXABVAsciiString@@@Z @0x00441E4D 129B.
// Honest-address Faction prefix check over a map at +8. Normalizes the name
// to Faction prefix via startsWith/set/concat then finds it in the map.
// Evidence: strings Faction; callees rowed 0x2BE9C 0x55F5 0x6987 0x1F8437;
// caller 0x004426D1; mirrors PlayerPosition::rva003023B8.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> AsciiPreferenceMap;

Bool Rva00441E4DFaction(void *holder, const AsciiString &name)
{
	AsciiPreferenceMap *m = (AsciiPreferenceMap *)((char *)holder + 8);
	if (m->empty())
		return true;
	AsciiString tmp(name);
	if (!((const StringBase<char> &)name).startsWith("Faction")) {
		((StringBase<char> &)(AsciiString &)tmp).set("Faction");
		((StringBase<char> &)(AsciiString &)tmp).concat((const StringBase<char> &)name);
	}
	return m->find(tmp) != m->end();
}

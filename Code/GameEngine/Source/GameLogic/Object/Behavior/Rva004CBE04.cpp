// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// stlport
//
// ?rva004CBE04@Rva004CBE04@@QAE_NABVAsciiString@@PAURva002C99FB@@@Z, retail 0x004CBE04, 45 bytes.
// Map-backed fetch: find key in map at +0x1C8 via rowed AsciiString _M_find,
// false when it equals end; else assign value at found+0x14 through rowed
// operator= 0x002C99FB into out and true. Stride and +0x14 from retail.
// Evidence: callees rowed 0x001F8437 plus 0x002C99FB; caller at 0x004CBE5C.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
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

struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva002C99FB
{
	int m_first;
	OpaqueRefElement4 m_second;
	Rva002C99FB &operator=(const Rva002C99FB &other);
};

class Rva004CBE04
{
public:
	bool rva004CBE04(const AsciiString &key, Rva002C99FB *out);
private:
	char m_pad[0x1C8];
	_STL::map<AsciiString, Rva002C99FB> m_map;
};

bool Rva004CBE04::rva004CBE04(const AsciiString &key, Rva002C99FB *out)
{
	_STL::map<AsciiString, Rva002C99FB>::iterator it = m_map.find(key);
	if (it != m_map.end()) {
		*out = it->second;
		return true;
	}
	return false;
}

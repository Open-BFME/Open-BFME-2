// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
// ?rva002AD5ED@Rva002AD5ED@@QAEMABVAsciiString@@@Z @0x002AD5ED 60B. Float lookup by name key in map at +0x288, miss returns BfmeZeroRange. Evidence: unlock lane, callees nameToKey 0x0009FA65 and _M_find 0x00388F63 rowed, data TheNameKeyGenerator and BfmeZeroRange, caller 0x0033A69A, neighbours Rva002AD19EArmor and PlayerO1Shard share RTS shard flags.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "ascii_string.h"

enum NameKeyType
{
	NK_Zero = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva002AD5ED
{
	char _pad[0x288];
public:
	_STL::map<int, int> m_map;
	float rva002AD5ED(const AsciiString &name);
};

float Rva002AD5ED::rva002AD5ED(const AsciiString &name)
{
	int key = TheNameKeyGenerator->nameToKey(name);
	_STL::map<int, int>::iterator it = m_map.find(key);
	if (it != m_map.end())
		return *(const float *)&it->second;
	return 0.0f;
}

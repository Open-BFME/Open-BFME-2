// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva002AD629@Player@@QAEHABVAsciiString@@@Z @0x002AD629 (56B): Player
// map<int, int> lookup by name. The name goes through the pinned
// NameKeyGenerator::nameToKey(const AsciiString &) 0x0009FA65 and the key
// through the rowed int-key _M_find 0x00388F63 on the map at Player +0x2D0;
// a hit returns the mapped int (node +0x14), a miss 0. Same shape as the
// rowed find twin Rva004E9600::rva004E95D4. No REL32 caller (address-only
// reference), so the name stays address-derived and the int return type is a
// structural inference.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class AsciiString;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Player
{
public:
	int rva002AD629(const AsciiString &name);

private:
	char m_pad[0x2D0];
	_STL::map<int, int> m_2d0;			// +0x2D0
};

int Player::rva002AD629(const AsciiString &name)
{
	int key = TheNameKeyGenerator->nameToKey(name);
	_STL::map<int, int>::iterator it = m_2d0.find(key);
	if (it != m_2d0.end())
		return (*it).second;
	return 0;
}

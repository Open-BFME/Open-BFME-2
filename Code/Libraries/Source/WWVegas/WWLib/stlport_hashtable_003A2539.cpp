// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x003A2539, 37 bytes. Hashtable node creation for AsciiString key
// with TreeHintPayload00207343 mapped value (same pair as
// stlport_rb_tree_hint_00302081).
// ?rva003A2539@Rva003A2539@@QAEPAURva003A2539Node@@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload00207343@@@_STL@@@Z
// Honest address name: __thiscall (ret 4: const pair&, ignores this, returns
// node*). Allocates 12 bytes via rowed byte allocator 0x307F0, clears next,
// constructs pair at +4 via rowed _Construct 0x2058E3. Caller at 0x3A2F33
// links node into Eva buckets and returns pair at +4. Layout follows
// _Hashtable_node (next + value).
typedef unsigned int UnsignedInt;

#include <map>

#include "ascii_string.h"

struct TreeHintPayload00207343
{
	unsigned char value;
	~TreeHintPayload00207343();
};

typedef _STL::pair<const AsciiString, TreeHintPayload00207343> TreeHintPair00207343;

namespace _STL
{
template <>
void _Construct<TreeHintPair00207343, TreeHintPair00207343>(
	TreeHintPair00207343 *, const TreeHintPair00207343 &);
template <>
class allocator<char>
{
public:
	static char *allocate(UnsignedInt bytes, const void *hint);
};
}

struct Rva003A2539Node
{
	void *_M_next;
	TreeHintPair00207343 _M_val;
};

class Rva003A2539
{
public:
	Rva003A2539Node *rva003A2539(const TreeHintPair00207343 &value);
};

Rva003A2539Node *Rva003A2539::rva003A2539(const TreeHintPair00207343 &value)
{
	Rva003A2539Node *node =
		(Rva003A2539Node *)_STL::allocator<char>::allocate(12, 0);
	node->_M_next = 0;
	_STL::_Construct(&node->_M_val, value);
	return node;
}

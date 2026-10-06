// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005537EB@Rva005537EB@@QAEGXZ @0x005537EB 49B: Rb sum walks header +0x10 via increment summing word +0x12. Evidence: unlock lane calls rowed increment 0x00024250 plus callers 0x0038B08F 0x005BE01F plus empty check left versus header.
#include <deque>

namespace _STL
{
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

// ?rva005537BA@Rva005537BA@@QAEGXZ @0x005537BA 49B.
// Target evidence: Ghidra gives a 49-byte boundary immediately before the
// matched 49-byte Rb sum at 0x005537EB. Both walk the leftmost node, add its
// word at +0x12, and advance through the rowed _M_increment at 0x00024250.
// This body reads its header pointer at this+4; the adjacent sibling reads
// its header at this+0x10. Original class and method identities are unknown.
struct Rva005537BANode : public _STL::_Rb_tree_node_base
{
	unsigned short data10;
	unsigned short data12;
};

class Rva005537BA
{
	char pad00[4];
	Rva005537BANode *header04;
public:
	unsigned short rva005537BA();
};

unsigned short Rva005537BA::rva005537BA()
{
	unsigned short sum = 0;
	Rva005537BANode *node = (Rva005537BANode *)header04->_M_left;
	while (node != header04)
	{
		sum += node->data12;
		node = (Rva005537BANode *)_STL::_Rb_global<bool>::_M_increment(node);
	}
	return sum;
}

struct Rva005537EBNode : public _STL::_Rb_tree_node_base
{
	unsigned short data10;
	unsigned short data12;
};
class Rva005537EB
{
	char pad00[0x10];
	Rva005537EBNode *header10;
public:
	unsigned short rva005537EB();
};
unsigned short Rva005537EB::rva005537EB()
{
	unsigned short sum = 0;
	Rva005537EBNode *node = (Rva005537EBNode *)header10->_M_left;
	while (node != header10)
	{
		sum += node->data12;
		node = (Rva005537EBNode *)_STL::_Rb_global<bool>::_M_increment(node);
	}
	return sum;
}

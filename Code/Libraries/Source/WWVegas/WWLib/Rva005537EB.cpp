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

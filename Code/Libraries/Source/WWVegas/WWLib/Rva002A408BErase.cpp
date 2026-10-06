// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002A408B@Rva002A408B@@QAEXPAURva002A408BNode@@@Z, retail 0x002A408B, 59 bytes. Rb erase-one: rebalance-for-erase then destroy pair<AsciiString AudioEventRTS> value at +16 and free. Evidence: calls 0x00025620 rebalance plus 0x002A12E1 pair dtor plus _free 0x00030830; dec count at +4 ret 4; same 59B shape as Rva00383F9C 0x00383F9C and Rva00439325 0x00439325; callers 0x002A47BC 0x002A4A03; unblocks 0x002A4975.
#include "ascii_string.h"

extern "C" void __cdecl free(void *block);

class AudioEventRTS;

namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	typedef _Rb_tree_Color_type _Color_type;
	typedef _Rb_tree_node_base *_Base_ptr;
	_Color_type _M_color;
	_Base_ptr _M_parent;
	_Base_ptr _M_left;
	_Base_ptr _M_right;
};
template <class _Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _Rebalance_for_erase(
		_Rb_tree_node_base *__z, _Rb_tree_node_base *&__root,
		_Rb_tree_node_base *&__leftmost, _Rb_tree_node_base *&__rightmost);
};
template <class _T1, class _T2> struct pair
{
	~pair();
};
}

struct Rva002A408BNode : public _STL::_Rb_tree_node_base
{
};

class Rva002A408B
{
	_STL::_Rb_tree_node_base *m_header;
	int m_count;
public:
	void rva002A408B(Rva002A408BNode *pos);
};

void Rva002A408B::rva002A408B(Rva002A408BNode *pos)
{
	_STL::_Rb_tree_node_base *toDelete = _STL::_Rb_global<bool>::_Rebalance_for_erase(
		pos, m_header->_M_parent, m_header->_M_left, m_header->_M_right);
	((_STL::pair<AsciiString, AudioEventRTS> *)(toDelete + 1))->~pair();
	if (toDelete)
		free(toDelete);
	--m_count;
}

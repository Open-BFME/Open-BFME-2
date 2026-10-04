// ?rva003042DD@Rva003042DD@@QAEXPAURva003042DDNode@@0@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003042DD@Rva003042DD@@QAEXPAURva003042DDNode@@0@Z @0x003042DD 68B: Rb erase(first last).
// Evidence: calls rowed clear 0x0022E177 plus rowed erase-one 0x00303DA4 plus rowed _M_increment 0x00024250; caller 0x00304384 pinned erase-key calls with same this; first-begin last-end check then loop erase-first-plusplus.
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
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *__x);
};
}

struct Rva00303DA4Node : public _STL::_Rb_tree_node_base
{
};

class Rva00303DA4
{
public:
	void rva00303DA4(Rva00303DA4Node *__pos);
};

class Rva0022E121
{
public:
	void rva0022E177();
};

struct Rva003042DDNode : public _STL::_Rb_tree_node_base
{
};

class Rva003042DD
{
	_STL::_Rb_tree_node_base *m_header;
	int m_count;
public:
	void rva003042DD(Rva003042DDNode *__first, Rva003042DDNode *__last);
};

// ?rva003042DD@Rva003042DD@@QAEXPAURva003042DDNode@@0@Z present-unmatched
void Rva003042DD::rva003042DD(Rva003042DDNode *__first, Rva003042DDNode *__last)
{
	_STL::_Rb_tree_node_base *__h = m_header;
	if (__first == (_STL::_Rb_tree_node_base *)__h->_M_left && __last == (_STL::_Rb_tree_node_base *)__h) {
		((Rva0022E121 *)this)->rva0022E177();
		return;
	}
	while (__first != __last) {
		Rva003042DDNode *__tmp = __first;
		__first = (Rva003042DDNode *)_STL::_Rb_global<bool>::_M_increment(__first);
		((Rva00303DA4 *)this)->rva00303DA4((Rva00303DA4Node *)__tmp);
	}
}

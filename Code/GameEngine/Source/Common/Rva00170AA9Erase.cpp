// cl: /EHs /MD
// ?rva00170AA9@Rva00170AA9@@QAEXPAURva00170AA9Node@@@Z 0x00170AA9 59B
// Rb erase-one: rebalance-for-erase then destroy RefCountPtr TextureClass value
// at +16 via rowed 0x0017098D and free 0x00030830, then --count at +4, ret 4.
// Evidence: callees 0x00025620 plus 0x0017098D plus 0x00030830 all rowed;
// callers at 0x00170BA5 and 0x00170D2C; same 59B shape as 0x00383380.
extern "C" void __cdecl free(void *block);

template <class T> class RefCountPtr { public: ~RefCountPtr(); };
class TextureClass;
typedef RefCountPtr<TextureClass> Rva00170AA9Value;

namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	typedef _Rb_tree_Color_type _Color_type;
	typedef _Rb_tree_node_base* _Base_ptr;
	_Color_type _M_color;
	_Base_ptr _M_parent;
	_Base_ptr _M_left;
	_Base_ptr _M_right;
};
template <class _Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base* __cdecl _Rebalance_for_erase(
		_Rb_tree_node_base* __z, _Rb_tree_node_base*& __root,
		_Rb_tree_node_base*& __leftmost, _Rb_tree_node_base*& __rightmost);
};
}

struct Rva00170AA9Node : public _STL::_Rb_tree_node_base
{
};

class Rva00170AA9
{
	_STL::_Rb_tree_node_base* m_header;
	int m_count;
public:
	void rva00170AA9(Rva00170AA9Node* pos);
};

void Rva00170AA9::rva00170AA9(Rva00170AA9Node* pos)
{
	_STL::_Rb_tree_node_base* toDelete = _STL::_Rb_global<bool>::_Rebalance_for_erase(
		pos, m_header->_M_parent, m_header->_M_left, m_header->_M_right);
	((Rva00170AA9Value*)(toDelete + 1))->~Rva00170AA9Value();
	if (toDelete)
		free(toDelete);
	--m_count;
}

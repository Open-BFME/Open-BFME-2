// cl: /GX-
// ?rva00358DC2@Rva00358DC2@@QAEXPAURva00358DC2Node@@@Z @0x00358DC2 (59B):
// Rb erase-one: rebalance-for-erase then destroy Rva00358B65 value at +16 and free.
// Evidence: calls 0x00025620 rebalance-erase plus 0x00358B65 dtor plus _free 0x00030830;
// same 59B shape as Rva00383F9C erase 0x00383F9C.
extern "C" void __cdecl free(void *block);

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
}

struct Rva00358B65
{
	~Rva00358B65();
};

struct Rva00358DC2Node : public _STL::_Rb_tree_node_base
{
};

class Rva00358DC2
{
	_STL::_Rb_tree_node_base *m_header;
	int m_count;
public:
	void rva00358DC2(Rva00358DC2Node *pos);
};

void Rva00358DC2::rva00358DC2(Rva00358DC2Node *pos)
{
	_STL::_Rb_tree_node_base *toDelete = _STL::_Rb_global<bool>::_Rebalance_for_erase(
		pos, m_header->_M_parent, m_header->_M_left, m_header->_M_right);
	((Rva00358B65 *)(toDelete + 1))->~Rva00358B65();
	if (toDelete)
		free(toDelete);
	--m_count;
}

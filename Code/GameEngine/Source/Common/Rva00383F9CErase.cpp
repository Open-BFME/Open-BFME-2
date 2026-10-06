// cl: /MD /EHsc
// ?rva00383F9C@Rva00383F9C@@QAEXPAURva00383F9CNode@@@Z 0x00383F9C 59B
// Rb erase: rebalance-for-erase then destroy Rva value at +16 and free.
// Evidence: calls 0x00025620 rebalance-erase plus 0x00382B3F dtor plus _free; caller 0x00384F07.
extern "C" void __cdecl free(void* block);

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

struct BuddyInfo
{
	~BuddyInfo();
};

struct Rva00382B3F
{
	unsigned int m_00;
	BuddyInfo m_04;
	~Rva00382B3F();
};

struct Rva00383F9CNode : public _STL::_Rb_tree_node_base
{
	Rva00382B3F m10;
};

class Rva00383F9C
{
	_STL::_Rb_tree_node_base* m_header;
	int m_count;
public:
	void rva00383F9C(Rva00383F9CNode* pos);
};

void Rva00383F9C::rva00383F9C(Rva00383F9CNode* pos)
{
	_STL::_Rb_tree_node_base* toDelete = _STL::_Rb_global<bool>::_Rebalance_for_erase(
		pos, m_header->_M_parent, m_header->_M_left, m_header->_M_right);
	((Rva00383F9CNode*)toDelete)->m10.~Rva00382B3F();
	if (toDelete)
		free(toDelete);
	--m_count;
}

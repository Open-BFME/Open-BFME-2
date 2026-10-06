// cl: /EHs /MD
// ?rva003833BB@Rva003833BB@@QAEXPAURva003833BBNode@@@Z 0x003833BB 53B
// Rb _M_erase: recurse-right via +12 walk-left via +8 destroy value at +16 via rowed CameraMarker dtor 0x29D7C2 and free 0x30830 ret 4.
// Evidence: callees 0x29D7C2 plus 0x30830 both rowed; caller clear 0x383A28 pushes root at +4 and resets header; same 53B shape as landed erases 0x380EB1 and 0x4D1B38.
extern "C" void __cdecl free(void *block);

struct CameraMarker
{
	~CameraMarker();
};

struct Rva003833BBNode
{
	unsigned int m_color;
	Rva003833BBNode *m_parent;
	Rva003833BBNode *m_left;
	Rva003833BBNode *m_right;
};

class Rva003833BB
{
public:
	void rva003833BB(Rva003833BBNode *node);
};

void Rva003833BB::rva003833BB(Rva003833BBNode *node)
{
	while (node)
	{
		rva003833BB(node->m_right);
		Rva003833BBNode *left = node->m_left;
		((CameraMarker *)(node + 1))->~CameraMarker();
		free(node);
		node = left;
	}
}

// ?rva00383A28@Rva00383A28@@QAEXXZ 0x00383A28 41B
// _Tree::clear counterpart to erase 0x003833BB: if count at +4 nonzero erase
// root at header+4 then reset left/parent/right and count.
// Evidence: sole callee 0x003833BB rowed in this TU; callers at 0x383A51
// 0x383EB2 0x38407F 0x385B78; same 41B shape as clear 0x383EEA in BfmeConv802.cpp.
class Rva00383A28
{
public:
	void rva00383A28();
private:
	Rva003833BBNode *m_header;
	unsigned int m_count;
};

void Rva00383A28::rva00383A28()
{
	if (m_count != 0)
	{
		((Rva003833BB *)this)->rva003833BB(m_header->m_parent);
		m_header->m_left = m_header;
		m_header->m_parent = 0;
		m_header->m_right = m_header;
		m_count = 0;
	}
}

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

struct Rva00383380Node : public _STL::_Rb_tree_node_base
{
};

// ?rva00383380@Rva00383380@@QAEXPAURva00383380Node@@@Z 0x00383380 59B
// Rb erase-one: rebalance-for-erase then destroy CameraMarker value at +16 and free.
// Evidence: calls 0x00025620 rebalance-erase plus 0x0029D7C2 CameraMarker dtor
// plus free 0x00030830; callers at 0xA79C6 0xA7A2A 0xA81F5 0x383A84 0x463E3C;
// same 59B shape as 0x383F9C in Rva00383F9CErase.cpp.
class Rva00383380
{
	_STL::_Rb_tree_node_base* m_header;
	int m_count;
public:
	void rva00383380(Rva00383380Node* pos);
};

void Rva00383380::rva00383380(Rva00383380Node* pos)
{
	_STL::_Rb_tree_node_base* toDelete = _STL::_Rb_global<bool>::_Rebalance_for_erase(
		pos, m_header->_M_parent, m_header->_M_left, m_header->_M_right);
	((CameraMarker*)(toDelete + 1))->~CameraMarker();
	if (toDelete)
		free(toDelete);
	--m_count;
}

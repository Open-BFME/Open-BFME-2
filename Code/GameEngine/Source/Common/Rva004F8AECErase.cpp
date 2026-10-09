// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva004F8AEC@Rva004F8AEC@@QAEXPAURva004F8AECNode@@@Z retail 0x004F8AEC 53B
// Rb _M_erase: recurse-right via +12 walk-left via +8 destroy value at +16 via pinned Rva004F7DD4 dtor 0x004F7DD4 and free 0x30830 ret 4.
// Evidence: callees 0x004F7DD4 pin plus 0x30830 rowed; caller clear 0x004F8DD4 pushes root at +4 and resets header; same 53B shape as landed erases 0x003833BB and 0x00502610.
extern "C" void __cdecl free(void *block);

struct Rva004F7DD4
{
	~Rva004F7DD4();
};

struct Rva004F8AECNode
{
	unsigned int m_color;
	Rva004F8AECNode *m_parent;
	Rva004F8AECNode *m_left;
	Rva004F8AECNode *m_right;
};

class Rva004F8AEC
{
public:
	void rva004F8AEC(Rva004F8AECNode *node);
};

void Rva004F8AEC::rva004F8AEC(Rva004F8AECNode *node)
{
	while (node)
	{
		rva004F8AEC(node->m_right);
		Rva004F8AECNode *left = node->m_left;
		((Rva004F7DD4 *)(node + 1))->~Rva004F7DD4();
		free(node);
		node = left;
	}
}

// ?rva004F8DD4@Rva004F8DD4@@QAEXXZ retail 0x004F8DD4 41B
// Rb clear counterpart to erase 0x004F8AEC: if count at +4 nonzero erase root
// at header+4 then reset left/parent/right and count.
// Evidence: sole callee 0x004F8AEC rowed in this TU; caller at 0x004F938D;
// same 41B shape as clear 0x00383A28 in Rva003833BBErase.cpp.
class Rva004F8DD4
{
public:
	void rva004F8DD4();
private:
	Rva004F8AECNode *m_header;
	unsigned int m_count;
};

void Rva004F8DD4::rva004F8DD4()
{
	if (m_count != 0)
	{
		((Rva004F8AEC *)this)->rva004F8AEC(m_header->m_parent);
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

struct Rva004F88BBNode : public _STL::_Rb_tree_node_base
{
};

// ?rva004F88BB@Rva004FA168Map@@QAEXURva004F88BBIterator@@@Z retail 0x004F88BB 59B
// Rb erase-one: rebalance-for-erase then destroy Rva004F7DD4 value at +16 and free.
// Evidence: calls 0x00025620 rebalance-erase plus 0x004F7DD4 pin plus free
// 0x00030830; callers at 0x004F8D8A 0x004F927F; same 59B shape as 0x00383380
// in Rva003833BBErase.cpp.
// Caller4F922C constructs and copies a one-word iterator in its argument
// slot. Keep the map receiver and iterator contract while preserving the
// native rebalance, mapped-value cleanup and node free.
struct Rva004F88BBIterator {
 void *node;
 Rva004F88BBIterator(void *p):node(p){}
 Rva004F88BBIterator(const Rva004F88BBIterator &p):node(p.node){}
};
class Rva004FA168Map
{
	_STL::_Rb_tree_node_base* m_header;
	int m_count;
 unsigned unknown8;
public:
	void rva004F88BB(Rva004F88BBIterator pos);
};

void Rva004FA168Map::rva004F88BB(Rva004F88BBIterator pos)
{
	_STL::_Rb_tree_node_base* toDelete = _STL::_Rb_global<bool>::_Rebalance_for_erase(
		static_cast<Rva004F88BBNode *>(pos.node), m_header->_M_parent, m_header->_M_left, m_header->_M_right);
	((Rva004F7DD4*)(toDelete + 1))->~Rva004F7DD4();
	if (toDelete)
		free(toDelete);
	--m_count;
}

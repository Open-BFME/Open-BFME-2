// ?rva0039F7A5@Rva0039F7A5@@QAEXXZ
// partial score=0.95 date=2026-10-06
// cl: /O1 /Oy- /MD
//
// ?rva0039F7A5@Rva0039F7A5@@QAEXXZ @0x0039F7A5 127B: max-scan over an
// RB tree with indirect chaining, range-17 dump lane.
//
// Clears the +0xB0/+0xB4 maxima, walks the +0xA4 tree through the rowed
// STLport _M_increment 0x00024250: per node the +0x18 item's +0x0C feeds
// the +0xB0 max, then its +0x334 chain is drained through the rowed
// 0x005C4AF5 getter held as a function pointer, each element's +0x34
// feeding the +0xB4 max. Maxima store value+1 on >= (unsigned).

namespace _STL
{

struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Dummy>
class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};

}

class Rva005C4AF5DwordField
{
public:
	int get() const;
};

// Indirect dispatch through the rowed 0x005C4AF5 getter: __fastcall
// carries the single pointer in ecx exactly like its __thiscall.
typedef int (Rva005C4AF5DwordField::*Rva0039F7A5Hook)() const;

struct Rva0039F7A5Item
{
	char m_pad00[0x0c]; // +0x00
	int m_0c; // +0x0C
	char m_pad10[0x334 - 0x10];
	void *m_head334; // +0x334
};

struct Rva0039F7A5Elem
{
	char m_pad00[0x34]; // +0x00
	int m_34; // +0x34
};

struct Rva0039F7A5Node
{
	_STL::_Rb_tree_node_base m_link; // +0x00
	char m_pad10[8]; // +0x10
	Rva0039F7A5Item *m_item18; // +0x18
};

class Rva0039F7A5
{
public:
	void rva0039F7A5();

private:
	char m_pad00[0xa4];
	_STL::_Rb_tree_node_base *m_headerA4; // +0xA4
	char m_padA8[0xb0 - 0xa8];
	unsigned int m_maxB0; // +0xB0
	unsigned int m_maxB4; // +0xB4
};

// ?rva0039F7A5@Rva0039F7A5@@QAEXXZ
void Rva0039F7A5::rva0039F7A5()
{
	int off = 0;
	m_maxB4 = off;
	m_maxB0 = off;
	Rva0039F7A5Node *node = (Rva0039F7A5Node *)m_headerA4->_M_left;
	if (node != (Rva0039F7A5Node *)m_headerA4) {
		volatile Rva0039F7A5Hook hook = &Rva005C4AF5DwordField::get;
		do {
			Rva0039F7A5Item *item = node->m_item18;
			if ((unsigned int)item->m_0c >= m_maxB0)
				m_maxB0 = item->m_0c + 1;
			Rva0039F7A5Elem *e = (Rva0039F7A5Elem *)item->m_head334;
			while (e != 0) {
				if ((unsigned int)e->m_34 >= m_maxB4)
					m_maxB4 = e->m_34 + 1;
				e = (Rva0039F7A5Elem *)(((Rva005C4AF5DwordField *)(off + (char *)e))->*hook)();
			}
			node = (Rva0039F7A5Node *)_STL::_Rb_global<bool>::_M_increment(&node->m_link);
		} while (node != (Rva0039F7A5Node *)m_headerA4);
	}
}

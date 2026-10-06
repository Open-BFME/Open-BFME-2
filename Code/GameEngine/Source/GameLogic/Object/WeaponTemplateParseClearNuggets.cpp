// cl: /DNDEBUG /MD /GX-
//
// ?Rva002CA8E8Parse@@YAXPAVINI@@PAX1PBX@Z, retail 0x002CA8E8 (90B): the
// ClearNuggets FieldParse proc of the WeaponTemplate table (row 0x00C011D8).
// Walks the nugget list at instance + 0x17C (STLport list<int> nodes holding
// nugget pointers), globally deleting every nugget (virtual destructor in slot
// 0, then operator delete) unless the template's +0x160 flag is set and the
// nugget's +0x124 flag is clear; then empties the list (rowed
// _List_base<int>::clear 0x0023DAA5) and clears the byte at +0x114. Name
// address-derived.

class INI;

class Rva002CA8E8Nugget
{
public:
	virtual ~Rva002CA8E8Nugget();
	unsigned char m_unreconstructed_04[0x124 - 4];
	bool m_124;
};

struct Rva002CA8E8Node
{
	Rva002CA8E8Node *m_next;
	Rva002CA8E8Node *m_prev;
	int m_data;
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class _List_base;
template <> class _List_base<int, allocator<int> >
{
public:
	void clear();
	Rva002CA8E8Node *_M_node;
};
}

struct Rva002CA8E8Template
{
	unsigned char m_unreconstructed_000[0x114];
	bool m_114;
	unsigned char m_unreconstructed_115[0x160 - 0x115];
	bool m_160;
	unsigned char m_unreconstructed_161[0x17C - 0x161];
	_STL::_List_base<int, _STL::allocator<int> > m_nuggets;	// +0x17C
};

// ?Rva002CA8E8Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva002CA8E8Parse(INI *, void *instance, void *, const void *)
{
	Rva002CA8E8Template *self = (Rva002CA8E8Template *)instance;
	_STL::_List_base<int, _STL::allocator<int> > &nuggets = self->m_nuggets;
	for (Rva002CA8E8Node *node = nuggets._M_node->m_next; node != nuggets._M_node; node = node->m_next)
	{
		if (!self->m_160 || ((Rva002CA8E8Nugget *)node->m_data)->m_124)
			::delete (Rva002CA8E8Nugget *)node->m_data;
	}
	nuggets.clear();
	self->m_114 = false;
}

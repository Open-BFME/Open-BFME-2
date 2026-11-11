// cl: /MD
namespace _STL
{
typedef bool _Rb_tree_Color_type;
struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
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
struct ArmyIconMapNode
{
	_STL::_Rb_tree_node_base m_base;
	int m_key;
};
struct ArmyIconMapHeader
{
	char m_00[8];
	ArmyIconMapNode *m_leftmost;
};
#include "../../Include/GameClient/Rva005F2278.h"
#include "../../Include/Common/Rva005E4DAF.h"
class Rva005E4E1B
{
public:
	void rva005E4E1B();
private:
	char m_00[0x14];
	Rva005F2278 *m_14;
	char m_pad18[0x1C - 0x18];
	ArmyIconMapHeader *m_1C;
};
void Rva005E4E1B::rva005E4E1B()
{
	ArmyIconMapHeader *end = m_1C;
	ArmyIconMapNode *it = end->m_leftmost;
	if (it == (ArmyIconMapNode *)end)
		return;
	do {
		int k = it->m_key;
		if (m_14->rva005F2278(k))
			((Rva005E4DAF *)this)->Deselect(k);
		it = (ArmyIconMapNode *)&*_STL::_Rb_global<bool>::_M_increment(&it->m_base);
	} while (it != (ArmyIconMapNode *)end);
}

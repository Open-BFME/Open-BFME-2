// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva00170DB7@Rva00170BFF@@QAE?AURva00170DB7Out@@ABVRva00170999@@@Z @0x00170DB7 134B.
// The boundary is in reverse/ghidra_functions.csv. Caller 0x00170EFE uses this
// helper when its insertion hint cannot prove a neighboring slot. Its target
// walk compares the first unsigned dword of Rva00170999 with the node value at
// +0x10, returning an 8-byte iterator/flag record or inserting through the
// rowed worker at 0x00170BFF. The container and value identities remain
// address-derived; the record models only observed return bytes and layout.
#include <map>

class Rva00170999;

struct Rva00170EFENode
{
	unsigned int _color;
	Rva00170EFENode *_parent;
	Rva00170EFENode *_left;
	Rva00170EFENode *_right;
	char _value10[0x14];
};

struct Rva00170EFEIter
{
	Rva00170EFENode *node;
	Rva00170EFEIter &operator--()
	{
		node = (Rva00170EFENode *)_STL::_Rb_global<bool>::_M_decrement(
			(_STL::_Rb_tree_node_base *)node);
		return *this;
	}
};

struct Rva00170DB7Out
{
	Rva00170EFENode *node;
	bool inserted;
	Rva00170DB7Out(const Rva00170EFEIter &iter, bool flag)
		: node(iter.node), inserted(flag) {}
};

class Rva00170BFF
{
	Rva00170EFENode *_00Head;
	int _04Flag;
public:
	Rva00170EFEIter rva00170BFF(Rva00170EFENode *x,
		Rva00170EFENode *y, const Rva00170999 &value,
		Rva00170EFENode *w);
	Rva00170DB7Out rva00170DB7(const Rva00170999 &value);
};

Rva00170DB7Out Rva00170BFF::rva00170DB7(const Rva00170999 &value)
{
	Rva00170EFENode *y = _00Head;
	Rva00170EFENode *x = _00Head->_parent;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = _STL::less<unsigned int>()(
			*(const unsigned int *)&value,
			*(const unsigned int *)x->_value10);
		x = comp ? x->_left : x->_right;
	}
	Rva00170EFEIter j;
	j.node = y;
	if (comp && y == _00Head->_left)
		return Rva00170DB7Out(rva00170BFF(y, y, value, 0), true);
	if (comp)
		--j;
	if (_STL::less<unsigned int>()(
		*(const unsigned int *)((Rva00170EFENode *)j.node)->_value10,
		*(const unsigned int *)&value))
		return Rva00170DB7Out(rva00170BFF(x, y, value, 0), true);
	return Rva00170DB7Out(j, false);
}

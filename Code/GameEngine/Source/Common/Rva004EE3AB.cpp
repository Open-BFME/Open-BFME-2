// cl: /MD
// ?rva004EE3AB@Rva004EE3AB@@QAEHABV?$BitFlags@$0HE@@@0@Z, retail 0x004EE3AB, 78 bytes.
// RB-tree sum with BitFlags filter: tree at +0xC0, sums +0x14 where +0x10 obj non-null
// and its +0x108 flags pass testSetAndClear. Evidence: rowed 0x0030A146 0x00024250;
// prev 0x004EE35D /O1 /MD sibling same shape at +0xB4; ret 8 two args.
template <int N>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const;
private:
	unsigned m_words[7];
};

namespace _STL
{
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class D> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

struct Rva004EE3ABObj
{
	char m_pad[0x108];
	BitFlags<116> m_flags;
};

struct Rva004EE3ABNode : _STL::_Rb_tree_node_base
{
	Rva004EE3ABObj *m_10;
	int m_14;
};

class Rva004EE3AB
{
public:
	int rva004EE3AB(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear);
private:
	char m_pad[0xC0];
	_STL::_Rb_tree_node_base *m_C0;
};

int Rva004EE3AB::rva004EE3AB(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear)
{
	_STL::_Rb_tree_node_base *node = m_C0->_M_left;
	int sum = 0;
	while (node != m_C0) {
		Rva004EE3ABNode *n = (Rva004EE3ABNode *)node;
		if (n->m_10 && n->m_10->m_flags.testSetAndClear(mustBeSet, mustBeClear))
			sum += n->m_14;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return sum;
}

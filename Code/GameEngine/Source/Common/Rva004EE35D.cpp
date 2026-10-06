// cl: /MD
// ?rva004EE35D@Rva004EE35D@@QAEHABV?$BitFlags@$0HE@@@0@Z, retail 0x004EE35D, 78 bytes.
// RB-tree sum with BitFlags filter: like LivingWorldScoreKeeper::rva004EE33B but tree at
// +0xB4, sums +0x14 where +0x10 obj non-null and its +0x108 flags pass
// testSetAndClear. Evidence: rowed 0x0030A146 0x00024250; prev/next /O1 /MD;
// ret 8 two args; callers 0x005BE469 0x005C0333 0x005C1290 0x005C1347.
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

struct Rva004EE35DObj
{
	char m_pad[0x108];
	BitFlags<116> m_flags;
};

struct Rva004EE35DNode : _STL::_Rb_tree_node_base
{
	Rva004EE35DObj *m_10;
	int m_14;
};

class Rva004EE35D
{
public:
	int rva004EE35D(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear);
private:
	char m_pad[0xB4];
	_STL::_Rb_tree_node_base *m_B4;
};

int Rva004EE35D::rva004EE35D(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear)
{
	_STL::_Rb_tree_node_base *node = m_B4->_M_left;
	int sum = 0;
	while (node != m_B4) {
		Rva004EE35DNode *n = (Rva004EE35DNode *)node;
		if (n->m_10 && n->m_10->m_flags.testSetAndClear(mustBeSet, mustBeClear))
			sum += n->m_14;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return sum;
}

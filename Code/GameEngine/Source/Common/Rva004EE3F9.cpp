// cl: /O1 /MD
// ?rva004EE3F9@Rva004EE3F9@@QAEHABV?$BitFlags@$0HE@@@0@Z, retail 0x004EE3F9, 78 bytes.
// RB-tree sum with BitFlags filter: tree at +0xCC, sums +0x14 where +0x10 obj non-null
// and its +0x108 flags pass testSetAndClear. Evidence: rowed 0x0030A146 0x00024250;
// prev 0x004EE3AB /O1 /MD sibling same shape at +0xC0; ret 8 two args.
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

struct Rva004EE3F9Obj
{
	char m_pad[0x108];
	BitFlags<116> m_flags;
};

struct Rva004EE3F9Node : _STL::_Rb_tree_node_base
{
	Rva004EE3F9Obj *m_10;
	int m_14;
};

class Rva004EE3F9
{
public:
	int rva004EE3F9(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear);
private:
	char m_pad[0xCC];
	_STL::_Rb_tree_node_base *m_CC;
};

int Rva004EE3F9::rva004EE3F9(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear)
{
	_STL::_Rb_tree_node_base *node = m_CC->_M_left;
	int sum = 0;
	while (node != m_CC) {
		Rva004EE3F9Node *n = (Rva004EE3F9Node *)node;
		if (n->m_10 && n->m_10->m_flags.testSetAndClear(mustBeSet, mustBeClear))
			sum += n->m_14;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return sum;
}

class Rva00261C89
{
public:
	bool rva00261C89();
};

struct Rva004EE485Node : _STL::_Rb_tree_node_base
{
	Rva00261C89 *m_10;
	int m_14;
};

class Rva004EE485
{
public:
	int rva004EE485();
private:
	char m_pad[0xC0];
	_STL::_Rb_tree_node_base *m_C0;
};

int Rva004EE485::rva004EE485()
{
	_STL::_Rb_tree_node_base *node = m_C0->_M_left;
	int sum = 0;
	while (node != m_C0) {
		Rva004EE485Node *n = (Rva004EE485Node *)node;
		if (n->m_10 && n->m_10->rva00261C89())
			sum += n->m_14;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return sum;
}

class Rva004EE447
{
public:
	int rva004EE447();
private:
	char m_pad[0xB4];
	_STL::_Rb_tree_node_base *m_B4;
};

int Rva004EE447::rva004EE447()
{
	_STL::_Rb_tree_node_base *node = m_B4->_M_left;
	int sum = 0;
	while (node != m_B4) {
		Rva004EE485Node *n = (Rva004EE485Node *)node;
		if (n->m_10 && n->m_10->rva00261C89())
			sum += n->m_14;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return sum;
}

class Rva004EE4C3
{
public:
	int rva004EE4C3();
private:
	char m_pad[0xCC];
	_STL::_Rb_tree_node_base *m_CC2;
};

int Rva004EE4C3::rva004EE4C3()
{
	_STL::_Rb_tree_node_base *node = m_CC2->_M_left;
	int sum = 0;
	while (node != m_CC2) {
		Rva004EE485Node *n = (Rva004EE485Node *)node;
		if (n->m_10 && n->m_10->rva00261C89())
			sum += n->m_14;
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	return sum;
}

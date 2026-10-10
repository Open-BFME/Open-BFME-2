// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1Rva001E72B4@@UAE@XZ, retail 0x001E72B4..0x001E7389 (213 bytes, EH):
// a subsystem's destructor (opaque pin of its scalar deleting destructor;
// table 0x00BDE970), sibling of Rva001FF909Dtor.cpp. It ::deletes the value
// of every node of its int-keyed tree at +0x0C and clears it (rowed
// 0x001E6731), ::deletes every object of its pointer vector at +0x18 by
// index and empties it (rowed vector<void *> erase 0x0031BD55); then the
// vector storage goes to GameFree, the tree wrapper dies (its inline
// destructor runs the rowed tree destructor 0x001E6F27; its out-of-line copy
// for the unwind map is the rowed 0x001E6FE5), and SubsystemInterface last.
// Owner and element identities are not established.
#include <vector>

void __cdecl Rva00030830GameFree(void *);
namespace _STL {
struct _Rb_tree_node_base;
template<> inline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
template<> vector<void *>::iterator vector<void *>::erase(iterator first, iterator last);
}

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	int m_04;
	int m_08;
};

class Rva001E72B4Owned
{
public:
	virtual ~Rva001E72B4Owned();
};

struct Rva001E72B4Node
{
	int m_color;
	Rva001E72B4Node *m_parent;
	Rva001E72B4Node *m_left;
	Rva001E72B4Node *m_right;
	int m_key;
	Rva001E72B4Owned *m_value;
};

namespace _STL {
template <class _Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

class Rva001E6731
{
public:
	~Rva001E6731();
	void rva001E6731();
	Rva001E72B4Node *m_header;
	int m_count;
	int m_compare;
};

struct Rva001E6FE5
{
	~Rva001E6FE5() {}
	Rva001E72B4Node *header() const { return m_tree.m_header; }
	void clear() { m_tree.rva001E6731(); }
	Rva001E6731 m_tree;
};

class Rva001E72B4 : public SubsystemInterface
{
public:
	virtual ~Rva001E72B4();
private:
	Rva001E6FE5 m_map;			// +0x0C
	_STL::vector<void *> m_owned;		// +0x18
};

Rva001E72B4::~Rva001E72B4()
{
	for (Rva001E72B4Node *node = m_map.header()->m_left; node != m_map.header();
	     node = reinterpret_cast<Rva001E72B4Node *>(
		     _STL::_Rb_global<bool>::_M_increment(reinterpret_cast<_STL::_Rb_tree_node_base *>(node))))
		::delete node->m_value;
	m_map.clear();
	for (unsigned int i = 0; i < m_owned.size(); ++i)
		::delete static_cast<Rva001E72B4Owned *>(m_owned[i]);
	m_owned.clear();
}

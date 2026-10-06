// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002241AC@Rva000427195@@QAEPAURva002241ACNode@@ABVRva0022304A@@@Z @0x002241AC 37B
// STLport hashtable _M_new_node of the AsciiString-keyed hash_map (class Rva000427195, the
// family of bucketIndex 0x00223149): a 0x18-byte node from the rowed byte allocator
// 0x000307F0, next cleared, the pair Rva0022304A placement-copied at +4 by the rowed
// _Construct 0x002238B4; no catch block; ret 4 (this unused).
// Evidence: node size 0x18 = next + AsciiString + 16-byte Rva0022300F (pair layout from the
// rowed ctor 0x002233F0); sole caller 0x002249ED (_M_insert) links the node into a bucket.
#include "ascii_string.h"

namespace _STL
{
template <class T> class allocator;
template <> class allocator<char>
{
public:
	static char *allocate(unsigned int bytes, const void *hint);
};
template <class T1, class T2> void _Construct(T1 *p, const T2 &value);
}

class Rva0022300F
{
public:
	Rva0022300F(const Rva0022300F &o);
	~Rva0022300F();
private:
	int m_body[4];
};

class Rva0022304A
{
public:
	Rva0022304A(const Rva0022304A &o);
private:
	AsciiString m_head;
	Rva0022300F m_item;
};

struct Rva002241ACNode
{
	Rva002241ACNode *next;
	Rva0022304A value;
};

class Rva000427195
{
public:
	Rva002241ACNode *rva002241AC(const Rva0022304A &obj);
};

Rva002241ACNode *Rva000427195::rva002241AC(const Rva0022304A &obj)
{
	Rva002241ACNode *node = (Rva002241ACNode *)_STL::allocator<char>::allocate(sizeof(Rva002241ACNode), 0);
	node->next = 0;
	_STL::_Construct(&node->value, obj);
	return node;
}

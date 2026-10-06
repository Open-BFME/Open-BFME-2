// ?rva00224BDB@Rva00224BDBMap@@QAEAAVRva0022300F@@ABVAsciiString@@@Z
// partial score=0.9 date=2026-10-06
// ?rva00224BDB@Rva00224BDBMap@@QAEAAVRva0022300F@@ABVAsciiString@@@Z
// partial score=0.9 date=2026-10-04
// ?rva00224BDB@Rva00224BDBMap@@QAEAAVRva0022300F@@ABVAsciiString@@@Z
// partial score=0.9 date=2026-10-01
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva00224BDB@Rva00224BDBMap@@QAEAAVRva0022300F@@ABVAsciiString@@@Z @0x00224BDB 155B
// Find-or-insert lookup keyed by AsciiString, the binding table at
// BfmeAptWindowManager+0x48 (caller bfmeSetText 0x00225301). The shape is the
// STLport hash_map::operator[] ternary: find (rowed 0x0041534B, iterator returned
// through a hidden pointer, null node means end), and on a miss build a
// default Rva0022300F (0x002231E7) and the key/value pair (0x002233F0), insert
// it (0x002249ED) and return the value at pair+4; on a hit return node+8. The
// two conditional temporaries are tracked by the bit flags at ebp-0x10 and
// destroyed by the rowed 0x0022304A / 0x0022300F. The container's real
// template identity is not established, so names stay address-derived.
#include "ascii_string.h"

class Rva0022300F
{
public:
	Rva0022300F();
	~Rva0022300F();
private:
	char m_body[0x10];
};

class Rva0022304A
{
public:
	Rva0022304A(const AsciiString &head, const Rva0022300F &item);
	~Rva0022304A();

	AsciiString m_head;
	Rva0022300F m_item;
};

struct Rva00224BDBNode
{
	Rva00224BDBNode *m_next;
	Rva0022304A m_value;
};

class Rva00056F61;

// The rowed iterator find 0x0041534B (Code/GameEngine/Source/GameClient/
// Rva00056F61IterFind.cpp), shared with the other AsciiString-keyed tables.
struct Rva0041534BIter
{
	Rva00224BDBNode *m_node;
	Rva00056F61 *m_table;
	Rva0041534BIter(Rva00224BDBNode *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
	bool operator==(const Rva0041534BIter &o) const { return m_node == o.m_node; }
};

class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
	Rva0022304A &rva002249ED(const Rva0022304A &value);
	Rva0041534BIter end() { return Rva0041534BIter(0, this); }
};

class Rva00224BDBMap
{
public:
	Rva0022300F &rva00224BDB(const AsciiString &key);
private:
	Rva00056F61 m_table;
};

Rva0022300F &Rva00224BDBMap::rva00224BDB(const AsciiString &key)
{
	Rva0041534BIter it = m_table.rva0041534B(&key);
	return it == m_table.end()
		? m_table.rva002249ED(Rva0022304A(key, Rva0022300F())).m_item
		: it.m_node->m_value.m_item;
}

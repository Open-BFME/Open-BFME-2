// cl: /DNDEBUG /MD
// ?rva00286214@Rva00286214@@QAEPAURva00286214Node@@PBVRva00285672@@@Z @ 0x00286214 73B
// BST lower_bound find over nodes with key at +0x10: left at +8 right at +0xC.
// Uses rowed Rva00285672 less compare (node key vs key then key vs best key).
// Callers at 0x00286683 0x00286A57 0x00286C5C 0x002880A2 0x0028819B.
// Shape levers: the loop is written as an explicit goto bottom test so MSVC
// rotates it (target's jmp-to-test), and the tail is `best == table || compare`
// so both true arms share the single `best = table` store.
class Rva00285672
{
public:
	bool rva00285672(const Rva00285672 &) const;
	char m_lead[8]; // +0x00
	int m_first; // +0x08
	int m_second; // +0x0C
};

struct FireCellCentre
{
	int x;
	int y;
};
struct Rva00286214Node
{
	void *pad0;
	Rva00286214Node *link4;
	Rva00286214Node *m_left;
	Rva00286214Node *linkC;
	char m_pad10[8];
	FireCellCentre m_key;
};

struct Rva002860CFIterator
{
	Rva00286214Node *m_node;
	Rva002860CFIterator(Rva00286214Node *node) : m_node(node) {}
	Rva002860CFIterator(const Rva002860CFIterator &that) : m_node(that.m_node) {}
};

class Rva002860CFHost
{
public:
	void rva002860CF(Rva002860CFIterator it);
private:
	void *m_ptr; // +0x00
	int m_4; // +0x04
};

struct Rva00287B2AResult
{
	Rva00287B2AResult(Rva00286214Node *node, bool inserted) : m_node(node), m_inserted(inserted) {}
	Rva00286214Node *m_node;
	bool m_inserted;
};

class Rva00286214
{
public:
	Rva00286214Node *rva00286214(const Rva00285672 *key);
	void erase(Rva002860CFIterator pos) { ((Rva002860CFHost *)this)->rva002860CF(pos); }
	Rva00286214();	// the map's default ctor 0x00242F01
	~Rva00286214();	// the tree teardown 0x0028681A
 __declspec(noinline) Rva00287B2AResult rva00287B2A(const Rva00285672 *key);	// insert 0x00287B2A
	Rva00286214Node *m_header;
	unsigned int m_size;	// +0x04
	unsigned int size() const { return m_size; }
	char m_pad08[4];
};

Rva00286214Node *Rva00286214::rva00286214(const Rva00285672 *key)
{
	Rva00286214Node *table = m_header;
	Rva00286214Node *best = table;
	Rva00286214Node *n = table->link4;
	if (!n)
		goto test;
body:
	if (!reinterpret_cast<const Rva00285672 *>(n->m_pad10)->rva00285672(*key)) {
		best = n;
		n = n->m_left;
	}
	else
		n = n->linkC;
test:
	if (n)
		goto body;
	if (best == table || key->rva00285672(*reinterpret_cast<const Rva00285672 *>(best->m_pad10)))
		best = table;
	return best;

}

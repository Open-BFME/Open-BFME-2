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
	bool rva00285672(const Rva00285672 &other) const;
	char m_lead[8];
	int m_first;
	int m_second;
};

struct Rva00286214Node
{
	void *pad0;
	Rva00286214Node *link4;
	Rva00286214Node *link8;
	Rva00286214Node *linkC;
	Rva00285672 key;
};

class Rva00286214
{
public:
	Rva00286214Node *rva00286214(const Rva00285672 *key);
private:
	Rva00286214Node *m_table;
};

Rva00286214Node *Rva00286214::rva00286214(const Rva00285672 *key)
{
	Rva00286214Node *table = m_table;
	Rva00286214Node *best = table;
	Rva00286214Node *n = table->link4;
	if (!n)
		goto test;
body:
	if (!n->key.rva00285672(*key)) {
		best = n;
		n = n->link8;
	}
	else
		n = n->linkC;
test:
	if (n)
		goto body;
	if (best == table || key->rva00285672(best->key))
		best = table;
	return best;

}

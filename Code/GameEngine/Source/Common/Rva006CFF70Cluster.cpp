// cl: /DNDEBUG /MD
//
// Address-derived recovery of the 59-byte chain-node prepend at RVA 0x006CFF70
// (ret 4, this in ecx, one const& argument). Identity is proven by its own
// neighbourhood, not guessed: the matched sibling remove
// ?rva006CFFE0@Rva008951B0Owner@@QAEXABVRva008951B0Handle@@@Z (0x006CFFE0, see
// Rva006CFFE0Remove.cpp) walks the same node {Entry* at +0, Node* next at +4}
// and frees it through ?freeBlock@Rva006DB270@@QAEXPAXH@Z at 0x006DB270 via the
// pool instance at 0x00E176E8. This body allocates that same 8-byte node from
// the rowed pool allocBlock ?allocBlock@Rva006DB160@@QAEPAXH@Z (0x006DB160),
// stores the argument handle's node into +0, zeroes +4 and links the node at
// the owner's head. Every callee is rowed; the name is not, so it stays
// address-derived.

class Rva006DB160
{
public:
	void *allocBlock(int blockSize);
};

extern class Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva008951B0Entry;

class Rva008951B0Node
{
public:
	Rva008951B0Entry *m_bfmeEntry;
	Rva008951B0Node *m_bfmeNext;
};

class Rva008951B0Handle
{
public:
	Rva008951B0Entry *m_bfmeNode;
};

class Rva008951B0Owner
{
public:
	void rva006CFF70(const Rva008951B0Handle &h);

	Rva008951B0Node *m_bfmeHead;
};

// ?rva006CFF70@Rva008951B0Owner@@QAEXABVRva008951B0Handle@@@Z
void Rva008951B0Owner::rva006CFF70(const Rva008951B0Handle &h)
{
	Rva008951B0Node *node = (Rva008951B0Node *)(*(Rva006DB160 **)&g_pChainBlockAllocator)->allocBlock(8);
	if (node) {
		node->m_bfmeEntry = h.m_bfmeNode;
		node->m_bfmeNext = 0;
	} else {
		node = 0;
	}
	node->m_bfmeNext = m_bfmeHead;
	m_bfmeHead = node;
}

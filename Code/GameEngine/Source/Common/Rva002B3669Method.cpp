// cl: /DNDEBUG /MD
// ?rva002B3669@Rva002BA8F1Logic@@QAE_NXZ @0x002B3669 19B: Rva002BA8F1Logic method
// returning byte at item +0xAA or false. Evidence: same shape as sibling rva002B3740
// in PinnedForwarders1830.cpp; callee 0x002B2B2D pin-only; caller 0x0023DA5B.

struct Rva002B3740Item
{
	char m_pad[0xAA];
	bool m_aa;
};

class Rva002BA8F1Logic
{
public:
	Rva002B3740Item *rva002B2B2D();
	bool rva002B3669();
};

bool Rva002BA8F1Logic::rva002B3669()
{
	Rva002B3740Item *item = rva002B2B2D();
	if (!item)
		return false;
	return item->m_aa;
}

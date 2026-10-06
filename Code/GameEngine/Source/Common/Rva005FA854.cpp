// cl: /DNDEBUG /MD
// ?rva005FA854@Rva005FA854@@QAE_NXZ @0x005FA854 32B evidence: thiscall bool
// over m_00; null yields false; else pinned thiscall-0
// ?rva005FEC0C@Rva005FA854Inner@@QAEXXZ @0x005FEC0C on m_00 (ecx already
// holds this, no reload); then logical-not of m_00->m_10 (xor plus cmp
// plus sete, MSVC not-shape) reloaded after the call. TU-local view only.
class Rva005FA854Inner
{
public:
	void rva005FEC0C();
	int m_pad[4];
	int m_10;
};

class Rva005FA854
{
public:
	bool rva005FA854();
private:
	Rva005FA854Inner *m_00;
};



bool Rva005FA854::rva005FA854()
{
	Rva005FA854Inner *r = m_00;
	if (!r)
		return false;
	r->rva005FEC0C();
	return !m_00->m_10;
}

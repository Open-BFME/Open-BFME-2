// cl: /DNDEBUG /MD
// ?rva00366500@Rva00366500@@QAE_NH@Z 0x00366500 45B bitfield setter at +0xC bits 4-9 mask 0x3F0 callers 0x0052E6E6 0x0052E914 0x00366E2E

class Rva00366500
{
	unsigned int m_pad00;
	unsigned int m_pad04;
	unsigned int m_pad08;
	unsigned int m_field0C;
public:
	bool rva00366500(int v);
	bool rva0036652D(int v);
};

bool Rva00366500::rva00366500(int v)
{
	unsigned int cur = m_field0C;
	unsigned int field = (cur >> 4) & 0x3f;
	if (field == (unsigned int)v)
		return false;
	m_field0C = (cur & ~0x3f0u) | (((unsigned int)v << 4) & 0x3f0u);
	return true;
}

bool Rva00366500::rva0036652D(int v)
{
	unsigned int cur = m_field0C;
	unsigned int field = (cur >> 10) & 0x3f;
	if (field == (unsigned int)v)
		return false;
	m_field0C = (cur & ~0xfc00u) | (((unsigned int)v << 10) & 0xfc00u);
	return true;
}

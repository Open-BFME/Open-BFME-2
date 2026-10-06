// cl: /MD
//
// ?rva00318CEB@Rva00318CEB@@QAE_NPBURva00318CEBOther@@@Z, retail 0x00318CEB, 26 bytes.
// Null-checked equality: if other is null returns false else returns
// other->m_14 == this->m_54 via sub/neg/sbb/inc. Callers are FUN_006BC971
// at 0x002BCA19 and FUN_006BEECD at 0x002BEF14. Identity beyond the two
// offsets is unproven so the name stays honest address-derived.

struct Rva00318CEBOther
{
	char m_pad[0x14];
	int m_14;
};

class Rva00318CEB
{
public:
	bool rva00318CEB(const Rva00318CEBOther *other);
private:
	char m_pad[0x54];
	int m_54;
};

bool Rva00318CEB::rva00318CEB(const Rva00318CEBOther *other)
{
	if (other == 0)
		return false;
	return other->m_14 == m_54;
}

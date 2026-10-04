// cl: /O1 /DNDEBUG /MD
// ?rva002C943B@Rva002C943B@@QAEXPBURva002C943BSrc@@@Z, retail 0x002C943B, 39 bytes.
// Five-field copy with first field via +0x04 pointer plus +0x0C.
// Evidence: unlock lane; caller 0x002C8D2A; prev/next TU flags.
struct Rva002C943BInner { int m_0C[4]; int m_0C_val; };
struct Rva002C943BSrc {
	char m_pad00[4];
	Rva002C943BInner *m_04;
	char m_pad08[0x10 - 0x08];
	int m_10;
	int m_14;
	int m_18;
	char m_pad1C[0x28 - 0x1C];
	int m_28;
};
class Rva002C943B {
public:
	void rva002C943B(const Rva002C943BSrc *src);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};
void Rva002C943B::rva002C943B(const Rva002C943BSrc *src)
{
	m_00 = *(int *)((char *)src->m_04 + 0x0c);
	m_04 = src->m_14;
	m_08 = src->m_10;
	m_0C = src->m_28;
	m_10 = src->m_18;
}

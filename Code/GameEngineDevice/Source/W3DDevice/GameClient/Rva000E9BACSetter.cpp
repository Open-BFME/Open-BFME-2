// cl: /MD
// ?rva000E9CFB@Rva000E9BAC@@QAEXABVRva000E3A8D@@@Z @0x000E9CFB 29B: vector assign at +0x4FB60 plus flag at +0x4FB5E.
// Evidence: retail lea ecx [esi+0x4FB60] calls rowed 0x000E3A8D then mov byte [esi+0x4FB5E],1; offsets match Rva000E9BAC member at 0x4FB60; caller 0x00069CE6.

class Rva000E3A8D
{
public:
	Rva000E3A8D &rva000E3A8D(const Rva000E3A8D &other);
private:
	char m_pad[12];
};

class Rva000E9BAC
{
public:
	void rva000E9CFB(const Rva000E3A8D &other);
private:
	char m_pad00[0x4FB5E];
	bool m_flag5E;
	char m_pad5F;
	Rva000E3A8D m_vec60;
};

void Rva000E9BAC::rva000E9CFB(const Rva000E3A8D &other)
{
	m_vec60.rva000E3A8D(other);
	m_flag5E = true;
}

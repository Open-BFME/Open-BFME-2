// cl: /MD
// ?rva000EDF23@Rva000EDF23@@QAEXABVRva000E3A8D@@@Z @0x000EDF23 29B: vector assign at +0x44548 plus flag at +0x44546.
// Evidence: retail lea ecx [esi+0x44548] calls rowed 0x000E3A8D then mov byte [esi+0x44546],1; same shape as rowed 0x000E9CFB setter; caller 0x00069CE6.

class Rva000E3A8D
{
public:
	Rva000E3A8D &rva000E3A8D(const Rva000E3A8D &other);
private:
	char m_pad[12];
};

class Rva000EDF23
{
public:
	void rva000EDF23(const Rva000E3A8D &other);
private:
	char m_pad00[0x44546];
	bool m_flag46;
	char m_pad47;
	Rva000E3A8D m_vec48;
};

void Rva000EDF23::rva000EDF23(const Rva000E3A8D &other)
{
	m_vec48.rva000E3A8D(other);
	m_flag46 = true;
}

// cl: /O1 /MD
// ?rva000EF137@Rva000EF137@@QAEXABVRva000E3A8D@@@Z 0x000EF137 29: vector-member assign plus flag set.
// Evidence: callee rowed ?rva000E3A8D@Rva000E3A8D@@QAEAAV1@ABV1@@Z at 0x000E3A8D; caller at 0x00069CE6; offsets +0x2EE0A flag and +0x2EE0C vector match W3DPropBuffer gap but owner unproven so honest Rva name.
class Rva000E3A8D
{
public:
	Rva000E3A8D &rva000E3A8D(const Rva000E3A8D &other);
private:
	void *m_start;
	void *m_finish;
	void *m_end;
};
class Rva000EF137
{
public:
	void rva000EF137(const Rva000E3A8D &other);
private:
	char m_pad[0x2EE0A];
	unsigned char m_flag0A;
	char m_pad0B;
	Rva000E3A8D m_vec;
};
void Rva000EF137::rva000EF137(const Rva000E3A8D &other)
{
	m_vec.rva000E3A8D(other);
	m_flag0A = 1;
}

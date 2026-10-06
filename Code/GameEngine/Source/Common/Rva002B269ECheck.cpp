// cl: /O1 /MD
//
// ?rva002B269E@Rva002B269E@@QAE_NH@Z retail 0x002B269E 50 bytes.
// Leaf check: null-gated id compare at +0x98/+0x14 plus rowed id-gated
// Rva002E071E::rva002E0BC0 (int return, tested as byte) then byte at +0x10b.
// Identity via pin plus callers 0x0009C84C and rowed Rva0056B613Forward
// 0x0056B626 and rowed callee 0x002E0BC0; prev/next share /O1 /MD.
class Rva002E071E
{
public:
	int rva002E0BC0(int id);
	char m_pad[0x14];
	int m_14;
};

class Rva002B269E
{
public:
	bool rva002B269E(int id);
private:
	char m_pad[0x98];
	Rva002E071E *m_98;
	char m_pad9C[0x10b - 0x9c];
	bool m_10b;
};

bool Rva002B269E::rva002B269E(int id)
{
	Rva002E071E *p = m_98;
	if (!p)
		return false;
	if (id == p->m_14)
		return true;
	if ((unsigned char)p->rva002E0BC0(id) != 0)
		return m_10b;
	return false;
}

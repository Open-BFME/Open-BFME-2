// cl: /MD
//
// ?rva005F83F4@Rva005F83F4@@QAEXABURva005F83F4Data@@@Z @0x005F83F4 20B.
// Evidence: unlock lane; 3x movsd 12B from arg to [m_04+0x0C];
// callers 0x005E8892 0x005E8EC5; prev/next Rva000AD6F4Members.

struct Rva005F83F4Data
{
	int m_data[3];
};

struct Rva005F83F4Inner
{
	char m_pad[0x0c];
	Rva005F83F4Data m_field;
};

class Rva005F83F4
{
public:
	void rva005F83F4(const Rva005F83F4Data &src);
	char m_lead[4];
	Rva005F83F4Inner *m_ptr;
};

void Rva005F83F4::rva005F83F4(const Rva005F83F4Data &src)
{
	m_ptr->m_field = src;
}

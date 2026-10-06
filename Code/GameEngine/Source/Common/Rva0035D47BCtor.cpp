// cl: /MD
//
// ??0Rva0035D47B@@QAE@XZ @ 0x0035D45A 33B.
// Ctor via base Rva001DBAA4 plus vtable 0x008164F0 with +4=2 +9=1 +0xC=0.
// Evidence: vtable store 0x008164F0 same as dtor 0x0035D47B, callee 0x001DBAA4 row.
class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_4;
	bool m_8;
	bool m_9;
	bool m_A;
	char m_padB;
	int m_C;
};

class Rva0035D47B : public Rva001DBAA4
{
public:
	Rva0035D47B();
	virtual ~Rva0035D47B();
};

Rva0035D47B::Rva0035D47B()
{
	m_C = 0;
	m_4 = 2;
	m_9 = true;
}

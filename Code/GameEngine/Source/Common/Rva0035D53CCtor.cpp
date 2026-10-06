// cl: /MD
//
// ??0Rva0035D53C@@QAE@XZ @0x0035D6B8 37B.
// Ctor via base Rva001DBAA4 plus vtable 0x00816510 with +4=6 +9=1 +0xC=0 +0x20=-1.
// Evidence: vtable store, caller 0x0035D71B, callee 0x001DBAA4 row.
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

class Rva0035D53C : public Rva001DBAA4
{
public:
	Rva0035D53C();
	virtual ~Rva0035D53C();
private:
	char m_pad10[0x20 - 0x10];
	int m_20;
};

Rva0035D53C::Rva0035D53C()
{
	m_4 = 6;
	m_9 = true;
	m_C = 0;
	m_20 = -1;
}

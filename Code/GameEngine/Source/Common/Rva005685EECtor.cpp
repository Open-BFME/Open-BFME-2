// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva005685EE@@QAE@PAXPAXPAX@Z @0x0056858C 98B.
// Constructor: base Rva005C3549(a,b,c) (pinned 0x005C3697), store vptr
// 0x00C6CF74, then m_member.m_value = new Rva0056833F(this,a,b) (0x28
// bytes, pinned 0x0056833F); a null new stays null. Sibling shape of the
// unlanded Rva005C3549 ctor 0x005C3697 and of the rowed Rva00577838 ctor
// (new-inner-into-member). The dtor TU keeps Rva0056850D::m_value private;
// it is public here only for the single store, layout identical.
class Rva005C3549
{
public:
	virtual ~Rva005C3549();
	Rva005C3549(void *a, void *b, void *c);
};

class Rva0056833F
{
public:
	virtual ~Rva0056833F();
	Rva0056833F(void *owner, void *a, void *b);
private:
	char m_pad[0x24];
};

struct Rva0056850D
{
	void *m_value;
};

class Rva005685EE : public Rva005C3549
{
public:
	virtual ~Rva005685EE();
	Rva005685EE(void *a, void *b, void *c);
private:
	char m_unmodelled_04[0x8];
	Rva0056850D m_member;	// +0xC
};

Rva005685EE::Rva005685EE(void *a, void *b, void *c)
	: Rva005C3549(a, b, c)
{
	m_member.m_value = new Rva0056833F(this, a, b);
}

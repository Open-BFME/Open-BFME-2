// cl: /O1 /DNDEBUG /MD /EHsc
//
// Rva0053ED1A follow-on methods around 0x0053EF7B/0x0053EFAE.
// Evidence: same class view as Rva0053ED1ACtor.cpp (primary
// GameEngineDeletingBase at +0, secondary Rva005C6D4D at +0xC covering
// +0xC..+0x47, vector at +0x48 with end pointer at +0x4C, ints at +0x54
// and +0x58). 0x0053EFAE reads +0x58/+0x54, conditionally calls 0x0053EF7B
// with ecx intact, then tail-jumps to the secondary-base method at
// 0x005C6D9C with ecx=this+0xC. 0x0053EF7B stores +0x58 to +0x54, then
// dispatches on it: zero tail-calls 0x0053EF2E, nonzero takes virtual slot
// 5 (0x14) on the secondary base. Names are generated; the secondary
// base's real type and the callees' identities are not established.

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

class Rva005C6D4D
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	void rva005C6D9C();
	void rva0053EF2EHelper();
private:
	char m_pad04[0x38];
};

class Rva0053ED1A : public GameEngineDeletingBase, public Rva005C6D4D
{
public:
	void rva0053EF7B();
	void rva0053EFAE();
	void rva0053EF2E();
private:
	char m_vec48[0x0C];
	int m_at54;
	int m_at58;
};

void Rva0053ED1A::rva0053EF7B()
{
	m_at54 = m_at58;
	if (m_at58 != 0)
		static_cast<Rva005C6D4D *>(this)->v5();
	else
		rva0053EF2E();
}

void Rva0053ED1A::rva0053EFAE()
{
	if (m_at58 != m_at54)
		rva0053EF7B();
	static_cast<Rva005C6D4D *>(this)->rva005C6D9C();
}

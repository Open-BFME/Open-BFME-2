// cl: /DNDEBUG /MD

// ?rva0039F56E@Rva0039F56E@@QAEXXZ, RVA 0x0039F56E, 41B. Chain lane: container
// reset; when the +4 flag is set it tears down the +0/+4 chain through rowed
// 0x0039EA21, self-links the head at +8/+0x0C, clears +4s and the flag. The
// +4 chain element type is the rowed teardown TU's node (forward-declared;
// only pointers cross here) while the head links are the local honest
// struct. Owner derives from rowed Rva0039EA21 for the inherited teardown
// call with unchanged this. Callers at 0x0039FB26/0x003A2F72/0x0039FB0C.
// Flags copy Rva0039EA21.cpp (no EH frame in retail).
struct Rva0039EA21Node;

struct Rva0039F56ELinks {
	int m_00;
	Rva0039EA21Node *m_04;
	struct Rva0039F56ELinks *m_08;
	struct Rva0039F56ELinks *m_0c;
};

class Rva0039EA21
{
public:
	void rva0039EA21(Rva0039EA21Node *n);
};

class Rva0039F56E : public Rva0039EA21
{
public:
	void rva0039F56E();
private:
	Rva0039F56ELinks *m_00;
	int m_04;
};

void Rva0039F56E::rva0039F56E()
{
	if (!m_04)
		return;
	rva0039EA21(m_00->m_04);
	m_00->m_08 = m_00;
	m_00->m_04 = 0;
	m_00->m_0c = m_00;
	m_04 = 0;
}

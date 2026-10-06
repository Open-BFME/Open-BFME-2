// cl: /DNDEBUG /MD
//
// ??0Rva00495C22@@QAE@XZ @0x00495C22 33B.
// Calls the rowed 4-byte ??0Rva00360D26Member@@QAE@XZ, then stores 0.0f at
// +4 (xorps) and the pooled 1.0f at +8 (VA 0x00BBB8D8). No vptr.

class Rva00360D26Member
{
public:
	Rva00360D26Member();

private:
	unsigned int m_record;
};

class Rva00495C22 : public Rva00360D26Member
{
public:
	Rva00495C22();

private:
	float m_a;
	float m_b;
};

Rva00495C22::Rva00495C22()
{
	m_a = 0.0f;
	m_b = 1.0f;
}

// cl: /O1 /DNDEBUG /MD
//
// ?rva00509753@Made002CC7DE@@QAEXHH@Z retail 0x00509753 45B.
// Forward (a,b) to Rva002CA9CA at +0x128 when present, then tail to
// Rva0020AA00Target::notify at +0x12c when present.
// Evidence: prev Made002CC7DE ctor zeroes +0x128/+0x12c; base size 0x128;
// callees rowed/pinned; chain via 0x002CAC6E.
class Rva002CA9CA
{
public:
	void rva002CAC6E(int a, int b);
};

class Rva0020AA00Target
{
public:
	void notify(int a, int b);
};

class Rva00507823
{
public:
	Rva00507823();
private:
	unsigned char m_pad[0x128];
};

class Made002CC7DE : public Rva00507823
{
public:
	void rva00509753(int a, int b);
private:
	Rva002CA9CA *m_128;		// +0x128
	Rva0020AA00Target *m_12C;	// +0x12C
};

void Made002CC7DE::rva00509753(int a, int b)
{
	Rva002CA9CA *p1 = m_128;
	if (p1 != 0)
		p1->rva002CAC6E(a, b);
	Rva0020AA00Target *p2 = m_12C;
	if (p2 == 0)
		return;
	p2->notify(a, b);
}

// cl: /Ob0

class Rva007F0210
{
	int m_00;
	const void *m_table;
	int m_08;

public:
	Rva007F0210 &set(int a, int b);
};

// BFME1 stores 0x0107301C here, BFME2 0x00BBAC1C: an address, not a scalar.
static int dummyTableAnchor;

Rva007F0210 &Rva007F0210::set(int a, int b)
{
	m_00 = a;
	m_08 = b;
	m_table = &dummyTableAnchor;
	return *this;
}

// cl: /Ob0

class Rva007F0210
{
	int m_00;
	const void *m_table;
	int m_08;

public:
	Rva007F0210(int a, int b);
};

// BFME1 stores 0x0107301C here, BFME2 0x00BBAC1C: an address, not a scalar.
static int dummyTableAnchor;

// The (int, int) constructor of the online-service records: retail calls
// 0x0065D090 only from the 64 .CRT$XCU dynamic initializers of file-scope
// records (StaticTagInitializers.cpp, StaticTagInitializerC6D010.cpp), each
// with ecx = the record, and the body returns this.
Rva007F0210::Rva007F0210(int a, int b)
{
	m_00 = a;
	m_08 = b;
	m_table = &dummyTableAnchor;
}

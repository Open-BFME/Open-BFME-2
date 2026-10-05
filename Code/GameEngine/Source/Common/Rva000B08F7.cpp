// cl: /O1 /DNDEBUG /MD
// ?rva000B08F7@Rva000B08F7@@QAEXXZ @0x000B08F7 147B
// Chain from Pod36 one-arg 0x000B0899 plus E16 one-arg 0x000B086E. Large clear with two 0x1000 int blocks plus vector resizes. Evidence: calls rowed Pod36 resize plus E16 resize, members 0x80B0 E16 plus 0x80BC Pod36 plus 0x120E0-E8 plus loop 0xB0 0x40B0, callers 0x000B0ACD plus 0x000B0C38, prev Pod36 plus next Vslot forwarder.
class BfmeE16Vector
{
	char m_pad[12];
public:
	void resize(unsigned int n);
};

class BfmePod36Vector
{
	char m_pad[12];
public:
	void resize(unsigned int n);
};

class Rva000B08F7
{
public:
	void rva000B08F7();
private:
	char m_pad00[8];
	int m_8;
	int m_C;
	char m_pad10[0x20 - 0x10];
	int m_20;
	int m_24;
	char m_pad28[0x98 - 0x28];
	int m_98;
	int m_9C;
	int m_A0;
	int m_A4;
	int m_A8;
	char m_padAC[0xB0 - 0xAC];
	int m_0B0[0x1000];
	int m_40B0[0x1000];
	BfmeE16Vector m_80B0;
	BfmePod36Vector m_80BC;
	int m_80C8;
	char m_pad80CC[0x120D4 - 0x80CC];
	int m_120D4;
	char m_pad120D8[0x120E0 - 0x120D8];
	int m_120E0;
	int m_120E4;
	int m_120E8;
	int m_120EC;
};

void Rva000B08F7::rva000B08F7()
{
	m_8 = 0;
	m_C = 0;
	m_20 = 0;
	m_24 = 0;
	m_120E0 = 0;
	m_120E4 = 0;
	m_80C8 = 0;
	m_120E8 = 0x81;
	m_120EC = 0x81;
	m_98 = 0;
	m_9C = 0;
	m_A4 = 0;
	m_A0 = 0;
	m_120D4 = 1;
	m_80BC.resize(1);
	m_A8 = 0;
	m_80B0.resize(1);
	for (int i = 0; i < 0x1000; ++i) {
		m_0B0[i] = 0;
		m_40B0[i] = 0;
	}
}

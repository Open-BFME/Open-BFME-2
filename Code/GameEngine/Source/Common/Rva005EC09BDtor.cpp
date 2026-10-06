// cl: /MD /EHsc
// ??1Rva005EC09B@@QAE@XZ retail 0x005EC09B 91B
// Non-virtual dtor: under EH state 2, when the Apt window manager global
// g_bfmeAptWindowManager (VA 0x00DFE4CC) is set, its pinned
// ?method@Rva00224B7DTarget@@QAE_NH@Z 0x00224B7D is called with m_04; then
// member dtors -- rowed ??1Rva005241B0@@QAE@XZ on +0x20, rowed
// ??1Rva0052413E@@QAE@XZ on +0x14, and the +0x10 holder whose inline dtor runs
// the rowed ?rva005FA874@Rva005FA874@@QAEXXZ. Names address-derived.

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00224B7DTarget
{
public:
	bool method(int value);
};

class Rva005FA874
{
public:
	~Rva005FA874()
	{
		rva005FA874();
	}
	void rva005FA874();
private:
	void *m_ptr;
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva005241B0
{
public:
	~Rva005241B0();
private:
	char m_pad[12];
};

class Rva005EC09B
{
public:
	~Rva005EC09B();
private:
	int m_00;
	int m_04;
	char m_pad08[8];
	Rva005FA874 m_10;
	Rva0052413E m_14;
	Rva005241B0 m_20;
};

Rva005EC09B::~Rva005EC09B()
{
	if (g_bfmeAptWindowManager)
		((Rva00224B7DTarget *)g_bfmeAptWindowManager)->method(m_04);
}

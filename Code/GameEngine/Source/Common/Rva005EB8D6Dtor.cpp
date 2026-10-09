// cl: /O1 /MD /EHsc /arch:SSE /G7
// ??1Rva005EB8D6@@QAE@XZ, RVA 0x005EB8D6, 127 bytes.
// Address-based destructor; member offsets and destruction order follow retail accesses. The Apt-manager base relationship is inferred from the call target and the existing manager global declaration.
class AptPlayer
{
public:
	bool RemoveLevel(int value);
};
class AsciiString;
class BfmeAptWindowManager : public AptPlayer
{
public:
	void rva00225375(const AsciiString &, const AsciiString &, bool);
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva0052413E
{
	char m_storage[0x0C];
public:
	~Rva0052413E();
};
class Rva005241B0
{
	char m_storage[0x0C];
public:
	~Rva005241B0();
};
class Rva005242D7
{
	char m_storage[0x0C];
public:
	~Rva005242D7();
};
class Rva005FA874
{
	char m_storage[4];
public:
	void rva005FA874();
	~Rva005FA874() { rva005FA874(); }
};
class Rva00226883
{
	char m_storage[0x0C];
public:
	~Rva00226883();
};
class Rva005EB8D6
{
public:
	char m_pad00[4];
	int m_status;
	char m_pad08[8];
	Rva0052413E m_member10;
	Rva005241B0 m_member1C;
	Rva005242D7 m_member28;
	Rva005FA874 m_member34;
	Rva00226883 m_map38;
	Rva00226883 m_map44;
	~Rva005EB8D6();
};
Rva005EB8D6::~Rva005EB8D6()
{
	if (g_bfmeAptWindowManager != 0)
		g_bfmeAptWindowManager->RemoveLevel(m_status);
}

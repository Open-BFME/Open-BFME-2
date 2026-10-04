// cl: /O1 /G7 /DNDEBUG /MD
// ?rva00262F19@AIUpdateInterface@@UAEXABVRva0035149F@@@Z @0x00262F19 69B leaf via vtable slot 117.
// Evidence: slot 117 (0x1D4) of AIUpdate vtables 0x00847B98 0x0084CA00 0x0084CCA0 0x0084D330 0x008505F8 0x008508C8 0x00852FB0 0x00853AA8 0x00853D30; neighbours AIUpdateInterface /O1; callees rowed 0x0033FCC8 0x00351759 plus pin notify plus g_Va00DBA4E4.
class Rva0035149F
{
public:
	char m_data[12];
};
class Rva0033FCC8
{
public:
	void rva0033FCC8();
};
class Rva00351759
{
public:
	class Rva0035149F &rva00351759(const class Rva0035149F &other);
};
class BfmeSubVfn1A6
{
public:
	void notify(int a, void *b);
};
extern int g_Va00DBA4E4;
class Machine
{
public:
	char m_pad00[0x38];
	unsigned char m_38;
};
class AIUpdateInterface
{
	char m_pad00[0x30 - 4];
	Machine *m_machine;
public:
	virtual void rva00262F19(const class Rva0035149F &arg);
};
void AIUpdateInterface::rva00262F19(const class Rva0035149F &arg)
{
	unsigned char saved = m_machine->m_38;
	m_machine->m_38 = 0;
	((Rva0033FCC8 *)m_machine)->rva0033FCC8();
	((Rva00351759 *)m_machine)->rva00351759(arg);
	int v = g_Va00DBA4E4 * 10;
	((BfmeSubVfn1A6 *)m_machine)->notify(7, (void *)v);
	if (saved)
		m_machine->m_38 = 1;
}

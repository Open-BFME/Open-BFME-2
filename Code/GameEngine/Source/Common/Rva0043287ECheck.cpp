// cl: /MD
// ?rva0043287E@Rva0043287E@@QAEHXZ, retail 0x0043287E, 31 bytes.
// Returns 1 if int at +0x200 > 0 else delegates to Rva00222A8BTarget::rva00222A53.
// Evidence: callers 0x00432AFB 0x00432BCF 0x00432CEE 0x00432D2C; callee row 0x00222A53; global TheRva00222A8BTarget.
class Rva00222A8BTarget
{
public:
	unsigned char rva00222A53();
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva0043287E
{
public:
	int rva0043287E();
private:
	char m_pad[0x200];
	int m_200;
};
int Rva0043287E::rva0043287E()
{
	return (m_200 > 0 || (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva00222A53());
}

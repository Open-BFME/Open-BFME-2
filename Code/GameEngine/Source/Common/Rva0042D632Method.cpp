// cl: /MD
// ?rva0042D632@Rva0042D632@@QAEXXZ @0x0042D632 74B: state switch on inner +8 driving Apt invokes.
// Evidence: rowed free invoke 0x00516F21 (strings SetState _fadeOut) plus pin 0x0022277D;
// caller 0x0042C39A; neighbours 0x0042D55B 0x0042D697.

class Rva00222A8BTarget
{
public:
	void rva0022277D(void *owner);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
#pragma comment(linker, "/alternatename:?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")

void __cdecl Rva00516F21Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const char *value);

struct Rva0042D632Inner
{
	char m_pad00[4];
	void *m_04;
	unsigned int m_08;
};

class Rva0042D632
{
public:
	void rva0042D632();
private:
	Rva0042D632Inner *m_00;
};

void Rva0042D632::rva0042D632()
{
	switch (m_00->m_08)
	{
	case 1:
		TheRva00222A8BTarget->rva0022277D(m_00->m_04);
		m_00->m_08 = 0;
		break;
	case 2:
		Rva00516F21Invoke(TheRva00222A8BTarget, m_00->m_04, "SetState", "_fadeOut");
		m_00->m_08 = 3;
		break;
	}
}

// cl: /MD
// ?update@Rva0042D5DD@@QAEXXZ @0x0042D5DD 85B: Apt fade-state update via rowed Rva00516F21Invoke 0x00516F21 (SetState/_fadeIn) or rowed Rva002224FE 0x002224FE on the manager at 0x00DFE4CC. Evidence: count at inner +8 selecting Invoke path (3-4) or setter path (0); strings verified; REL32s to rowed callees.
class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
#pragma comment(linker, "/alternatename:?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")

void Rva00516F21Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const char *value);

class Rva002224FE
{
public:
	bool rva002224FE(int index);
};

struct Rva0042D5DDInner
{
	char m_pad00[4];
	void *m_04;
	int m_08;
};

class Rva0042D5DDHost
{
public:
	void update();
private:
	Rva0042D5DDInner *m_00;
};

void Rva0042D5DDHost::update()
{
	int c = m_00->m_08;
	if (c != 0) {
		if (c > 2 && c <= 4) {
			Rva00516F21Invoke(TheRva00222A8BTarget, m_00->m_04, "SetState", "_fadeIn");
			m_00->m_08 = 2;
		}
		return;
	}
	((Rva002224FE *)TheRva00222A8BTarget)->rva002224FE((int)m_00->m_04);
	m_00->m_08 = 1;
}

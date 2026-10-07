// cl: /DNDEBUG /MD
//
// ?rva005EB825@Rva005EB825@@QAEXXZ, retail 0x005EB825, 85 bytes.
// State switch through inner at +0: clears +0xC, case 1 calls pinned
// Rva00222A8BTarget::rva0022277D with +0x4 then clears state, cases 2 and 5
// call rowed Rva00516F21Invoke with SetState/_fadeOut then set state 3.
// Evidence: string literals _fadeOut SetState, extern TheRva00222A8BTarget,
// rowed 0x00516F21 plus pinned 0x0022277D, caller jmp at 0x005EB8C5,
// offsets +0 +0x4 +0x8 +0xC from retail.
class Rva00222A8BTarget
{
public:
	// Native provider compares the incoming 32-bit index with 14 and returns AL.
	bool rva0022277D(int index);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
void __cdecl Rva00516F21Invoke(Rva00222A8BTarget *t, void *p, const char *a, const char *b);

struct Rva005EB825Inner
{
	char m_pad00[0x4];
	void *m_04;
	int m_08;
	int m_0C;
};

class Rva005EB825
{
public:
	void rva005EB825();
private:
	Rva005EB825Inner *m_00;
};

void Rva005EB825::rva005EB825()
{
	m_00->m_0C = 0;
	switch (m_00->m_08) {
	case 1:
		TheRva00222A8BTarget->rva0022277D(reinterpret_cast<int>(m_00->m_04));
		m_00->m_08 = 0;
		break;
	case 2:
	case 5:
		Rva00516F21Invoke(TheRva00222A8BTarget, m_00->m_04, "SetState", "_fadeOut");
		m_00->m_08 = 3;
		break;
	default:
		break;
	}
}

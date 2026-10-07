// ?rva00574A19@Rva00574A19@@QAEXH@Z
// partial score=0.78 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00574A19@Rva00574A19@@QAEXH@Z retail 0x00574A19 98B
// Ghidra boundary is 98B. The method obtains a pointer through the rowed
// +4 ptr-chase getter at 0x0042D6B4, builds a temporary TreeHintRef from the
// rowed Rva00574499 global via the direct 0x005744DD factory call, assigns it
// to this+0x6C, releases the temporary, then calls the rowed one-arg forwarder
// at 0x001FF3A9. The dummy stack word and all outer field meanings are unknown.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ref;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	__forceinline ~TreeHintRef00217D4C()
	{
		if (m_ref != 0)
			ReleaseTreeHintRef00217D4C(m_ref);
	}
};
class Rva0042D6B4PtrChaseField
{
public:
	int get() const;
};
class Rva00574499
{
public:
	TreeHintRef00217D4C rva005744DD();
};
class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &ref);
};
extern unsigned g_Va00E0630C;
class Rva00574A19
{
public:
	void rva00574A19(int unused);
private:
	char m_pad00[0x14];
	Rva0042D6B4PtrChaseField *m_14;
	char m_pad18[0x54];
	TreeHintRef00217D4C m_6c;
};
void Rva00574A19::rva00574A19(int)
{
	Rva001FF3A9 *target = (Rva001FF3A9 *)m_14->get();
	if (target != 0) {
		TreeHintRef00217D4C temporary = ((Rva00574499 *)&g_Va00E0630C)->rva005744DD();
		m_6c = temporary;
		target->rva001FF3A9(m_6c);
	}
}

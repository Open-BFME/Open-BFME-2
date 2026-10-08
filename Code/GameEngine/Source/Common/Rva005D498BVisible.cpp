// cl: /O1 /G7 /MD
// AptScrollBar::Impl::SetVisible (WorldBuilder name, AptScrollBar.cpp line 123: SetVisible fired on change of +0x25).
// was ?rva005D498B@Rva005D498B@@QAEX_N@Z @0x005D498B 66B: guarded SetVisible fire via rowed 0x005277D9 with prefix from +8 else empty. Evidence: same shape as 0x005D4949 SetEnabled 66B plus rowed Fire callee plus strings SetVisible and empty fallback g_Rva0107301CEmptyString plus global TheRva00222A8BTarget; guard m_25 vs bool arg; caller jmp at 0x005D49D8.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr);
struct Rva005D498BInner
{
	char m_pad8[8];
	char m_name[1];
};
class AptScrollBar
{
public:
	class Impl;
};
class AptScrollBar::Impl
{
public:
	void SetEnabled(bool v);
	void SetVisible(bool v);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005D498BInner *m_inner08;
	char m_pad0C[0x24 - 0x0C];
	bool m_24;
	bool m_25;
};

// AptScrollBar::Impl::SetEnabled (WorldBuilder name, AptScrollBar.cpp line 112;
// string "SetEnabled"): retail 0x005D4949 66B, the same guarded fire as
// SetVisible on the flag at +0x24.
void AptScrollBar::Impl::SetEnabled(bool v)
{
	if (v == m_24)
		return;
	bool flag = v;
	const char *prefix = m_inner08 ? m_inner08->m_name : "";
	Rva005277D9Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, prefix, "SetEnabled", &v);
	m_24 = flag;
}
void AptScrollBar::Impl::SetVisible(bool v)
{
	if (v == m_25)
		return;
	bool flag = v;
	const char *prefix = m_inner08 ? m_inner08->m_name : "";
	Rva005277D9Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, prefix, "SetVisible", &v);
	m_25 = flag;
}

// The owner-side forwarders: retail 0x005D49CD and 0x005D49D5 (8B each) load
// the impl at +0x14 and jump to SetEnabled / SetVisible above; callers
// 0x005F2633, 0x005F266C, 0x005F2676. Address-named (no WorldBuilder lead).
class Rva005D49CD
{
public:
	void rva005D49CD(bool v);
	void rva005D49D5(bool v);
private:
	char m_pad00[0x14];
	AptScrollBar::Impl *m_impl14;
};

void Rva005D49CD::rva005D49CD(bool v)
{
	m_impl14->SetEnabled(v);
}

void Rva005D49CD::rva005D49D5(bool v)
{
	m_impl14->SetVisible(v);
}

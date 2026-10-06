// cl: /MD
// AptScrollBar::Impl::SetVisible (WorldBuilder name, AptScrollBar.cpp line 123: SetVisible fired on change of +0x25).
// was ?rva005D498B@Rva005D498B@@QAEX_N@Z @0x005D498B 66B: guarded SetVisible fire via rowed 0x005277D9 with prefix from +8 else empty. Evidence: same shape as 0x005D4949 SetEnabled 66B plus rowed Fire callee plus strings SetVisible and empty fallback g_Rva0107301CEmptyString plus global TheRva00222A8BTarget; guard m_25 vs bool arg; caller jmp at 0x005D49D8.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
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

// AptScrollBar::Impl::SetEnabled @0x005D4949 66B: the same guarded fire as
// SetVisible below, with the string "SetEnabled" (0x00C75A74) and the state
// at +0x24. Its only caller is the scroll bar's forwarder 0x005D49CD.
void AptScrollBar::Impl::SetEnabled(bool v)
{
	if (v == m_24)
		return;
	bool flag = v;
	const char *prefix = m_inner08 ? m_inner08->m_name : g_Rva0107301CEmptyString;
	Rva005277D9Fire(TheRva00222A8BTarget, m_level04, prefix, "SetEnabled", &v);
	m_24 = flag;
}
void AptScrollBar::Impl::SetVisible(bool v)
{
	if (v == m_25)
		return;
	bool flag = v;
	const char *prefix = m_inner08 ? m_inner08->m_name : g_Rva0107301CEmptyString;
	Rva005277D9Fire(TheRva00222A8BTarget, m_level04, prefix, "SetVisible", &v);
	m_25 = flag;
}

class Rva005D49D5
{
public:
	void SetVisible(bool visible);

private:
	unsigned char m_pad00[0x14];
	AptScrollBar::Impl *m_impl14;
};

void Rva005D49D5::SetVisible(bool visible)
{
	m_impl14->SetVisible(visible);
}

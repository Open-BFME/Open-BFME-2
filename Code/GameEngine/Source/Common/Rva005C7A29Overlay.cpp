// cl: /GX-
//
// ?SetAutoAbilityOverlayVisibility@Impl@InGameCommandButtonMovieClip@@QAEX_N@Z @0x005C7A29 (92B).
// AutoAbility overlay show/hide via AptCall 0x0050E9FE with _show/_hide.
// Skips when +0x4C clear or state at +0x54 already equals the bool arg.
// Prefix is +0x0C plus 8 else g_Rva0107301CEmptyString; level is +0x08.
// Evidence: strings _show _hide SetAutoAbilityOverlayState; externs
// g_Rva0107301CEmptyString and TheRva00222A8BTarget; caller 0x005C7C5D
// adjusts this by +4 then tail-jmps; callee row Rva0050E9FE.cpp.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

class InGameCommandButtonMovieClip
{
public:
	class Impl;
};

class InGameCommandButtonMovieClip::Impl
{
public:
	void SetAutoAbilityOverlayVisibility(bool show);
	void SetFlashEffectVisibility(bool show);
	void SetProductionCount(int count);
	void SetState(int state);

private:
	char _pad0[8];
	void *m_08;
	void *m_0C;
	char _pad1[0x3C];
	bool m_4C;
	char _pad2[7];
	bool m_54;
	bool m_55;
};

void InGameCommandButtonMovieClip::Impl::SetAutoAbilityOverlayVisibility(bool show)
{
	if (!m_4C)
		return;
	if (show == m_54)
		return;
	const char *which = "_show";
	if (!show)
		which = "_hide";
	const char *prefix = m_0C ? (const char *)((char *)m_0C + 8) : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_08, prefix, "SetAutoAbilityOverlayState", &which);
	m_54 = show;
}

// ?SetFlashEffectVisibility@Impl@InGameCommandButtonMovieClip@@QAEX_N@Z @0x005C7A85 (92B) FlashEffect state +0x55 same pattern.
void InGameCommandButtonMovieClip::Impl::SetFlashEffectVisibility(bool show)
{
	if (!m_4C)
		return;
	if (show == m_55)
		return;
	const char *which = "_show";
	if (!show)
		which = "_hide";
	const char *prefix = m_0C ? (const char *)((char *)m_0C + 8) : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_08, prefix, "SetFlashEffectState", &which);
	m_55 = show;
}

class Rva005C7C5D
{
public:
	void rva005C7C5D(bool show);
	void rva005C7C65(bool show);

private:
	char _pad0[4];
	InGameCommandButtonMovieClip::Impl *m_04;
};

void Rva005C7C5D::rva005C7C5D(bool show)
{
	return m_04->SetAutoAbilityOverlayVisibility(show);
}

void Rva005C7C5D::rva005C7C65(bool show)
{
	return m_04->SetFlashEffectVisibility(show);
}

// Retail 0x005C7C75, 8 bytes: adjust this by +4 then tail-jmp to rowed
// InGameCommandButtonMovieClip::Impl::SetState(int) (0x005C7B96). Callers 0x005679DA 0x005C3818.
// ?rva005C7C75@Rva005C7C75@@QAEXH@Z
class Rva005C7C75
{
public:
	void rva005C7C75(int index);
private:
	char _pad0[4];
	InGameCommandButtonMovieClip::Impl *m_04;
};

void Rva005C7C75::rva005C7C75(int index)
{
	return m_04->SetState(index);
}

// Retail 0x005C7C6D, 8 bytes: gap between 0x005C7C65 and 0x005C7C75 same file;
// plus4 tail to rowed InGameCommandButtonMovieClip::Impl::SetProductionCount(int)
// (0x005C7AE1). Caller 0x005C38DB.
// ?rva005C7C6D@Rva005C7C6D@@QAEXH@Z
class Rva005C7C6D
{
public:
	void rva005C7C6D(int index);
private:
	char _pad0[4];
	InGameCommandButtonMovieClip::Impl *m_04;
};

void Rva005C7C6D::rva005C7C6D(int index)
{
	return m_04->SetProductionCount(index);
}

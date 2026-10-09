// cl: /MD
// ?SetLineSize@Impl@AptScrollBar@@QAEXM@Z @0x005D4B1F 79B: float line-size setter via rowed Fire 0x00527925 with SetLineSize plus EmptyString fallback. Evidence: ucomiss float at +0x1C plus rowed Fire callees plus TheRva00222A8BTarget 0x009FE4CC plus g_Rva0107301CEmptyString 0x007BAC1C plus SetLineSize literal plus unblocks 0x005D4BC1 caller 0x005D4BCC.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);

struct Rva005D4B1FTeam
{
	char m_pad[8];
	char m_name[1];
};

// AptScrollBar::Impl::SetLineSize (WorldBuilder name): it fires the same "SetLineSize"
// literal on a change, as the rowed AptScrollBar::Impl::SetVisible does.
class AptScrollBar
{
public:
	class Impl;
};
class AptScrollBar::Impl
{
public:
	void SetLineSize(float v);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005D4B1FTeam *m_team08;
	char m_pad0C[0x1C - 0x0C];
	float m_float1C;
};

void AptScrollBar::Impl::SetLineSize(float v)
{
	if (v != m_float1C) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "SetLineSize", &v);
		m_float1C = v;
	}
}

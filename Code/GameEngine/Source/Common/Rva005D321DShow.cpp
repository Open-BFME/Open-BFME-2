// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// StrategicHUD::RegionStatsTrayMovieClip::Impl::SetVisibility (WorldBuilder name, line 289: SetState _show/_hide on change of +0x68).
// was ?rva005D321D@Rva005D321D@@QAEX_N@Z retail 0x005D321D 85B
// Evidence: guard bool at +0x68; _show else _hide reusing arg slot; prefix from +4 else g_Rva0107301CEmptyString; level at +0; SetState via rowed 0x0050E9FE; global TheRva00222A8BTarget; caller jmp 0x005D3289; precedent Rva005F086E::rva005F086E
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);
struct Rva005D321DInner
{
	char m_pad8[8];
	char m_name[1];
};
namespace StrategicHUD
{
class RegionStatsTrayMovieClip
{
public:
	class Impl;
};
}
class StrategicHUD::RegionStatsTrayMovieClip::Impl
{
public:
	void SetVisibility(bool flag);
private:
	void *m_level00;
	Rva005D321DInner *m_inner04;
	char m_pad08[0x68 - 0x08];
	bool m_flag68;
};
void StrategicHUD::RegionStatsTrayMovieClip::Impl::SetVisibility(bool flag)
{
	if (flag == m_flag68)
		return;
	const char *state = flag ? "_show" : "_hide";
	const char *prefix = m_inner04 ? m_inner04->m_name : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level00, prefix, "SetState", &state);
	m_flag68 = flag;
}

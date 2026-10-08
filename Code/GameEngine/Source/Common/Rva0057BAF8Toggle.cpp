// cl: /Ireference/shims/bfme2_ascii /MD
// StrategicHUD::SelectionDetailsUIImpl::SetToggleButtonEnabled (WorldBuilder name, line 226: SetToggleButtonState _enabled/_disabled on change of +0x2D).
//
// was ?rva0057BAF8@Rva0057BAF8@@QAEX_N@Z, retail 0x0057BAF8, 86 bytes.
// Toggle-button Apt state via rowed AptCall 0x0050E9FE with _enabled/_disabled.
// Skips when bool at +0x2d already equals arg; prefix is +0x18 plus 8 else
// g_Rva0107301CEmptyString; level is +0x14; function SetToggleButtonState.
// Evidence: strings _enabled _disabled SetToggleButtonState; externs
// g_Rva0107301CEmptyString and TheRva00222A8BTarget; caller 0x0057BBBB;
// precedent Rva005F086E 86B same shape (InGameCommandButtonMovieClip::Impl mov-first which).
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva0057BAF8Inner
{
	char m_pad8[8];
	char m_name[1];
};

namespace StrategicHUD
{
class SelectionDetailsUIImpl;
}
class StrategicHUD::SelectionDetailsUIImpl
{
public:
	void SetToggleButtonEnabled(bool flag);
private:
	char m_pad00[0x14];
	void *m_level14;
	Rva0057BAF8Inner *m_inner18;
	char m_pad1C[0x2D - 0x1C];
	bool m_flag2D;
};

void StrategicHUD::SelectionDetailsUIImpl::SetToggleButtonEnabled(bool flag)
{
	if (flag == m_flag2D)
		return;
	const char *state = "_enabled";
	if (!flag)
		state = "_disabled";
	const char *prefix = m_inner18 ? m_inner18->m_name : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level14, prefix, "SetToggleButtonState", &state);
	m_flag2D = flag;
}

// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// StrategicHUD::ChecklistUIImpl::SetExpandButtonEnabled (WorldBuilder name, line 1101: SetExpandButtonState on change of +0x25).
// was ?rva0057A961@Rva0057A961@@QAEX_N@Z @0x0057A961 86B.
// Expand-button Apt state setter: early-out on cached byte +0x25, then AptCall SetExpandButtonState with "_up"/"_disabled".
// Evidence: unlock lane plus caller 0x0057B499 push 1 plus callee row ?Rva0050E9FEAptCall plus strings SetExpandButtonState _up _disabled plus globals TheRva00222A8BTarget g_Rva0107301CEmptyString.
class Rva00222A8BTarget
{
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva0057A961Name
{
	char m_pad[8];
	char m_name[1];
};

namespace StrategicHUD
{
class ChecklistUIImpl;
}
class StrategicHUD::ChecklistUIImpl
{
public:
	void SetExpandButtonEnabled(bool flag);
private:
	char m_pad0[12]; // +0
	void *m_level; // +0xc
	Rva0057A961Name *m_namePtr; // +0x10
	char m_pad14[17]; // +0x14
	bool m_state; // +0x25
};

void StrategicHUD::ChecklistUIImpl::SetExpandButtonEnabled(bool flag)
{
	if (flag == m_state)
		return;
	const char *state = flag ? "_up" : "_disabled";
	const char *prefix;
	if (m_namePtr)
		prefix = m_namePtr->m_name;
	else
		prefix = "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level, prefix, "SetExpandButtonState", &state);
	m_state = flag;
}

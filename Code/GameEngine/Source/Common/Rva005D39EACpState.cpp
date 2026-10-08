// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?ShowCommandPoints@SelectionUIImpl@StrategicHUD@@QAEXHH@Z retail 0x005D39EA 107B
// Evidence: cached ints at +0x28 +0x2c via StrategicHUD::SetCommandPointsString 0x005D3966; shown-once bool at +0x31 via SetCPState _show rowed 0x005FB5E6; level at +0x04 outer at +0x08 prefix from +8 else g_Rva0107301CEmptyString; global TheRva00222A8BTarget; sibling Rva005D3B9A prefix layout
struct Rva005D2FD0Inner
{
	char m_pad8[8];
	char m_name[1];
};
struct Rva005D2FD0Outer
{
	Rva005D2FD0Inner *m_ptr;
};
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
namespace StrategicHUD
{
	void SetCommandPointsString(int level, Rva005D2FD0Outer *outer, int a, int b);
}
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);
namespace StrategicHUD {
class SelectionUIImpl;
}

class StrategicHUD::SelectionUIImpl
{
public:
	void ShowCommandPoints(int a, int b);
	void HideCommandPoints();
private:
	void *m_unused00;
	int m_level04;
	Rva005D2FD0Outer m_outer08;
	char m_pad0C[0x28 - 0x0c];
	int m_a28;
	int m_b2c;
	char m_pad30;
	bool m_flag31;
};
void StrategicHUD::SelectionUIImpl::ShowCommandPoints(int a, int b)
{
	if (a != m_a28 || b != m_b2c) {
		SetCommandPointsString(m_level04, &m_outer08, a, b);
		m_a28 = a;
		m_b2c = b;
	}
	if (!m_flag31) {
		const char *prefix = m_outer08.m_ptr ? m_outer08.m_ptr->m_name : "";
		Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_level04, prefix, "SetCPState", "_show");
		m_flag31 = true;
	}
}
// ?HideCommandPoints@SelectionUIImpl@StrategicHUD@@QAEXXZ retail 0x005D3A55 60B
// Evidence: hide-once bool at +0x31 via SetCPState _hide rowed 0x005FB5E6; same level +0x04 outer +0x08 as 0x005D39EA; global TheRva00222A8BTarget
void StrategicHUD::SelectionUIImpl::HideCommandPoints()
{
	if (m_flag31) {
		const char *prefix = m_outer08.m_ptr ? m_outer08.m_ptr->m_name : "";
		Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_level04, prefix, "SetCPState", "_hide");
		m_flag31 = false;
	}
}

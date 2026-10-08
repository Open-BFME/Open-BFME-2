// cl: /MD
// StrategicHUD::ChecklistUIImpl::SetCurrentItem (WorldBuilder name, line 1076: SetCurrentItemState _show/_hide on the changed +0x34 item).
// was ?rva0057AC27@Rva0057AC27@@QAEXH@Z, retail 0x0057AC27 104B. Unlock: selected-index Apt SetCurrentItemState show/hide via TheRva00222A8BTarget.
// Evidence: callees AptCall 0x005FB5E6 rowed; strings _show _hide SetCurrentItemState literals; EmptyString and TheRva00222A8BTarget externs; callers 0x0057AD58 0x0057B3B5.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

namespace StrategicHUD
{
class ChecklistUIImpl;
}
class StrategicHUD::ChecklistUIImpl
{
public:
	void SetCurrentItem(int index);
private:
	char m_pad00[0x0C];
	void *m_level0C;
	void *m_prefix10;
	char m_pad14[0x30 - 0x14];
	int m_30;
	int m_34;
};

void StrategicHUD::ChecklistUIImpl::SetCurrentItem(int index)
{
	if (index == m_34)
		return;
	bool diff = (m_34 != m_30);
	m_34 = index;
	if (index != m_30) {
		if (diff)
			return;
		const char *prefix = m_prefix10 ? (const char *)m_prefix10 + 8 : "";
		Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level0C, prefix, "SetCurrentItemState", "_show");
	} else {
		const char *prefix = m_prefix10 ? (const char *)m_prefix10 + 8 : "";
		Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level0C, prefix, "SetCurrentItemState", "_hide");
	}
}

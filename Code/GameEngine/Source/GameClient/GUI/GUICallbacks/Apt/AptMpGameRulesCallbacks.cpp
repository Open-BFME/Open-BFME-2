// cl: /DNDEBUG /MD
//
// BFME2's lobby game rules panel (the AptMpGameSetup panel's +0xD0 member)
// Apt callback "AptMpGameRules::Reset", 0x0057E6DD, bound by that name as
// a member pointer by the panel's registration 0x0057F0AA; that binding is
// its only reference. The class is named for the string's prefix.

extern "C" __declspec(dllimport) char *__cdecl strchr(const char *text, int c);
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *text, const char *pattern);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

// Rva00559F7ESwitchGetters.cpp's per-mode counts.
int Rva00559F7EGet(int mode);
int Rva00559F95Get(int mode);

class GameWindow;

// A rule widget list (+0x64 combo boxes, +0x70 check boxes).
struct AptMpGameRulesWidgets
{
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

// Unrowed 0x00559FAC (cdecl; resets the 0x28-byte rules block at +0x8C
// for the mode at +0x60), pinned by address.
void __cdecl Rva00559FAC(int mode, void *rules);

class AptMpGameRules
{
public:
	virtual void v00();
	// vslot 1: a rule changed (the derived +0xD0 member forwards it to the
	// panel, 0x0043FE01).
	virtual void ruleChanged(int rule, bool silent);

	void Reset(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void rva0057E6C1();
	// Bound as "MpGameRules::NumComboBoxes" (query 0) and
	// "MpGameRules::NumCheckBoxes" (query 1), so it keeps its address.
	void ExternFunc(int query, char *result, bool skip);

	// Unrowed 0x0057E5B5 (refreshes one rule's widget), pinned by address.
	void UpdateRuleGadget(int rule);
	// Unrowed 0x0057EF46 (files a widget under its index), 0x0057EF18 and
	// 0x0057ED2B, pinned by address.
	void rva0057EF46(AptMpGameRulesWidgets *widgets, const char *index, GameWindow *window);
	void rva0057EF18();
	void rva0057ED2B();

private:
	unsigned char m_pad004[0x60 - 0x04];
	int m_mode; // +0x60
	AptMpGameRulesWidgets m_comboBoxes; // +0x64
	AptMpGameRulesWidgets m_checkBoxes; // +0x70
	unsigned char m_pad07c[0x89 - 0x7C];
	bool m_89; // +0x89
	unsigned char m_pad08a[0x8C - 0x8A];
	unsigned char m_rules[0x28]; // +0x8C
};

// Retail 0x0057E55A, 65 bytes: bound as "MpGameRules::NumComboBoxes" and
// "MpGameRules::NumCheckBoxes", an Apt query answering the mode's counts.
void AptMpGameRules::ExternFunc(int query, char *result, bool skip)
{
	switch (query)
	{
	case 0:
		if (!skip)
			sprintf(result, "%d", Rva00559F7EGet(m_mode));
		break;
	case 1:
		if (!skip)
			sprintf(result, "%d", Rva00559F95Get(m_mode));
		break;
	}
}

// Retail 0x0057E6C1, 23 bytes. Name unknown. Refreshes the ten rule
// widgets (0x0057E5B5 each); the pinned 0x0057E6D8 jumps here.
void AptMpGameRules::rva0057E6C1()
{
	for (int rule = 0; rule < 10; ++rule)
		UpdateRuleGadget(rule);
}

// Retail 0x0057E6DD, 42 bytes: "AptMpGameRules::Reset" resets the rules
// for the mode, reports rule 10 and refreshes the widgets.
void AptMpGameRules::Reset(const char *unused)
{
	Rva00559FAC(m_mode, m_rules);
	ruleChanged(10, true);
	rva0057E6C1();
}

// Retail 0x0057F036, 116 bytes: "AptMpGameRules::InitGadgets" files each
// "RuleComboBox_<n>" or "RuleCheckBox_<n>" window under its index. Retail
// keeps an EBP frame here, which cl's frame pointer omission does not.
#pragma optimize("y", off)
void AptMpGameRules::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	const char *index = strchr(name, '_');
	if (!index)
		return;
	++index;
	AptMpGameRulesWidgets *widgets;
	if (strstr(name, "RuleComboBox_"))
		widgets = &m_comboBoxes;
	else if (strstr(name, "RuleCheckBox_"))
		widgets = &m_checkBoxes;
	else
		return;
	rva0057EF46(widgets, index, window);
	if (m_89)
		rva0057EF18();
	else
		rva0057ED2B();
}
#pragma optimize("", on)

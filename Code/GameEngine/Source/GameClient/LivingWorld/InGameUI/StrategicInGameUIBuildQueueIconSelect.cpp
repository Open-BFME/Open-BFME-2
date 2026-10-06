// cl: /O1 /DNDEBUG /MD /EHsc
// StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::Select, retail
// 0x005E70F8, 25 bytes.
// Name: WorldBuilder (StrategicInGameUIBuildQueueDetailsPanel.cpp line 552):
// unless already selected (+0x20), the icon's slot (GetIconSlot, inlined in
// retail as the +0x0C pointer) is put in state 2 through
// StrategicHUD::BuildQueueIconSlot::SetState (retail: virtual slot 9), then
// the icon is marked selected.
// Evidence: callers at 0x005E7A33 0x005E7CD4 0x005E87BA.

namespace StrategicHUD
{
class BuildQueueIconSlot
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void SetState(int state);
};
}

namespace StrategicInGameUI
{
class BuildQueueDetailsPanel
{
public:
	class Impl;
};

class BuildQueueDetailsPanel::Impl
{
public:
	class Icon;
};

class BuildQueueDetailsPanel::Impl::Icon
{
public:
	void Select();

private:
	StrategicHUD::BuildQueueIconSlot *GetIconSlot() { return m_iconSlot; }

	char m_pad00[0x0C];
	StrategicHUD::BuildQueueIconSlot *m_iconSlot;	// +0x0C
	char m_pad10[0x10];
	bool m_selected;								// +0x20
};
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::Select()
{
	if (m_selected)
		return;
	GetIconSlot()->SetState(2);
	m_selected = true;
}

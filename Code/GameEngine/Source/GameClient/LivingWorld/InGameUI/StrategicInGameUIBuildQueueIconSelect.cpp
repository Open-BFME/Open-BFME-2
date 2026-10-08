// cl: /O1 /DNDEBUG /MD /EHsc
// StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon: Select (retail
// 0x005E70F8, 25 bytes), the ctor 0x005E7D77, its refresh 0x005E7C56 and
// the icon-slot listener slots of its vtable 0x00877F14.
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
	virtual bool v0();
	virtual void v1(void *listener);
	virtual void v2();
	virtual void v3(void *value);
	virtual void v4();
	virtual void v5(int value);
	virtual void v6();
	virtual void SetQuantity(int quantity);
	virtual void v8();
	virtual void SetState(int state);
};
}

// Impl::GetIconAtQueueIndex in WorldBuilder (rowed address-named, 0x005E73E4).
class Rva005E73E4
{
public:
	void *rva005E73E4(int queueIndex);
};

// The icon's help hide check (rowed address-named, 0x005E73B2).
class Rva005E73B2
{
public:
	void rva005E73B2();
};

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

	void SelectQueueIndex(int queueIndex);
	void ShowUnitStats(int queueIndex); // 0x005E7B28 (WorldBuilder name, pinned)

private:
	Icon *GetIconAtQueueIndex(int queueIndex) { return (Icon *)((Rva005E73E4 *)this)->rva005E73E4(queueIndex); }

	char m_pad00[0x30];
	int m_selectedQueueIndex; // +0x30, -1 when none
};

// The +0x1C member cleared by the ctor and destroyed on unwind.
struct Rva005E7D77Member
{
	Rva005E7D77Member() : m_value(0) {}
	~Rva005E7D77Member();

	int m_value;
};

// Target facts: vtable 0x00877F14 = { 0x005E7DF7, 0x005E712A, 0x005E73DC,
// 0x005E7977, 0x005E715F, 0x005E7166 }: the icon slot's listener. WorldBuilder
// names slots 0..3 OnBuildQueueIconSlotLeftClicked / RightClicked / RollOut /
// RollOver; slots 4 and 5 (clear / set +0x21) are unnamed there.
class BuildQueueDetailsPanel::Impl::Icon
{
public:
	Icon(Impl *owner, int queueIndex, StrategicHUD::BuildQueueIconSlot *iconSlot, void *value10, int value14, int quantity);
	void Select();
	void Deselect(); // 0x005E7111 (rowed)
	void rva005E7C56();
	void rva005E789A(); // 0x005E789A (pinned)

	virtual void OnBuildQueueIconSlotLeftClicked(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRightClicked(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRollOut(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRollOver(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void rva005E715F(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void rva005E7166(StrategicHUD::BuildQueueIconSlot *slot);

private:
	StrategicHUD::BuildQueueIconSlot *GetIconSlot() { return m_iconSlot; }

	Impl *m_owner;									// +0x04
	int m_queueIndex;								// +0x08
	StrategicHUD::BuildQueueIconSlot *m_iconSlot;	// +0x0C
	void *m_10;										// +0x10
	int m_14;										// +0x14
	int m_quantity;									// +0x18
	Rva005E7D77Member m_1c;							// +0x1C
	bool m_selected;								// +0x20
	bool m_21;										// +0x21
};
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::Select()
{
	if (m_selected)
		return;
	GetIconSlot()->SetState(2);
	m_selected = true;
}

// WorldBuilder Icon::Icon (StrategicInGameUIBuildQueueDetailsPanel.cpp:455).
StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::Icon(Impl *owner, int queueIndex, StrategicHUD::BuildQueueIconSlot *iconSlot, void *value10, int value14, int quantity)
	: m_owner(owner), m_queueIndex(queueIndex), m_iconSlot(iconSlot), m_10(value10), m_14(value14), m_quantity(quantity), m_selected(false), m_21(false)
{
	rva005E7C56();
}

// 0x005E7C56 (called by the ctor; unnamed in WorldBuilder): pushes the
// icon's values into its slot and registers itself as the slot's listener.
void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::rva005E7C56()
{
	StrategicHUD::BuildQueueIconSlot *slot = GetIconSlot();
	slot->v3(m_10);
	slot->v5(m_14);
	slot->SetQuantity(m_quantity);
	slot->SetState(m_selected ? 2 : 1);
	slot->v1(this);
	if (slot->v0())
		rva005E789A();
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::OnBuildQueueIconSlotLeftClicked(StrategicHUD::BuildQueueIconSlot *slot)
{
	m_owner->SelectQueueIndex(m_queueIndex);
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::OnBuildQueueIconSlotRollOut(StrategicHUD::BuildQueueIconSlot *slot)
{
	((Rva005E73B2 *)this)->rva005E73B2();
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::OnBuildQueueIconSlotRollOver(StrategicHUD::BuildQueueIconSlot *slot)
{
	rva005E789A();
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::rva005E715F(StrategicHUD::BuildQueueIconSlot *slot)
{
	m_21 = false;
}

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::rva005E7166(StrategicHUD::BuildQueueIconSlot *slot)
{
	m_21 = true;
}

// WorldBuilder Impl::SelectQueueIndex: selecting the selected index again
// deselects it; the unit stats follow the selection.
void StrategicInGameUI::BuildQueueDetailsPanel::Impl::SelectQueueIndex(int queueIndex)
{
	if (queueIndex != m_selectedQueueIndex)
	{
		if (m_selectedQueueIndex >= 0)
			GetIconAtQueueIndex(m_selectedQueueIndex)->Deselect();
		GetIconAtQueueIndex(queueIndex)->Select();
		m_selectedQueueIndex = queueIndex;
	}
	else
	{
		GetIconAtQueueIndex(queueIndex)->Deselect();
		m_selectedQueueIndex = -1;
	}
	ShowUnitStats(m_selectedQueueIndex);
}

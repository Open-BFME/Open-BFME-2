// cl: /O1 /DNDEBUG /MD /EHsc
// Range-34 dump lane: 86B index switch at 0x005E7CAA (ret 4, plain).
// Switches the +0x30 index via rowed 0x005E73E4 accessor plus the rowed
// BuildQueueDetailsPanel::Impl::Icon teardown and select methods, then forwards +0x30 to pinned
// 0x005E7B28. Callee evidence already rows the three helpers for this
// caller. All identities unproven (address-derived).
class Rva005E73E4
{
public:
	void *rva005E73E4(int index);
};

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
	void Deselect();
private:
	char m_pad00[0x0C];
	StrategicHUD::BuildQueueIconSlot *m_iconSlot;
	char m_pad10[0x10];
	bool m_selected;
};
}

class Rva005E7CAA
{
public:
	void rva005E7CAA(int arg);
	void rva005E7B28(int v);
private:
	char m_pad[0x30];
	int m30;
};

void Rva005E7CAA::rva005E7CAA(int arg)
{
	int cur = m30;
	if (arg != cur) {
		if (cur >= 0)
			((StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon *)((Rva005E73E4 *)this)->rva005E73E4(cur))->Deselect();
		((StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon *)((Rva005E73E4 *)this)->rva005E73E4(arg))->Select();
		m30 = arg;
	}
	else {
		((StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon *)((Rva005E73E4 *)this)->rva005E73E4(arg))->Deselect();
		m30 = -1;
	}
	rva005E7B28(m30);
}

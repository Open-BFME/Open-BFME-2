// cl: /DNDEBUG /MD /EHsc
// StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::Deselect (WorldBuilder name, StrategicInGameUIBuildQueueDetailsPanel.cpp line 564: GetIconSlot (inlined, +0x0C) SetState(1) virtual slot 9 when selected).
// was ?rva005E7111@Rva005E7111@@QAEXXZ, retail 0x005E7111, 25 bytes.
// Guarded teardown: if byte at +0x20 is clear return; else virtual slot 9 on +0x0C with 1.
// Evidence: callers at 0x005E7A3A 0x005E7CC5 0x005E7CE8; mirror of 0x005E70F8.

class Rva005E7111Inner
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
	virtual void vfunc(int arg);
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
};
}
class StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon
{
public:
	void Deselect();

private:
	char m_pad[0x0C];
	Rva005E7111Inner *m_ptr;
	char m_pad2[0x10];
	bool m_flag;
};

void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::Deselect()
{
	if (!m_flag)
		return;
	m_ptr->vfunc(1);
	m_flag = false;
}

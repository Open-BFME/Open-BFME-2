// cl: /DNDEBUG /MD /EHs-c-
// StrategicInGameUI::DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip::GetPlayerData (WorldBuilder name, lines 1124..1125: the +0x10 table entry for side +0x14 offset by +0x18).
// was ?rva005EA575@Rva005EA575@@QAEHXZ @0x005EA575 22B thiscall indexed elem address via ranges
// Computes m_i2*0x24 plus m_begin of range m_i1 from base at this+0x10; sizes 0xC and 0x24 match Rva005EA58B ranges; caller 0x005EAF82
namespace StrategicInGameUI
{
class DynamicAutoResolveDialog
{
public:
	class Impl;
};
class DynamicAutoResolveDialog::Impl
{
public:
	class PlayerPanelMovieClip;
};
}
class StrategicInGameUI::DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip
{
public:
	int GetPlayerData();
private:
	char m_pad[0x10];
	void *m_base;
	int m_i1;
	int m_i2;
};
int StrategicInGameUI::DynamicAutoResolveDialog::Impl::PlayerPanelMovieClip::GetPlayerData()
{
	int a = m_i1 * 12;
	int b = m_i2 * 36;
	void *base = m_base;
	return b + *(int *)((char *)base + a + 0x1c);
}

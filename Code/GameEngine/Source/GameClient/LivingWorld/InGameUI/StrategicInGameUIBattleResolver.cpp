// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::BattleResolver::Impl (WorldBuilder
// StrategicInGameUIBattleResolver.cpp). Target facts for
// OnLivingWorldAutoResolveBattleCompleted 0x005CFB9E (virtual, pointer at
// 0x00875584; ret 0xC):
// unless veterancy data is already held (+0x14, WorldBuilder
// m_veterancyData) it builds the auto-resolve data from the event's three
// arguments (0x005ED15D in StrategicVeterancy.cpp). Argument types are
// passed through untyped.
class StrategicVeterancy
{
public:
	class Data;
};

StrategicVeterancy::Data *__cdecl Rva005ED15DCreateAutoResolve(void *a, void *b, void *c);

namespace StrategicInGameUI
{
class BattleResolver
{
public:
	class Impl;
};
}

class StrategicInGameUI::BattleResolver::Impl
{
public:
	virtual void OnLivingWorldAutoResolveBattleCompleted(void *a, void *b, void *c);

private:
	char m_pad04[0x14 - 0x04];
	StrategicVeterancy::Data *m_veterancyData; // +0x14
};

void StrategicInGameUI::BattleResolver::Impl::OnLivingWorldAutoResolveBattleCompleted(void *a, void *b, void *c)
{
	if (!m_veterancyData)
		m_veterancyData = Rva005ED15DCreateAutoResolve(a, b, c);
}

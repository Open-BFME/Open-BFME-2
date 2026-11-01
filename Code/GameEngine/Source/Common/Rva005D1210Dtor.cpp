// cl: /MD /EHsc
// ??1Impl@TacticalBattleResolver@StrategicInGameUI@@QAE@XZ retail 0x005D1210 61B
// Pointee dtor run by the rowed owning-pointer reset 0x005D127C. Body (EH
// state 0): delete the object at +4 through the rowed safe-delete helper
// ?Rva005EC135Delete 0x005EC135 when set; then the +8 member's inline dtor
// calls the rowed ?clear@Rva000AD6F4 0x000AD6F4. WorldBuilder names this body
// StrategicInGameUI::TacticalBattleResolver::Impl::~Impl
// (StrategicInGameUITacticalBattleResolver.cpp:172, ASSERT(!m_veterancyData),
// callgraph score 1.0); helper names stay address-derived.

void Rva005EC135Delete(void **slot);

#include "../../Include/Common/Rva000AD6F4.h"

namespace StrategicInGameUI {
class TacticalBattleResolver
{
public:
	class Impl
	{
	public:
		~Impl();

	private:
		int m_00;
		void *m_object; // +0x04
		Rva000AD6F4 m_08; // +0x08
	};
};
}

StrategicInGameUI::TacticalBattleResolver::Impl::~Impl()
{
	if (m_object != 0)
		Rva005EC135Delete(&m_object);
}

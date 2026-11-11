// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva005CE10A@Rva005CE10A@@QAEXXZ, retail 0x005CE10A, 27 bytes.
// Helper-then-validate-then-tail: calls +0x18 member rva004E0750, validates this as StringBase<G>, tail-jumps +0x18 member rva004E0741.
// Evidence: packet disassembly push esi mov esi ecx mov ecx [esi+0x18] call 0x4E0750 mov ecx esi call validate 0xB3FD0 mov ecx [esi+0x18] pop esi jmp 0x4E0741, VTABLE slot 4 table 0x00875158, callees rowed.
#include "ascii_string.h"
namespace StrategicInGameUI { class PlanningPhaseBuildingSelection; }
template <> class StringBase<unsigned short>
{
	friend class StrategicInGameUI::PlanningPhaseBuildingSelection;
	void validate() const;
};
#include "../../Include/Common/Rva004E0750.h"
#include "../../Include/Common/Rva004E0741.h"
class StrategicInGameUI::PlanningPhaseBuildingSelection
{
public:
	virtual void rva005CE10A();
private:
	char m_pad[0x14];
	Rva004E0750 *m_18;
};
void StrategicInGameUI::PlanningPhaseBuildingSelection::rva005CE10A()
{
	m_18->rva004E0750();
	((StringBase<unsigned short> *)this)->validate();
	((Rva004E0741 *)m_18)->rva004E0741();
}

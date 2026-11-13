// cl: /DNDEBUG /MD /EHsc
// platformsdk
// ?rva0057473A@Rva005746AF@@UAEXXZ retail 0x0057473A 120B
// Virtual slot 1 of 0x0086E3B0 (base Rva005746AF ctor 0x005746AF) and 0x0086E3CC (derived Rva005747DA).
// Evidence: vtable slot 1 shared by both ctors; timeGetTime throttle 1000ms on +8; TreeHintRef at +0xC via rowed op= 0x002174A4 and Release 0x0007DEEF;
// slot 6 (0x18) virtual returning TreeHintRef by value through hidden pointer; second half via rowed get 0x0042D6B4 and forwarder 0x001FF3A9 with TreeHintRef arg.
// Honest Rva name on proven base class. Row type note: get row declares int but result is used as object pointer; forwarder row declares 0 args but retail passes TreeHintRef const& which its slot0 target pops.

#include <windows.h>
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
__forceinline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}


#include "../../Include/Common/Rva0042D6B4PtrChaseField.h"

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9_slot0();
	void rva001FF3A9(const TreeHintRef00217D4C &hint);
};

struct Rva0057473AOuter
{
	char m_pad[0x20];
	void *m_field20;
};

#include "../../Include/Common/Rva005746AF.h"

void Rva005746AF::rva0057473A()
{
	if (m_0C.m_ptr != 0)
		return;
	if (timeGetTime() - m_08 < 1000)
		return;
	m_0C = GetHint();
	if (m_0C.m_ptr == 0)
		return;
	int q = ((Rva0042D6B4PtrChaseField *)((Rva0057473AOuter *)m_04)->m_field20)->get();
	if (!q)
		return;
	((Rva001FF3A9 *)q)->Rva001FF3A9::rva001FF3A9(m_0C);
}

// ??1Rva005746AF@@UAE@XZ retail 0x005746D2 104B
// Own vptr 0x0086E3B0; under EH state 0, when the hint at +0xC is set and the
// object fetched through the rowed get 0x0042D6B4 on m_04's +0x20 field
// reports it through the no-arg virtual getter (pinned twin
// ?rva005CB265@Rva005CB265@@UAEHXZ 0x005CB265), that object is cleared via
// the rowed forwarder 0x005CB260; then the hint member's inline dtor releases
// it through 0x0007DEEF. Same unlock check as Rva005E73B2Check.cpp.
#include "../../Include/Common/Rva005CB265.h"


// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: self-assign guard at 0x1DE3E3 (31B). Skips when the
// argument equals this; otherwise runs the rowed 0x3A2A41 clear helper
// then the 0x1DDCC5 copy. Returns this. (First callee was VA 0x7A2A41 in
// draft; retail REL32 proves RVA 0x3A2A41, which already has a rowed name.)

#include "../../Include/GameLogic/Rva000427195.h"
class Rva001DDCC5
{
public:
	void rva001DDCC5(void *other);
};
#include "../../Include/GameClient/Rva001DE3E3.h"

// ?rva001DE3E3@Rva001DE3E3@@QAEPAV1@PAV1@@Z
Rva001DE3E3 *Rva001DE3E3::rva001DE3E3(Rva001DE3E3 *other)
{
	if (other != this) {
		((Rva000427195 *)this)->rva003A2A41();
		((Rva001DDCC5 *)this)->rva001DDCC5(other);
	}
	return this;
}

// The retail call in this body reads 0x001DDCC5, an address the ledger already
// carries as ?_M_copy_from@?$hashtable@U?$pair@$$CBHURva001DDCC5Record@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHURva001DDCC5Record@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHURva001DDCC5Record@@@_STL@@@2@@_STL@@AAEXABV12@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?rva001DDCC5@Rva001DDCC5@@QAEXPAX@Z=?_M_copy_from@?$hashtable@U?$pair@$$CBHURva001DDCC5Record@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHURva001DDCC5Record@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHURva001DDCC5Record@@@_STL@@@2@@_STL@@AAEXABV12@@Z")

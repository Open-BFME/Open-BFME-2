// cl: /MD
//
// ??0Rva0056ACFF@@QAE@PAX@Z @0x0056AF94 31B.
// Constructor: run the pinned EH 0x0056AD80 initializer through the canonical
// Rva0056AC26 base; the compiler then installs the 0x00C6D19C vftable at +0
// and the 0x00C6D160 vftable at +8. Honest address-derived name. The tables
// themselves are emitted by the destructor unit Rva0056AC26Derived.cpp.
class Rva0056AC26Owner;
#include "../../Include/Common/Rva0056AC26.h"

class Rva0056ACFF : public Rva0056AC26
{
public:
	virtual ~Rva0056ACFF();
	virtual bool ac26Slot1();
	virtual bool b1Slot1(Rva002B4BC9Arg *arg);	// Base2-view slot 1, defined in Rva0056AC26Derived.cpp
	virtual bool slot4(LivingWorldArmy *army, Rva00318C32Ret *target);
	Rva0056ACFF(void *owner);
};

Rva0056ACFF::Rva0056ACFF(void *owner)
	: Rva0056AC26((Rva0056AC26Owner *)owner)
{
}

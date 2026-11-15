// cl: /MD
//
// ??0Rva0056ACDF@@QAE@PAXHH@Z @0x0056AF4B 45B.
// Constructor: run the pinned EH 0x0056AD80 initializer with the first
// arg, store the second/third args at +0x14/+0x18, then install the
// 0x00C6D14C vftable at +0 and the 0x00C6D110 vftable at +8. Follows the
// landed Rva0056ACFF/Rva0056AE4A recipe (standalone address-derived class,
// base via cast, vtbls via externs). Honest address-derived name.

// 0x0056AD80 is matched as the constructor Rva0056AC26(Rva0056AC26Owner *).
class Rva0056AC26Owner;
#include "../../Include/Common/Rva0056AC26.h"

class Rva0056ACDF : public Rva0056AC26
{
public:
	virtual ~Rva0056ACDF();
	virtual bool ac26Slot1();
	virtual int slot14(int);
	Rva0056ACDF(void *arg1, int arg2, int arg3);
private:
	int m_14;
	int m_18;
};

Rva0056ACDF::Rva0056ACDF(void *arg1, int arg2, int arg3)
	: Rva0056AC26((Rva0056AC26Owner *)arg1), m_14(arg2), m_18(arg3)
{
}

// cl: /MD
//
// ??0Rva0056ACDF@@QAE@PAXHH@Z @0x0056AF4B 45B.
// Constructor: run the pinned EH 0x0056AD80 initializer with the first
// arg, store the second/third args at +0x14/+0x18, then install the
// 0x00C6D14C vftable at +0 and the 0x00C6D110 vftable at +8. Follows the
// landed Rva0056ACFF/Rva0056ADF1 recipe (standalone address-derived class,
// base via cast, vtbls via externs). Honest address-derived name.

// 0x0056AD80 is matched as the constructor Rva0056AC26(Rva0056AC26Owner *).
class Rva0056AC26Owner;
#include "../../Include/Common/Rva0056AC26.h"

extern "C" const void *const __identifier("??_7Rva0056ACDF@@6BRva0056AC26@@@")[];
extern "C" const void *const __identifier("??_7Rva0056ACDF@@6BRva0056ACDF_B1@@@")[];

class Rva0056ACDF
{
public:
	Rva0056ACDF(void *arg1, int arg2, int arg3);
};

Rva0056ACDF::Rva0056ACDF(void *arg1, int arg2, int arg3)
{
	((Rva0056AC26 *)this)->Rva0056AC26::Rva0056AC26((Rva0056AC26Owner *)arg1);
	*(int *)((char *)this + 0x14) = arg2;
	*(int *)((char *)this + 0x18) = arg3;
	*(unsigned int *)this = ((unsigned int)__identifier("??_7Rva0056ACDF@@6BRva0056AC26@@@"));
	*(unsigned int *)((char *)this + 8) = ((unsigned int)__identifier("??_7Rva0056ACDF@@6BRva0056ACDF_B1@@@"));
}

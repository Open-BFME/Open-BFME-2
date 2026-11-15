// cl: /MD
//
// ??0Rva0056AE4A@@QAE@PAXH@Z @0x0056ADF1 53B.
// Constructor: run the pinned 0x0056AD80 initializer, null +0x14, install
// the 0x00C6D23C vftable at +0 and the 0x00C6D200 vftable at +8, then set
// +0x14 to the global-int at g_00DFEF10[0x100] plus the int argument.
// Honest address-derived name.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0056AC26Owner;
#include "../../Include/Common/Rva0056AC26.h"

struct Rva0056ADF1Glob
{
	char m_pad[0x100];
	int m_100;
};

class Rva0056AE4A : public Rva0056AC26
{
public:
	virtual ~Rva0056AE4A();
	virtual bool ac26Slot1();
	Rva0056AE4A(void *owner, int arg2);
private:
	int m_14;
};

Rva0056AE4A::Rva0056AE4A(void *owner, int arg2)
	: Rva0056AC26((Rva0056AC26Owner *)owner), m_14(0)
{
	m_14 = (*(Rva0056ADF1Glob **)&TheLivingWorldLogic)->m_100 + arg2;
}


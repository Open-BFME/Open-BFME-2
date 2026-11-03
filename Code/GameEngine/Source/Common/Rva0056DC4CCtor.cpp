// cl: /O1 /MD
//
// ??0Rva0056DC4C@@QAE@PAX@Z @0x0056DC4C 31B.
// Constructor: run matched 0x002D2C34 base, set +0x58 to the argument,
// clear +0x5C via AND-zero, install 0x00C6DB78 at +0. Sibling of the
// rowed 0x0056AF94 tiny ctor. Honest address-derived name.
#include "../../Include/GameClient/Rva005248D0.h"

// The retail table at RVA 0x0086DB78: 10 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0056DC6B@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern "C" const void *const vtbl_00C6DB78[10] = {
	(const void *)&__identifier("??_GRva0056DC6B@@UAEPAXI@Z"), // slot 0 0x0056DC88
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("_purecall"), // slot 2 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 3 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 4 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 5 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 6 0x0003B810
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 7 0x0050B5C6
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 8 0x0050B5C6
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 9 0x0047A699
};

class Rva0056DC4C
{
public:
	Rva0056DC4C(void *arg);
private:
	char m_pad[0x58];
	void *m_58;
	int m_5C;
};

Rva0056DC4C::Rva0056DC4C(void *arg)
{
	((Rva005248D0 *)this)->Rva005248D0::Rva005248D0();
	m_58 = arg;
	m_5C &= 0;
	*(unsigned int *)this = ((unsigned int)vtbl_00C6DB78);
}

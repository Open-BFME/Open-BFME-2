// cl: /MD
//
// ??0Rva00605C6A@@QAE@XZ @0x00605C58 18B.
// Chain from 0x00605C91: calls rowed base ctor then stores vtable 0x0087AAE0.
// Evidence: callee 0x00605C91 ??0Rva00605C91@@QAE@XZ row, vtable VA 0x00C7AAE0,
// dtor 0x00605C6A ??1Rva00605C6A@@UAE@XZ same vtable, caller 0x00604B1F.

#include "../../Include/Common/File.h"

class Rva00605C91 : public File
{
public:
	Rva00605C91();
};

// The retail table at RVA 0x0087AAE0: 18 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00605C6A@@UAEPAXI@Z")();
void __identifier("?open@LocalFile@@UAE_NPBDH@Z")();
void __identifier("?close@LocalFile@@UAEXXZ")();
void __identifier("?read@LocalFile@@UAEHPAXH@Z")();
void __identifier("?write@LocalFile@@UAEHPBXH@Z")();
void __identifier("?seek@LocalFile@@UAEHHW4seekMode@File@@@Z")();
void __identifier("?nextLine@LocalFile@@UAEXPADH@Z")();
void __identifier("?scanInt@LocalFile@@UAE_NAAH@Z")();
void __identifier("?scanReal@LocalFile@@UAE_NAAM@Z")();
void __identifier("?scanString@LocalFile@@UAE_NAAVAsciiString@@@Z")();
void __identifier("?print@File@@UAA_NPBDZZ")();
void __identifier("?size@File@@UAEHXZ")();
void __identifier("?position@File@@UAEHXZ")();
void __identifier("?readEntireAndClose@LocalFile@@UAEPADXZ")();
void __identifier("?convertToRAMFile@LocalFile@@UAEPAVFile@@XZ")();
void __identifier("?lock@File@@UAEXXZ")();
void __identifier("?unlock@File@@UAEXXZ")();
void __identifier("?open@LocalFile@@UAE_NPBGH@Z")();
}
extern const void *const g_00C7AAE0[18] = {
	(const void *)&__identifier("??_GRva00605C6A@@UAEPAXI@Z"), // slot 0 0x00605C75
	(const void *)&__identifier("?open@LocalFile@@UAE_NPBDH@Z"), // slot 1 0x00605CFB
	(const void *)&__identifier("?close@LocalFile@@UAEXXZ"), // slot 2 0x00605A7D
	(const void *)&__identifier("?read@LocalFile@@UAEHPAXH@Z"), // slot 3 0x00605DF7
	(const void *)&__identifier("?write@LocalFile@@UAEHPBXH@Z"), // slot 4 0x00605E34
	(const void *)&__identifier("?seek@LocalFile@@UAEHHW4seekMode@File@@@Z"), // slot 5 0x00605E5D
	(const void *)&__identifier("?nextLine@LocalFile@@UAEXPADH@Z"), // slot 6 0x00605E91
	(const void *)&__identifier("?scanInt@LocalFile@@UAE_NAAH@Z"), // slot 7 0x0060606F
	(const void *)&__identifier("?scanReal@LocalFile@@UAE_NAAM@Z"), // slot 8 0x00606133
	(const void *)&__identifier("?scanString@LocalFile@@UAE_NAAVAsciiString@@@Z"), // slot 9 0x00605F54
	(const void *)&__identifier("?print@File@@UAA_NPBDZZ"), // slot 10 0x00602451
	(const void *)&__identifier("?size@File@@UAEHXZ"), // slot 11 0x00602412
	(const void *)&__identifier("?position@File@@UAEHXZ"), // slot 12 0x00602447
	(const void *)&__identifier("?readEntireAndClose@LocalFile@@UAEPADXZ"), // slot 13 0x00605F0D
	(const void *)&__identifier("?convertToRAMFile@LocalFile@@UAEPAVFile@@XZ"), // slot 14 0x00605FDF
	(const void *)&__identifier("?lock@File@@UAEXXZ"), // slot 15 0x006024CA
	(const void *)&__identifier("?unlock@File@@UAEXXZ"), // slot 16 0x006024EE
	(const void *)&__identifier("?open@LocalFile@@UAE_NPBGH@Z"), // slot 17 0x00605D36
};

class Rva00605C6A : public Rva00605C91
{
public:
	Rva00605C6A();
};

Rva00605C6A::Rva00605C6A()
	: Rva00605C91()
{
	*(const void **)this = g_00C7AAE0;
}

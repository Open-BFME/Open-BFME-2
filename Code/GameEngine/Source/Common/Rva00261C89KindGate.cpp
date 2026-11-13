// cl: /O1 /G7 /MD
// One-time init two global 7-word flags then KindOf gate: B8 set but not 9C set.
// Evidence: chain from 0x002618A2/0x002618FA landing; caller 0x003E603E this-plus-4 no pushes; rowed BitFlags test 0x002615C0; neighbours 0x002619A0/0x00262002.
#include "../../Include/Common/BitFlagsTemplate.h"
class Rva002618A2
{
public:
	Rva002618A2 *rva002618A2(int unused, int b1, int b2, int b3);
	Rva002618A2 *rva002618FA(int unused, int b1, int b2, int b3, int b4, int b5);
private:
	unsigned m_words[7];
};
extern unsigned g_00DFEAD4;
// Owned here (its only reader); retail .bss zero-initializes it (VA 0x00DFEAD4).
unsigned g_00DFEAD4 = 0;
extern char g_00DFEA98;		// anchor only: 0x00DFEA98 + 4 spells the 9C object
// Owned here (its only reader); retail .bss zero-initializes it (VA 0x00DFEA98).
char g_00DFEA98 = 0;
extern Rva002618A2 g_00DFEAB8;
// Owned here (its only reader); retail .bss zero-initializes it (VA 0x00DFEAB8).
Rva002618A2 g_00DFEAB8;
extern Rva002618A2 g_00DFEA9C;
// Owned here (its only reader); retail .bss zero-initializes it (VA 0x00DFEA9C).
Rva002618A2 g_00DFEA9C;
#define InitFlagsB (*(unsigned char *)&g_00DFEAD4)
#define InitFlagsD g_00DFEAD4
#define GlobalB8Init (&g_00DFEAB8)
#define Global9CInit (&g_00DFEA9C)
#define GlobalB8Test ((BitFlags<69> *)((char *)&g_00DFEA9C + 0x1C))
#define Global9CTest ((BitFlags<69> *)(&g_00DFEA98 + 4))
class Rva00261C89
{
public:
	bool rva00261C89();
private:
	char m_pad[0x108];
	unsigned m_kind[7];
};
bool Rva00261C89::rva00261C89()
{
	if ((InitFlagsB & 1) == 0) {
		InitFlagsD |= 1;
		GlobalB8Init->rva002618FA(0, 8, 9, 10, 11, 12);
	}
	if ((InitFlagsB & 2) == 0) {
		InitFlagsD |= 2;
		Global9CInit->rva002618A2(0, 0x6d, 7, 0x59);
	}
	void *kind = m_kind;
	return GlobalB8Test->test(kind) && !Global9CTest->test(kind);
}

// Codegen: the bool result is the && expression itself, which cl materialises as an int 1/0
// (`xor eax,eax; inc eax` / `xor eax,eax`, as retail); an if/return true/false shape gives
// inc al / xor al,al instead. Callers test AL. The two flag objects are named
// externs at retail's addresses; every address is spelled from a different base symbol per use
// (init vs test) because the same symbol twice makes cl hoist both addresses into EBX/EDI where
// retail rematerialises `mov ecx, imm32` before each call.

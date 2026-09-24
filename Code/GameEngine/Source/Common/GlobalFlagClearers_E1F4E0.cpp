// B2-native flag-word clearer on the .data flag word g_Va00E1F4E0:
//
//     mov eax,[<address>] / and al,0xFE / mov [<address>],eax / ret
//
// Same shape as the GlobalFlagClearers_08.cpp run (byte-register narrowing
// of `return g &= mask`, a /G7 Pentium-4 peephole: defaults emit
// `and eax,imm`). Singleton on this global (whole-image imm32 scan finds
// only this body's load/store pair); a .rdata table slot at 0x00964D6C
// points at it. Identity is not recovered; the name derives from the
// address, following GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E1F4E0;

unsigned int Rva007AB490ClearFlag(void)
{
	return g_Va00E1F4E0 &= 0xFFFFFFFEu;
}

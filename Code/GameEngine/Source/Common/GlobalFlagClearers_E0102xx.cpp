// 17 further clearers formerly here are rowed as their matched parents'
// /G7 guard-rollback $L funclets (EXACT EH graphs); see reverse/deleted_rows.csv.
// Eighteen B2-native flag-word clearers on 17 .data flag words
// (0x00E01DE0-0x00E048F8):
//
//     mov eax,[<address>] / and a<l,h>,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFxx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E02820;
// g_Va00E02820: matched references place it at VA 0xe02820 (zero-filled .bss).
unsigned int g_Va00E02820;

unsigned int Rva00780FA4ClearFlag(void)
{
	return g_Va00E02820 &= 0xFFFFFFFEu;
}


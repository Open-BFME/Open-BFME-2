// Five clearers formerly here are rowed as their matched parents'
// /G7 guard-rollback $L funclets (EXACT EH graphs); see reverse/deleted_rows.csv.
// Six B2-native flag-word clearers across six .data flag words of one
// contiguous run (0x0075D47B-0x0075F15C):
//
//     mov eax,[<address>] / and al,0xFE / mov [<address>],eax / ret
//
// All six clear al bit 0. Same /G7 byte-register narrowing as
// GlobalFlagClearers_08.cpp (defaults emit `and eax,imm`). Each body
// carries a .rdata table slot (0x008FF520 and on). Identity is not
// recovered; names derive from addresses, following
// GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DE1E48;
// g_Va00DE1E48: matched references place it at VA 0xde1e48 (zero-filled .bss).
unsigned int g_Va00DE1E48;
extern unsigned int g_Va00DE1E70;
// g_Va00DE1E70: matched references place it at VA 0xde1e70 (zero-filled .bss).
unsigned int g_Va00DE1E70;

unsigned int Rva0075E4D4ClearFlag(void)
{
	return g_Va00DE1E70 &= 0xFFFFFFFEu;
}


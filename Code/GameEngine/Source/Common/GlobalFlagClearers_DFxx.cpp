// 24 further clearers formerly here are rowed as their matched parents'
// /G7 guard-rollback $L funclets (EXACT EH graphs); see reverse/deleted_rows.csv.
// Twenty-eight B2-native flag-word clearers on 26 .data flag words
// (0x00DE6128-0x00DFF158):
//
//     mov eax,[<address>] / and a<l,h>,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E06x.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFD8E4;
// g_Va00DFD8E4: matched references place it at VA 0xdfd8e4 (zero-filled .bss).
unsigned int g_Va00DFD8E4;
extern unsigned int g_Va00DFE014;
extern unsigned int g_Va00DFEDE4;
extern unsigned int g_Va00DFEEC4;
extern unsigned int g_Va00DFEEDC;
extern unsigned int g_Va00DFF040;
// g_Va00DFF040: matched references place it at VA 0xdff040 (zero-filled .bss).
unsigned int g_Va00DFF040;

unsigned int Rva007774BEClearFlag(void)
{
	return g_Va00DFF040 &= 0xFFFFFFFEu;
}


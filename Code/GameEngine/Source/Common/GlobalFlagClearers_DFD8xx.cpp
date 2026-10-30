// 5 further clearers formerly here are rowed as their matched parents'
// /G7 guard-rollback $L funclets (EXACT EH graphs); see reverse/deleted_rows.csv.
// Eight B2-native flag-word clearers across six .data flag words of one
// contiguous run (0x0076929D-0x0076B9FF):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot (0x0090E178
// and on). Identity is not recovered; names derive from addresses,
// following GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFDC48;
// g_Va00DFDC48: matched references place it at VA 0xdfdc48 (zero-filled .bss).
unsigned int g_Va00DFDC48;
extern unsigned int g_Va00DFDC50;
// g_Va00DFDC50: matched references place it at VA 0xdfdc50 (zero-filled .bss).
unsigned int g_Va00DFDC50;
extern unsigned int g_Va00DFDCD8;
// g_Va00DFDCD8: matched references place it at VA 0xdfdcd8 (zero-filled .bss).
unsigned int g_Va00DFDCD8;
extern unsigned int g_Va00DFE014;
// g_Va00DFE014: matched references place it at VA 0xdfe014 (zero-filled .bss).
unsigned int g_Va00DFE014;

unsigned int Rva0076B063ClearFlag(void)
{
	return g_Va00DFDCD8 &= 0xFFFFFFFEu;
}

// The76B248 action belongs to positional GenericObjectCreationNugget::create.
// Its native parent now emits the guard cleanup and owns the sole guard datum.
// The 76B21C/76B229 actions (and 76B1DF/76B20F, formerly in
// GlobalFlagClearers_DFxx.cpp) belong to GenericObjectCreationNugget::doStuffToObj,
// whose native parent emits them and owns the guard datum at 0x00DFDCF4.


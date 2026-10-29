// .data flag words kept defined here: g_Va00DFEEC4 is
// still declared by GlobalFlagClearers_DFxx.cpp, and g_Va00DFEEB0 and
// g_Va00DFEEDC are owned here by reverse/data_rows.csv. The unit's 12 former B2-native
// clearers are each rowed as a matched parent's /G7 local-static guard
// rollback ($L funclet) under the parent's EXACT EH graph; see
// reverse/deleted_rows.csv.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFEEB0;
// g_Va00DFEEB0: matched references place it at VA 0xdfeeb0 (zero-filled .bss).
unsigned int g_Va00DFEEB0;
extern unsigned int g_Va00DFEEC4;
// g_Va00DFEEC4: matched references place it at VA 0xdfeec4 (zero-filled .bss).
unsigned int g_Va00DFEEC4;
extern unsigned int g_Va00DFEEDC;
// g_Va00DFEEDC: matched references place it at VA 0xdfeedc (zero-filled .bss).
unsigned int g_Va00DFEEDC;


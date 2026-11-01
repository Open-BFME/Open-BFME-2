// .data flag word g_Va00DFEE10 kept defined here: reverse/data_rows.csv owns
// it in this unit. The unit's 10 former B2-native
// clearers are each rowed as a matched parent's /G7 local-static guard
// rollback ($L funclet) under the parent's EXACT EH graph; see
// reverse/deleted_rows.csv.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFEE10;
// g_Va00DFEE10: matched references place it at VA 0xdfee10 (zero-filled .bss).
unsigned int g_Va00DFEE10;


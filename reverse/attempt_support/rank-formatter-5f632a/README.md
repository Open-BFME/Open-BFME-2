# StrategicHUD rank formatter owner reconciliation

At BFME2 a158e26677 with committed BFME1 575ba2b04743f190f069805fbdc59936123c45da, rename the existing 194-byte C++ owner at RVA 5F632A to `StrategicHUD::FormatRankString`. Keep its existing Common translation unit, and update the real cached-rank setter in Rva005F6220Apt.cpp to call the same namespace function.

## Independent identity evidence

WorldBuilder names the counterpart at VA162C760 `StrategicHUD::FormatRankString`, with its assertion in StrategicHUDHeroArmyDetailsMovieClip.cpp:37. Both bodies guard negative rank, initialize a function-local AsciiString with the complete `APT:RankLabel` literal, register its cleanup with atexit, fetch through TheGameText slot38, format the returned Unicode string using the rank, and return a UnicodeString. Retail calls the established StringBase constructor37BA0, atexit6291F8, Unicode format6CB5D0, copy37050, and release36E70 in the same order. The call at RVA 5F6407 belongs to the existing 77-byte cached-rank setter5F63EC, which forwards the formatted result to the independently named SetLeaderRankString.

The native formatter is complete at5F632A..5F63EC, ending RET. Its two arguments are the hidden Unicode result slot and the signed rank, consistent with the free cdecl function. Existing StrategicHUD.cpp and the BattlePromptArmyPanelClipOwnerFwd.h / RegionDetailsArmiesClipOwnerFwd.h owners establish StrategicHUD as a namespace; no private StrategicHUD class is introduced.

WorldBuilder provides the original readable owner and source-family lead. Retail supplies the behavior, calling convention, full extent, literal, native calls, static lifecycle, and actual consumer. The existing split Common home is retained to avoid inventing an unwitnessed new translation unit.

## Verification and remaining cleanup debt

Normal whole-source build passes8/8 rows across the two affected homes, retaining522 row bytes. It verifies three string literals and two empty-string references. Original link_check --refresh completed with both witnessed homes LINKS: formatter204→204 and caller316→316,520 predicted linked bytes. Its older census is from2026-10-08 at62ab434507; the current refresh rebuilt2,206 stale ledger objects and retained that witnessed provider universe. This is a scoped current linker prediction, not a new full census or a claim about units absent from that census.

The existing10-byte atexit cleanup row at7B9A23 remains byte-for-byte unchanged. Its native registration is the formatter's PUSH BB9A23; the callback loads the same local string atE0692C and tail-calls the established releaseBuffer36410. The legacy logical alias key is retained only to preserve the existing binding. Removing it by rowing the actual COFF label `_$E2` is separately refused: the current ledger already rows that label at7B945A in VslotSmallBodiesAJ.cpp. Both real compiler symbols have COFF storage class3 (STATIC); the narrow two-row check_csv reproduction nevertheless treats them as one global name and refuses the two addresses. The attached receipt records this representation limitation. No new pin, alias, global, code carrier, or verifier change is added.

This repair adds0 unique C++ bytes and removes0 cleanup hatches; it replaces one address-owned function identity with its supported readable owner. The formatter and actual consumer have0 remaining supported unrowed bodies. The only other WorldBuilder queue entry in that source family, SetLeaderIconSelected5F618E/86, is already rowed upstream. Original class identity on that independently recovered row remains separate work.

## Shadow data-name control

The normal hooks expose two new shadow keys after the owner rename. The read-only data_ledger CLI control confirms that the string E0692C is the same 4-byte owned local static, 1 definition / 2 references, whose compiler-derived name now contains StrategicHUD::FormatRankString. Its committed generated name is stale. The guard E06930 remains the same pre-existing provisional global: external g_Va00E06930 and the TU-local compiler guard coexist, 2 definitions / 4 references. Its old compiler-local spelling was already keyed in data_check_baseline.txt. The namespace rename changes that spelling, exposing the existing debt under a new key; it creates no data definition or native storage change. The attached narrow before/current control records both facts.

Full data-ledger regeneration also changes 1,566 unrelated rows, adds 1,103, and removes 7, so this repair does not publish that broad generated metadata or hand-edit its rows. No baseline is grown to silence the warnings. The public shadow data checker returns 0; its two new name keys remain explicitly documented rather than claimed repaired.

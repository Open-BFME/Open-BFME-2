### LINK-025: `StlSweepR3Rva0002CCC3.cpp`'s opaque hashtable record needs the macro table's real type
Status: Blocked (identity prerequisite). Updated: 2026-10-26; inspected revision: 308a442bae.
Evidence / affected units: `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva0002CCC3.cpp` (67 B): unresolved
`Rva0002CCC3Record` `operator==` and `hash::operator()`, plus a wrong-selected `clear`. Retail 0x0002CCC3 calls the
folded `clear` 0x002234FE, whose node deleter is the `pair<const AsciiString,AsciiString>` `_M_delete_node`
0x0002C9A6; its callers are 0x0002CD71 and 0x0002CD7B (INIMacroTable's dtor per the re_attempts.log 0x0002CD7B entry).
Completed: trial (reverted, logged in re_attempts.log): instantiating only `~hashtable` with a declaration-only `clear`
builds 2/2 exact and drops the opaque references, but the pinned `clear` name stays unresolved.
Remaining / next check: name the macro table's hash_map type (it differs from 0x002236B9's
`rts::hash<AsciiString>` instance) and respell the record in this unit; `INIMacroTable.cpp` was file-claimed by
another seat on 2026-10-26.
Clearance: pending.
Census confirmation: not claimed.

- **Current-input confirmation (2026-10-26, inspected `896af21680`, index `d1f046749a`):** `build/link-report.md` and `build/link-worker-20261026/` verifies both rows remain byte-exact and the original two opaque references plus losing/wrong-selected clear remain. The recorded declaration-only trial was not repeated because it leaves the clear name without a provider. Native `0x0002CCC3` still calls `0x002234FE`; recover the macro-table element identity and reconcile row owners before an emission change. Clearance and census confirmation remain pending.

2026-11-06 typed lifetime follow-up (base da93446935): the current owner in INI.cpp and its sole 2CD71 holder now use INI.cpp's existing nocase MacroMap view, replacing the fake one-byte hash-set record. Native57B plus EXACT EH, holder5B, normal137/137, four data rows and normal/private code/provider equality pass; bounded preview preserves9185B. This reconciles an existing type model, not the original mapped typedef, TU placement or runtime clearance. The retained clear-owner cast and the misnamed2CD7B lifetime remain open. [Proof and ordered prerequisites](../../reverse/attempt_support/ini-macro-native-lifetime-20261106/README.md).

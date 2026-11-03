# Selection hashtable clear: saved-index binding audit

Read-only, 2026-11-03. No compilation, fetch/refresh, claims, tracked edits, or gate run. Exact decorated name and raw current symbol details are in index.json.

The changed symbol is `clear()` for `hashtable<pair<const int,Rva0043001DElement>,...>`.

- Saved local index: **2026-11-02 08:35 / 984a4cdc4d**; underlying census **06:54 / 357ce2a88f**.
- It has exactly **one COMDAT definer**, `SelectionXlat.obj`, at saved zero-based position **11649**, digest **0a51f2b4ca84**, native verdict **None**. There are no strong definers, ledger-owner objects, or /MAP holder exceptions for this exact name. Consequently the saved-order holder is this sole object; no alternate provider can absorb its changed body.
- Narrow exact-symbol searches of functions.csv and symbols.csv return no row or pin. **Native placement and native byte correctness remain unknown.** No name/placement is inferred from neighboring template instantiations.
- The existing aggregate reference graph has schema 1. It marks this name **not globally referenced**, but records one incoming edge: the destructor of the same typed hashtable calls this clear. The saved index contains **no per-object reference contributions**, so that edge cannot be attributed to a particular original object/root contribution from this evidence. Historical aggregate unreferenced status is not proof that the current merged object cannot reach it.
- A permitted read of the MAIN workspace object, `build/match/^code_^game^engine_^source_^game^client_^message^stream_^selection^xlat.obj`, finds the current clear is **84 bytes**, digest **51445f4f590c**. It has three REL32 sites: non-const vector<void*>::operator[] at offsets 25 and 55, and this exact typed `_M_delete_node` at offset 41. Full bytes and names are in JSON. This object's whole SHA256 differs from its saved-index digest, as expected for current changed output; no equivalence to historical object bytes is claimed.

These are saved-order/reference facts plus a fresh main-object symbol read. They do not establish a current per-object reachability closure, a retail identity, or permission to ignore this payload change. The parent independently inspects control/candidate incoming COFF relocations and runs the unmodified guard. No additional checks were performed here.

Report complete; all tracked reads stopped.

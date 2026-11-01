# GameText: requested pure slots are retail-pure

Native table RVA 00804E90 is the abstract GameTextInterface table. Slots
14-21 all contain RVA 0003B810, retail's real __purecall. Its subsystem
init/reset/update slots 1/9/10 are also genuinely pure. The emitted
GameTextInterface table in GameText.cpp has exactly those 11 pure entries.

GameTextManager's native table RVA 00804FA8 supplies concrete functions in
14-21 (fetch overloads, fetchPtr overloads, prefix lookup, map-file init and
translate-mode setters/getters). Both current manager table emitters,
GameText.cpp and GameTextManager.cpp, contain NO __purecall relocation.
No false-pure fix is indicated. The TSV records all 45 base/derived slots.

GameText.cpp is also held by StarkillerHDX@fleet (Debug header adoption),
so that scope was skipped for edits. The pure base declarations should stay.
An RVA 00804E90 here is VA 00C04E90, not VA 00804E90.

Three-unit direct table cohort: GameEngineDeletingBaseDerived.cpp 620,
GameText.cpp 4,795, GameTextManager.cpp 198, all LINKS, current total 5,613 B.
The preview prints census 4,190 -> current 5,613 because the index predates
other workers' seed consolidation. This read-only audit adds none of that
1,423 B. Source and object table content are unchanged by this handoff.

Current object table emitters:

- Code/GameEngine/Source/GameClient/GameText.cpp; SHA256 e8e479785f677633d88cce5acc1ae74bf500cc41dbceb23f36edbdbc80918e78.
- Code/GameEngine/Source/GameClient/GameTextManager.cpp; SHA256 df342b0e1c2e8e0ee30bbdf7e610e79a2d1d506edbb9ffae6e0b85cdda5be4aa.

[Slot inventory](game-text.tsv).

Base: `42ba5fba3d67de6fd90e938e491169eea70fd6d2`. Seat: `halilkkaya-codex` in wt_d.
Retail table addresses and targets in the TSV are RVAs; add 00400000 for VAs.
Targets were read as little-endian DWORDs from the retail image through
build.exe_image/rva_to_file_offset. Only those exact addresses were streamed
from functions.csv; the complete function ledger was not materialized.

The TSV inventories each selected slot. Up to three representative matched
names and three source paths are listed independently (not paired);
matched_row_count records the full count. A rowed address alone does not
prove the current declaration's signature, owner, receiver adjustment or
complete vftable contract. Concrete slots are inventoried without that claim.

The initial foreground ./build.sh passed all 99,276 rows and 2,253 data
rows, FULL GATE OK. This handoff changes no Code, row, pin or header.
The link previews below use index 86db074988, 2026-11-01 14:31; they are
scoped predictions, not census or runtime proof.

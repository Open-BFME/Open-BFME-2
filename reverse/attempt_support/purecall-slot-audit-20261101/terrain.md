# TerrainLogic seed false-pure slots: held scope

Native primary table RVA 007FB2C8 has these genuine pure slots:
8-12, 15, 16 and 50 (all target RVA 0003B810). Leave them pure.

The seed's prospective table would instead replace these 19 real targets:
13, 14, 17-30, 32, 33 and 40. Every target is already rowed. The TSV lists
all 51 native slots, exact targets and representative existing owners.
The source caveat is in TerrainLogic.cpp around its class declaration.

Skipped: TerrainLogic.cpp and subsequently class:TerrainLogic are held by
StarkillerHDX@fleet. The class and file dry runs were refused; no source
edit or virtual respell was attempted.

Current-object distinction: TerrainLogic.cpp emits NO TerrainLogic vftable.
The constructor and deleter emit only a five-slot Snapshot primary and the
14-slot subsystem/two four-slot listener copies. Their listener slot 2 is
pure as in retail. Thus the seed's 19 false entries are prospective upon
composition; they are not 19 __purecall relocations in its current object.
The donor primary's truncated contract also needs reconciliation before
composition. Do not claim table correctness just because the views link.

The three-unit current preview is 3/3 LINKS: seed 10,683, constructor 476,
deleter 298, total 11,457 -> 11,457 B against the index. Sources are unchanged.

Current object table emitters:

- Code/GameEngine/Source/GameLogic/Map/TerrainLogicCtor.cpp; SHA256 6607782e8fc5511493faae3b1d895927f21444530f8fa657bc46c94a5a2f5c7f.
- Code/GameEngine/Source/GameLogic/Map/TerrainLogicDeleter.cpp; SHA256 3c38094fb43ff0d8a9c573810a95aab965c7eacea71484fce82da1c2bca0f8d1.

[Slot inventory](terrain.tsv).

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

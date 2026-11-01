# GarrisonContain false-pure slots: held scope

The seed and constructor both emit the same false-pure entries:

| Native table RVA | Receiver offset | False-pure slots | Count |
| --- | --- | --- | --- |
| 008461F8 | +00 | 1-17, 19-26 | 25 |
| 00846080 | +20 | 0-75 | 76 |
| 008463D8 | +2C | 1 | 1 |

Every one of these 102 native targets has a matched ledger row. None is
retail __purecall (RVA 0003B810). The attached TSV names every target and
representative existing owners. This is 102 distinct slot positions, emitted
twice, not 204 distinct fixes.

Skipped: live claims refuse GarrisonContain.cpp under StarkillerHDX@fleet
(header adoption and overlapping held scopes). A class:GarrisonContain dry
run is held too. No constructor-only repair was made while the other table
emitter remains held. Once released, reconcile actual signatures and inherited
owners across both emitters. Their primary COMDAT is currently 33 slots and
the contain COMDAT 79; the native primary has 28. Pure declarations are only
one part of that contract problem; matching code bodies does not certify it.

Current direct emitter/referrer cohort, source unchanged:
GarrisonContain.cpp LINKS 3,403; GarrisonContainCtor.cpp LINKS 282;
2/2 LINKS, 3,685 -> 3,685 B against the index. These agreeing copies still
contain the false entries above. The initial full gate also verifies their
matched bodies; no additional source reconstruction was attempted.

Current object table emitters:

- Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp; SHA256 45bfffef1bd0b7ef8f60bb35c3160cbecf6008af9335486a8246ed54dbdec02f.
- Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainCtor.cpp; SHA256 e00fe8221507a85ad2038bab7a8af13fdc05b8425fa5957dab66e1f35c7b3d22.

[Slot inventory](garrison.tsv).

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

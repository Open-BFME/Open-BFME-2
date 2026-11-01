# Shadow owner views: incomplete, no false-pure declaration to replace

The consecutive three-word native run at table RVA 007CEFA0 is:

| Slot | Target RVA | Fact |
| --- | --- | --- |
| 0 | 000EFAD2 | Rowed BfmeShadowBufferOwnerBase deleting destructor. |
| 1 | 000B3FD0 | Shared empty RET; rowed under multiple existing identities. |
| 2 | 0003B810 | Retail's real __purecall. |

Current BfmeShadowPrefix.h models only slot 0. It declares no pure method.
All five BfmeShadowBufferOwnerBase table emitters supply a one-slot table;
Rva007B1380Ctor.cpp supplies a one-slot Rva007B1380 table. Rva000F0F2BFinish
stores the latter's existing name explicitly. None emits a false __purecall
slot. The TSV records both current name views over the same native run.

Leave slot 2 pure if/when this run is modeled completely. Do not add guessed
method names, arbitrary aliases or new pure declarations to pad the other
views. The canonical-class register and header explicitly state that only
the destructor slot has been modeled and complete extent is unproven;
data_rows.csv owns a verified four-byte prefix, while data_ledger.csv records
a 12-byte
run. Complete class extents, each folded table's distinct owners and
all derived overrides remain a separate contract-recovery prerequisite.
This audit does not certify the one-slot views as runtime-complete.

All nine class/table/referrer units remain LINKS, 5,880 -> 5,880 B against
the index, including the explicit Rva000F0F2B binding. Their sources are unchanged.

Additional held source hits were skipped: TunnelContain and LivingWorldLogic.
The assigned BehaviorModule, Object, UpdateModule, GameLogic, ScriptEngine
and GeometryInfo core scopes were not entered. No slot count is claimed for
those unaudited held classes. The particle repair is separate in particle-info.md.

Current object table emitters:

- Code/GameEngine/Source/Common/Rva00109610Dtor.cpp; SHA256 8a8ed2748e33d2852073548681e4c8ceb65c35657f9dd253b386c0566f28c55a.
- Code/GameEngine/Source/Common/Rva007B1380Ctor.cpp; SHA256 f13a61de9e2856190cd9caea5559cb5b76fe354908a3e77f427c3c1e4d3fef3a.
- Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/BfmeShadowBufferOwnerBaseDtor.cpp; SHA256 0ae02c6d0a2b868cb6bd4523a87af37a4e3f1f8320fc7992a2222b24ee7a53c8.
- Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp; SHA256 8e4db5e5b18d0968d47d74f0dea243b3955a7e1c4bb44f1110a806b9828013b9.
- Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowCtor.cpp; SHA256 2aaef52b91c21c013e7f2452fabe771985475d54540501202bbe7cf72661b255.
- Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowV2.cpp; SHA256 1098371449473f773146c48b5b5e609a056d73e31bdfcf2b49234fe9fe3611ef.

[Slot inventory](shadow.tsv).

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

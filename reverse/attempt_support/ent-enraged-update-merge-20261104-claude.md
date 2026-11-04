# EntEnragedUpdate update consolidation

Inspected base: `f9c0be296a` (2026-11-04, local tip after the view reconcile
`Share the Object and module-data views across EntEnragedUpdate.cpp's files`).
The approved destination is `Code/GameEngine/Source/Common/EntEnragedUpdate.cpp`;
its TU name remains provisional. No donor path is claimed as a retail path.

Prerequisite (previous commit): the update donor's Object view (getControllingPlayer,
m_pos via Coord3D.h, m_body/m_ai, m_flags438) and the string-backed module-data
names from retail's field table 0xC56A98 (EnragedTransitionTime, TransitionFX,
OnBuffFX, OffBuffFX at +0x20..+0x2C) were reconciled into the seed with
`tu_views.py`. 27/27 rows stayed exact.

`tu_skeleton.py --merge` accepted the seed and
`GameLogic/Object/Update/EntEnragedUpdateUpdate.cpp`, deleted the donor and
repointed one functions.csv and one tu_map.csv source cell. TU assignments and
evidence were not regenerated. No new matched bytes are claimed; source files fall
by one.

Verification:

- `./build.sh Code/GameEngine/Source/Common/EntEnragedUpdate.cpp`: 27/27 exact in
  one file; three string literals and two float literals verified.
- `find_declared_unmatched.py`: all defined functions matched.
- `check_csv.py` OK (99,452 function rows); `class_gate.py --staged` exit 0;
  `tu_ownership.py --staged --shadow` exit 0; `data_check.py --staged` zero findings.
- `eh_verify.py`: EXACT 5 of 5.
- `link_check.py` (published index, census 2026-11-04 17:56 at `8c757ea0db`):
  LINKS, 524 -> 1,416 authored bytes. The extra bytes belonged to the absorbed
  donors already; this is a preview, not a census gain.

Consolidation audit (sole source move in the batch):

- No donor keys in code-identity, data, hatch, header or MS-header registers
  (`rg EntEnragedUpdateUpdate reverse/*.tsv reverse/*.csv reverse/*.txt` finds only
  functions.csv, tu_map.csv and the published census link_status.csv). No debt is
  retired. The seed's pending ModuleData header-queue entry remains.
- No tooling, hook, workflow, build.sh or include consumer names the old path.
  The merge's provenance comment, historical attempt evidence and the published
  link_status.csv keep it on purpose.

Remaining donors: `Common/FamilyDeletingDtors_muse-x7q-eb73.cpp` (mixed with
StealthUpdateModuleData; compile C2511, the seed has no
`EntEnragedUpdateModuleData(EmitVtableTag *)` ctor) and
`GameLogic/Object/Update/EntEnragedUpdateModuleDataDtor.cpp` (novtable Snapshot
dtor view; composed bytes differ). Both need the module-data ctor/dtor view
conflict solved first. Retail's field table also puts FriendlyDeadFilter at
+0x18 and HatedObjectFilter at +0x1C, so the seed's `m_hatedFilter`/
`m_friendlyFilter` names are swapped (left for the naming lane). Census
confirmation and the full consumer audit happen at the next scheduled census.

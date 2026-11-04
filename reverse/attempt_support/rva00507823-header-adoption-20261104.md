# Rva00507823: three canonical-header adoptions (2026-11-04)

Inspected revision: 3358de24a1 (source parent 752128e4ec). Scope claimed as
`class:Rva00507823` by `yasinschroeder-codex3` through the header picker.

Removed private Rva00507823 declarations from:

- `Code/GameEngine/Source/Common/Rva00507823Check.cpp`: retain the bitset operation through an explicit view of the canonical mask storage.
- `Code/GameEngine/Source/Common/Rva00507877Resolve.cpp`: retain the mask/vector operations through explicit views of canonical storage. Named reference locals changed code generation in a trial; the final expressions preserve the original bytes.
- `Code/GameEngine/Source/GameLogic/Object/DamageNugget_generateDamageInfo.cpp`: remove the derived padding that compensated for the old four-byte private base; the canonical base supplies the same 0x128-byte extent.

The shared header, method names, ledger rows, compiler options and symbol pins
are unchanged. This establishes no new class or donor identity.

## Verification

- Baseline and final `./build.sh` verification: 4/4 rowed bodies exact (ledger extents 126, 17, 163 and 988 bytes). String, float and import checks pass.
- Strict `find_declared_unmatched.py`: all defined functions already matched in each changed source.
- `header_adopt_lane.py accept --class Rva00507823`: PASS for all three sources; the owning tool retired exactly their three header-queue rows. Other class debts in those sources remain.
- Original/final `link_census.object_facts` agree exactly for all three objects: COMDAT name/digest/size, exclusive definitions, undefined externals and weak externals. Verdict annotations were excluded from that comparison. Facts captured under `build/codex3-rva507823/`.
- `link_check.py` predicts all three continue to link: 143 -> 143, 162 -> 162 and 988 -> 988 executable bytes (1,293 total). Its historical census label is 2026-11-04 17:56 at 8c757ea0db. This is a scoped preview, not a new census or headline linking gain.
- `check_csv.py`: 99,450 function rows, 9,328 symbol rows and 2,268 data rows valid. `git diff --check` passes.

## Remaining scope

The automatic adoption trial on all twelve queued class consumers accepted none
before these source adaptations. Nine queued consumers remain unchanged: the
constructor/destructor require real member lifetime handling, some derived
views require offset/virtual-slot reconciliation, and three derived units still
refer to an `accepts` name absent from the canonical header. No merge, vtable
provider repair, source-count reduction or whole-class clearance is claimed.
The obstacle-register search for this class and the selected source names found
no existing entry; no new link obstacle was established by these three changes.

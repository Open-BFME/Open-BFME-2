# CreateAHero text-cache traversal header adoption

Inspected revision: `2d62ba84f272cc3ff0e68d592063b72cb7111da3`.
Scope: `Code/GameEngine/Source/GameLogic/Object/CreateAHeroTextWarmup.cpp`,
`?rva0021CB1F@CreateAHeroManager@@QAEXXZ`, RVA `0x0021CB1F`, 978 bytes.

The canonical header already reserves the vector storage at +0x14C and +0x168.
The existing target-backed element views remain local; the member function reads
those fields as the same vector types. This replaces the private manager class
without changing the shared header or a symbol name. It claims no recovered
original method name or new member-layout evidence.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/CreateAHeroTextWarmup.cpp`
  passed before and after: 1/1 code rows, string, float and import checks.
- Before/after COFF external-definition sets are identical (seven definitions,
  zero removed, zero added). No inline member provider, data definition, thunk
  or alternatename binding was removed.
- `find_declared_unmatched.py` passed after the edit.
- One `header_adopt_lane.py accept --class CreateAHeroManager` over the six-file
  served cohort passed this source and retired exactly its one header-queue row.
  The other five sources were restored by the trial tool, retain private views,
  and remain queued; no debt was retired for them.
- A separate ordinary `link_check.py` preview reports LINKS, census-attributed
  bytes 970 -> 970, index census `2026-11-08 12:06 at f4727bbd09`.
  This is a bounded preview, not a real image link or runtime test.

Remaining cohort prerequisites are unchanged: manager parser data rows,
nested class/layout reconciliation, script-glue fields, subsystem base fields,
and the GameSlotApparent vector view. No source paths moved.

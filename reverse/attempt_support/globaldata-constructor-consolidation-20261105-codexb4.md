# GlobalData constructor consolidation, 2026-11-05

Scope: `GlobalData.cpp` and the five clean donors served by the consolidation
picker. Preparation commit: `aebada2d09`. Claim owner:
`yasinschroeder-codexb4`.

The target constructor at RVA `0x00235A21` constructs 22 elements of 24 bytes
through the rowed `WeaponBonus` constructor at `0x00235A0E`. The donor expresses
this as `WeaponBonus[22]`; the seed previously declared 528 bytes of raw storage.
The preparation adopts the donor's member view without changing the pointer
member in `GlobalData`. The placeholder class name remains unchanged. This
does not claim a recovered external donor path or type name.

## Verification and merge

- The first `tu_skeleton.py --merge GlobalData.cpp --dry-run` accepted no donors.
- The preparation byte-verifies 140/140 functions and three data rows;
  `find_declared_unmatched.py` passes. Its link preview stays LINKS, 7,662 bytes.
  The commit hook also verifies six EXACT EH graphs. The shadow identity check
  reports the `GlobalData` constructor's `AsciiString::clear` binding; no debt
  entry was retired or suppressed.
- The subsequent normal `tu_skeleton.py --merge` accepts the seed and
  `Rva00235A21Ctor.cpp`. It rebuilds the stale TU map in memory (154 approved rows
  in the plan), removes that donor, and repoints its one function row and the
  committed TU map's source column. The map was not regenerated for this commit.
- Final `./build.sh Code/GameEngine/Source/Common/GlobalData.cpp`: 141/141
  functions, three data rows, seven string literals, 53 compiler float literals
  and nine named imports pass. The 117 funclet pins verify through parent EH
  data despite compiler label renumbering.
- Final declared-unmatched, `check_csv.py` and staged whitespace checks pass.
- Final link preview: LINKS, 7,662 -> 7,684 bytes for the destination. The index
  is the published 2026-11-04 22:40 census at `3a95b274a2`. The merge's link guard
  also preserves its census-linked seed/donor scope. This is a preview, not a
  new census or a headline linking gain.
- Scoped naming for the inspected empty `Rva00235A21::Rva00235A21` constructor
  reports no available complete functions; there are no local/parameter names
  to propose in this body.

## Consolidation and tooling audit

Audited the staged move on top of `aebada2d09` and the entire pending source-path
change: `Rva00235A21Ctor.cpp` -> `GlobalData.cpp`.

Searches of tools, hooks, workflows, Code, docs and reverse find no active
consumer of the removed path. Remaining mentions are the merge's provenance
comment and the historical `region-award-link-20261020/candidate.patch` (and the
attempt log, deliberately retained as history). Function and TU-map source
columns now name the destination. There are no donor entries in gate, data,
code-identity, header, MS-header, hatch or unclaimed-source registers; no key
needs transferring or retiring. The destination's existing header debts remain.
No pins, aliases or hatches were added or removed. The scoped builds and link
guard verify the composed provider/binding behavior; the publication hook's
outgoing batch audit remains authoritative for affected consumers.

## Remaining donors

- `rva00235312Rva00235312Farm.cpp`: `SubsystemInterface` redefinition and seed
  `GlobalData` members absent from the donor's lighting view. Reconcile those
  views before another merge trial.
- `Rva00236285Ctor.cpp`: seed raw-storage view has no donor `m_14` member.
  `Rva002362B4Dtor.cpp` also rejects compilation. Existing evidence identifies
  these as constructor/destructor views of one tutorial-map member; unify the
  five string fields and vector identity before retrying.
- `MultiPlayOtherMultParsers.cpp`: composition fails bytes. Reconcile the seed's
  private INI and multiplayer views with the donor's canonical headers and
  preserve the seed constructor's exception behavior before another trial.

These four donors remain untouched; the three mixed files also stay in place.
The concrete result is one fewer Code source file with matched coverage kept.

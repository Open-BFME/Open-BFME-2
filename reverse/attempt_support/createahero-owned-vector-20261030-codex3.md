# CreateAHeroManager owned-pointer cleanup view

2026-10-30, inspected base `69fa252df2`, owner `yasinschroeder-codex3`.
Scope: `Code/GameEngine/Source/Common/CreateAHeroManager.cpp`, with the
file claim and destructor claim `0x0021FFEE`.

## Target facts

The complete 279-byte destructor uses `this+0x174` for its explicit clear
call at `0x0022001C`, reaching `0x0040A59B`. Its later member cleanup call
at `0x002200AE` reaches `0x0040A603` on the same member. The latter's native
56-byte body clears through `0x0040A59B`, reads the first pointer, and frees
it when non-null. Its EH cleanup reaches the existing base destructor at
`0x0007FAB3`.

The constructor unit, `Common/0CreateAHeroManager21FE49.cpp`, already models
this member as `Rva0040A530`, derived from the pointer-range view
`Rva0040A3F9`. Constructor `0x0040A530` initializes that range through
`0x00211E58` and stores the ownership flag at member offset `0xC`.
Clear `0x0040A59B` tests that flag, passes the begin/end pointers to
`0x0040A1AC` for owned-element destruction, then erases the range through
`0x0031BD55`. These operations establish the pointer-vector view; the
shared address of the older tree destructor alias alone does not.

## Source correction

Reuse the constructor's existing neutral pointer-range and derived cleanup
declarations in the manager destructor unit. The member occupies 16 bytes,
including its flag at manager offset `0x180`; four remaining bytes precede
the string at `0x188`. The previous tree view occupied 12 bytes and treated
the flag as padding. Existing private member spellings are retained.

The member cleanup now binds `??1Rva0040A530@@QAE@XZ`, whose already-rowed
body lives in the constructor unit at `0x0040A603`, instead of the old
`_Rb_tree<int, pair<const int, Rva0040A603Record>, ...>` alias. No provider,
pin, alias, ledger owner or source path is added or removed. The legacy
tree-shaped provider remains outside this repair. No original application
container name or external donor provenance is claimed.

## Verification

- Frozen-file checks pass before and after the edit, retaining the three
  existing unclaimed-definition exemptions.
- Ordinary build passes all 34 source rows and literal/import checks.
- Before/after COFF comparison preserves the complete 279-byte destructor
  exactly. Its only changed relocation is at `+193`, replacing the tree
  destructor spelling with the existing pointer-vector destructor spelling.
  Both resolve to native `0x0040A603`. All other external COMDAT fingerprints,
  strong definitions, weak definitions and reference-graph edges are
  unchanged; the root dependency changes only that destructor spelling.
  Local object facts are in `build/createahero-dtor-object-facts.json`.
- The edited source's four EH graphs are EXACT, with no baselined finding.
- Strict preparation of the edited source, constructor unit,
  `Common/Rva0040A1ACHeroPtrAlgos.cpp` and
  `WWVegas/WWLib/Rva0040A530Ctor.cpp` passes 66/66 rows, three strings,
  one float, 40 funclet bindings and six complete STLport constructor folds.
  All four receive reusable receipts; no index or census is published.
- Paired EH verification reports EXACT 8, no baseline entries or missing
  objects. All four sources preview LINKS against `6fe1089c24`
  (2026-10-30 04:25), retaining 2,258 authored bytes: 1,271 + 430 + 529 + 28.
- The staged-tree batch audit returns INCONCLUSIVE (exit 2): that census
  index predates the outgoing source base, and affected consumer
  `Code/GameEngine/Source/Common/AIBuildable.cpp` lacks a current receipt.
  Full affected-consumer selection and absence of losses remain unverified.
  Carry all four scoped sources and the wider consumers into the next
  scheduled census; no nightly, link cycle or smoke runner was started.

## TU approval boundary

The default picker served Common/CreateAHeroManager.cpp TU approval. The
current map has 81 proposed main-code rows for that path (including one
unledgered row), while the 81 already-approved rows are its unwind/handler
placements. Destructor `0x0021FFEE` itself has only the proposed `N` path
hint. The pre-edit consolidation evidence packet has no original-path
evidence or approved alternative for the existing main source. Other
fragments retain competing Common/GameLogic paths; WorldBuilder's
CreateAHero.cpp pairing is a file/identity lead, not verified target TU
provenance. No F/Z/S anchor was established during this pass.

This repair reconciles a member lifetime view as a prerequisite. It does
not approve a TU, merge a source, recover new bytes, retire a register key,
or claim census/ownership progress. TU approval still needs target path
evidence and resolution of the competing assignments.

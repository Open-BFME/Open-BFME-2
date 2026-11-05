# Devastate special-power interface adoption, 2026-11-05

Inspected source revision: `72cb4e3a0a`. Scope: the two bodies in
`DevastateSpecialPowerSlots.cpp`, RVAs `0x004C822C` (68 bytes) and
`0x004C82D1` (20 bytes). The four-file consolidation was not applied.

## Evidence and change

Target fact: native secondary table VA `0x00C5E430` slots 10/11/12 contain
VAs `0x008C822C`, `0x008C82D1`, `0x008C82E5`. The existing constructor
identifies the interface receiver at object+0x10. The existing canonical
`SpecialPowerModule.h` declares these operations with unsigned command options.
Native bytes alone do not establish signedness for an unread or forwarded word.

Replace the private 13-slot pure interface with that canonical header. Correct
the two overrides' argument types to match the canonical interface and call its
named `doSpecialPowerAtLocation` instead of private `slot12`. Keeping signed
arguments makes new overloads and adds an unwanted receiver adjustment to the
20-byte body; the unsigned overrides retain its exact native receiver and bytes.
Function identifiers, row extents, paths, flags and pins are unchanged. Ledger
decoration and seed comments follow the corrected signatures; old rows are
tombstoned. `rename.py` does not support signature changes. No semantic naming
claim or `name_basis.csv` change is made.

## Verification and provider preservation

- Normal `./build.sh DevastateSpecialPowerSlots.cpp`: 2/2 exact; literal exact.
  Both affected files pass `find_declared_unmatched.py`; the seed's existing
  protected-destructor marker remains a separate obligation.
- Normal builds of all 12 possible caller files selected by header acceptance:
  471/471 exact, 125 EH funclets resolved through parents, 91 literals plus 24
  empty, 17 float operands and 7 imports verified. The cohort comprises Object,
  CombineHorde, Devastate seed, GrabPassenger seed and doSpecialPower,
  HordeDispatch, ManTheWalls, PlayerUpgrade, SplitHorde, LuaScriptEngine,
  ScriptActions and ScriptActions_garrison.
- `header_adopt_lane.py accept --class SpecialPowerModuleInterface` over the
  complete Slots cohort passes and retires its single two-RVA queue entry.
- All 139,925 local `build/**/*.obj` files were searched for either old mangled
  signature, then hits checked as COFF external symbols. There were no undefined
  references: only definitions in the pre-change unit and scratch copies.
  The removed private interface supplied pure declarations, no inline bodies.
- Before/after `link_census.object_facts`, normalizing only the two signature
  spellings, preserve all five COMDAT payload/relocation fingerprints, both
  exclusive definitions, all three undefined externals and zero weak aliases.
  Fingerprints: helper `6246c280fc30` (34B), getPosition `6f3401ddf1c6` (4B),
  doSpecialPower `14b03c370878` (68B), literal `a6b62776a4a2` (67B),
  doSpecialPowerAtObject `1691fdef8fd4` (20B). These compare object identity;
  the normal builds separately establish retail byte matches.
- `link_check.py DevastateSpecialPowerSlots.cpp`: LINKS 88 -> 88 against local
  index `112a456a2c` (2026-11-05 15:52). This is a preview, not a new census or
  a real-link measurement. Fetch retained this newer local index.

## Remaining consolidation work

The initial supported dry run accepted zero donors. The seed still lacks the
complete shared Devastate override declarations; location and destructor
composition still need receiver/lifetime reconciliation. The canonical interface
prerequisite in Slots is now removed. Retry composition only after those shared
declarations and native destructor boundaries are reconciled. No source-file
reduction or linked-byte gain is claimed.

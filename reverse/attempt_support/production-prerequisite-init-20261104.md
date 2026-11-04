# ProductionPrerequisite init emission cleanup

Inspected `7b37872da9bdd481a120d695e35081b6acbd0cc7`; published provider index
2026-11-04 02:25 at `5a13f2cd61`. Scope: LINK-064's
`Code/GameEngine/Source/Common/RTS/ProductionPrerequisite.cpp` only.

Removed the unrowed Zero Hour `ProductionPrerequisite::init` definition and its
`present-unmatched` marker. Its member-pointer expression only retained the
rowed `vector<PrereqUnitRec>::push_back` instantiation. Moving that expression
into the existing `calcNumPrereqUnitsOwned` definition preserves all six rows
(429 bytes) without emitting another method. No ledger names, rows, pins,
aliases, headers or source paths change. The hatch register shrinks by one;
unrelated stale register entries reported by `hatch_counters --update` were
left untouched.

Verification:

- Baseline and final `./build.sh` pass 6/6, including string, float and import
  reference checks. Final `find_declared_unmatched.py` reports all definitions
  matched, without the baseline's one unclaimed definition.
- All 138,202 `.obj` files under `build/` were scanned for the exact removed
  `?init@ProductionPrerequisite@@QAEXXZ` name. None contained it; no undefined
  relocation consumer was found. The scan used COFF symbols and relocation
  roots/edges for any raw-name candidates.
- Current-provider `link_check.py` still predicts LINKED 0 -> 0, but its
  unresolved set shrinks from four to three: `AsciiString::set` disappears.
  `freeBytes`, imported allocator allocate/deallocate, and the existing wrong
  copy constructor / `_Construct` / overflow copies remain. This is cleanup,
  not a linked-byte or census gain.

The supported `tu_skeleton.py --split ... --for
Code/GameEngine/Source/Common/LivingWorldScoreKeeper.cpp --dry-run` cannot carve
0x004EE1E2/0x004EE20B: both report `no definition spells its name`, because
they are implicit template emissions. No move was applied. A direct explicit
push_back instantiation also fails MSVC C2248 on the donor header's private
record; that trial was replaced with the verified member-scope expression.

Next: recover explicit PerTurnStats template definitions and reconcile their
existing providers/callers under LINK-064 before moving the two implicit
helpers or replacing the Zero Hour header chain. The different native element
families and approved TU assignments are existing target evidence; the Zero
Hour donor supplies neither BFME 2's PerTurnStats identity nor its layout.

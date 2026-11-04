# HorseHordeContain name-key donor

Inspected input: `384350437864ebc5130387af5f2ccb3f9a40b3d3`.

The approved provisional TU is
`Code/GameEngine/Source/GameLogic/Object/Contain/HorseHordeContain.cpp`.
The scoped consolidation planner reports separate mixed/incomplete and declaration
prerequisites; it does not approve a move. The current-map merge planner independently
selects the name-key donor and its two compiler-generated EH rows for this TU.

Target evidence: retail primary table VA `0x00C45C38` has slot 4 VA
`0x008766E8`, the existing 69-byte `HorseHordeContain::getModuleNameKey() const`
row. Base table VA `0x00C45050` has a different getter in the same slot
(VA `0x0086F860`). The root primary view already reserves this slot as `s04`.
Replacing that unused declaration with the getter signature and declaring the
derived override preserves all later slots and the existing ledger identities.
No external donor facts are needed and no real source-path recovery is claimed.

Before reconciliation, `tu_skeleton --merge --dry-run` accepts no donor: the
name-key definition is absent from the seed class. After reconciliation it accepts
the seed and `HorseHordeContainPoolKey.cpp`, six rows together. The other five
donors still fail on their distinct private base, member or include declarations.

Verification of the declaration repair:

- `./build.sh .../HorseHordeContain.cpp`: 3/3 exact, string/float/import checks pass.
- `find_declared_unmatched.py`: all defined functions already matched.
- `link_check.py`: LINKS, 1,402 -> 1,402 bytes against census `5a13f2cd61`
  (2026-11-04 02:25); prediction only, no census gain claimed.

Next: commit this verified prerequisite separately, then apply the accepted
composition through `tu_skeleton.py`, verify its EH graph and path consumers,
and retain all remaining donors and their debt.

# ActionManager special-power interface adoption

Inspected revision: `6b9c853538`; date: 2026-11-04.

## Target facts and change

`Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h` records the
retail interface vtable, including `getPercentReady` at slot 2 and
`rva0049466D(const Coord3D *)` at slot 18. The two ActionManager sources
declared the latter slot separately as `v18(int)` and `ready(const Coord3D *)`.
The first source passes only zero; the second passes zero or a location.

Both sources now include that existing canonical header and call its slot-18
declaration. No shared header, ledger identity, pin or source path changed.
`header_adopt_lane.py adopt --class SpecialPowerModuleInterface --header
Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h --apply` passed
both files after aligning those local call spellings. Its `accept` command
passed both units and retired exactly their two header-queue rows.

## Verification

- `./build.sh Code/GameEngine/Source/Common/RTS/ActionManager.cpp
  Code/GameEngine/Source/Common/RTS/ActionManagerCanDoSpecialPowerAtLocation.cpp`:
  34/34 matched; all 16 renamed compiler funclet labels verified through their
  parent EH graph; string, float and import reference checks passed.
- `find_declared_unmatched.py` on each source: all defined functions matched.
- `link_check.py` on both current objects: both LINKS, 5,201 -> 5,201 linked
  bytes in this preview (1,491 and 3,710 respectively). Census reference:
  2026-11-04 07:28, `a62ac1c10b`. This is a local preservation check, not a new
  census or a real-game link.

## Consolidation prerequisites retained

The supported planner completed for `Code/GameEngine/Source/Common/RTS/`.
Its stale-map paths are hints; `tu_skeleton` rebuilt the current map in memory
and found 78 approved ActionManager rows, three eligible sources and four
mixed sources. No map regeneration or source move was applied.

The initial merge dry run accepted no donor. `Rva0041C9C4.cpp` failed with
an undefined `Overridable` base; the location donor failed on `SHROUDED` and
its former `ready` member. This change resolves only the interface member
prerequisite. No post-adoption merge is claimed.

`tu_views.py --dry-run --class BfmeRefCF --class Object` separately reported:

- `BfmeRefCF`: renaming the location view's `data` member is conservatively
  refused because `StringBase<char>::Header` also has a `data` member.
- `Object`: the location view derives from `Thing`, while the other two views
  declare no base. These layouts need evidence-based reconciliation.
- `Overridable`, `SpecialPowerTemplate` and `SpecialPowerModuleInterface`
  belong to the canonical-header lane; the first two remain prerequisites.

Next work is reconciling those remaining views and enum spellings, then running
the supported merge dry run again. No aliases were removed and no data or
identity debt was retired. Source file count and census headlines are unchanged.

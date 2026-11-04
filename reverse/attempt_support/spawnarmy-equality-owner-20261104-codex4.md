# SpawnArmy equality owner reconciliation

Inspected revision: `671907172b`, 2026-11-04. Scope: the 76-byte
`rva004E20AB` helper and its approved provisional destination
`Code/Libraries/Source/WWVegas/WWLib/SpawnArmy.cpp`.

Target facts: the existing row calls `StringBase<char>::compare` at
RVA `0x000069D6` for four-byte members at +4, +8 and +12, then compares
the byte at +16. The previous view used `AsciiString::compare`, whose
pin and shim alias lead to that same owner. No donor identity or original
record name is established here.

Change: use the existing `StringBase<char>` storage and compare declaration
directly. No shared header, pin, alias pragma or register is edited.
The shared AsciiString alias remains in `ascii_string.h`, included by
this helper, the verified SpawnArmy TU and other consumers.

Independent prerequisite checks:

- `./build.sh Code/GameEngine/Source/Common/Rva004E20ABEqual.cpp`:
  1/1 code rows exact, all 76 bytes preserved; reference checks pass.
- `find_declared_unmatched.py` passes before and after the change.
- Ordinary `link_check.py` before and after: the helper LINKS (76 bytes),
  SpawnArmy LINKS (2,808 authored bytes), index `a62ac1c10b`,
  2026-11-04 07:28. These previews do not change the census headline.
- No helper keys occur in the identity, data, header, Microsoft-header or
  hatch debt registers.

The first direct-owner trial included `string_base.h` itself. It passed
independently but composition resolved that basename to WWLib's different
header and refused the duplicate class definition. Retaining the existing
`ascii_string.h` include selects its sibling shim header consistently.

The prerequisite source repair was committed as `82cceb36c2` and handed to
the runner publisher. After the runner's rebase, the full SpawnArmy unit
still passes 68/68 code rows and all seven checked string literals.

The final `tu_skeleton.py --merge ... --dry-run` accepts just the seed and
`Rva004E20ABEqual.cpp`: 69 rows, preserving the census-linked units through
the merge guard. The winning plan is cached locally; regenerate the naming
planner if relevant inputs change. No source-path move has been applied.

Applying the merge refuses shared folded RVA `0x0007FAB3`, held by
`Burachi-3D@Burak/85351563` for the ArmyPlacer TU. The claimability check
confirms the live claim (3.9 hours remaining). Retry the normal merge only
after that claim releases, then verify the resulting TU, audit path consumers
and protected-register transfers, and publish the move. Do not bypass the
claim. Notify's existing declaration/overload blocker remains unchanged.
There is no source-file reduction or census gain in this repair.

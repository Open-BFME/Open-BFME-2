# Buildable-status map instantiation cleanup

Base: BFME 2 `43231d14ed`; reference `337e4b48e8`.
Source: `Code/Libraries/Source/WWVegas/WWLib/VAsciiStringRva002460C3.cpp`.

The source's own comment identified `GameLogic::instantiateBuildableOverrideIndex`
as a synthetic copy of the setter, used only to instantiate the map's owned
`operator[]`. The real setter at `0x00246F71` already belongs to
`GameLogicSetBuildableStatusOverride.cpp`. The synthetic name has no ledger
row, and the unmatched-body checker lists it. This is existing cleanup debt,
not a lost retail row.

Deleting only the wrapper and its private GameLogic class stops VC7.1 from
emitting the specialization and fails all four rows. An explicit member
template instantiation emits the specialization without the synthetic caller.
The final source also replaces its local `size_t` typedef with `<stddef.h>`.

## Verification

- Original and final supported builds pass all four rows: the 121-byte map
  operator at `0x002460C3`, its handler, the existing five-byte destructor
  alias and the 25-byte cleanup at `0x0077169D`.
- The final funclet's label renumbers from the ledger's `$L6239` to `$L6215`;
  the verifier proves it through the parent EH data. No pin changes.
- All five retained external COMDAT fingerprints match the original object,
  including normalized relocation targets. The only removed external record
  and COMDAT is the 29-byte synthetic caller; no external is added, and weak
  externals are unchanged.
- The fetched index (`6fe1089c24`, 2026-10-30 04:25) records only this source
  touching the synthetic name. There are no remaining Code references to it.
- The unmatched-body checker now reports all definitions matched. Strict
  explicit-provider preparation passes all four rows. Ordinary preview retains
  LINKS, 131 -> 131 authored bytes. This is not a census update.
- The owning Microsoft-header auditor finds zero local Microsoft-name
  occurrences and its scoped `refresh_queue` removes only this source's row.
  `hatch_counters.py --update` removes only this source's GameLogic exemption,
  reducing `class_gate_allow` from 38 to 37.
- The staged-tree outgoing-batch audit is INCONCLUSIVE: its index predates the
  base and the first affected consumer without a current receipt is
  `Common/0CreateAHeroManager21FE49.cpp`. Full affected-consumer selection and
  loss checks remain unverified; carry the provider and wider consumers into
  the next scheduled census. No census gain is claimed.

## Remaining header-register obstacle

`header_adopt_lane.py accept --class GameLogic SOURCE` refuses because the
source does not include `Common/GameLogicObjectLookupView.h`. There is no
GameLogic declaration or use left; adding that include would be unrelated to
the remaining map implementation. The tool's historical-discovery exception
does not cover removal of an originally present class. Record this as a false
reject, keep the header queue row and leave the verifier unchanged. A supported
acceptance path for removal of an unnecessary class remains required.

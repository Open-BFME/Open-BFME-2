# RainOfFireUpdate canonical module hierarchy prerequisite

Inspected revision: `d12228f71e` (2026-11-04).

The supported merge dry run still accepted no constructor/destructor donors.
The constructor conflicts with the emitted Secondary20 table; the destructor
conflicts with the private ObjectModule/BehaviorModuleInterface definitions in
RainOfFireUpdateView.h. The existing attempt is recorded in
`consolidation-rainoffireupdate-2026-11-04.md`.

This repair replaces that local header's five private module-base definitions
with the canonical UpdateModule header, preserving the existing RainOfFire
layout and using canonical m_moduleData/m_object members. The module-data
pointer is cast to the existing RainOfFire view at its uses. Canonical headers
are unchanged; only the claimed consumer and its private header are edited.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/RainOfFireUpdate.cpp`:
  9/9 rows exact, including the renumbered local-static funclet; two string
  literals and 13 float literals verified.
- `find_declared_unmatched.py` on the source and private header: no unmatched
  definitions.
- `link_check.py --prepare-current` produced a strict reusable byte receipt.
- `link_check.py` on the source: LINKS, 1,192 -> 1,192 bytes against census
  2026-11-04 16:16 at `2f0cb97f52`. This is a preview, not a new census.

Next: retry the supported merge with the canonical hierarchy in place; reconcile
the destructor's remaining RainOfFireUpdate/Secondary20 declarations separately
if still refused. The constructor's explicit table definitions still require
their own reconciliation. No merge or source-file reduction is claimed here.

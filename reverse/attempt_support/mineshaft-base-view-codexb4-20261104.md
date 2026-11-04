# Mineshaft constructor base-view reconciliation, 2026-11-04

Inspected revision: `36175a67db`. Scope: `BehaviorModuleBase` in
`MineshaftPortalBehaviour.cpp` and `MineshaftPortalBehaviourCtor.cpp`.

`tu_views.py` applied the seed's existing +4 `const ModuleData *m_moduleData`
and +8 `Object *m_object` fields to the constructor donor. This replaces its
integer placeholders without changing layout or the private virtual slot.
These spellings come from the existing seed; no external donor provenance is claimed.

Checks: sanctioned `./build.sh` passes the constructor's sole 96-byte row;
`find_declared_unmatched.py` passes; `link_check.py` predicts LINKS, 96 -> 96
bytes, using the 2026-11-04 20:47 census index at `f12552d0a7`. Its unreferenced
vector-constructor diagnostic remains nonblocking. No new census is claimed.

The tool's before/after merge trials accept zero donors. Remaining causes are
LINK-300's frame scope, duplicate allocator specialization, subsystem include
and manager vtables. No source path, ledger row, alias or debt key moved.

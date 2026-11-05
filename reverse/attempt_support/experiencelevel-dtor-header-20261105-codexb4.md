# Experience-level destructor string-record header adoption

Base: `fb680906b2`; owner: `yasinschroeder-codexb4`; date: 2026-11-05.

The claimed `ExperienceLevelDtor.cpp` carried a private eight-byte
`BfmeStringRecord000B94D2` view. It is only an owned member, with no access to
its old `bytes` field. Replace the private body with the existing canonical
header, retaining the owned member, destructor symbol, and complete layout.
No shared header or ledger identity changes.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/System/ExperienceLevelDtor.cpp`
  passes before and after: 11/11 function rows, all six renumbered EH funclet
  bindings, and string/float/import checks.
- `find_declared_unmatched.py` passes before and after.
- Ordinary build objects preserve all 15 external symbol facts and all six
  relocation-aware COMDAT digests (`tu_views.coff_externals` and
  `link_census.comdat_bodies`).
- `link_check.py` before the edit predicts LINKS, 222 -> 222 authored bytes.
- `header_adopt_lane.py accept --class BfmeStringRecord000B94D2` passes after
  the edit and retires exactly this unit's header-queue row through its
  structural, byte and link verdict. This is header debt reduction, with no
  census or real-link gain claimed.

The fresh supported ExperienceLevelSystem merge dry run still accepted zero
of thirteen donors before this adoption. Other layout, specialization-order
and private-view conflicts remain; this adoption alone does not resolve them.
Raw local receipts are under `build/codexb4-experience-dtor-*` and
`build/experience-20261105-codexb4/dtor-bindings.json`.

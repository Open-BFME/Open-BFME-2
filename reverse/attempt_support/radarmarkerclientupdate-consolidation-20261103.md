# RadarMarkerClientUpdate consolidation, 2026-11-03

Inspected base: b96e682d44. Scope: the picker-claimed RadarMarkerClientUpdate
TU and its four whole-file donors. No external donor source was used.

Target facts: the constructor row at 0x004C9BCD calls the rowed
Rva00362EC7 constructor (0x00362EC7). The destructor donor already models
that base through DrawableModule. DrawableModule's shared header supplies
ModuleData at +4 and Drawable at +8; clientUpdate accesses those locations
and the one-pointer marker at +0x0C. The existing module-data destructor
uses an AsciiString at +8. These facts support a common access/layout view;
they do not recover Rva00362EC7's complete virtual interface or original name.

## Reconciliation

The seed and clientUpdate donor now share the Rva00362EC7-based leaf
view, smart-marker member, and module-data view. The updater uses the seed's
existing m_markerType spelling. The base destructor remains a declaration;
these two units emit no new Rva00362EC7 destructor or vtable.

- `./build.sh` for both sources: 11/11 rows exact, including parent-bound
  funclets whose compiler labels changed; string, float and import checks pass.
- `find_declared_unmatched.py` for both: all defined functions already matched.
- `link_check.py` for both: 2/2 clean; 178 -> 178 and 138 -> 138 census-authored
  bytes preserved (index census 8661f15284, 2026-11-03 20:03). This is a local
  prediction, not a new headline census.
- `tu_skeleton.py --merge ... --dry-run`: accepts the existing seed and the
  clientUpdate donor (11 rows); previously accepted none.

## Remaining donors

- RadarMarkerClientUpdateCtor.cpp: its explicit +0 vtable field conflicts
  with the polymorphic base view. Reconcile constructor initialization without
  adding a second vtable identity; keep its 32-byte match.
- RadarMarkerClientUpdateDtor.cpp: m_0C / m_marker ownership shape differs.
  A trial replacing its private DrawableModule with the canonical header kept
  all five byte matches, but `header_adopt_lane.py accept` refused link loss.
  Direct link_check reported unresolved
  `?GetSnapshotName@DrawableModule@@MBEPBDXZ` and a different first-selected
  `??_7Rva00362EC7@@6B@`. The trial was reverted. Resolve this base/vtable
  prerequisite before retrying its adoption or merge.
- MarkerTypeUpdateModuleDataCtor.cpp: its explicit `__identifier` vtable extern
  collides with the destructor's compiler-owned table; the constructor also
  retains its queued private ModuleData view. It needs its own verified repair.
- ModuleDataBuildFieldParse.cpp and ConstIntGetters4.cpp remain mixed files;
  the merge does not split them.

No alias, pin, hatch or baseline was added or removed by the reconciliation.

# TerrainCollisionModuleInfo::getEventFX: retail export and its two callers

2026-11-06; base `7a08207b34d`. Status: repair verified locally, awaiting the automated
real link. This resolves the blocked verdict of 0x0056468E in `reverse/re_attempts.log`.

## Target facts

Export ordinal 1686 names `?getEventFX@TerrainCollisionModuleInfo@FXParticleSystem@@QAEPBVFXList@@XZ`
at `0x0056468E`. The row stood under the placeholder `Rva0056468E`.

## Change

- The canonical header declares `getEventFX` and types `m_18` as `const FXList *`.
  None of its other includers names `m_18`.
- `Rva0056468E.cpp` defines the member against that header.
- `Rva003AEE16CopyCtor.cpp` calls it through the class view the file already had, so
  the earlier random-variable concern does not arise.
- `Rva005646BC.cpp` includes the header. Its hand-spelled
  `__identifier("??_7Snapshot@@6B@")` clashed with the canonical Snapshot, which was
  the earlier blocker. The subobject destructor now calls `Snapshot::~Snapshot()`
  explicitly, and the inline body produces the same table store.

No second body, alias or hatch is added, and the old name is tombstoned.

## Verification

- `./build.sh` on the three units: **18/18** rows exact.
- `./build.sh` on the header's five dependents: all rows exact, and all five preview LINKS.
- `link_check.py`: 3 of 3 LINKS, 899 -> 899 bytes against index `d707d2f53b`. This is
  a preview, not an export-link check.
- `class_gate.py` reports nothing for the changed files.
- `Rva005646BC`'s object now defines COMDAT copies of `??1Snapshot`, `??_GSnapshot` and
  `??_7Snapshot`. Their digests equal the majority digest of the 384 to 387 copies in
  index `d707d2f53b`.

No real-link or runtime result is claimed.

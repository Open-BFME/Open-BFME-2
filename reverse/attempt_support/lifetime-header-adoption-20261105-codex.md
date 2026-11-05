# LifetimeUpdate header adoption, 2026-11-05

Inspected revision: `5128dc56f7`. Claim owner: `yasinschroeder-codex`.
Scope: the five LifetimeUpdate consumers in the header queue. No shared header,
pin, alias or ledger identity changed.

## Retained repair

`PalantirObjectProgress.cpp` now includes the canonical
`GameLogic/Module/LifetimeUpdateClass.h` instead of a padded private class.
Its LifetimeUpdate-only accesses use the canonical fields at +0x24 and +0x28;
TemporarilyDefectUpdate's separate `m_startFrame` is unchanged. These offsets
come from the existing target-fact contract; no new semantic field name is claimed.
The automatic rewrite refused the shared field spelling, so those two explicit
LifetimeUpdate accesses were aligned before running `adopt --apply` again.

`header_adopt_lane.py accept --class LifetimeUpdate` accepted this source and
retired exactly its one queue row. The other four rows remain queued.

## Rejected provider adoption

Aligning LifetimeUpdate.cpp's constructor initializer and member accesses with
canonical `m_field24` and `m_field28` lets `adopt --apply` byte-verify the source.
Acceptance nevertheless refuses a real link loss: 675 -> 0 bytes, with these
unresolved canonical names:

- `??1LifetimeUpdate@@UAE@XZ`
- `?GetSnapshotName@LifetimeUpdate@@MBEPBDXZ`
- `?loadPostProcess@LifetimeUpdate@@MAEXXZ`
- `?xfer@LifetimeUpdate@@MAEXPAVXfer@@@Z`

Existing ledger facts, distinct from naming approval:

- 0x003A49D1: `??1Rva003A49D1@@UAE@XZ`, Rva0024A797Derived.cpp.
- 0x003A49EA: `?name@Rva003A49EANamed@@QBEPBDXZ`, ModuleNameGetters2.cpp.
- 0x003A4AFA: `?xfer@Rva003A49D1@@MAEXPAVXfer@@@Z`, LifetimeUpdate.cpp.
- 0x00497805: `?loadPostProcess@Rva00497805@@MAEXXZ`, BattlePlanUpdate.cpp;
  its ledger note describes a shared module-table tail call.

The canonical header's existing retail-vtable evidence connects these slots to
LifetimeUpdate, but the names/providers require their normal approval workflow,
including shared/folded identity checks. Do not add aliases to force adoption.
LifetimeUpdate.cpp was restored byte-for-byte and rebuilt after the trial.

Other cohort failures (no retained edits): ModuleFactoryInit.cpp has a Module
redefinition; HordeContainIface11CSlots.cpp has an ambiguous `m_20` rewrite with
AttributeModifierStore; GenericObjectCreationNuggetDoStuffToObj.cpp has no
canonical counterpart for BehaviorModule's private `m_interface` at +0xC.

## Final verification

- `./build.sh` on LifetimeUpdate.cpp and PalantirObjectProgress.cpp: 18/18 rows
  exact, including the five generated EH/funclet rows; string and float checks pass.
- `find_declared_unmatched.py` on the two sources: passes.
- Current-object `link_check.py`: LifetimeUpdate.cpp 675 -> 675 bytes;
  PalantirObjectProgress.cpp 546 -> 546 bytes, both LINKS (census index
  2026-11-05 05:17 at `c95fcfcfcd`).
- Final `header_adopt_lane.py accept` on PalantirObjectProgress.cpp: PASS.

This is one retired header-debt row, with linking coverage preserved. No new
census, real-link result or headline linked-byte gain is claimed.

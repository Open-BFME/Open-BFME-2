# ParticleSystemTemplate::createSlaveSystem: retail export

2026-11-06; base `5f3c26f35a9`. Status: repair verified locally, awaiting the automated
real link. This resolves the blocked verdict of 0x001F9CF3 in `reverse/re_attempts.log`,
which waited only on another worker's claim on `0x002115C5`.

## Target facts

Export ordinal 1552 names
`?createSlaveSystem@ParticleSystemTemplate@FXParticleSystem@@QBE?AV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@_N@Z`
at `0x001F9CF3`. The row carried a placeholder name that returned
`BfmeParticleSystemHandle`, the same 12-byte handle.

## Change

- `ParticleSystemTemplateCreateSlave.cpp` and `ParticleSystemConstructor.cpp` declare a
  `TrackingPtr<T>` view and use the exported signature.
- The constructor's unwind funclet `0x0076B9C0` now calls
  `??1?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@QAE@XZ`. Its body folds with
  `0x002115C5`, so `add_match.py --icf-owner` rows it there with `fold-proof=`, by the
  `a182fe7973` recipe.
- An unused declaration of the old name leaves `ParticleSystemDestructor.cpp`.

The old name is tombstoned. A `tu-skeleton` comment in `ParticleSys.cpp` still spells
it; that file was not otherwise touched.

## Verification

- `./build.sh` on the create and constructor units: **20/20** rows exact. The destructor
  unit builds exact too.
- `pin_consistency.py --check` passes.
- `link_check.py`: 3 of 3 LINKS, 1,860 -> 1,871 bytes against index `d707d2f53b`; the 11
  bytes are the new destructor row. This is a preview, not an export-link check.

No real-link or runtime result is claimed.

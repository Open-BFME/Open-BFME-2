# ProjectileNugget canonical Matrix3D adoption

Base: `f2bee160cf`. The default picker claimed the vanished
`WeaponEffects/ProjectileNuggetLaunch.cpp` header-debt scope. History shows
`dc4d318951` absorbed that source into `Common/Made002CC7DE.cpp`, where
its 0x00509A3C row still exists. The destination file scope was claimed
before editing. This is existing header debt, not a lost matched body.

The merged unit now includes `Matrix3DData.h` and its row-copy helper
accepts canonical `Vector4` references. Its member-wise copy and transform
arithmetic remain unchanged. The private Matrix3D and ProjectileNuggetRow
storage declarations are removed. No shared header, path, pin, row identity,
compiler flag or data owner changes.

`header_adopt_lane.transfer_sources` first carried the vanished source's
queue entry to the merged unit without retiring it. Then
`header_adopt_lane.py accept --class Matrix3D` passed and retired both
queue entries itself. The commit's per-key Debt-Retired trailer accounts
for the already-vanished source; its body remains in the merged unit and
the canonical-header acceptance covers that body too.

## Verification

- Baseline and final `./build.sh` pass all 14 matched function rows and the
  literal check. Frozen-source checks pass before and after editing.
- `eh_verify.py` reports EXACT 2; the build resolves both renumbered funclet
  labels through their verified parent EH data.
- Final `link_check.py --prepare-current` passes 14/14 rows with strict
  reusable receipts. An earlier preparation overlapped the queue transfer
  and correctly refused moved inputs; no receipt was accepted from that run.
- All 34 retained COMDAT name/digest/size tuples, strong definitions,
  undefined bindings, weak externals, relocation roots and retained
  reference edges are identical. The renamed row-copy helper has the same
  digest and size as its previous spelling. The added Matrix3D and Vector4
  constructors and vector-construction helper have respectively 58, 163
  and 913 identical copies in the fetched index. Their added reference
  edges are confined to the constructor helpers. Object facts are compared
  without assigning any retail-truth verdict; byte builds supply that proof.
- Ordinary preview retains LINKS and 1,565 -> 1,565 authored bytes against
  index `12b9e7a7c0` (2026-10-30 10:11; census `2c21184e84`). This is a
  prediction, not a new census measurement. The supported index fetch
  retained that same index and imported its published objects.
- Final staged-tree batch audit exits 2, INCONCLUSIVE: the index predates
  the outgoing base, and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
  current receipt. Carry this provider and wider consumers into the next
  scheduled census; full affected-consumer selection/loss checks and
  census confirmation remain pending. The earlier scoped audit also
  refused this provider's strict receipt after the new evidence files
  changed the include-search inventory. Re-preparing after all filenames
  were present succeeded, and the final audit passed that provider check.

The BFME 1 reference freshness marker was verified on 2026-10-29 17:57 UTC
at `f64f0f32d56adf72bee366d42cbb2a72cf192ae3`, within 72 hours. No donor
implementation is used. Scratch baseline/final objects, source and
comparison JSON are under `build/projectile-matrix-codexb/`.

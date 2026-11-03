### ProjectileNugget canonical Matrix3D storage (2026-10-30)

At base `f2bee160cf`, Made002CC7DE.cpp replaces its private Matrix3D storage
with the canonical header and takes Vector4 references in the row-copy helper.
History confirms the vanished ProjectileNuggetLaunch.cpp was merged, with its
0x00509A3C body retained. The owning acceptance passes the destination and
retires both header-queue entries after transferring the vanished entry.
All 14 rows and two EXACT EH graphs pass; strict preparation succeeds.
All 34 retained COMDAT fingerprints, external bindings and relocation roots
remain identical; the renamed helper has identical bytes, and added canonical
constructor helpers have identical indexed providers. Ordinary preview retains
LINKS and 1,565 authored bytes against index `12b9e7a7c0` (2026-10-30 10:11).
The staged audit is INCONCLUSIVE on that older index and the missing current
`Common/0CreateAHeroManager21FE49.cpp` consumer receipt. Carry the provider
and wider consumers into the next scheduled census; full affected-consumer
selection/loss checks and census confirmation remain pending. No census gain
is claimed. [Verification](../../reverse/attempt_support/projectile-nugget-matrix-header-20261030-codexb.md).

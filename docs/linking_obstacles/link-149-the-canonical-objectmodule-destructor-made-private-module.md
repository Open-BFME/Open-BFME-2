### LINK-149: the canonical ObjectModule destructor made private module views emit duplicate destructors (2026-10-29, seat yasinschroeder-claudeb2)

Status: repaired for four units, pending census confirmation; the related
RebuildHoleExposeDie unit is LINK-145's (below). 1c1d489768 adopted ObjectModule.h, which declares
`virtual ~ObjectModule()`. Units whose private UpdateModule, DamageModule or
derived-module views declare no destructor therefore gained implicit virtual
destructors. Each was emitted as a COMDAT that collides with the rowed
out-of-line bodies:
- `??1UpdateModule@@UAE@XZ` 0x0024A797, Rva0024A797DeletingDtor.cpp
- `??1DemoTrapUpdate@@UAE@XZ` 0x00495916, Rva0024A797Derived.cpp
- `??1WanderAIUpdate@@UAE@XZ` 0x004A935D, Rva0026E836Derived.cpp
- `??1CallHelpOnDamage@@UAE@XZ` 0x004BB4D1, TailJumpWrappers5B.cpp
- `??1DamageModule@@UAE@XZ`, symbols.csv 0x004B96CC; the COMDAT copy was not retail's body

The 85f6b7f40c census therefore lists nine units that linked at 840db2d676
as not linking. Repair: the views in DemoTrapUpdate.cpp, WanderAIUpdate.cpp,
RadarUpdateConstructor.cpp and CallHelpOnDamageCtor.cpp now declare those
destructors out of line, as retail compiled them. All rows stay exact (10/10,
12/12, 1/1, 1/1). `link_check.py` on the four edited units plus the four
rowed providers predicts LINKS for 8/8 (LINKED 3,730 -> 3,809 B).

RebuildHoleExposeDie.cpp's matching duplicate (row 0x004867F9) was repaired
separately by LINK-145, which moved that row into its approved TU. The
CallHelpOnDamage duplicate LINK-145 leaves open for TailJumpWrappers5B.cpp is
the one this entry's CallHelpOnDamageCtor.cpp view repair addresses.

Current-object follow-up (2026-10-30, base `c083ef052d`): both
Rva0026E836Derived.cpp and WanderAIUpdate.cpp verify 12/12 rows. Their paired
preview overlays the repaired declaration and retains 2/2 LINKS, 428 + 646
authored bytes, against `85f6b7f40c`; an isolated destructor-unit preview still
sees the index's historical duplicate. No new repair or census gain is claimed.
The supported split of the Wander destructor into its approved TU is blocked
before writing: the mixed file's retained linker alias would be duplicated,
growing its hatch count. Recover the secondary-interface contract and remove
the alias before retrying. No paths moved; consumer and census confirmation
remain pending. [Checks and prerequisite](../../reverse/attempt_support/wander-dtor-split-20261030-codexb4.md).

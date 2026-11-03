### LINK-157: a canonical base adoption renamed a vftable that a sibling unit binds by explicit identifier (2026-10-30, seat halilkkaya-lk8)

Status: repaired for the one affected unit; census confirmation pending.
`AttributeModifierAuraUpdateCtor.cpp` (128 B) stores its four vptrs through
explicit `extern "C"` vftable identifiers instead of compiling the class's
vtables. Its primary table (0x00C50D2C) was spelled
`??_7AttributeModifierAuraUpdate@@6BModule@@@`, the name the destructor unit
emitted while its private base was called `Module`. `bdd953ddfc` moved
`AttributeModifierAuraUpdateDtor.cpp` onto the canonical
`Module.h`/`ObjectModule.h` chain, so its compiled table became
`??_7AttributeModifierAuraUpdate@@6BObjectModule@@@` and the ctor's name had
no definer (census 2c21184e84: sole blocker, unresolved). Fix: the ctor binds
the name the only definer emits. Both rows store the same retail address, so
scoped DIR32 consistency over the ctor and dtor rows stays OK (6 symbols);
`./build.sh` 2/2; `link_check` 143 -> 271 B over both units (ctor 0 -> 128).
A sweep of every census-unresolved `??_7` name against same-class defined
tables found no other unit with this mismatch. Pattern: after a header
adoption renames a base, grep explicit `__identifier("??_7<Class>@@6B<old base>@@@")`
bindings in sibling units.

Update 2026-11-03 (seat leonardbuhl-claude): same cause, second family.
`f2bb856a7c` (canonical `DefaultPhysicsModuleInfo`) and `a24cc69d73`
(canonical `Rva003AEEB3`) renamed the secondary vftables of `Rva003ABD20`,
`Rva003ABD81`, `Rva003AEDE9` and `Gen005ED0D0`, so six explicit
`__identifier` bindings in `ModuleCtorChainsA.cpp` had no definer (real link
at d0b9cc5d27 blocker, 6 names). Each old name was mapped to its new one by
address, reading retail's DIR32 value at every relocation of the emitting
ctors (`Rva003ABD20Ctor.cpp`, `Rva003ABD81Ctor.cpp`, `Rva003AEDE9CopyCtor.cpp`,
`Rva003AEE16CopyCtor.cpp`): `..._3AEE16` HeadBase -> `6BDefaultModuleHeadBase@@@`
(0x0081CF18, 0x0081CF68), SecondBase -> `6BRva003AEEB3Slot14@@@` (0x0081C574,
0x0081C5B8, 0x0081C61C, 0x0081C6A0). The two split siblings
(`ModuleCtorChainsA_Rva003ABAF3.cpp`, `..._Rva003ABB93.cpp`) carried the same
names and were repointed too. `./build.sh` 42/42 and 19 data rows OK;
`link_check` (census 8661f15284) 649 -> 1,389 B over the three units
(`ModuleCtorChainsA.cpp` 0 -> 740). No other `Code/` file still binds the
retired names. Census confirmation pending.

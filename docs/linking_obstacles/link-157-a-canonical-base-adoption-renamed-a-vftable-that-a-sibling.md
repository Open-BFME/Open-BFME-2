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

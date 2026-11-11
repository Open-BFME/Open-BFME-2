### LINK-157: DeflectSpecialPower's ctor view gave its collide interface a placeholder slot (2026-10-30, seat halilkkaya-lk8)

Status: repaired; census confirmation pending.
`DeflectSpecialPowerConstructorThunk.cpp` (78 B) lost `??_7DeflectSpecialPower@@6B@`
to the first copy, `DeflectSpecialPower.cpp`'s (census 2c21184e84: sole
blocker). That name is the +0x38 interface table, retail 0x00C5D974, whose
slot 0 is the rowed `onCollide` override 0x004C55B2 (the ctor 0x004C545D and
dtor 0x004C54BE store it at +0x38). The thunk's placeholder
`DeflectSpecialPowerIface5` declared `deflectSpecialPowerIface5Anchor()`, so
its copy named that anchor instead. Fix: the interface declares the one pure
`onCollide(Object *, const Coord3D *, const Coord3D *)` slot and
DeflectSpecialPower overrides it; the table now names the rowed override like
the first copy, and the interface's own table (0x00C40818) is `__purecall`.
The interface keeps its placeholder name on purpose: the census index also
holds a seven-slot `??_7CollideModuleInterface@@6B@` (CollideModuleCtor.obj), so
spelling it `CollideModuleInterface` here would add a conflicting one-slot copy.
Verified: `./build.sh` 1/1; scoped DIR32 consistency over the thunk,
DeflectSpecialPower.cpp and SupplyCenterDockUpdateConstructor.cpp OK
(21 symbols); `link_check` 591 -> 669 B over the five DeflectSpecialPower units
(thunk 0 -> 78). Follow-up done: nothing referenced
`?deflectSpecialPowerIface5Anchor@DeflectSpecialPowerIface5@@UAEXXZ` any more
(census touches: only the old thunk and its definer), so its present-unmatched
definition in `SupplyCenterDockUpdateConstructor.cpp` is removed (1/1 row,
LINKS 49 -> 49 B; one hatch line retired).

The separate +0x20 table at RVA 0x0085D98C has nine retail entries. Both installer views now declare its second entry, isSpecialAbility, and the concrete override returns false at RVA 0x0047A699. [Native slot evidence](../../reverse/attempt_support/deflect-secondary-slot-004c5551.md).

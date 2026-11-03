### LINK-154: TeamPrototype::moveTeamTo's file-wide `/Oy-` framed its Coord3D copy (2026-10-30)

e2191b6e81 replaced the unit's frame-pointer pragma with a file-level `/Oy-`.
That flag also gave the unit's inline `Coord3D(const Coord3D &)` an ebp
frame (28 B). The other 66 index copies agree on a frameless 25 B copy, and
the unit's copy, now first in link order, was its sole blocker. The row's own
frame comes from its ESP save for the by-value argument, so `/O1` without
`/Oy-` still matches it (1/1). Removing the flag changes only three inline
COMDATs (the Coord3D copy, the DLINK_ITERATOR constructor and
`iterate_TeamInstanceList`). Nothing is added or removed, and the undefined
externals are identical. Preview against index `6fe1089c24`: LINKS, 0 -> 90
bytes. Census confirmation is pending. Of the other 544 `/Oy-` units, only
`DebugDestructorThunk.cpp` and `ArmyHeroIconCtor.cpp` are blocked, and
neither by an inline copy of this kind.

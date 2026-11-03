### LINK-145: placeholder 5-byte destructor rows duplicate their module unit's implicit destructor (2026-10-29, seat b1)

Status: RebuildHoleExposeDie repaired, pending census confirmation; the rest open.
The 85f6b7f40c census lists RebuildHoleExposeDie.cpp linked=no with one
duplicate, `??1RebuildHoleExposeDie@@UAE@XZ`: TailJumpWrappers5B.cpp defined it
strongly (a novtable view, row 0x004867F9), while the module unit's ctor emits
the vtable and so the implicit destructor COMDAT. Repair: the row moves into its
approved TU (tu_map), where the implicit destructor compiles to retail's 5-byte
`jmp ~DieModule` once the TU's DieModule declares its out-of-line
`virtual ~DieModule()` (an explicit empty destructor there stores the three
vptrs first, so it does not match). TailJumpWrappers5B.cpp drops its copy;
9/9 and 65/65 rows exact. Preview: RebuildHoleExposeDie.cpp 0 -> 670 B, all
18 units naming the class still link.
Cleared for `??1CallHelpOnDamage@@UAE@XZ` (0x004BB4D1) from the other side
(2026-10-29, seat dd-20): the row stays in TailJumpWrappers5B.cpp, and
CallHelpOnDamageCtor.cpp declares `virtual ~CallHelpOnDamage()` and its base
`virtual ~DamageModule()` out of line, so the module unit emits neither implicit
COMDAT and keeps referencing retail's rowed 25B `??1DamageModule` at 0x004B96CC
(Rva0049B47CThreeVptrDerived.cpp). Preview against index 85f6b7f40c:
TailJumpWrappers5B.cpp LINKS 0 -> 309 B and CallHelpOnDamageCtor.cpp LINKS
0 -> 46 B (355 B together); the ctor's own row stays exact (46 B). A later
consolidation that moves the row into the approved TU keeps these declarations.
Still open: the other rows of that file's table (e.g. RiderChangeContain,
LevelGrantSpecialPower) may hide the same split; check each against its module
unit.

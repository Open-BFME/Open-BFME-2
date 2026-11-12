### LINK-662: canonical header adoption drops a unit's noinline destructor
Status: Repair landed / awaiting census confirmation. Updated: 2026-11-12; inspected revision: d3809cf5c05 (census index c31795c94c).

**Problem.** OwnedPointerResets.cpp defines the 5-byte pointee destructors its owning-pointer resets and clears
call (each `~X` tail-jumps to a rowed clear helper). Retail calls those destructors out of line, so the unit's
private views declared them `__declspec(noinline)`. Five adoptions replaced the private views with generated
canonical headers (`tools/header_adopt_lane.py`) that declare a plain `~X();`, so cl expanded each destructor and
the resets and clears called the clear helper instead:

| canonical header commit (StarkillerHDX) | destructor | rows that changed call target |
|---|---|---|
| "Register canonical Rva00527FA2, adopt it in 5 units" (2026-11-11, before the census) | 0x00527FA2 | ?reset@Rva002D390E, ?clear@Rva002D3931 |
| "Register canonical Rva005D32D4, adopt it in 3 units" (2026-11-11, before the census) | 0x005D32D4 | ?clear@Rva005786CD |
| "Register canonical Rva0052710C, adopt it in 4 units" (2026-11-11, before the census) | 0x0052710C | ?reset@Rva002D38AE, ?clear@Rva002D3894 |
| "Register canonical Rva004E668E, adopt it in 3 units" (2026-11-12, after the census) | 0x004E668E | ?reset@Rva0029B5FD, ?clear@Rva0029B5E3 |
| "Register canonical Rva005E893E, adopt it in 3 units" (2026-11-12, after the census) | 0x005E893E | ?reset@Rva005CE236, ?clear@Rva005CE21C |

The byte gate passed all nine rows (`Functions: OK 79/79`): each new REL32 target is one `jmp` away from retail's.
link_check refuses the five COMDAT resets ("not retail's body"). So OwnedPointerResets.cpp was already at 0 bytes in
the c31795c94c census. After the Rva005E893E adoption, ThrowingNewHelpers.cpp (1,388 B in the census) also stopped
linking, because its `m_build.reset(...)` selects OwnedPointerResets.cpp's wrong `?reset@Rva005CE236` copy.
AptPalantirCallbacks.cpp, which calls the Rva002D38AE and Rva002D390E resets, was at 0 bytes for the same reason.

**Completed.** "Keep OwnedPointerResets.cpp's six pointee destructors out of line under their canonical headers"
puts `__declspec(noinline)` on the unit's out-of-line definitions of the five canonical destructors (0x004E668E,
0x0052710C, 0x00527FA2, 0x005D32D4, 0x005E893E). 0x005D4FFC still has its private noinline declaration. No header
or contract is edited. Object diff before and after: exactly the nine REL32 targets change (clear helper -> `??1X`),
plus `.debug$S`. A REL32 check of all 79 rows against retail found 9 different targets before and 0 after. Retail
evidence: for example, 0x005CE236+0x14 is `e8 f0a60100` -> 0x005E893E and 0x005786CD+0xD is `e8 f6ab0500`
-> 0x005D32D4. `./build.sh` exact 79/79; `find_declared_unmatched` clean; scoped DIR32 OK. link_check
(c31795c94c) over the 13 units that define, include or call these classes: 13/13 LINKS, LINKED 17,792 -> 21,358 B
(OwnedPointerResets.cpp 0 -> 1,927, AptPalantirCallbacks.cpp 0 -> 1,639, ThrowingNewHelpers.cpp back to 1,388,
the other ten unchanged).

**Recipe.** When a unit defines a destructor (or any small member) that retail calls out of line, and the unit
adopts a canonical header that declares it plainly, put `__declspec(noinline)` on the unit's definition. Do not
re-declare the class privately. Compare every REL32 target of the unit's rows with retail, not only the byte gate.

**Remaining / next check.** Tooling (not edited here): header_adopt_lane could refuse an adoption that changes a
REL32 target of a matched row, as LINK-660 asks for novtable. The byte gate could also report a REL32 target that
differs from retail's even when one `jmp` joins the two. Census confirmation: awaiting the next published census
(expect OwnedPointerResets.cpp and AptPalantirCallbacks.cpp to link and ThrowingNewHelpers.cpp to return).

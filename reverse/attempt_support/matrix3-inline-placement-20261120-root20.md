# Matrix3 consolidation placement conflict

Inspected the `f4c8293eba7` worktree. The picker claimed 16 donors.
A fresh `tu_skeleton --plan` reported 53 approved rows, 17 donor
files and eight mixed files. The read-only naming inventory
completed. The relevant donors retain their current source paths.

The Matrix3 seed's ten math methods occupy 0x007167E0–0x00717110.
The disputed region contains LivingWorldVisual code beginning at
0x003FB602. The current seed file contains both regions. The fresh plan
assigns the disputed LivingWorld rows to the math path through
class-site evidence; the ten Matrix3 rows have separate proposed
WWmatrix3 placement evidence. The three WorldBuilder
pairings at 0x003FC6C3, 0x003FC74A and 0x003FCEA3 name
`Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldVisual.cpp`.
The map's own N hints give that same source for the named methods.

The two class-site anchors are `Matrix3x3::Rotate_Z` at
0x003FBF50 and 0x003FC4C2. Both definitions in the pinned Zero Hour
`matrix3.h` are `WWINLINE` at lines 851 and 856. The 163-byte
ledger row cites a byte-matched BFME1 `sphereobj` emission of the
header body. The attempts for the 202-byte overload also reproduce
it from that donor. The class declaration's location therefore
does not establish the TU that emitted either retail copy.
The regions have different retail flag profiles, which is
supporting evidence involving their code generation.

Commit `9ab7f148248` previously moved 0x003FB793 and 0x003FCD58
into the seed after byte and link checks. It used the same anchors.
The earlier [TU-approval handoff](matrix3-tu-approval-20261028-codex3.md)
records the underlying evidence gap.

The appropriate follow-up is to review whether an independently
witnessed nonvirtual header-inline body can stop supplying
class-site placement evidence in this case. The current mapper
intentionally limits its header-COMDAT exclusion to constructors
and virtual members, and its regression suite covers the
nonvirtual case. Any approval rule change needs a scoped test
and holdout before retrying a source move. The WorldBuilder
path by itself does not approve a BFME II source move.

The native baseline verified 13 rows and one data row across the
seed and pickbox donor. The owning header tool retired the existing
canonical `Rva003F936EHost` key for the seed and accepted the pickbox
donor's use of `LivingWorldVisual::m_robj14` at +0x14. The pickbox
retains its 54-byte row and 54 scoped linked bytes at its current path.

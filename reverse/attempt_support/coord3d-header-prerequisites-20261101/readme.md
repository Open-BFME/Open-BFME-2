# Remaining Coord3D header prerequisites

At master 7e6d5ab28c the picker served the six remaining Coord3D header rows.
The supported `header_adopt_lane.py adopt --class Coord3D --header
Code/Libraries/Include/Lib/Coord3D.h` dry run refused every source and wrote no
Code or register change. Its command names the six sources below; a compact
verdict summary accompanies this handoff.

* Coord3DCopy.cpp requires its StlportVectorRva00601A3A.cpp consumer in the same
  verified symbol migration.
* Rva0055A246Ctor.cpp, coord3d.cpp and matrix4d.cpp trigger the coordinated
  dependency check (2,293 additional source mentions per diagnostic).
* Weapon_bfmeGetLOSVictimPos.cpp defines a custom Coord3D constructor absent
  from the canonical declaration.
* coord3d_crossproduct.cpp needs the absent CrossProduct member.

The known boundary remains the class/struct mangling mismatch, missing native
member declarations, and per-unit lifetime requirements. The shared-header
member-addition failure in Player::initFromDict remains documented in the
attempt log; no shared header or contract was changed in this pass.

Two private matrix trials replaced only its three-float private class with
the canonical include: one plain include and one preceded by `class Coord3D;`.
Both match 14 unique RVAs out of 24 ledger rows and miss the same eight
Coord3D-bearing names. A legal forward declaration does not preserve the
required MSVC V-key when the actual definition is struct-keyed. No symbol
alias or other workaround was introduced.

Private weapon trials removed its custom Coord3D constructor and used a named
return object plus the existing member-call view. The POD header introduces
a stack temporary and copy (46 bytes versus native 30). Direct by-value return
still copies (45 bytes). The supported constructor companion produces 52 bytes
for direct by-value return, and 63 for the final named-return trial. The
callee identity stays the existing adjustment provider; the hidden-result
and copy shape does not match. No private trial is retained in Code or claimed
as progress. The final complete candidate stays local under build.

Next work requires an approved coordinated class-key/member/lifetime plan,
with all affected providers and callers verified together. The six queue rows
remain in their owning register. These are current prerequisites, not lost
matched coverage. No linking or census gain is claimed.

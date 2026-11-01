# Coord3D weapon return profile: rejected companion trial

Base `8c6bd6ae65d`, published preview index `0d24c60eef` (2026-11-01
09:19). The default picker claimed the six remaining Coord3D adoption
units. Before edits, normal verification passes 113/113 rows across
Coord3DCopy.cpp, Rva0055A246Ctor.cpp, Weapon_bfmeGetLOSVictimPos.cpp,
coord3d.cpp, coord3d_crossproduct.cpp and matrix4d.cpp. Frozen-file checks
pass; the allowed pre-existing markers are retained.

The class/struct and interface prerequisites in LINK-018 remain in current
sources: the library/copy/Bezier/matrix rows use V-form class symbols, while
the canonical and existing companion headers use struct. CrossProduct is
absent from the canonical interface; its previous shared-member/EH regression
was not retried. No broad signature migration or shared-header growth is made.

The weapon wrapper already returns struct Coord3D. Its private constructor
forwards the hidden result pointer directly to the existing target-position
provider, producing the complete native 30-byte body at
`0x002CB65B..0x002CB679`. An existing Coord3DCtorView.h companion offers a
possible alternative to growing the canonical interface: remove the private
weapon-specific constructor, pass a named result to the same existing
member-pointer call, then return it through the shared non-POD copy contract.

That experiment fails the normal byte gate. MSVC emits 63 bytes: it allocates
a twelve-byte temporary, passes that address, then copies its three words to
the hidden output slot. Native instead forwards the output slot directly.
The rejected patch and gate output are adjacent. This rules out this named
return form under the current compiler profile; it does not prove every
possible return reconstruction impossible. No new ABI cast, pin or alias is
introduced, and the existing provider's TargetCoord/flag interface is not
asserted to be the final application contract.

The trial is fully reverted. Normal verification again passes the 30-byte
body, frozen checks pass, and all restored external COMDAT byte/relocation
facts and strong/undefined/weak symbol sets equal the archived before facts.
The original ordinary preview is LINKS, 30 -> 30 bytes. No source/header,
ledger, queue or hatch change is retained; no header debt, source-file,
authored-C++ or census linking gain is claimed. The class scope is released.

Next: reconcile the actual native hidden-return/provider contract or find a
byte-exact shared construction path before retiring this queue key. The other
five units retain their documented class-key/interface prerequisites. Broad
Coord3D dependent recomputation and census confirmation remain separate work.

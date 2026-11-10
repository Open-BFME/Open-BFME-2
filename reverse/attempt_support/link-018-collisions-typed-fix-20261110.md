# LINK-018 collisions: rejected sources and what a typed fix needs (2026-11-10, swarm Link lane)

The combined collision fix was reviewed twice (GPT Sol, 2026-11-10, REQUEST CHANGES both times). Every rejected unit
byte-matches its rows but reaches a shared 12-byte body through a cast to another type. None of it is in master. The rejected
sources are kept outside the repo, in the lane's sweeps directory.

## Rejected units
| unit | row | rejected construct |
|---|---|---|
| StlportVectorAssignCoord3D.cpp | operator= 0x2CD098 | `capacity()` through `reinterpret_cast<const vector<Coord3D> *>`, to keep the element's capacity COMDAT out |
| Coord3DVectorFillInsert.cpp | fill-insert 0x82719 | an anonymous `{float X, Y, Z}` record used as a Vector3 |
| Rva000C0513Resize.cpp | 0xC0513 | a `Coord3D` parameter passed on as `*(const BfmeE12 *)&val` |
| Coord3DVectorFillInsertO1.cpp | _M_fill_insert 0x4E29C8 | `vector<BfmeE12>` reinterpreted as the PrereqUnitRec vector, to reach its rowed helper |

The review did not flag these, but they use the same pattern: `PUSH_POINT` in Rva000E0AE2ObjectRegistration.cpp, the
`vector<Vector3>` clear in GapBodiesGE37.cpp, and `(Coord3D *)` casts in Rva00082C98Clamp.cpp.

## Target facts (game.dat 1.06)
- No export names any of these element types or their vectors' members.
- Parser 0x2CE849 stores the third word of the 0x2CD098 element straight from `INI::scanUnsignedInt` (no conversion), so the
  element is neither Coord3D nor Vector3. Its copies are hand-written (0x2CA86E, 0x346C2D move the fields through edx).
- A real `const Vector3` local in the fill-insert matches 5/5 rows. Its object adds one unreferenced `??0Vector3@@QAE@ABV0@@Z`
  COMDAT, the same shape as Coord3D's exported copy constructor 0x4216D3.

## What a typed fix needs
- The real element type of each family, from retail's own code: its parser or constructor, its copy shape, its field types.
- Each shared body reached by its own instantiation name. Where retail folded bodies, a fold-proven pin
  (`pin_admission.py --add`, `fold-proof=`) instead of a cast.
- Plan: sweeps/link-018/element-types.md. It is the prerequisite for the class-key flip.

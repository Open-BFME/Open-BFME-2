# 0x0012FE00: the sorted-insert's name and signature (LINK-661, sortingrenderer.cpp)

Seat halilkkaya-cs97, base `4b82f841b5a`, 2026-11-12. No rename was made; this is
the evidence a naming seat needs to make it.

Why it matters: the TU map approves Get_Sorting_Struct (0x0012FD80, by T) and this
row (by Z) for `sortingrenderer.cpp` only once 0x0012FE00 is spelled as a
`SortingRendererClass::Insert_Triangles` overload (cs96's in-memory `tu_map.build`,
LINK-661). That approval is the first step of the merge that gives `sorted_list` /
`clean_list` one definition and ends the per-frame SortingNodeStruct leak.

Current row: `?Insert@BfmeSortingDispatchAt0012FE00@@SAXABUTargetCenter3@@IIII@Z`,
1520 B, `SortingRendererBFME1.cpp`, matched. Eleven units spell the placeholder
(`rg -l BfmeSortingDispatchAt0012FE00 Code`).

## Target facts (retail bytes and matched rows)

- Static `__cdecl`, no `this`; five stack arguments. Arguments 2-5 are compared
  against 65535 as 32-bit unsigned values before use (`unsigned int`, `IIII`),
  exactly as in Insert_VolumeParticle 0x00130410 (rowed `...SphereClass@@IIIII@Z`),
  whose body is this one plus a sixth multiplier.
- The body reads the first argument only at +0, +4 and +8 (three floats of a
  centre projected through world*view).
- Callers that build the argument build 12 bytes, three zero floats, no fourth
  store: the four-`unsigned short` overload 0x0011C6B0 (matched,
  `SortingRendererInsertTrianglesNoSphere.cpp`), DX8Wrapper::Draw_Triangles'
  sorting branch (call at 0x00120613, `DX8DrawTrianglesDispatch.cpp`),
  `linegrp.cpp`, `pointgr.cpp`. Every caller matches with that 12-byte object.
- Callers that hold a sphere (`StreakRendererRenderStreak.cpp`,
  `StreakRendererSetTextureBFME1.cpp`, `seglinerenderer.cpp`, the forwarder
  0x0012630B) pass the address of their `const SphereClass &obj_sphere`, which is
  also the address of its Center.

## Donor facts (Zero Hour / BFME 1 source; they suggest, they do not prove)

- ZH and BFME 1 `sortingrenderer.h` declare
  `Insert_Triangles(const SphereClass&, unsigned short x4)` and the
  four-`unsigned short` overload; ZH's four-argument overload builds
  `SphereClass sphere(Vector3(0,0,0), 0.0f)`, which stores a radius too.
- `build/zh_sweep/match.json` holds ZH's
  `?Insert_Triangles@SortingRendererClass@@SAXABVSphereClass@@GGGG@Z` with bucket
  `no-placement`, so `canonical:zh` cannot grade it, and its spelling (`GGGG`) is
  not this body's (`IIII`) in any case.
- `reverse/wb_name_leads.csv` at 0x0012FE00 is a callgraph lead naming
  Insert_VolumeParticle: a hint, and wrong.

## Inferences

- Owner and identifier: `SortingRendererClass::Insert_Triangles` (the sphere
  overload's role, the four-short overload tail-calls it, Insert_VolumeParticle is
  its twin). Strong, but an inference: no canonical basis grades it.
- Parameter 1: the 12-byte construction at four call sites argues for a
  centre-only type (`const Vector3 &`) in BFME 2 rather than ZH's 16-byte
  `SphereClass`, whose constructor would store the radius. cs96's simulation used
  `SphereClass`; for the map's Z evidence the parameter type does not matter, for
  the name it does. Undecided: needs the naming lane's review.

## Route and its blockers

1. No canonical basis applies (above), so the respell is `inferred`: two distinct
   workers' votes through `name_lane.py` with a `--respell-batch` manifest and
   `--prepared` texts for all eleven units (docs/naming.md, "Prepared
   ordinary-function respells"). This seat cast none: AGENTS.md rules out the
   external reviewer the submission would dispatch, and one vote approves nothing.
2. `reverse/symbols.csv:3765` pins the ZH spelling
   `?Insert_Triangles@SortingRendererClass@@SAXABVSphereClass@@GGGG@Z` at
   0x0012FE00 (`pin_consistency.py --symbol`: consistent, owned by the placeholder
   row). `rename.py function --respell` refuses while an alias pin shares the
   address, so the rename must settle this pin (its consumers bind the GGGG
   spelling) in the same plan.
3. Then `tu_skeleton.py --split SortingNodeStructDtor.cpp --for sortingrenderer.cpp`
   (Get_Sorting_Struct out; the SortingNodeStruct dtor 0x0012FCA0 and `??_G`
   0x001303F0 stay proposed for SortingNodeStruct.cpp by their class-name hint)
   and `--merge sortingrenderer.cpp`.

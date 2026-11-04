# vector<"W3DAnimationInfo">::insert 0x00538944: element identity

Measured 2026-11-04 at 3d9f2fc655 (link index 5a13f2cd61, census 171fb36062).

Target facts:
- 0x00538944 (149 B, `W3DAnimationInfoVectorInsert.cpp`) calls Construct
  0x00469C61, copy 0x0004254E, `__copy_backward_ptrs` 0x005B2B1E and the
  overflow worker 0x0047008E. 0x00469C61 and 0x0047008E are rowed as the
  `BfmeFloat4Record00469C61` vector helpers (`stlport_vector_float4_469c61.cpp`).
  0x0004254E is the folded 31-byte four-dword memberwise copy (Region2D owner).
- `reverse/tu_map.csv` approves 0x00538944 into `QuadStrip2D.cpp`. That unit's
  `addStrip`, `rva0053892C` (reserve) and strip loops use `QuadStrip2D::m_vec`
  as `vector<BfmeFloat4Record00469C61>`; `insertStrip` (0x005389ED) casts the
  same member to `vector<W3DAnimationInfo>`.

Donor facts: the BFME 1 donor
(`reference/open-bfme-1/.../W3DAnimationInfoVectorInsert.cpp`) states its
element's first member is an AsciiString and that it has a destructor;
`W3DModelDraw.obj` here emits `_Destroy<W3DAnimationInfo*>` as a 33-byte
destroy loop.

Inference: one 16-byte trivially destructible record (four floats, memberwise
copy) carries two spellings. The `W3DAnimationInfo` spelling on 0x00538944,
`QuadStrip2D::insertStrip` and `Rva0030BE41::rva0030BC2B` (and its pins at
0x00469C61, 0x0047008E, 0x0004254E, 0x005B2B1E) came from the donor sweep and
does not fit the retail bodies.

Trials (all reverted):
1. Declaration-only `_Construct<W3DAnimationInfo>` in the insert unit: insert
   stays 149/149.
2. Also declaration-only `_M_insert_overflow<W3DAnimationInfo>`: insert FAILS
   (body changes; the 2026-10 forwarder trial saw frame 0x10->0x18).
3. Insert unit with `/D_CRTIMP= /Ireference/shims/bfmealloc`: insert FAILS.
4. Trial 1 plus a W3DAnimationInfo (4-float, memberwise copy) instantiation of
   `_Construct` and `_M_insert_overflow` in `stlport_vector_float4_469c61.cpp`:
   both units build (8/8) and `link_check` previews both as LINKS (insert
   0 -> 149 bytes). Not kept: the provider also emits `_M_clear`, `_Destroy`,
   `__destroy`, `__destroy_aux` for `W3DAnimationInfo` with trivial-destructor
   bodies that collide by name with W3DModelDraw's real class (ODR clash; the
   kept copy would decide whether real W3DAnimationInfo vectors run destructors).

Next: settle the element's identity under docs/naming.md (the readable donor
spelling cannot be folded into the placeholder by `rename.py class --fold`;
it needs a naming decision or a `restored` revert), then respell the three
rows and the insert unit onto the float4 family, whose helpers already link.

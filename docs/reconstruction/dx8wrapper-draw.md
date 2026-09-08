# BFME2 primitive drawing

The recovered static role `BfmeDrawOps::Draw` matches all 452 code bytes at RVA
`0x1203C0`, plus both trailing 16-byte switch tables. The final return is at
`0x120583`; tables occupy VA `0x520584..0x5205A3`, followed by twelve alignment
bytes before the next function. All eight table entries and both references to
those tables are verified against their actual labels within the emitted body.

The older header declares a five-argument routine with 16-bit counts. This
retail routine takes five 32-bit unsigned arguments (primitive, start, polygon
count, minimum vertex, vertex count) and a sixth boolean selecting indexed
rendering. The recovered role preserves that independently decoded ABI without
misdeclaring the older header's function. It invokes the independently verified
render-state application routine before binding/drawing behavior.

The reconstruction preserves:

* The polygon lower-limit check and runtime triangle-disable switch.
* A conditional emissive-only pass. If enabled at VA `0xDEC3D8`, a missing
  material or all three emissive components below `0.1f` suppress the draw.
  The constant is independently `CD CC CC 3D` at VA `0xBC2424`. Unordered float
  comparisons retain retail behavior; the threshold was not inferred from the
  relocation-masked byte match.
* Snapshot-mode `IDirect3DDevice9::ValidateDevice`, even though its diagnostic
  output is absent in this retail build.
* Vertex-count inference for static/sorting and dynamic buffers, the separate
  non-indexed path, correct D3D9 base/start offsets, and sorting-buffer fallback.
* Polygon, vertex, and draw accounting at the same points as the retail body.

This function establishes the previously unexamined state fields, relative to
base VA `0xDEE5D8`:

| Field | Offset and width |
| --- | --- |
| Dynamic vertex offset | `0x278`, unsigned short |
| Dynamic vertex count | `0x27A`, unsigned short |
| Dynamic index offset | `0x27C`, unsigned short |
| Index base offset | `0x28C`, unsigned short |
| Vertex buffer's vertex count | pointee `+0xC`, unsigned short |

The two additions/subtractions involving vertex and index-base offsets were
reconciled in source order so that every emitted global reference resolves to
its actual field. Treating those words as interchangeable relocation targets
would produce inconsistent state-object bases and is rejected by the audit.
All 42 existing bodies remain exact with the refined field views.

Two callees are identified without claiming their code as new completed bodies:

* `Debug_Statistics::Record_DX8_Polys_And_Vertices`, RVA `0x129540`, is 68 bytes
  through return `0x129583`. It tests the shader NPatch bit and the independently
  proven caps support flag, optionally scales polygon count by the square of
  the NPatch level, and updates polygon, vertex, and draw counters. This agrees
  with the reference statistics source.
* `bfmeDrawSortingPrimitive`, RVA `0x11D710`, is the recovered five-unsigned
  sorting conversion role. All 539 bytes through return `0x11D92A` were decoded.
  It rejects polygon/vertex counts above 65535, creates dynamic vertex/index
  access objects, copies and rebases the sorting data, binds D3D9 buffers,
  submits a triangle draw, accounts for it, and releases both access objects.
  Its explicit bounds checks corroborate the wider caller ABI. Its exception
  metadata is a separate obligation when that callee's body is reconstructed.

Existing verified identities supply material emissive retrieval (`0x13CC80`)
and render-state application (`0x11D930`). Eight global bases were independently
checked: draw limit `0xDEDA80`, emissive mode `0xDEC3D8`, render state `0xDEE5D8`,
triangle enable `0xDB5FCD`, snapshot mode `0xDEC3FD`, device `0xDEDA34`, draw
counter `0xDEDA6C`, and API-call counter `0xDEDA98`.

The SDK-ordered D3D9 interface supplies `ValidateDevice`, `DrawPrimitive`, and
`DrawIndexedPrimitive` at vtable byte offsets `0x118`, `0x144`, and `0x148`.
There are no exception tables, string literals, or direct imports in this body;
the compiler float literal and all switch-table targets were independently
verified before the normal source gate.

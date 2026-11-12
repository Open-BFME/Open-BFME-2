# VertexLoc split (LINK-661): extern route and pointgr.cpp merged-context probes, 2026-11-12

Seat halilkkaya-pg1, base `b8e28c36439`. Goal: `PointGroupClass::Render`'s helpers in pointgr.cpp and the
0x0017A890 body (`PointGroupClassRva0017A890.cpp`) use one VertexLoc. Nothing landed in `Code/`; this file
records what was measured so the next attempt starts from it.

## Target facts (retail image)

- One datum: VA 0x00DF708C (RVA 0x009F708C, 16 bytes, `VectorClass<Vector3>`). Every user names that one
  address: 0x0017A890 reads `.Vector` (`[0xDF7090]`) as its first instruction; the sizer 0x0017F150 (called
  from Render) reads `+8` and passes `0xDF708C` to Resize; 0x00179B50 reads `[0xDF7090]` twice; 0x0017E920
  clears it; the initializer 0x007ACF20 constructs it and the atexit 0x007B7400 (59 bytes) destroys it with
  the destructor and Clear inlined.
- 0x0017A890 sits inside pointgr.cpp's address run (0x00179B50 before it, 0x0017D770 after it), and
  retail builds its four `Vector3` arrays through `??_H` (call target RVA 0x00001423, the linked /O1 copy)
  with `??0Vector3@@QAE@XZ` (VA 0x0087A6A9). Retail 0x00179B50 calls the same `??_H` three times, Render
  0x0017F400 never.

## Our objects at the base

- `pointgr.obj` defines the external `?VertexLoc@@3V?$VectorClass@VVector3@@@@A` with its own `_$E32`
  initializer (26 bytes) and `_$E33` atexit (a 10-byte `jmp ??1` thunk, because pointgr.cpp declares the
  `VectorClass<Vector3>` destructor without defining it).
- `PointGroupClassRva0017A890.obj` defines a second, static `_VertexLoc` with its own `_$E6`/`_$E7` pair.
  No ledger row names those two funclets.
- `Rva007ABEF3ArgCtorInits.obj` (0x007ACF20) and `Rva007B7280Siblings.obj` (0x007B7400) name pointgr.obj's
  external symbol. Neither function is in a `.CRT$XCU` table, so at run time only the two objects' own
  `_$E` pairs run. The 0x0017A890 body writes through its own copy, which is never resized.

## Route A: one storage by declaration (refused)

The donor compiled with `extern VectorClass<Vector3> VertexLoc;`, or with a non-static definition, in place
of `static`: 12,000 bytes long, 1,897 bytes differ, the first at offset 0. With internal linkage cl hoists
the load `mov eax,[VertexLoc+4]` above `sub esp,0xB8`, as retail does. With external linkage the load stays
after the pushes, in `esi`, and the register allocation of every case changes. The hoist survives address
taking: the donor with an extra `VertexLoc.Resize(n,0)` function before or after the body, or a
`Length()` reader, stays exact. So linkage itself is the cause, not aliasing, type, constness or
initialization. No external spelling reproduces the body, which confirms the 2026-10-20 handoff
(`rva17a890-2026-10-20.md`, session 6).

## Route B: the merge (blocked on the seed's `??_H` anchor)

Probe: pointgr.cpp's text with the forward `extern` dropped, `static VectorClass<Vector3> VertexLoc;`, and the
donor body (`flag01` spelled `BILLBOARD`) inserted before `Rva00912CF0`. The probe was compiled with
`build.compiler_command` into `build/` (never `build/match/`) and scored against retail per symbol with
relocation bytes masked. Seed rows are pointgr.cpp's 65 rows, without `$L` and `__ehhandler`.

The probe copy needs `/O2 /arch:SSE /G7` spelled in its `// cl:` line. pointgr.cpp gets those flags from
`flag_defaults` for its own path only, so a renamed copy compiles x87 (9,136 bytes). That was the first
artefact to rule out.

| variant | 0x0017A890 | `??_H` calls (0x00179B50 / Render / 0x0017A890) | seed rows |
|---|---|---|---|
| retail | 12,000 | 3 / 0 / 4 | - |
| donor alone (landed file) | exact | - / - / 4 | - |
| donor + `bfmeVciAnchor` under `#pragma optimize("gsy")` | 11,772 | - / - / 0 | - |
| donor + the same anchor without the pragma | exact | - / - / 4 | - |
| donor + a `Vector3 anchor[2]` function first | exact | - / - / 4 | - |
| merged, seed as is (gsy anchor) | 11,820, 10,115 differ from 0x07 | 3 / 0 / 0 | all exact |
| merged, anchor function removed | 12,232, 10,319 differ from 0x00 | 6 / 1 / 5 | 0x00179B50 3,836 B, Render 925 B, RenderVolumeParticle 1,269 B; the rest exact |

Finding (target fact plus measurement): the seed's `bfmeVciAnchor` hatch has cl synthesize `??_H` under
"gsy" (/O1-like), small enough to inline. Inlined `??_H` with the force-inline empty `Vector3()`
disappears, so the merged 0x0017A890 builds its arrays inline. cs99 read this as the Vector3 shim
(`vector3_len_link.h` is the same `WWINLINE Vector3(void) {}` as the donor's `vector3.h`; the only
difference is `Length`). Without the anchor, `??_H` is /O2-shaped and stays out of line in 0x0017A890 too.
But 0x00179B50, Render and RenderVolumeParticle then gain `??_H` calls retail does not have,
`DX8Wrapper::Get_Transform` stops inlining, and 0x0017A890 loses the `VertexLoc` load hoist even though it
is static. One TU gives one `??_H`, and neither shape gives retail's 3 / 0 / 4.

Inference (not proven): retail's pointgr.cpp differs from the seed in what reaches `??_H` first and in the
Matrix4/Vector4 views. The seed's file order is not retail's (Render compiles before 0x00179B50), and the
real TU also holds the destructor 0x00178ED0 and `_Init` 0x0017E210 (`PointGroupClassInit.cpp`, which
carries its own gsy anchor). A merge that reproduces retail probably needs the whole approved TU and no
anchor, in retail order.

## What a landing still needs (in order)

1. A merged-context pointgr.cpp whose `??_H` inlining gives 3 / 0 / 4 without the gsy anchor (drop the
   hatch; try retail function order and the Init/destructor donors in the same probe), with all 65 seed rows
   and the 12,000-byte body exact.
2. The canonical `PointGroupClass.h` adopted by the seed (header_queue). `BILLBOARD` vs `flag01`,
   `_Init`/`_Shutdown`, `Update_Arrays`, `friend ::Rva00912CF0`, the 2-argument `RenderVolumeParticle`.
3. VertexLoc static in pointgr.cpp, with 0x007ACF20 and 0x007B7400 rowed as pointgr.obj's own `_$E` pair
   (`object-symbol=_$E<n>`, as the VertexDiffuse/VertexUV rows 0x007ACF40/0x007B7440/0x007ACF60/0x007B7480
   already are). The atexit is 59 bytes only if the `VectorClass<Vector3>` destructor is inline-visible in
   pointgr.cpp, so the decl-only destructor goes. The /O2 `??_G` copy that then appears is already emitted
   today by `Rva007B7280Siblings.obj`; check which copy the link keeps.

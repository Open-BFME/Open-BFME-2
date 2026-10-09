// ?RenderStreak@StreakRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@PAVVector4@@PAMABVSphereClass@@PAI@Z
// partial score=0.4 date=2026-09-14
// CORRECTION 2026-10-09: the historical recipe below confuses VA and RVA.
// Its callback VA 0x0087A6A9 is executable RVA 0x0047A6A9: mov eax,ecx; ret.
// The native iterator at RVA 0x00746CAD constructs four 16-byte elements.
// Do not omit this call or hardcode a callback based on the old rdata claim.
// This file is a historical recipe, not a compilable recovered RenderStreak body.
// Current home TU emits 13399/14026 bytes; transform, VB/FVF ABI and catch
// differences remain. Init at 0x00743190 and UV assignment at 0x00743260
// already have exact owner rows; they are not additional recovery bytes.
// ?RenderStreak@StreakRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@PAVVector4@@PAMABVSphereClass@@PAI@Z
// partial score=0.4 date=2026-09-14
//
// FORK RECIPE for StreakRendererClass::RenderStreak, 0x00743700, 14026B.
// The body in Code/Libraries/Source/WWVegas/WW3D2/streakRender.cpp:332-1435 is
// ~85% verbatim (40/49 REL32 resolve today) but CANNOT land from that TU:
// the ZH dx8wrapper.h/sortingrenderer.h close class DX8Wrapper, and ZH's
// Get_Transform inline emits the wrong shape. Fork to a dedicated TU that
// redeclares DX8Wrapper/SortingRendererClass minimally (precedent:
// dx8wrapper_draw_prim.cpp, DynamicVBAccessClassDeinit.cpp, Cftp*.cpp).
// Copy the // cl: line + // stlport marker + operator delete[] line from
// streakRender.cpp:1-4 verbatim (flags affect codegen: /arch:SSE /G7).
//
// CALLEE MAP (retail targets read from game.dat e8 sites, all verified by
// anchored capstone disasm; * = needs action, rest resolve via ledger/pins):
//   0x74371d -> 0x629000  SEH/except frame setup (resolves)
//   0x743dde -> 0x71CE10  ?Transform@VectorProcessorClass@@SAXPAVVector3@@PBV2@ABVMatrix3D@@H@Z (row 2991, matched)
//   0x743ee0 -> 0x743280  subdivision_util (row 3162, matched, redeclare member)
//   0x74403c x25 -> 0x4233A  Vector3::Dot_Product/Cross_Product family (resolves; do NOT touch)
//   0x7468a3 -> 0x13B040  *VB ctor: ??0BfmeDynamicVBAccess@@QAE@IIGI@Z (row 6091).
//     Retail pushes: 0, ebx=vnum, 5, (2+(sorting!=0)). Use BfmeSortingVBAccess
//     (pins 161/270/304/340 already map that name onto these extents, all
//     pin_consistency green): `BfmeSortingVBAccess Verts(type,5,vnum,0)`.
//   0x7468bc -> 0x13AA00  *VB WriteLock ctor ??0WriteLock@BfmeDynamicVBAccess@@QAE@PAU1@@Z (row 5187)
//     via `BfmeSortingVBAccess::WriteLock Lock(&Verts)` (resolves via pin 270).
//   0x746b4b -> 0x13AB00  *VB WriteLock dtor (row 5188, pin 340).
//   0x746b66 -> 0x139240  ??0DynamicIBAccessClass@@QAE@GG@Z (row 2544). KEEP ZH IB side.
//   0x746b7c -> 0x138CA0  IB WriteLock ctor (row 6111). KEEP.
//   0x746bbe -> 0x138D80  IB WriteLock dtor (row 6112). KEEP.
//   0x746bcc -> 0x11D690  ?Set_Index_Buffer@DX8Wrapper@@SAXABVDynamicIBAccessClass@@G@Z (row 3720). KEEP.
//   0x746bd8 -> 0x11D5C0  *Set_Vertex_Buffer, 1 ptr arg (&Verts @ebp-0x294).
//     Ghidra FUN_0051d5c0 197B, unclaimed. PROVEN: dx8wrapper.cpp:2339 body
//     compiles to 197B matching target through +0x76, differing only in vba
//     field offsets +8 ([esi+0x12]/[edx+0x10]/[esi+0x14] = BfmeSortingVBAccess
//     vertexOffset/vertexCount/buffer). 4-5 image-wide pairings with known
//     Set_Index_Buffer (0xf7cb5/c1, 0xf94c6/d2, 0x101025/2e, ...). ADD PIN:
//     ?Set_Vertex_Buffer@DX8Wrapper@@SAXABVBfmeSortingVBAccess@@@Z,0x0011D5C0
//     (run pin_consistency.py --symbol first; document twin-alias note).
//   0x746be3 -> 0x11F4B0  Set_Texture(0,tex) (resolves; COPY ZH decl
//     Set_Texture(unsigned,TextureBaseClass*) verbatim).
//   0x746c1f -> 0x610B00 / 0x746c31 -> 0x610A40  shader-region thiscalls
//     (resolve today from ZH shader.h decls; COPY those decls, change nothing).
//   0x746c46 -> 0x12FE00  *Insert_Triangles IIII (pin 538 exists). Declare
//     `static void Insert_Triangles(const SphereClass&,unsigned,unsigned,unsigned,unsigned)`
//     in minimal SortingRendererClass. Retail pushes: ebx,0,esi,0,+obj_sphere.
//   0x746c50 -> 0x120620  *Draw_Triangles IIII (pin 467 exists). Declare
//     `static void Draw_Triangles(unsigned,unsigned,unsigned,unsigned)`.
//   0x746c62 -> 0x138BE0  ??1DynamicIBAccessClass@@QAE@XZ (row 2178). KEEP.
//   0x746c74 -> 0x13A780  ??1BoxDynamicVBAccessClass@@QAE@XZ (row 2164) via pin 304
//     (??1BfmeSortingVBAccess@@QAE@XZ). Verts dtor position. No action.
//   0x746cad -> 0x1423    vector_constructor_iterator (pin 393 ??_H) with
//     (ptr=[ebp-0x388], size=16, count=4, ctor=0x0087A6A9 = RDATA STRING TABLE
//     "#include/ERROR: Could not open..."!). Semantics UNKNOWN (a ctor in
//     rdata cannot execute; game works, so treat as opaque). DO NOT EMIT the
//     call; DO reserve the 64B at [ebp-0x388] (frame must total 0x5A84; retail
//     prologue `mov eax,0x5A84`, ours today 0x5A40). The ~15B push/call gap is
//     the accepted known delta. See MYSTERY below.
//
// TAIL ADAPTATIONS (streakRender.cpp:1362-1429):
//   - Verts: BfmeSortingVBAccess as above (literal 5, trailing 0).
//   - Fill loop: REWRITE. Retail reads Verts.format (96B FVF record,
//     pin-161 note) fields at +0xC/+0x10/+0x44/+0x24 (NOT methods), and
//     inlines Convert_Color_Clamp (comiss clamp vs xmm2=[0xBBB8D8]=1.0f,
//     gated by byte [0xE08D2C]). Extract BfmeDynamicFVFPrefix layout from
//     bfmedynamicvertexbuffer.cpp:60-100 + retail bytes 0x7468C1-0x746B4B.
//   - IB section: DROP try/catch + IndexBufferExceptionFunc (retail has ZERO
//     e8 between 0x746B7C and 0x746BBE — proven by raw scan + anchored disasm).
//   - Draws: IIII decls above; `if (sorting) Insert(...) else Draw(...)` shape
//     already matches (retail je 0x746C50).
//   - SetVB: honest Bfme overload decl (fork's DX8Wrapper is yours) + new pin.
//
// GET/SEt_TRANSFORM INLINE BODIES (must inline; retail has no calls):
//   Get_Transform(VIEW,view): `mov eax,[0xDEC4F4]; test eax,0x80000(VIEW_IDENTITY);
//   je load` — flag SET: init [ebp-0x148..0x10C] matrix to identity diagonal
//   from [0xBBB8D8] (scalar movss stores, NOT vectorized); flag CLEAR: load
//   4x16B from globals [0xDEE804..]. Replicate with scalar assignments.
//   Set_Transform(VIEW,view) at exit: saves [ebp-0x148..0x114 decks] to
//   [0xDEE804..] + `mov eax,[0xDEC4F4]` flag dance; read full tail
//   0x746CB2-0x746DCE for exact ops. Global names: copy extern decls from
//   dx8wrapper.cpp (same ledger data symbols).
//
// MYSTERY (blocker for final ~15B): exit-path vector_ctor with rdata "ctor"
//   0x0087A6A9 (string table, NOT code). Verified: anchored disasm from
//   0x746C58, raw file bytes, PE section map (.rdata 0x7BA000, file read
//   corrected for vaddr->raw skew). 0x2FD80/0x2FDE0 hits nearby are FALSE
//   POSITIVES (E8 inside other instructions; capstone-confirmed absent).
//   If the rest converges, either hardcode the documented cast or leave the
//   15B gap in the verdict.
//
// FRAME: retail 0x5A84. Locals: Verts@ebp-0x294(24B), WL@ebp-0x1A0(12B),
//   ib@ebp-0x194, mystery64@ebp-0x388, matrix@ebp-0x148(64B), shader scratch
//   @ebp-0x3C, flag save @ebp-0x2C, sorting @ebp-0xD. Check fork obj offsets.
//
// t=95min model=muse-spark Everett analysis+recipe, no Code/ changes made
// (worktree clean); next: write fork TU, compile, decode_calls, iterate.
void streakRender_fork_recipe_placeholder(void);

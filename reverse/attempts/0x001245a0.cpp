// ?Do_Onetime_Device_Dependent_Inits@DX8Wrapper@@SAXXZ
// partial score=0.27 date=2026-09-09
// cl: (compiled as part of Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp)
//
// ?Do_Onetime_Device_Dependent_Inits@DX8Wrapper@@SAXXZ
// 0x001245A0, 283 bytes. Ours emits 77. This is NOT a near miss -- retail does
// something structurally different -- but every callee is decoded below, so
// the next agent starts from a map rather than a hex dump.
//
// THE FINDING: BFME2 HEAP-ALLOCATES TWO OBJECTS THAT ZERO HOUR MAKES STATIC.
// Retail carries a full SEH frame (push -1 / push handler / fs:[0]) that our
// body has no reason to emit, and inside it are TWO copies of the classic
// `p = operator new(n); if (p) p->ctor();` shape, each with its own unwind
// state stored to [esp+0x24] -- 0 for the first, 1 for the second. That is
// what the frame is for. Zero Hour's TheDX8MeshRenderer is a static instance;
// retail news it.
//
// EVERY REL32 DECODED (offset -> target, and what the ledger already knows):
//
//   0x01e -> 0x001207B0  UNKNOWN   (first call; ours has Compute_Caps here)
//   0x069 -> 0x00039660  UNKNOWN   (MissingTexture::_Init by position)
//   0x075 -> 0x0013EB60  pin       ?_Init_Filters@TextureFilterClass@@SAXW4TextureFilterMode@1@@Z
//   0x07c -> 0x0002FDA0  row       ??2@YAPAXI@Z          <-- operator new #1
//   0x095 -> 0x00145AA0  UNKNOWN   <-- ctor #1, called as `mov ecx,eax / call`
//   0x0ad -> 0x00144530  row       ?Init@DX8MeshRendererClass@@QAEXXZ
//   0x0b8 -> 0x0069E440  row       ?DX8_Assert@@YAXXZ    (where ours has SHD_INIT)
//   0x0bf -> 0x0002FDA0  row       ??2@YAPAXI@Z          <-- operator new #2
//   0x0d8 -> 0x0017414B  UNKNOWN   <-- ctor #2
//   0x0ee -> 0x00174E20  UNKNOWN   \
//   0x0f3 -> 0x0013D9B0  UNKNOWN    | five calls, and our source's tail has
//   0x0f8 -> 0x0017E210  UNKNOWN    | exactly five: BoxRenderObjClass::Init,
//   0x0fd -> 0x00177923  UNKNOWN    | VertexMaterialClass::Init,
//   0x102 -> 0x0013A7D0  UNKNOWN   /  PointGroupClass::_Init,
//   0x107 -> 0x00122510  row       ShatterSystem::Init, TextureLoader::Init
//                                  then ?Set_Default_Global_Render_States@ (matched)
//
// So the TAIL already agrees and only the middle diverges. Since allocation #1
// is immediately followed by DX8MeshRendererClass::Init at 0x00144530 -- a
// name the ledger already holds -- ctor #1 at 0x00145AA0 is almost certainly
// ??0DX8MeshRendererClass@@QAE@XZ. That is an inference from adjacency, NOT a
// proof, and it must be confirmed the usual way (does a unit that emits that
// constructor byte-match at 0x00145AA0?) before any row or pin spends the name.
//
// Allocation #2's result is stored to the global at 0x00DF6F94 and its ctor is
// at 0x0017414B. Nothing in either ledger names either one yet, and there is
// no adjacency argument for it, so it stays UNKNOWN rather than guessed.
//
// WHAT TO DO NEXT, in order:
//   1. Confirm 0x00145AA0 is DX8MeshRendererClass's constructor.
//   2. Change TheDX8MeshRenderer from a static instance to a pointer that this
//      function news, and see whether the SEH frame and the first unwind state
//      appear. A missing frame where retail has one usually means a missing
//      destructible object, and here the object is the allocation itself.
//   3. Identify the class stored at 0x00DF6F94 from its ctor at 0x0017414B --
//      read what that body writes (a vtable store gives the class away).
//   4. Only then re-diff. `py -3 tools/align_diff.py
//      Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp
//      '?Do_Onetime_Device_Dependent_Inits@DX8Wrapper@@SAXXZ' 0x001245A0 283`
//      currently reports 5 structural regions and -206 bytes; regions 3 and 5
//      are small (the DX8_Assert call and the SEH epilogue) and will close on
//      their own once the two allocations are right.
//
// Do NOT "fix" this by adding a try/catch or a dummy destructible local to
// conjure the frame. The frame is a consequence of the two heap allocations;
// producing it by other means would match a byte pattern without recovering
// what the code does.

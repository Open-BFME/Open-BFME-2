# P23 prep: RefCountPtr against retail, for one canonical header

Static-defects lane, 2026-11-07. Read-only. The canonical header waits for Crash triage's RefCountClass
phase 1 (seat2, prototype B) to reach master.

## Why

BaseHeightMapRenderObjClass's +0xD4 is a reference-counted holder, not the canonical header's
`void *field00D4`:
- the constructor 0x0006C9CF nulls it (`mov [esi+0xD4], ebx`);
- its unwind funclets destroy it through 0x0017098D, a release-if-non-null destructor;
- the destructor 0x0006D0D7 releases it inline at its own EH state (`mov ecx,[esi+0xD4]`; if non-null, call
  `Release_Ref` 0x0061ED10).

BaseHeightMap.h already returns `RefCountPtr<TextureClass>` from its texture getters (forward-declared
only). `class_contract.py` records no data members past the vptr, so the type has to be spelled in the
header itself, and that needs a complete canonical `RefCountPtr`. BaseHeightMap.h reaches 45 ledger sources
(`header_dependents.py --staged` on master e20616cbfd).

## Retail's holder bodies

| Body | Retail | Shape |
|---|---|---|
| destructor, out-of-line `Release_Ref` | 0x0017098D, 12 B (about 50 ICF names; first `??1?$RefCountPtr@VTextureClass@@@@QAE@XZ`) | `mov ecx,[ecx]; test; je; jmp Release_Ref`: `if (Referent) Referent->Release_Ref();` as a tail call |
| destructor, inline RefCountClass `Release_Ref` | 0x0007B724, 16 B (`RefCountPtr<CameraClass>`, `<FXShaderSetup>`, `<FXShader::RenderingMethod>`) | `mov ecx,[ecx]; test; je; dec [ecx+4]; jne; mov eax,[ecx]; jmp [eax]`: the same body, Release_Ref inlined (count at +4, Delete_This in slot 0) |
| copy constructor | 0x000424BB, 21 B (pin `??0?$RefCountPtr@VTextureClass@@@@QAE@ABV0@@Z`; rowed as the converting `??$?0VAssetReference@@@...`) | store `rhs.Referent`, then `if (Referent) Referent->Add_Ref();` with Add_Ref inline as `inc word [edx+4]` |
| `operator=(const RefCountPtr &)` | 0x000424D0, 40 B (`??4?$RefCountPtr@VTextureClass@@@@QAEABV0@ABV0@@Z`, RefCountPtrTextureAssign.cpp) | Add_Ref rhs first, Release_Ref the old referent (call 0x0061ED10), then `Referent = rhs.Referent`, return `*this` |
| vector deleting destructor | 0x0004559C, 75 B (`??_E?$RefCountPtr@VTextureClass@@@@QAEPAXI@Z`) | arrays of `RefCountPtr<TextureClass>` exist |

`T`'s own reference counting differs between the two destructors. TextureBaseClass (0x0061ED10) keeps a
16-bit count at +4 and deletes through vtable slot 8 when the 0x1000000 flag is set; its Add_Ref is an inline
`inc word [+4]`. RefCountClass-derived types (0x0007B724) inline `dec [+4]` and call Delete_This through
slot 0. The template does not care: it calls `T::Add_Ref` / `T::Release_Ref`.

## The four candidate definitions

- Zero Hour (`reference/open-bfme-1/.../GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ref_ptr.h`):
  `T *Referent`. Its default constructor nulls; its copy constructor stores, then Add_Refs; its
  `operator=(const RefCountPtr &)` Add_Refs rhs, Releases, assigns; its destructor is
  `if (Referent) Referent->Release_Ref();`. All four match retail's bodies above. It includes always.h and
  wwdebug.h; DummyPtrType and FAIL_IF/G_ASSERT come from those.
- The shim (`reference/shims/bfmestreak/ref_ptr.h`) is Zero Hour's text plus a three-line header comment;
  the code is identical. Its comment says the destructor "omits the dead post-release clear", but Zero
  Hour's destructor has no clear either, so the note is inaccurate rather than a difference.
- `Rva0006ACBDMethod.cpp`: `T *m_ptr`; default constructor nulls; `operator=` declared out of line (retail
  0x000424D0); inline destructor identical to Zero Hour's. A strict subset under another member name.
- `BaseHeightMapScorchResources.cpp`: `T *Referent`; a `__declspec(noinline) RefCountPtr(int kind)`
  constructor (no Zero Hour counterpart by that signature: Zero Hour has the private
  `RefCountPtr(T *, ReferenceHandling)` and `RefCountPtr(DummyPtrType *)`, which needs a look before
  adoption); `operator=` declared; inline destructor identical.

## For the canonical header

- Write it from Zero Hour's template: every body retail shows matches it. Keep `Referent` as the member
  (Zero Hour's name, also the second private copy's), and keep `operator=` and the copy constructor inline:
  retail's 0x000424BB/0x000424D0 are their COMDATs.
- Its only dependency is `T::Add_Ref`/`T::Release_Ref` at instantiation. It does not need refcount.h
  itself, but its users' `T` (TextureClass, RefCountClass types) do, which is why it waits for phase 1.
- Adopting it: `Rva0006ACBDMethod.cpp` renames `m_ptr` -> `Referent` (header_adopt_lane's field renames).
  `BaseHeightMapScorchResources.cpp`'s `RefCountPtr(int)` must be identified first (which retail call it
  stands for), then mapped to Zero Hour's constructor of that shape.
- Then BaseHeightMap.h: `RefCountPtr<TextureClass> field00D4;` (+0xD4), and adopt the header in
  BaseHeightMapConstructor.cpp (the unit's `RefTex vertexScorch` becomes the canonical field). Last, P23's
  table fix on canonical rendobj.h, as P22.

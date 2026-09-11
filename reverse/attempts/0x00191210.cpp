// ?Get_Texture@BFMELineRendererTexture@@QBE?AVTextureHandleClass@ParticleBufferClass@@XZ
// partial score=0.69 date=2026-09-12
// ?Get_Texture@BFMELineRendererTexture@@QBE?AVTextureHandleClass@ParticleBufferClass@@XZ
// cl: (part_buf.cpp's own line) /Ireference/shims/bfmeparticleline ... /arch:SSE /G7 /DNDEBUG /MD
//
// Named by Code/Libraries/Source/WWVegas/WW3D2/part_buf.cpp (BFME_ParticleBuffer_TextureFields
// overlay already casts `lineRenderer` to this class and calls Get_Texture() -- the class stub
// and the mangled name are both already proven there, only the body is missing).
//
// SegLineRendererClass keeps its `TextureClass *Texture;` at offset 0 (see
// reference/shims/bfmeparticleline/seglinerenderer.h); TextureBaseClass::Add_Ref increments a
// WORD at offset+4 (reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/texture.h).
// ParticleBufferClass::TextureHandleClass (part_buf.h, in reference/shims/bfmeparticlehandle/)
// has a trivial one-arg ctor that just stores Ptr -- it does NOT add-ref -- so the add-ref has
// to happen in this function's body, matching retail's conditional `add word [ecx+4],1`.
//
// STUCK ON: instruction order, not semantics or size. This compiles to exactly 29 bytes (same
// as retail) with 20/29 bytes positionally identical (score 0.6897, unresolved=[]), but retail
// stores the pointer into the sret slot (`mov [eax],ecx`) BEFORE the null branch, while every
// C++ phrasing tried here computes the store AFTER the branch merges:
//
//   retail:  push ecx / mov ecx,[ecx] / test ecx,ecx / mov eax,[esp+8] / mov [esp],0 /
//             mov [eax],ecx / je +5 / add word [ecx+4],1 / pop ecx / ret 4
//   this:    ... same prologue ... / je +5 / add word [ecx+4],1 / [merge] mov [eax],ecx /
//             pop ecx / ret 4
//
// Tried and rejected:
//  - Naming a `ParticleBufferClass::TextureHandleClass` local (any shape: constructed then
//    conditionally add-ref'd, or add-ref'd via a separate `TextureClass *tex` so the named
//    local itself is untouched between construction and `return`): every shape balloons to
//    84 bytes because ANY named local of a type with a user-provided destructor makes cl 13.10
//    emit a full SEH frame (push -1 / push handler / mov eax,fs:0 / push eax / mov fs:0,esp)
//    to guarantee its destructor runs on unwind, even under /EHsc-. This matches the codegen
//    lesson "a member with a destructor produces EH frames" -- it applies to plain locals too.
//  - Two separate `return TextureHandleClass(tex);` statements (one under `if (!tex)`, one
//    after the add-ref): compiles to 45 bytes -- two separate store instructions instead of
//    retail's one shared store, plus the extra branch/jmp to reach the shared epilogue.
//  - A ternary folded into the ctor argument (`tex ? (tex->Add_Ref(), tex) : tex`): 37 bytes,
//    same after-the-branch store ordering as the plain if/return shape (just adds a jmp).
//
// What's needed: a single-return, no-named-class-local shape where cl schedules the
// (address-independent, flag-independent) `mov [eax],ecx` store ahead of the `test`/`je` pair.
// Whatever source shape retail's author used, it must still resolve to exactly one ctor call
// and one add-ref call to hit 29 bytes with this ordering; try SEGLINERENDERER'S OWN Get_Texture
// or the previously-landed 0x001790E0 sibling (Code/Libraries/Source/WWVegas/WW3D2/
// bfme2_particle_texture_accessor.cpp) for a struct shape whose OWN constructor does the
// add-ref (`Ptr(p) { if(Ptr) ++Ptr->Refs; }`) instead of doing it in the caller -- that sibling
// is a different, already-matched address/layout, but if the compiler orders that pattern the
// other way it may translate here once TextureHandleClass's real ctor is off the critical path
// (e.g. wrapping it so the add-ref runs inside a helper the ctor argument calls, rather than a
// statement after construction).

class BFMELineRendererTexture
{
public:
	ParticleBufferClass::TextureHandleClass Get_Texture() const;
private:
	TextureClass *Texture;	// offset 0, matches SegLineRendererClass::Texture
};

ParticleBufferClass::TextureHandleClass BFMELineRendererTexture::Get_Texture() const
{
	TextureClass *tex = Texture;
	if (tex) tex->Add_Ref();
	return ParticleBufferClass::TextureHandleClass(tex);
}

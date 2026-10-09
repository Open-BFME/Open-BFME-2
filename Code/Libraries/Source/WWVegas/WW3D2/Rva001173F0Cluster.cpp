// cl: /DNDEBUG /MD /EHsc
//
// ?rva001173f0@@YAXI@Z, retail 0x001173F0, 22 bytes.
//
// Two-singleton helper sitting between WW3D::Set_Texture_Filter (0x00117280)
// and WW3D::Sync (0x00117490) in the ww3d neighbourhood:
//   mov ecx,[0x00DF363C] / call 0x00148030 (DX8MeshRendererClass::Flush)
//   mov ecx,[0x00DF6F94] / jmp  0x00174BA6 (unrowed).
// Native caller104956 passes its opaque render argument and pops it after
// this cdecl call; the parameter is unused here, hence absent from these22B.
// BFME1 ba7ddda7 WW3D::Flush(RenderInfoClass&) corroborates the argument.
// Keep an address-derived name and raw-word type until the receiver identity
// and render-info layout are independently established.
// Both globals already have established spellings elsewhere in this tree:
// TheDX8MeshRenderer (DX8TextureCategoryDtor.cpp) and TheMeshGapFillerContext
// (DX8Wrapper_Do_Onetime_Device_Dependent_Inits.cpp). The tail target has no
// row and no name, so it is pinned address-derived as a method of the class
// the 0xDF6F94 global already carries. Identity of the caller is not proven.

class DX8MeshRendererClass
{
public:
	void Flush();
};

class Rva00DF6F94GapFillerContext
{
public:
	void rva174ba6();
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;            // 0x00DF363C
extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext; // 0x00DF6F94

void rva001173f0(unsigned int renderArgument)
{
	TheDX8MeshRenderer->Flush();
	TheMeshGapFillerContext->rva174ba6();
}

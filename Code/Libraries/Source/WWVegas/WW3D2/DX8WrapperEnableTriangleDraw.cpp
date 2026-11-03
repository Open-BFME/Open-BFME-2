// cl: /DNDEBUG /MD
// DX8Wrapper::_Enable_Triangle_Draw(bool), retail 0x0012D2C0 (10B): the Zero
// Hour dx8wrapper.h inline, out of line -- stores its argument to
// DX8Wrapper::_EnableTriangleDraw (VA 0x00DB5FCD). It sits in the
// int3-padded sortingrenderer.cpp run beside the emitted
// VertexMaterialClass::Get_Lighting copy; no direct caller reaches it.
// upstream: GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
#include "DX8WrapperClass.h"

inline void DX8Wrapper::_Enable_Triangle_Draw(bool enable)
{
	_EnableTriangleDraw = enable;
}

// Keeps the inline's select-any copy emitted here (not retail code).
extern void (*const g_bfmeDX8EnableTriangleDrawAnchor)(bool);
void (*const g_bfmeDX8EnableTriangleDrawAnchor)(bool) = &DX8Wrapper::_Enable_Triangle_Draw;

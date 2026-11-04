// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// platformsdk
// ?Peek_Vertex_Material@MaterialInfoClass@@QBEPAVVertexMaterialClass@@H@Z
// retail 0x000636C9, 22 bytes, size-optimised (/O1).
//
// Bounds-checked Peek using the canonical MaterialInfoClass storage:
// vertex-material count at +0x18, array base at +0x0C.
// Retail callers: 0x0006374E, 0x000CE2A5, 0x0014BE36.

#include <windows.h>

#include "MaterialInfoClass.h"

inline VertexMaterialClass *MaterialInfoClass::Peek_Vertex_Material(int index) const
{
    if (index < field18) {
        return field0c[index];
    }
    return NULL;
}

extern VertexMaterialClass *(MaterialInfoClass::*const g_bfmePeekVertexMaterialAnchor)(int) const;
VertexMaterialClass *(MaterialInfoClass::*const g_bfmePeekVertexMaterialAnchor)(int) const = &MaterialInfoClass::Peek_Vertex_Material;

// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Semantic donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/Libraries/Source/WWVegas/WW3D2/matinfo.cpp and meshmdl.h.
// BFME2's material collector at 0x1703D0 independently reads CurMatDesc +0x94,
// Material +0xA8, MaterialArray +0xE8, and the material's dword refcount +4.
// These accessors are unique full-body placements: 0x1434F0..0x14350B and
// 0x16EB70..0x16EB93, each followed by int3 padding. The descriptor getter
// remains inline so the single-material accessor retains its native loads.
#include "VertexMaterialClass.h"
#include "MeshMatDescClass.h"
#include "MeshModelClass.h"
inline VertexMaterialClass *MeshModelClass::Get_Single_Material(int pass) const
{
    return CurMatDesc->Get_Single_Material(pass);
}
inline bool MeshModelClass::Has_Material_Array(int pass) const
{
    return CurMatDesc->Has_Material_Array(pass);
}

// Emit the inline accessors as foldable copies, like their original headers.
extern VertexMaterialClass *(MeshModelClass::*const MeshModelSingleMaterialAccessor)(int) const = &MeshModelClass::Get_Single_Material;
extern bool (MeshModelClass::*const MeshModelMaterialArrayAccessor)(int) const = &MeshModelClass::Has_Material_Array;

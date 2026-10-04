// cl: /G7 /DNDEBUG /MD
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
class VertexMaterialClass {
public:
    virtual void Delete_This();
    void Add_Ref() { ++References; }
private:
    unsigned int References;
};
class MeshMatDescClass {
    char beforeMaterial[0xA8];
    VertexMaterialClass *Material[4];
    char beforeMaterialArray[0x30];
    void *MaterialArray[4];
public:
    VertexMaterialClass *Get_Single_Material(int pass) const {
        if (Material[pass]) Material[pass]->Add_Ref();
        return Material[pass];
    }
    bool Has_Material_Array(int pass) const { return MaterialArray[pass] != 0; }
};
class MeshModelClass {
    char beforeCurrentDescription[0x94];
    MeshMatDescClass *CurMatDesc;
public:
    VertexMaterialClass *Get_Single_Material(int pass) const;
    bool Has_Material_Array(int pass) const;
};
VertexMaterialClass *MeshModelClass::Get_Single_Material(int pass) const
{
    return CurMatDesc->Get_Single_Material(pass);
}
// ?Has_Material_Array@MeshModelClass@@QBE_NH@Z present-unmatched
bool MeshModelClass::Has_Material_Array(int pass) const
{
    return CurMatDesc->Has_Material_Array(pass);
}

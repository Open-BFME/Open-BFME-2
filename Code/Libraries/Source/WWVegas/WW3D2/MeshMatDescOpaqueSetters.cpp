// cl: /O2 /G7 /DNDEBUG /MD
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// The reader at188AF0 installs these per-pass references at descriptor+B8.
// Its call at188B54 passes a context entry and the current pass. The pointee's
// original type is unknown; its RefCountClass prefix is established by target.
class RefCountClass {
public:
    void Add_Ref() { ++NumRefs; }
    void Release_Ref() { if (--NumRefs == 0) Delete_This(); }
    virtual void Delete_This();
private:
    int NumRefs;
};
class MeshMatDescClass {
    char prefix[0xB8];
    RefCountClass *OpaquePassBuffers[4];
public:
    void Set_Single_Rva0015A800(void *entry, int pass);
};
void MeshMatDescClass::Set_Single_Rva0015A800(void *entry, int pass)
{
    RefCountClass *value = (RefCountClass *)entry;
    if (value) value->Add_Ref();
    if (OpaquePassBuffers[pass]) OpaquePassBuffers[pass]->Release_Ref();
    OpaquePassBuffers[pass] = value;
}

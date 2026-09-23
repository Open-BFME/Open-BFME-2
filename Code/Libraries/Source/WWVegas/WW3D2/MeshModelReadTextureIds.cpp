// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
** BFME1 meshmdlio.cpp texture-ID reader adapted to BFME2 owning handles.
*/
// The texture-stage reader at18B080 calls this bool-returning body at189140.
// Target fields: model PolyCount24/DefMatDesc8C; context pass8C/stage90 and
// alternate descriptor124. Texture slots78 and arraysC8 select the descriptor.
class TextureClass {
public:
    void Add_Ref() { ++RefCount; }
    void Release_Ref();
private:
    unsigned char Prefix[4];
    unsigned short RefCount;
};
class BfmeHandleCX {
public:
    TextureClass *p;
    BfmeHandleCX() : p(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : p(other.p) { if (p) p->Add_Ref(); }
    ~BfmeHandleCX() { if (p) p->Release_Ref(); }
};
class ChunkLoadClass {
public:
    unsigned long Cur_Chunk_Length();
    unsigned long Read(void *data, unsigned long size);
};
class MeshMatDescClass {
private:
    unsigned char prefix[0x78];
public:
    TextureClass *Textures[4][2];
    char between[0x30];
    void *TextureArrays[4][2];
    unsigned char remaining[0x30];
    bool Has_Texture_Data(int pass, int stage) const {
        return Textures[pass][stage] != 0 || TextureArrays[pass][stage] != 0;
    }
    void Set_Single_Texture(const BfmeHandleCX &, int, int);
    void Set_Texture(int, const BfmeHandleCX &, int, int);
};
class MeshLoadContextClass {
private:
    unsigned char prefix[0x8c];
public:
    int CurPass;
    int CurTexStage;
    char before_desc[0x90];
    MeshMatDescClass AlternateMatDesc;
private:
    friend class MeshModelClass;
    BfmeHandleCX Peek_Texture(int index);
};
class MeshModelClass {
private:
    char prefix[0x24];
public:
    int PolyCount;
private:
    char before_desc[0x64];
public:
    MeshMatDescClass *DefMatDesc;
    int Get_Polygon_Count() const { return PolyCount; }
protected:
    bool read_texture_ids(ChunkLoadClass &cload, MeshLoadContextClass *context);
};
bool MeshModelClass::read_texture_ids(ChunkLoadClass &cload, MeshLoadContextClass *context) {
    unsigned int texid;
    int pass = context->CurPass;
    int stage = context->CurTexStage;
    // Determine whether this chunk belongs to the default or alternate material description.
    MeshMatDescClass *matdesc = DefMatDesc;
    if (DefMatDesc->Has_Texture_Data(pass, stage)) {
        matdesc = &context->AlternateMatDesc;
    }
    // Read in the texture(s) array.
    if (cload.Cur_Chunk_Length() == sizeof(unsigned int)) {
        cload.Read(&texid, sizeof(texid));
        matdesc->Set_Single_Texture(context->Peek_Texture(texid), pass, stage);
    } else {
        for (int i = 0; i < Get_Polygon_Count(); ++i) {
            cload.Read(&texid, sizeof(unsigned int));
            if (texid != 0xffffffff) {
                matdesc->Set_Texture(i, context->Peek_Texture(texid), pass, stage);
            }
        }
    }
    return true;
}


typedef char MaterialDescriptorSize118[(sizeof(MeshMatDescClass) == 0x118) ? 1 : -1];

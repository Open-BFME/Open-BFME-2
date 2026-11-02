// Target facts: constructors RVA 0x001708D0/0x0016FFD0 store count +4 = 1 and primary vtable VA 0x00BD46B8; destructor RVA 0x00170130 restores it at 0x0017014E and RefCountClass's VA 0x00BC650C at 0x001701CC. The primary table has two slots: inherited Delete_This RVA 0x0006CE57 and deleting destructor RVA 0x00170960, which calls 0x00170130. RefCountClass is the eight-byte base; there are no additional virtual slots. Allocation RVA 0x001701F7 requests 0x38 before copy construction at 0x00170216, and the constructors write through +0x34, establishing sizeof 0x38.
// Target facts: vector subobjects start at +8 and +0x20, with constructor tables VA 0x00BD4658/0x00BD4688 and destructor base tables VA 0x00BD4628/0x00BD4640. Constructor stores RVA 0x00170903..0x0017091D prove pointer +0x0C, int +0x10, bools +0x14/+0x15, int count +0x18 and growth +0x1C; the call at 0x0017092B constructs +0x20 through RVA 0x0016ED80, whose stores at 0x0016EDA9..0x0016EDB3 prove pointer +0x24, int capacity +0x28 and bools +0x2C/+0x2D. Stores at 0x00170934/0x0017093D initialize count +0x30 and growth +0x34. Destructor RVA 0x00170161..0x001701C9 confirms the pointer, allocation flag and capacity. Peek_Texture RVA 0x00135F35 and Replace_Texture RVA 0x00135F56 prove four-byte RefCountPtr<TextureClass> elements at +0x24. The vector storage below exposes neutral fields without defining new vector identities.
// Target facts: out-of-line ledger methods are the two constructors, destructor, Free RVA 0x0016EE70, Reset 0x001716B0, Add_Texture 0x0016FBF0 (void* signature), Add_Vertex_Material 0x00189670, Get_Texture_Index 0x0016FC10, Get_Vertex_Material 0x000B49A8, const Peek_Vertex_Material 0x000636C9, Reset_Texture_Mappers 0x00184010 and Has_Time_Variant_Texture_Mappers 0x00184060. Zero Hour GeneralsMD WW3D2/matinfo.h proves Vertex_Material_Count and Texture_Count; retail accesses at RVA 0x0016EE77 and 0x0016FBF5 corroborate their count offsets. Constructors, destructor and these rowed methods are declared out of line.

#ifndef BFME2_WW3D2_MATERIALINFOCLASS_H
#define BFME2_WW3D2_MATERIALINFOCLASS_H

#include "../WWLib/RefCountData.h"

class TextureClass;
class VertexMaterialClass;
template<class T> class RefCountPtr;

class MaterialInfoClass : public RefCountClass
{
public:
    MaterialInfoClass();
    MaterialInfoClass(const MaterialInfoClass &src);
    virtual ~MaterialInfoClass();

    void Reset();
    int Vertex_Material_Count() const { return field18; }
    int Texture_Count() const { return field30; }
    int Add_Vertex_Material(VertexMaterialClass *material);
    void *Add_Texture(void *texture);
    int Get_Texture_Index(const char *name);
    VertexMaterialClass *Get_Vertex_Material(int index);
    VertexMaterialClass *Peek_Vertex_Material(int index) const;
    RefCountPtr<TextureClass> Peek_Texture(int index);
    void Replace_Texture(int index, const RefCountPtr<TextureClass> &texture);
    void Reset_Texture_Mappers();
    bool Has_Time_Variant_Texture_Mappers();

private:
    void Free();

public:
    void *field08;
    VertexMaterialClass **field0c;
    int field10;
    bool field14;
    bool field15;
    unsigned char pad16[2];
    int field18;
    int field1c;
    void *field20;
    RefCountPtr<TextureClass> *field24;
    int field28;
    bool field2c;
    bool field2d;
    unsigned char pad2e[2];
    int field30;
    int field34;
};

#endif

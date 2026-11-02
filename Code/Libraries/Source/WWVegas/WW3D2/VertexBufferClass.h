// Target facts: constructor RVA 0x00139350 (ledger BfmeDynamicVBBase) initializes RefCountClass's int +4 to 1, installs VA 0x00BD2F40, and writes unsigned +8, ushort +0xC, int +0x10, pointer +0x14 and byte +0x18. Destructor RVA 0x00139410 restores 0x00BD2F40 at RVA 0x00139427, then the RefCountClass table 0x00BC650C at RVA 0x00139442. The parent constructor/destructor RVAs 0x00072882/0x00072892 establish its eight-byte prefix.
// Target facts: VA 0x00BD2F40 has slot 0 = RVA 0x0006CE57 (Delete_This) and slot 1 = RVA 0x0013ABC0 (deleting destructor); sorting/native constructors RVAs 0x00139660/0x0013AC00 install the next tables at VA 0x00BD2F48/0x00BD2F50 and place their pointer at +0x1C, establishing this base's sizeof 0x1C. RVAs 0x00139480/0x00139490 update int +0x10. Lock RVAs 0x001394A0/0x001395B0 store buffer +0 and data +4; destructor RVA 0x00139530 releases the buffer and mutex. Caller RVA 0x000D9A5D establishes 12-byte lock storage, including the opaque mutex tail at +8.
// Donor facts: Zero Hour WW3D2/dx8vertexbuffer.h proves type, VertexCount, engine_refs, fvf_info, the accessor/statistics names and Get_Vertex_Array. Its eight-byte lock prefix grows by the retail mutex tail; its empty W3DMPO base adds no target storage. The retail-only byte +0x18 retains a neutral name. Retail's constructor, destructor and lock bodies remain out of line.

#ifndef BFME2_WW3D2_VERTEXBUFFERCLASS_H
#define BFME2_WW3D2_VERTEXBUFFERCLASS_H

#include "../WWLib/RefCountData.h"

class FVFInfoClass;

class VertexBufferClass : public RefCountClass
{
protected:
    VertexBufferClass(unsigned type, unsigned FVF, unsigned short VertexCount, unsigned vertex_size = 0);
    virtual ~VertexBufferClass();

public:
    const FVFInfoClass &FVF_Info() const { return *fvf_info; }
    unsigned short Get_Vertex_Count() const { return VertexCount; }
    unsigned Type() const { return type; }
    unsigned Engine_Refs() const { return engine_refs; }
    void Add_Engine_Ref() const;
    void Release_Engine_Ref() const;

    static unsigned Get_Total_Buffer_Count();
    static unsigned Get_Total_Allocated_Vertices();
    static unsigned Get_Total_Allocated_Memory();

    class WriteLockClass
    {
    public:
        WriteLockClass(VertexBufferClass *vertex_buffer, int flags = 0);
        ~WriteLockClass();
        void *Get_Vertex_Array() { return Vertices; }

        VertexBufferClass *VertexBuffer;
        void *Vertices;
        unsigned char field08[4];
    };

    class AppendLockClass
    {
    public:
        AppendLockClass(VertexBufferClass *vertex_buffer, unsigned start_index, unsigned index_range, int flags = 0);
        ~AppendLockClass();
        void *Get_Vertex_Array() { return Vertices; }

        VertexBufferClass *VertexBuffer;
        void *Vertices;
        unsigned char field08[4];
    };

    unsigned type;
    unsigned short VertexCount;
    mutable int engine_refs;
    FVFInfoClass *fvf_info;
    bool field18;
};

#endif

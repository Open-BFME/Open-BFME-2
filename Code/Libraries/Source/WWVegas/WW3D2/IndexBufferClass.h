// Target facts: ctor RVA 0x001386C0 stores VA 0x00BD2EEC at +0, NumRefs = 1 at +4, engine_refs = 0 at +8, a 32-bit index_count at +0x0C and type at +0x10. DX8/Sorting ctors RVAs 0x00138980/0x00138B20 place their sole pointer at +0x14; Sorting allocation RVA 0x00138FCA requests 0x18 bytes, bounding the base layout to 0x14. Zero Hour WW3D2/dx8indexbuffer.h proves these member and accessor names; its empty W3DMPO contributes no storage and is omitted.
// Target facts: VA 0x00BD2EEC has two virtual slots, RVA 0x0006CE57 (inherited Delete_This) and RVA 0x001390A0 (protected deleting destructor, calls ~IndexBufferClass at RVA 0x00138710). The next table starts at VA 0x00BD2EF4. The destructor's final store at RVA 0x00138730 restores the RefCountClass table VA 0x00BC650C; this is base teardown, not an IndexBufferClass table conflict. RefCountClass ctor/dtor RVAs 0x00072882/0x00072892 prove its eight-byte primary base and the same two-slot order.
// Target facts: Add_Engine_Ref/Release_Engine_Ref RVAs 0x00138770/0x00138780 modify dword +8; WriteLock ctor RVA 0x00138790 reads dword count +0x0C and type +0x10. WriteLock/AppendLock ctors RVAs 0x00138790/0x001388C0 store the buffer at +0 and indices at +4; Copy RVAs 0x001390C0/0x00139160 reserve 12-byte locks. The remaining four bytes are opaque guard storage; ctor/dtor calls reach mutex RVAs 0x0011F520/0x00120F50. AppendLock returns RET 0x10 (four arguments); both lock destructor names resolve to RVA 0x00138840. Counter accessors RVAs 0x00138740/0x00138750/0x00138760 read totals; Copy overloads and all rowed special members remain out of line.

#ifndef BFME2_WW3D2_INDEXBUFFERCLASS_H
#define BFME2_WW3D2_INDEXBUFFERCLASS_H

#include "../WWLib/RefCountData.h"

class IndexBufferClass : public RefCountClass
{
protected:
    virtual ~IndexBufferClass();

public:
    IndexBufferClass(unsigned type, unsigned index_count);

    void Copy(unsigned int *indices, unsigned start_index, unsigned index_count);
    void Copy(unsigned short *indices, unsigned start_index, unsigned index_count);

    unsigned Get_Index_Count() const { return index_count; }
    unsigned Type() const { return type; }
    unsigned Engine_Refs() const { return engine_refs; }
    void Add_Engine_Ref() const;
    void Release_Engine_Ref() const;

    class WriteLockClass
    {
    public:
        WriteLockClass(IndexBufferClass *index_buffer, int flags = 0);
        ~WriteLockClass();
        unsigned short *Get_Index_Array() { return indices; }

        IndexBufferClass *index_buffer;
        unsigned short *indices;
        unsigned char slot08[4];
    };

    class AppendLockClass
    {
    public:
        AppendLockClass(IndexBufferClass *index_buffer, unsigned start_index, unsigned index_range, int flags = 0);
        ~AppendLockClass();
        unsigned short *Get_Index_Array() { return indices; }

        IndexBufferClass *index_buffer;
        unsigned short *indices;
        unsigned char slot08[4];
    };

    static unsigned Get_Total_Buffer_Count();
    static unsigned Get_Total_Allocated_Indices();
    static unsigned Get_Total_Allocated_Memory();

    mutable int engine_refs;
    unsigned index_count;
    unsigned type;
};

#endif

// Target facts: ctor RVA 0x00138980 stores NumRefs = 1 at +4, engine_refs = 0 at +8, a 32-bit index_count at +0x0C, type = 0 at +0x10 and vptr VA 0x00BD2EF4 at +0 (store RVA 0x001389D7). IndexBufferClass ctor RVA 0x001386C0 establishes the same prefix with its own table VA 0x00BD2EEC; the registered parent occupies 0x14 bytes. Allocation RVA 0x00138E84 requests 0x18 bytes and calls the DX8 ctor at RVA 0x00138EA9. The member address passed at RVA 0x00138A33 is +0x14, and dtor RVA 0x00138AD2 reads that pointer before Release through slot +8.
// Target facts: VA 0x00BD2EF4 contains two virtual slots: inherited Delete_This at RVA 0x0006CE57 and the public deleting destructor at RVA 0x00139200, which calls the rowed complete destructor RVA 0x00138AA0. The next table begins at VA 0x00BD2EFC. The complete destructor restores the DX8 table at RVA 0x00138ABF and the RefCountClass table VA 0x00BC650C at RVA 0x00138B09 after the inlined IndexBufferClass teardown. The latter is base teardown, not a competing DX8 table; no virtual slot is added beyond the parent's two.
// Target and donor facts: ctor RVAs 0x001389E8, 0x001389F2 and 0x00138A05 mask usage bits 1, 4 and 2; RVA 0x00138A42 invokes the D3D9 CreateIndexBuffer slot +0x6C with a shared-handle argument. Zero Hour WW3D2/dx8indexbuffer.h supplies UsageType, its enumerator names, index_buffer and Get_DX8_Index_Buffer; IDirect3DIndexBuffer8 is that donor's interface spelling, not a claim that retail uses D3D8. The unsigned-count ctor and virtual destructor stay out of line under their ledger names; Copy and reference operations are inherited from the registered parent.

#ifndef BFME2_WW3D2_DX8INDEXBUFFERCLASS_H
#define BFME2_WW3D2_DX8INDEXBUFFERCLASS_H

#include "IndexBufferClass.h"

struct IDirect3DIndexBuffer8;

class DX8IndexBufferClass : public IndexBufferClass
{
public:
    enum UsageType
    {
        USAGE_DEFAULT = 0,
        USAGE_DYNAMIC = 1,
        USAGE_SOFTWAREPROCESSING = 2,
        USAGE_NPATCHES = 4
    };

    DX8IndexBufferClass(unsigned index_count, UsageType usage = USAGE_DEFAULT);
    virtual ~DX8IndexBufferClass();

    IDirect3DIndexBuffer8 *Get_DX8_Index_Buffer() { return index_buffer; }

    IDirect3DIndexBuffer8 *index_buffer;
};

#endif

// cl: /MD
//
// ?clear@Rva000A8C9B@@QAEXXZ, RVA 0x000A8C9B, 19 bytes.
// Opaque single-holder clear: releases the OpaqueRefCounted referent at +0
// via rowed ?Release_Ref@OpaqueRefCounted@@QAEXXZ (0x00050ED3) then nulls it.
// Evidence: callers release OpaqueRefElement4 members (e.g. 0x0023DD34/0x0023DD3F
// on [esi+0x88]/[esi+0x8c] after ??4OpaqueRefElement4 assignment); tail-jmp
// target of FUN_004cbf9a (lea ecx [esi+0x18]; jmp); /O1 for and-zero holder.

class OpaqueRefCounted
{
public:
    void Release_Ref();
};

struct Rva000A8C9B
{
    OpaqueRefCounted *m_ptr;
    void clear();
};

void Rva000A8C9B::clear()
{
    if (m_ptr)
    {
        m_ptr->Release_Ref();
        m_ptr = 0;
    }
}

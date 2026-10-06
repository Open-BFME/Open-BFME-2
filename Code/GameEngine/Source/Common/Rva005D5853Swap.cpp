// cl: /MD
// ?Rva005D5853Swap@@YAXPAURva005D5853@@0@Z @0x005D5853 35B.
// Swap of 8-byte outer (ptr at +0 plus bool at +4 with padding) via tmp struct copy plus member assigns.
// Same layout as banked Rva005D5AB3 partial (ptr plus bool). Callers are sort partition 0x005D5D61 and 0x005D58C4.
struct Rva005D5853 {
    void *m_ptr;
    bool m_flag;
};
void Rva005D5853Swap(Rva005D5853 *a, Rva005D5853 *b)
{
    Rva005D5853 tmp = *a;
    a->m_ptr = b->m_ptr;
    a->m_flag = b->m_flag;
    b->m_ptr = tmp.m_ptr;
    b->m_flag = tmp.m_flag;
}

// ?Rva005D5876CopyBackward@@YAPAURva005D5853@@PAU1@00@Z @0x005D5876 50B.
// copy_backward for 8-byte ptr+bool entries via assignment. Evidence: caller 0x005D58DC; neighbours share /O1 /MD.
Rva005D5853 *Rva005D5876CopyBackward(Rva005D5853 *first, Rva005D5853 *last, Rva005D5853 *dest)
{
    int n = last - first;
    if (n > 0) {
        int i = n;
        do {
            --last;
            --dest;
            dest->m_ptr = last->m_ptr;
            dest->m_flag = last->m_flag;
        } while (--i != 0);
        return dest;
    }
    return dest;
}

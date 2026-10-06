// cl: /MD
// ??4Rva000A8CAE@@QAEAAV0@ABV0@@Z @0x000A8CAE 27B unlock.
// Copy assignment for opaque holder plus int: OpaqueRefElement4 at +0 via
// rowed ??4OpaqueRefElement4@@QAEAAU0@ABU0@@Z then int at +4, return *this.
// Evidence: push esi push edi mov edi [esp+0xc] push edi call 0x00239099
// mov eax [edi+4] mov [esi+4] eax pop edi mov eax esi ret 4; callers at
// 0x00062260 and 0x001D9BBD.
struct OpaqueRefElement4
{
    struct OpaqueRefCounted *m_ptr;
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

class Rva000A8CAE
{
public:
    Rva000A8CAE &operator=(const Rva000A8CAE &other);
private:
    OpaqueRefElement4 m_ref;
    int m_4;
};

Rva000A8CAE &Rva000A8CAE::operator=(const Rva000A8CAE &other)
{
    m_ref = other.m_ref;
    m_4 = other.m_4;
    return *this;
}

Rva000A8CAE *__cdecl Rva001D9BA4Copy(Rva000A8CAE *first, Rva000A8CAE *last, Rva000A8CAE *dest)
{
    int n = last - first;
    if (n <= 0)
        return dest;
    for (int i = n; i != 0; --i) {
        *dest = *first;
        ++first;
        ++dest;
    }
    return dest;
}

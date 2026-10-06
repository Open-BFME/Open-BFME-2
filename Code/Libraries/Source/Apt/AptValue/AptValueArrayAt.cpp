// cl: /MD
// ?rva006D8A50@BfmeAptValue006DCD20@@QAEPAV1@H@Z @0x006D8A50 (121 bytes).
// Array element access asserting nIndex < mnLength at _Apt.h:0x110 then
// nIndex < mnCapacity at _Apt.h:0x111 via the shared Apt assert pointer at
// 0x00A17734 and break flag at 0x009DC01C, returning m_data[nIndex].
// Layout (m_data at +0x20, mnCapacity at +0x24, mnLength at +0x28) and the
// array-value role are read from retail and callers: 0x006D94A0 loops over
// +0x28 calling this per index, 0x006D9B50 accesses +0x20/+0x28 after the
// rowed isArray checked cast, 0x006D9660 consumes the returned AptValue*.
// __asm int 3 is a proven blocker: the __debugbreak() intrinsic misplaces
// the second int3 between the pops (see AptValueCheckedCastsBFME2.cpp).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class BfmeAptValue006DCD20
{
    virtual void slot0();
    virtual void slot1();
public:
    unsigned int m_flags;
    char m_pad[0x18];
    BfmeAptValue006DCD20 **m_data;
    int mnCapacity;
    int mnLength;
public:
    int isArray() const;
    BfmeAptValue006DCD20 *rva006DCFA0();
    BfmeAptValue006DCD20 *rva006D8A50(int nIndex);
    void rva006D8AD0(int nIndex, BfmeAptValue006DCD20 *pNewValue);
};
extern BfmeAptValue006DCD20 *g_aptUndefinedAtE18078; // 0x00A18078
// g_aptUndefinedAtE18078: VA 0xe18078 (zero-filled .bss).
BfmeAptValue006DCD20 * g_aptUndefinedAtE18078;
BfmeAptValue006DCD20 *BfmeAptValue006DCD20::rva006D8A50(int nIndex)
{
    if (!(nIndex < mnLength)) {
        g_bfmeAptAssertAtE17734("nIndex < mnLength", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x110);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    if (!(nIndex < mnCapacity)) {
        g_bfmeAptAssertAtE17734("nIndex < mnCapacity", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x111);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return m_data[nIndex];
}
// ?Rva006D9B50Pop@@YAPAVBfmeAptValue006DCD20@@PAV1@@Z @0x006D9B50 (92 bytes).
// Array pop: returns undefined at 0x00A18078 when not isArray or empty,
// else At(last) (rowed 0x006D8A50) with undefined fallback for null/out of
// bounds, then decrements mnLength and nulls the freed slot. Callers: none
// yet (chain from 0x006D8A50); callees isArray at 0x006DC3A0, cast at
// 0x006DCFA0 and At are all rowed. Out-of-bounds and null-At share the
// global reload (not the edi local) to match retail's mov eax,[global].
BfmeAptValue006DCD20 *__cdecl Rva006D9B50Pop(BfmeAptValue006DCD20 *pValue)
{
    BfmeAptValue006DCD20 *undefined = g_aptUndefinedAtE18078;
    if (static_cast<unsigned char>(pValue->isArray())) {
        BfmeAptValue006DCD20 *arr = pValue->rva006DCFA0();
        int len = arr->mnLength;
        if (len > 0) {
            int last = len - 1;
            BfmeAptValue006DCD20 *value;
            if (last < 0 || last >= len)
                value = g_aptUndefinedAtE18078;
            else {
                value = arr->rva006D8A50(last);
                if (!value)
                    value = g_aptUndefinedAtE18078;
            }
            int newLen = arr->mnLength;
            BfmeAptValue006DCD20 **data = arr->m_data;
            --newLen;
            arr->mnLength = newLen;
            data[newLen] = 0;
            return value;
        }
    }
    return undefined;
}
// ?rva006D8AD0@BfmeAptValue006DCD20@@QAEXHPAV1@@Z @0x006D8AD0 (140 bytes).
// Array set: asserts pNewValue != NULL at _Apt.h:0x117 then nIndex <
// mnCapacity at _Apt.h:0x118 via the shared Apt assert pointer at
// 0x00A17734 and break flag at 0x009DC01C, AddRefs the new value through
// vtable slot0, Releases the old element through slot+4, then stores.
// Layout (m_data at +0x20, mnCapacity at +0x24) matches 0x006D8A50 in this
// TU; callers 0x006D9625 0x006D98E7 0x006D9C2A 0x006DA347 0x006DA537 pass
// (index, value) with ecx=this.
void BfmeAptValue006DCD20::rva006D8AD0(int nIndex, BfmeAptValue006DCD20 *pNewValue)
{
    if (!pNewValue) {
        g_bfmeAptAssertAtE17734("pNewValue != NULL", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x117);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    if (!(nIndex < mnCapacity)) {
        g_bfmeAptAssertAtE17734("nIndex < mnCapacity", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_Apt.h", 0x118);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    BfmeAptValue006DCD20 *old = m_data[nIndex];
    pNewValue->slot0();
    if (old)
        old->slot1();
    m_data[nIndex] = pNewValue;
}

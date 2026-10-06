// cl: /O2 /MD
// ?rva006E47C0@Rva006E34D0@@QAEXXZ @0x006E47C0 702B
// Apt GC mark pass over the main interpreter object: marks the two rooted
// AptValues at +0x6c/+0x9c, the flat array at +0, the 0x1c-stride array at
// +0x14, the four word-counted arrays at +0xc/+0x1c/+0x24/+0x2c, then the
// display-list mark at +0x30, the action-pool drain at +0xa0 and the 0x20-
// stride table at +0x34 whose +0x14 stack is an AptValuePtrStack drained via
// At() (assert m_nElements-nPos>0 at _AptValuePtrStack.h:0x89).
// Evidence: leaf lane, caller 0x006CD330, pin Rva006E34D0, callees rowed
// get 0x006DBB40 setGCMark 0x006DBC50 slot-0x34 rva006E39A0 rva006F6D30,
// layout read from retail offsets.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006DBB40ShrAndField
{
public:
    bool get() const;
};

class AptValue
{
public:
    virtual void unused0();
    virtual void unused1();
    virtual void unused2();
    virtual void unused3();
    virtual void unused4();
    virtual void unused5();
    virtual void unused6();
    virtual void unused7();
    virtual void unused8();
    virtual void unused9();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
public:
    virtual void unused13();
    void setGCMark(bool value);
};

class Rva006F6D30
{
public:
    void rva006F6D30(void *arg);
};

class Rva006E3230
{
public:
    void rva006E39A0();
};

class AptValuePtrStack
{
public:
    int m_nElements;
    int m_nCapacity;
    AptValue **m_aElements;
    AptValue *At(int nPos)
    {
        if (!(m_nElements - nPos > 0)) {
            g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x89);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        return m_aElements[m_nElements - nPos - 1];
    }
};

struct Entry1C
{
    AptValue *m_pValue;
    char _pad04[0x1c - 4];
};

struct Entry20
{
    void *m_pField0;
    AptValue *m_pValue;
    char _pad08[0x14 - 0x08];
    AptValuePtrStack m_stack;
};

class Rva006E34D0
{
public:
    void rva006E47C0();
private:
    AptValue **m_pArray0;
    int m_nCount0;
    char _pad08[2];
    unsigned short m_nCountC;
    AptValue **m_pArrayC;
    int m_nCount10;
    Entry1C *m_pArray14;
    char _pad18[2];
    unsigned short m_nCount1C;
    AptValue **m_pArray1C;
    char _pad20[2];
    unsigned short m_nCount24;
    AptValue **m_pArray24;
    char _pad28[2];
    unsigned short m_nCount2C;
    AptValue **m_pArray2C;
    Rva006F6D30 *m_pDisp;
    Entry20 *m_pArray34;
    char _pad38[0x6c - 0x38];
    AptValue *m_pValue6C;
    char _pad70[0x9c - 0x70];
    AptValue *m_pValue9C;
    Rva006E3230 *m_pActionPool;
    char _padA4[4];
    int m_nCountA8;
};

void Rva006E34D0::rva006E47C0()
{
    if (m_pValue6C != 0) {
        if (!((const Rva006DBB40ShrAndField *)m_pValue6C)->get()) {
            m_pValue6C->setGCMark(true);
            m_pValue6C->unused13();
        }
    }
    if (m_pValue9C != 0) {
        if (!((const Rva006DBB40ShrAndField *)m_pValue9C)->get()) {
            m_pValue9C->setGCMark(true);
            m_pValue9C->unused13();
        }
    }
    for (int i = 0; i < m_nCount0; ++i) {
        if (!((const Rva006DBB40ShrAndField *)m_pArray0[i])->get()) {
            m_pArray0[i]->setGCMark(true);
            m_pArray0[i]->unused13();
        }
    }
    for (int i = 0; i < m_nCount10; ++i) {
        if (!((const Rva006DBB40ShrAndField *)m_pArray14[i].m_pValue)->get()) {
            m_pArray14[i].m_pValue->setGCMark(true);
            m_pArray14[i].m_pValue->unused13();
        }
    }
    {
        int nC = m_nCountC;
        for (int i = 0; i < nC; ++i) {
            if (m_pArrayC[i] != 0) {
                if (!((const Rva006DBB40ShrAndField *)m_pArrayC[i])->get()) {
                    m_pArrayC[i]->setGCMark(true);
                    m_pArrayC[i]->unused13();
                }
            }
        }
    }
    {
        int nC = m_nCount1C;
        for (int i = 0; i < nC; ++i) {
            if (m_pArray1C[i] != 0) {
                if (!((const Rva006DBB40ShrAndField *)m_pArray1C[i])->get()) {
                    m_pArray1C[i]->setGCMark(true);
                    m_pArray1C[i]->unused13();
                }
            }
        }
    }
    {
        int nC = m_nCount24;
        for (int i = 0; i < nC; ++i) {
            if (m_pArray24[i] != 0) {
                if (!((const Rva006DBB40ShrAndField *)m_pArray24[i])->get()) {
                    m_pArray24[i]->setGCMark(true);
                    m_pArray24[i]->unused13();
                }
            }
        }
    }
    {
        int nC = m_nCount2C;
        for (int i = 0; i < nC; ++i) {
            if (m_pArray2C[i] != 0) {
                if (!((const Rva006DBB40ShrAndField *)m_pArray2C[i])->get()) {
                    m_pArray2C[i]->setGCMark(true);
                    m_pArray2C[i]->unused13();
                }
            }
        }
    }
    if (m_pDisp != 0) {
        m_pDisp->rva006F6D30(0);
    }
    m_pActionPool->rva006E39A0();
    for (int i = 0; i < m_nCountA8; ++i) {
        if (m_pArray34[i].m_pField0 == 0)
            continue;
        if (!((const Rva006DBB40ShrAndField *)m_pArray34[i].m_pValue)->get()) {
            m_pArray34[i].m_pValue->setGCMark(true);
            m_pArray34[i].m_pValue->unused13();
        }
        {
            int nInner = m_pArray34[i].m_stack.m_nElements;
            for (int j = 0; j < nInner; ++j) {
                AptValue *v = m_pArray34[i].m_stack.At(j);
                if (!((const Rva006DBB40ShrAndField *)v)->get()) {
                    v->setGCMark(true);
                    v->unused13();
                }
            }
        }
    }
}

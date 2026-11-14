// cl: /O2 /MD
// ?rva006E47C0@Rva006E34D0@@QAEXXZ @0x006E47C0 702B
// Apt GC mark pass over the main interpreter object: marks the two rooted
// AptValues at +0x6c/+0x9c, the flat array at +0, the 0x1c-stride array at
// +0x14, the four word-counted arrays at +0xc/+0x1c/+0x24/+0x2c, then the
// display-list mark at +0x30, the action-pool drain at +0xa0 and the 0x20-
// stride table at +0x34 whose +0x14 stack is an AptValuePtrStack drained via
// At() (assert m_nElements-nPos>0 at _AptValuePtrStack.h:0x89).
// Evidence: leaf lane, caller 0x006CD330, pin Rva006E34D0, callees rowed
// get 0x006DBB40 setGCMark 0x006DBC50 slot-0x34 rva006E39A0 DisplayListItem,
// layout read from retail offsets.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#include "../../../GameEngine/Include/Common/Rva006DBB40ShrAndField.h"

#include "AptValue.h"

#include "AptDisplayListState.h"

#include "AptActionQueueC.h"

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

#include "Rva006E34D0.h"

void Rva006E34D0::rva006E47C0()
{
    if (m_field6C != 0) {
        if (!((const Rva006DBB40ShrAndField *)m_field6C)->get()) {
            m_field6C->setGCMark(true);
            m_field6C->RegisterReferences();
        }
    }
    if (m_field9C != 0) {
        if (!((const Rva006DBB40ShrAndField *)m_field9C)->get()) {
            m_field9C->setGCMark(true);
            m_field9C->RegisterReferences();
        }
    }
    for (int i = 0; i < m_field04; ++i) {
        if (!((const Rva006DBB40ShrAndField *)((AptValue *)m_field00[i]))->get()) {
            ((AptValue *)m_field00[i])->setGCMark(true);
            ((AptValue *)m_field00[i])->RegisterReferences();
        }
    }
    for (int i = 0; i < m_field10; ++i) {
        if (!((const Rva006DBB40ShrAndField *)m_field14[i].m_pValue)->get()) {
            m_field14[i].m_pValue->setGCMark(true);
            m_field14[i].m_pValue->RegisterReferences();
        }
    }
    {
        int nC = m_field0A;
        for (int i = 0; i < nC; ++i) {
            if (m_field0C[i] != 0) {
                if (!((const Rva006DBB40ShrAndField *)m_field0C[i])->get()) {
                    m_field0C[i]->setGCMark(true);
                    m_field0C[i]->RegisterReferences();
                }
            }
        }
    }
    {
        int nC = m_field1A;
        for (int i = 0; i < nC; ++i) {
            if (m_field1C[i] != 0) {
                if (!((const Rva006DBB40ShrAndField *)m_field1C[i])->get()) {
                    m_field1C[i]->setGCMark(true);
                    m_field1C[i]->RegisterReferences();
                }
            }
        }
    }
    {
        int nC = m_field22;
        for (int i = 0; i < nC; ++i) {
            if (m_field24[i] != 0) {
                if (!((const Rva006DBB40ShrAndField *)m_field24[i])->get()) {
                    m_field24[i]->setGCMark(true);
                    m_field24[i]->RegisterReferences();
                }
            }
        }
    }
    {
        int nC = m_field2A;
        for (int i = 0; i < nC; ++i) {
            if (m_field2C[i] != 0) {
                if (!((const Rva006DBB40ShrAndField *)m_field2C[i])->get()) {
                    m_field2C[i]->setGCMark(true);
                    m_field2C[i]->RegisterReferences();
                }
            }
        }
    }
    if (m_field30 != 0) {
        ((AptDisplayListState *)m_field30)->DisplayListItem(0);
    }
    m_fieldA0->rva006E39A0();
    for (int i = 0; i < m_fieldA8; ++i) {
        if (((Entry20 *)m_field34)[i].m_pField0 == 0)
            continue;
        if (!((const Rva006DBB40ShrAndField *)((Entry20 *)m_field34)[i].m_pValue)->get()) {
            ((Entry20 *)m_field34)[i].m_pValue->setGCMark(true);
            ((Entry20 *)m_field34)[i].m_pValue->RegisterReferences();
        }
        {
            int nInner = ((Entry20 *)m_field34)[i].m_stack.m_nElements;
            for (int j = 0; j < nInner; ++j) {
                AptValue *aptValue = ((Entry20 *)m_field34)[i].m_stack.At(j);
                if (!((const Rva006DBB40ShrAndField *)aptValue)->get()) {
                    aptValue->setGCMark(true);
                    aptValue->RegisterReferences();
                }
            }
        }
    }
}

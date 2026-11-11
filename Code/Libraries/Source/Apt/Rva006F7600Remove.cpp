// cl: /DNDEBUG /MD
// ?remove@Rva006F7600@@QAEXH@Z @0x006F7600 95B evidence AptDisplayList assert i-range plus array shift with count at +0x80; caller 0x006F7885
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006F7600
{
public:
    void remove(int i);
    void *getMask(int i);
    void rva006F7570(struct Rva006F7570Item *pItem);
private:
    friend class AptAnimationPoolData;
    void *m_items[32];
    int m_nElements;
};
void Rva006F7600::remove(int i)
{
    if (i < 0 || i >= m_nElements) {
        g_bfmeAptAssertAtE17734("i >= 0 && i < nElements", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x54A);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    for (; i < m_nElements - 1; ++i)
        m_items[i] = m_items[i + 1];
    --m_nElements;
}
// ?rva006F7570@Rva006F7600@@QAEXPAURva006F7570Item@@@Z @0x006F7570 134B evidence AptDisplayList APT_ARRAYSIZE assert plus sorted insert with count at +0x80; caller 0x006F77E4
struct Rva006F7570Key {
    int m_00;
    int m_key;
};
struct Rva006F7570Item {
    char m_pad[0x4C];
    Rva006F7570Key *m_p;
};
void Rva006F7600::rva006F7570(Rva006F7570Item *pItem)
{
    int i = 0;
    if (m_nElements > 0) {
        for (; i < m_nElements; ++i) {
            Rva006F7570Item *cur = (Rva006F7570Item *)m_items[i];
            if (cur->m_p->m_key < pItem->m_p->m_key)
                break;
        }
        if (i >= 0x20) {
            g_bfmeAptAssertAtE17734("i < APT_ARRAYSIZE(aMasks)", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x53D);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
    }
    int j = m_nElements;
    if (j > i) {
        do {
            m_items[j] = m_items[j - 1];
            --j;
        } while (j > i);
    }
    m_items[i] = pItem;
    ++m_nElements;
}

// ?getMask@Rva006F7600@@QAEPAXH@Z @0x006F7660 62B. Ghidra-unlisted
// checked element read of the same 32-slot array: the AptDisplayList.cpp
// line 0x555 "i >= 0 && i < nElements" assert (retail texts), then slot i;
// the asm breakpoint keeps the load after it, as native.
void *Rva006F7600::getMask(int i)
{
    if (i < 0 || i >= m_nElements) {
        g_bfmeAptAssertAtE17734("i >= 0 && i < nElements", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x555);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    return m_items[i];
}

// ?rva006F7720Sub@AptAnimationPoolData@@QAEXPAXH@Z @0x006F7720 643B.
// Native 6F7720..6F79A3 ends with RET8 (Ghidra's 636B extent cuts the
// epilogue). Display-list visitor: walks the list from list->head->next,
// skipping undefined values (AptCIH.h:0xD8 this-assert) and kind 19 unless
// undefined. A non-negative clip depth (+0x4C info, +4) pushes the item
// onto the sorted 32-entry mask stack and visits it with 1; otherwise every
// stacked mask whose clip depth is below the item's signed 17-bit depth
// (+0x58) is visited with -1 and removed, then the item is visited with the
// caller's mode. Finally the remaining masks are visited with -1 front to
// back. Flags bit 4 (RVA 0x00A17718) chooses the clip-stack visitor
// 0x006F73A0 over 0x006F7330; both take the same three cdecl arguments.
// Target evidence for the shape: this unit's insert (0x006F7570) and remove
// (0x006F7600) are visible here, so the stack's count stays in EDI across
// the visitor calls and only reloads after them; remove(0) inlines into the
// final loop (its 0x54A assert), remove(last) stays a call. The stack's
// destructor is the 0x006F7540 empty assert (pinned
// ??1Rva006F7540@@QAE@XZ, the unwind action), so the stack object takes
// that class name. Field and class names are structural inferences; the
// method name is address-derived.
extern unsigned int g_bfmeExtra1282Flags;
#include "AptAnimationPoolData.h"
#include "BfmeAptValue006DCD20.h"
#include "../../../GameEngine/Include/Common/Rva006DBB30SarDwordField.h"
struct AptMaskInfo { int unknown00; int clipDepth; };
struct AptDisplayNode
{
    char unknown00[0x4C];
    AptMaskInfo *info;
    AptDisplayNode *prev, *next;
    signed int depth : 17;
    unsigned int flags : 15;
};
class Rva006F7540
{
public:
    Rva006F7540() : m_nElements(0) {}
    ~Rva006F7540()
    {
        if (m_nElements != 0) {
            g_bfmeAptAssertAtE17734("nElements == 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x537);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
    }
    AptDisplayNode *get(int i)
    {
        if (i < 0 || i >= m_nElements) {
            g_bfmeAptAssertAtE17734("i >= 0 && i < nElements", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x555);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        return m_items[i];
    }
    Rva006F7600 *stack() { return (Rva006F7600 *)this; }

    AptDisplayNode *m_items[32];
    int m_nElements;
};
void rva006F7330(void *context, void *item, int mode);
void *rva006F73A0(void *context, void *item, int mode);
typedef void (__cdecl *AptDisplayVisitor)(void *, void *, int);
struct AptDisplayHead { AptDisplayNode *head; };
// The canonical header keeps AptAnimationPoolData opaque; this unit reads only
// its display-list head at +0x00 through a local view.
struct AptAnimationPoolDataListView { AptDisplayHead *list; };
void AptAnimationPoolData::rva006F7720Sub(void *context, int mode)
{
    AptDisplayNode *item = ((AptAnimationPoolDataListView *)this)->list->head->next;
    Rva006F7540 masks;
    // The clip visitor's pointer result is discarded by this visitor type.
    AptDisplayVisitor visit;
    if (g_bfmeExtra1282Flags & 4)
        visit = (AptDisplayVisitor)rva006F73A0;
    else
        visit = rva006F7330;
    while (item) {
        if (!((BfmeAptValue006DCD20 *)item)->isUndefined()) {
            if (!item) {
                g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xD8);
                if (g_bfmeAptBreakOnAssertAtDDC01C)
                    __debugbreak();
            }
            if (((Rva006DBB30SarDwordField *)item)->get() != 19 || ((BfmeAptValue006DCD20 *)item)->isUndefined()) {
                if (item->info->clipDepth >= 0) {
                    masks.stack()->rva006F7570((Rva006F7570Item *)item);
                    visit(context, item, 1);
                } else {
                    while (masks.m_nElements > 0) {
                        if (masks.get(masks.m_nElements - 1)->info->clipDepth >= item->depth)
                            break;
                        visit(context, masks.get(masks.m_nElements - 1), -1);
                        masks.stack()->remove(masks.m_nElements - 1);
                    }
                    visit(context, item, mode);
                }
            }
        }
        item = item->next;
    }
    while (masks.m_nElements > 0) {
        visit(context, masks.get(0), -1);
        masks.stack()->remove(0);
    }
}

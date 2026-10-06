// cl: /DNDEBUG /MD
// ?rva006F7600@Rva006F7600@@QAEXH@Z @0x006F7600 95B evidence AptDisplayList assert i-range plus array shift with count at +0x80; caller 0x006F7885
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006F7600
{
public:
    void rva006F7600(int i);
    void rva006F7570(struct Rva006F7570Item *pItem);
private:
    void *m_items[32];
    int m_nElements;
};
void Rva006F7600::rva006F7600(int i)
{
    if (i < 0 || i >= m_nElements) {
        g_bfmeAptAssertAtE17734("i >= 0 && i < nElements", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x54A);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    int last = m_nElements - 1;
    if (i < last) {
        do {
            m_items[i] = m_items[i + 1];
            ++i;
        } while (i < m_nElements - 1);
    }
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

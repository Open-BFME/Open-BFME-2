// ?rva006FA340@Rva006FA340@@QAEXXZ
// partial score=0.35 date=2026-10-04
// cl: /O2 /MD
//
// ?rva006FA340@Rva006FA340@@QAEXXZ @0x006FA340 216B (banked near miss).
//
// BFME2 port of the BFME1 AptInput "advance current broadcast" walker
// (reference/open-bfme-1 game/Libraries/Source/Apt/AptInput.cpp,
// BfmeBroadcast1285::bfmeAdvance1285 plus its bfmeParseSuffix1285 helper). The
// target: if the current button instance's name already parses as a suffixed
// name, keep it; otherwise broadcast mode 2, release it, then scan the
// instance array for the next entry whose name parses and attach it, then
// broadcast mode 1. 0x006E1F00 is the setState call, 0x006FA100 the broadcast.
//
// BLOCKER (why this is banked, not landed): every call to the name-suffix
// parser 0x006F97F0 uses a bespoke register ABI - the EAStringC value in EAX,
// the *second out param in EBX, and the *first out param on the stack (caller
// does `add esp,4`), i.e. eax/ebx/stack. No MSVC 7.1 convention produces it:
// __cdecl/__stdcall put every arg on the stack, __fastcall uses ECX/EDX,
// __thiscall uses ECX. All four callers of 0x006F97F0 (0x006F9A49, 0x006F9B14,
// 0x006FA35D, 0x006FA3D0) share the identical setup, so it is the callee's ABI
// and cannot be expressed from C++. The body below is otherwise byte-faithful.

class EAStringC
{
public:
    bool IsEmpty() const;
    const char *getString() const;
    int getLength() const;
};

class AptCIH
{
public:
    virtual void AddRef();
    virtual void Release();

    char m_pad04[4];
    EAStringC m_name;
    char m_pad0c[0x6c - 0x0c];

    void rva006E1F00(int state);
};

bool __cdecl Rva006F97F0Parse(EAStringC *value, int *first, int *second);

class Rva006FA340
{
public:
    void rva006FA340();
    void rva006FA100(AptCIH *entry, int mode);

private:
    char m_pad00[8];
    unsigned short m_count;
    unsigned short m_capacity;
    AptCIH **m_entries;
    char m_pad10[0x6c - 0x10];
    AptCIH *m_current;
};

void Rva006FA340::rva006FA340()
{
    int first;
    int second;
    if (m_current != 0 && Rva006F97F0Parse(&m_current->m_name, &first, &second))
        return;

    if (m_current != 0) {
        m_current->rva006E1F00(1);
        rva006FA100(m_current, 2);
    }

    if (m_current != 0)
        m_current->Release();
    m_current = 0;

    int seen = 0;
    for (int index = 0; index < m_capacity; ++index) {
        if (seen == m_count)
            break;
        AptCIH *slot = m_entries[index];
        if (slot != 0) {
            if (!slot->m_name.IsEmpty() &&
                Rva006F97F0Parse(&slot->m_name, &first, &second)) {
                m_current = m_entries[index];
                m_current->AddRef();
                break;
            }
            ++seen;
        }
    }

    if (m_current != 0) {
        m_current->rva006E1F00(2);
        rva006FA100(m_current, 1);
    }
}

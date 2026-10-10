// cl: /O2 /EHs
#include "../../../../GameEngine/Include/Common/Rva00041004Lock.h"
// ?set@?$StringBase@G@@QAEXABV1@@Z @0x00037150 132B
// Wide StringBase copy set: skips self-assignment, releases its own buffer and
// shares the source buffer by reference count under the wide string lock.
// Evidence: BFME2 export and symbols.csv pin (UnicodeString copy assignment's
// call target), wide lock singleton Rva00035DF0Get at 0x00035DF0, rowed wide
// releaseBuffer 0x00036E70; the body is the narrow twin at 0x000366F0 with the
// wide lock. Model/flags: Code/Libraries/Source/WWVegas/WWLib/StringBaseNarrowCopySet.cpp.
typedef unsigned short wchar_t;

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *section) throw();
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section) throw();

class WideLock;

Rva00041004 *Rva00035DF0Get();

template <typename T>
class StringBase
{
    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
    void releaseBuffer();

public:
    __declspec(noinline) void set(const StringBase<T> &that);
};

class WideLock
{
    Rva00041004 *m_lock;
    unsigned char m_state;

public:
    // ??0WideLock@@QAE@PAVRva00041004@@@Z present-unmatched
    __forceinline WideLock(Rva00041004 *lock) : m_lock(lock)
    {
        if (!m_lock->m_flag)
            EnterCriticalSection(&m_lock->m_cs);
        m_state = 1;
    }

    // ??1WideLock@@QAE@XZ present-unmatched
    // Retail EH handler75CCE8 -> one-state map -> action75CCE0 selects
    // the full35B guard cleanup358B0: test +4 and clear it after optional leave.
    // Same8B callable view; original guard/template identity is unknown.
    __forceinline ~WideLock()
    {
        if (m_state) {
            if (!m_lock->m_flag)
                LeaveCriticalSection(&m_lock->m_cs);
            m_state = 0;
        }
    }
};

template <>
void StringBase<wchar_t>::set(const StringBase<wchar_t> &that)
{
    WideLock lock(Rva00035DF0Get());
    if (&that != this)
    {
        releaseBuffer();
        m_data = that.m_data;
        if (m_data)
            ++m_data->ref_count;
    }
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??4Rva00630D00UStr@@QAEAAV0@ABV0@@Z=?set@?$StringBase@G@@QAEXABV1@@Z")

// Native0040FB15..0040FB1A5B tail-forwards the unchanged receiver and
// const-reference argument to the owned wide StringBase::set at00037150.
// Ghidra calls the wrapper set; original outer type and lifetime role unknown.
// This pointer-only view never constructs or sizes an unknown owner.
struct Rva0040FB15WideStringCopyForward {
    void set(const StringBase<wchar_t> &that);
};
void Rva0040FB15WideStringCopyForward::set(const StringBase<wchar_t> &that) {
    reinterpret_cast<StringBase<wchar_t> *>(this)->set(that);
}

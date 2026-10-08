// cl: /O2 /EHs
#include "../../../../GameEngine/Include/Common/Rva00041004Lock.h"
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:??0?$StringBase@D@@QAE@ABV0@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")

// ??0?$StringBase@D@@AAE@ABV0@@Z @0x000365F0 66B
// ?set@?$StringBase@D@@QAEXABV1@@Z @0x000366F0 132B
// Narrow StringBase copy constructor and copy set: share the source buffer by
// reference count under the narrow string lock. set skips self-assignment and
// releases its own buffer first.
// Evidence: BFME2 exports and symbols.csv pins for both names (retail call
// targets of AsciiString's copy constructor and copy assignment), lock
// singleton Rva00035C90Get at 0x00035C90 (flag +0x20 bypass, cs +0x08, IAT
// Enter/Leave 0xBBA200/0xBBA204), rowed releaseBuffer 0x00036410.
// Model/flags donor TU Code/Libraries/Source/WWVegas/WWLib/StringBaseWideReleaseBuffer.cpp
// (same guard; /O2 /EHs gives set's manual EH frame around the releaseBuffer call,
// and the constructor, with no throwing call inside the guard, has none).

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *section) throw();
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section) throw();

class NarrowLock;

Rva00041004 *Rva00035C90Get();

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
    StringBase(const StringBase<T> &that);

public:
    void set(const StringBase<T> &that);
};

class NarrowLock
{
    Rva00041004 *m_lock;
    unsigned char m_state;

public:
    // ??0NarrowLock@@QAE@PAVRva00041004@@@Z present-unmatched
    __forceinline NarrowLock(Rva00041004 *lock) : m_lock(lock)
    {
        if (!m_lock->m_flag)
            EnterCriticalSection(&m_lock->m_cs);
        m_state = 1;
    }

    // ??1NarrowLock@@QAE@XZ present-unmatched
    // Retail EH handler75CCE8 -> one-state map -> action75CCE0 selects
    // the full35B guard cleanup358B0: test +4 and clear it after optional leave.
    // Same8B callable view; original guard/template identity is unknown.
    __forceinline ~NarrowLock()
    {
        if (m_state) {
            if (!m_lock->m_flag)
                LeaveCriticalSection(&m_lock->m_cs);
            m_state = 0;
        }
    }
};

template <>
StringBase<char>::StringBase(const StringBase<char> &that)
{
    NarrowLock lock(Rva00035C90Get());
    m_data = that.m_data;
    if (m_data)
        ++m_data->ref_count;
}

template <>
void StringBase<char>::set(const StringBase<char> &that)
{
    NarrowLock lock(Rva00035C90Get());
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
#pragma comment(linker, "/alternatename:??0BfmeSubA@@QAE@ABV0@@Z=?set@?$StringBase@D@@QAEXABV1@@Z")
#pragma comment(linker, "/alternatename:?set@BfmeQuickMatchSlot@@QAEXABV1@@Z=?set@?$StringBase@D@@QAEXABV1@@Z")
#pragma comment(linker, "/alternatename:??0AsciiStringWI@@QAE@ABV0@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:?copyFrom@BfmeTail50@@QAEXPBU1@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:??0AsciiStringWH@@QAE@ABV0@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:?copyFrom@BfmeTailF5@@QAEXPBU1@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:??0BfmeSubB@@QAE@ABV0@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:?bfmeSetBPD@BfmeSubBPD@@QAEXPAX@Z=??0?$StringBase@D@@AAE@ABV0@@Z")

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?bfmeCopyUVKE@BfmeUniVKE@@QAEXABV1@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:?bfmeSetBSF@BfmeSubBSF@@QAEXPAX@Z=??0?$StringBase@D@@AAE@ABV0@@Z")

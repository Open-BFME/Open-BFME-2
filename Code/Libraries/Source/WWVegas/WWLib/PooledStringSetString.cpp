// cl: /O2 /arch:SSE /MD /EHsc /I.
// platformsdk
// PooledString::setString at 0x006CB7C0, next to getHash (0x006CB780) in the same
// /O2 run as string_inline.cpp. Ghidra's 489 omits the trailing RET 4; the full
// body ends at 0x006CB9AC (492 B). Entry next0, folded-case alias4 and text8 are
// established by target comparisons; the 36-byte lock is the existing target ABI
// at 0x4411C1 (flag +20 and CS +8 witnessed by Enter/LeaveCriticalSection). The
// pool names come from retail's exports.
#define _DLL
#include <windows.h>
#include <string.h>
#include "Code/GameEngine/Include/Common/Rva00041004Lock.h"

template<class T> __forceinline volatile T &r1_vwrite(T &value) { return *(volatile T *)&value; }

extern "C" {
}

namespace _STL {
    template<class T> class allocator {
    public:
        static T *allocate(unsigned, const void *);
    };
}

class PooledString {
public:
    struct StringEntry {
        StringEntry *next;
        StringEntry *noCase;
        char text[1];
    };
private:
    template<class T> friend struct DataRowPrivateProbe;
    void setString(const char *text);
    unsigned getHash(const char *, int) const;
    // Retail exports all four: ?m_hash@PooledString@@0PAPAUStringEntry@1@A,
    // ?m_buf@PooledString@@0PADA, ?m_bufUsed@PooledString@@0IA and
    // ?m_null@PooledString@@0UStringEntry@1@A (defined in PooledString.cpp).
    static StringEntry m_null;
    static StringEntry *m_hash[0x2B7B];
    static char *m_buf;
    static unsigned m_bufUsed;
    StringEntry *m_entry;
};

PooledString::StringEntry *PooledString::m_hash[0x2B7B];
char *PooledString::m_buf;
unsigned PooledString::m_bufUsed;

class PooledStringGuard {
public:
    Rva00041004 *lock;
    bool held;
    PooledStringGuard(Rva00041004 &l) : lock(&l), held(false)
    {
        if (!lock->m_flag) EnterCriticalSection(&lock->m_cs);
        held = true;
    }
    ~PooledStringGuard()
    {
        if (!lock->m_flag) LeaveCriticalSection(&lock->m_cs);
    }
};

void PooledString::setString(const char *text)
{
    if (text && *text) {
        unsigned hash = getHash(text, strlen(text));
        static Rva00041004 poolLock(1);
        PooledStringGuard guard(poolLock);
        StringEntry **bucket = &m_hash[hash % 0x2B7B];
        StringEntry *entry = *bucket;
        for (; entry; entry = entry->next)
            if (strcmp(text, entry->text) == 0) {
                m_entry = entry;
                return;
            }
        unsigned bytes = (unsigned)(strlen(text) + sizeof(StringEntry));
        if ((unsigned)(m_bufUsed + bytes) > 0x40000) {
            r1_vwrite(m_buf) = _STL::allocator<char>::allocate(0x40000, (const void *)(('s' << 16) | ('t' << 8) | 'r'));
            r1_vwrite(m_bufUsed) = 0;
        }
        entry = (StringEntry *)(m_buf + m_bufUsed);
        m_bufUsed = m_bufUsed + bytes;
        strcpy(entry->text, text);
        StringEntry *alias = *bucket;
        for (; alias; alias = alias->next)
            if (_strcmpi(text, alias->text) == 0) {
                if (alias->noCase) alias = alias->noCase;
                break;
            }
        entry->noCase = alias;
        entry->next = *bucket;
        *bucket = entry;
    }
    else m_entry = &m_null;
}

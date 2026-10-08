// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva005F918D@@QAE@XZ, RVA 0x005F918D, 57 bytes.
// Dtor of 16-byte record {holder +0, words +4/+8, UnicodeString +0xC}.
// Releases wide string at +0xC via 0x36E70 then TargetRef at +0 via 0x7DEEF.
// Evidence: same callees as Rva005F8F96 holder plus StringBase release;
// callers 0x005E9B33 0x005E9C8C 0x005E9D0C; layout matches src of converting
// copy 0x005F91F3.
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
#include "unicode_string.h"
struct Rva005F918DHolder00 {
    TargetRef00217D4C *m_ptr;
    Rva005F918DHolder00(const Rva005F918DHolder00 &other) : m_ptr(other.m_ptr) { if (m_ptr) ++m_ptr->references; }
    __forceinline ~Rva005F918DHolder00() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct Rva005F918D {
    Rva005F918DHolder00 m_holder;
    unsigned int m_word4;
    unsigned int m_word8;
    UnicodeString m_text0C;
    ~Rva005F918D();
    Rva005F918D(const Rva005F918D &other);
};
Rva005F918D::~Rva005F918D() {}
// Native 5F9141..5F918D and WB160A5B0 copy the same 16-byte record.
// The holder is already owned while the wide-string copy may throw; its
// destructor establishes the native EH state and cleanup, absent in old trials.
Rva005F918D::Rva005F918D(const Rva005F918D &other)
 : m_holder(other.m_holder), m_word4(other.m_word4), m_word8(other.m_word8), m_text0C(other.m_text0C) {}

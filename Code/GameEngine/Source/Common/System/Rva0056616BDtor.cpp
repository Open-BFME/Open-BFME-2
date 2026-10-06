// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??1Rva0056616B@@UAE@XZ
// retail 0x0056616B, 243 bytes (Ghidra FUN_0096616b). Virtual dtor storing
// vtable 0x008689D0 then destroying 16 members in reverse (0xA8 down to 0x04)
// through rowed RvaVectorFamily dtors, rowed vector<AsciiString> 0x0002CC70 and
// inline AsciiString releaseBuffer; callers 0x0052D6A2 and 0x00566D83 support
// identity. Layout from retail offsets; AsciiString via shared header.

#include "ascii_string.h"

struct Rva0052CB26 { ~Rva0052CB26(); void *m_a; void *m_b; void *m_c; };
struct Rva0052CA6C { ~Rva0052CA6C(); void *m_a; void *m_b; void *m_c; };
struct Rva004FABE2 { ~Rva004FABE2(); void *m_a; void *m_b; void *m_c; };
struct Rva0052CC25 { ~Rva0052CC25(); void *m_a; void *m_b; void *m_c; };
struct Rva0052CCC4 { ~Rva0052CCC4(); void *m_a; void *m_b; void *m_c; };
struct Rva0052CD03 { ~Rva0052CD03(); void *m_a; void *m_b; void *m_c; };
struct Rva0052CD42 { ~Rva0052CD42(); void *m_a; void *m_b; void *m_c; };
struct Rva0052CDE1 { ~Rva0052CDE1(); void *m_a; void *m_b; void *m_c; };
struct Rva0052D1CD { ~Rva0052D1CD(); void *m_a; void *m_b; void *m_c; };
struct Rva0052D20C { ~Rva0052D20C(); void *m_a; void *m_b; void *m_c; };

namespace _STL {
template <typename T> class allocator {};
template <typename T, typename A> class vector {
public:
    ~vector();
    T *m_start;
    T *m_finish;
    T *m_end;
};
}

class Rva0056616B {
public:
    virtual ~Rva0056616B();
    AsciiString m_04;
    Rva0052CB26 m_08;
    Rva0052CA6C m_14;
    Rva004FABE2 m_20;
    Rva0052CC25 m_2C;
    Rva0052CCC4 m_38;
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > m_44;
    AsciiString m_50;
    Rva0052CD03 m_54;
    Rva0052CD42 m_60;
    Rva0052CCC4 m_6C;
    Rva0052CDE1 m_78;
    Rva0052CDE1 m_84;
    Rva0052D1CD m_90;
    Rva0052D20C m_9C;
    Rva0052CC25 m_A8;
};

Rva0056616B::~Rva0056616B() {}

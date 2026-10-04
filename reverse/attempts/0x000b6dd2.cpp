// ??1Rva00B6DD2@@UAE@XZ
// partial score=1.0 date=2026-10-04
// cl: /O1 /Ob1 /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
#include "Common/Snapshot.h"
// The native ctor iterator proves three 24-byte elements, each with the
// independently rowed B6971 destructor. This declaration emits no vtable.
class Rva00B6971 {
public: virtual ~Rva00B6971();
private: char m_storage04[20];
};
// Actual native base restore BBB554 has the complete canonical Snapshot table.
// This teardown-only abstract view emits no derived table or constructor.
class __declspec(novtable) Rva00B6DD2 : public Snapshot {
public: virtual ~Rva00B6DD2();
private: Rva00B6971 m_elements04[3];
};
inline Rva00B6DD2::~Rva00B6DD2() {}
#pragma inline_depth(0)
// ?emitRva00B6DD2 present-unmatched
void emitRva00B6DD2(Rva00B6DD2 *p) { p->Rva00B6DD2::~Rva00B6DD2(); }
#pragma inline_depth()

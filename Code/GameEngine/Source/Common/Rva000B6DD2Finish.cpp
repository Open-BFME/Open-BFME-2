// ??1DelayedLuaEventList@@UAE@XZ
// cl: /O1 /Ob1 /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
#include "Common/Snapshot.h"
// 0x000B6DD2 is DelayedLuaEventList's virtual dtor: its ctor row 0x000B6D8B stores
// vftable 0x007C9CF0, whose slot 0 is the scalar deleting dtor 0x000B6E0C calling this body.
// The native ctor iterator proves three 24-byte elements, each with the
// independently rowed B6971 destructor. This declaration emits no vtable.
class Rva00B6971 {
public: virtual ~Rva00B6971();
private: char m_storage04[20];
};
// Actual native base restore BBB554 has the complete canonical Snapshot table.
// This teardown-only abstract view emits no derived table or constructor.
class __declspec(novtable) DelayedLuaEventList : public Snapshot {
public: virtual ~DelayedLuaEventList();
private: Rva00B6971 m_elements04[3];
};
inline DelayedLuaEventList::~DelayedLuaEventList() {}
#pragma inline_depth(0)
// ?emitRva00B6DD2 present-unmatched
void emitRva00B6DD2(DelayedLuaEventList *p) { p->DelayedLuaEventList::~DelayedLuaEventList(); }
#pragma inline_depth()

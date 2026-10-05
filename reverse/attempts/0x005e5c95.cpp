// ?rva005E5C95@@YAPAPAVRva005E59C2@@PAPAV1@PBUPayload@1@@Z
// partial score=0.9 date=2026-10-05
// ?rva005E5C95@@YAPAPAVRva005E59C2@@PAPAV1@PBUPayload@1@@Z
// partial score=0.9 date=2026-10-05
// ?rva005E5C95@@YAPAPAVRva005E59C2@@PAPAV1@PBUPayload@1@@Z @0x005E5C95 50B
// nothrow-style factory for rowed Rva005E59C2 (0x14B, payload ctor at
// 0x005E59C2): explicit operator new (pinned ??2 0x0002FDA0) with null check,
// placement construction, store-or-null to out, AddRef when non-null, return
// out. Plain new never null-checks and std::nothrow has no operator-new pin,
// so the check is spelled explicitly; it emits the same head. The rowed class
// carries a virtual dtor; here the vtable slot is plain data (no virtuals
// declared, nothing emitted) purely to hold sizeof at 0x14. Honest free
// function name; the true factory identity is unproven.
#include <new>

// Forward nothrow-new to the game operator new so the TU can spell the
// retail null-checked allocation without referencing an unpinned nothrow
// overload. Static (like TU-local anchors elsewhere); inlines away.
static inline void *operator new(unsigned int s, const std::nothrow_t &)
{
	return operator new(s);
}

class Rva005E59C2
{
public:
	struct Payload { int v[3]; };
	Rva005E59C2(const Payload *src) throw();
	void AddRef() { ++m_ref; }
private:
	void *m_vtbl; // +0 (rowed class has a virtual dtor; kept as data)
	int m_ref; // +4
	Payload m_data; // +8
};

void *__cdecl operator new(unsigned int size);

#pragma optimize("y", off)
Rva005E59C2 **rva005E5C95(Rva005E59C2 **out, const Rva005E59C2::Payload *src)
{
	volatile int eh_state = 0;
	(void)eh_state;
	Rva005E59C2 *obj = NULL;
	obj = new (std::nothrow) Rva005E59C2(src);
	*out = obj;
	if (obj != NULL)
		obj->AddRef();
	return out;
}
#pragma optimize("", on)

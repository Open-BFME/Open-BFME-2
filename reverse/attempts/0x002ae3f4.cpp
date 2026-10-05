// ?rva002AE3F4@Rva002AE3F4@@QAEXW4ObjectID@@@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /GX-
// stlport
// ?rva002AE3F4@Rva002AE3F4@@QAEXW4ObjectID@@@Z, retail 0x002AE3F4, 65 bytes.
//
// List add-if-missing: search the member list at this+0x754 for the ObjectID
// and append it only when the search reached the end.
//
// Two corrections against the 0.97 bank, both established from retail:
//
// 1. SIGNATURE. Retail emits `lea eax,[ebp+8] / push eax` for find's value
//    operand and again for append's element, and retires `ret 4`. One
//    pointer-sized argument, dereferenced: ObjectID is passed BY REFERENCE.
//    The bank declared it by value. That matters beyond bookkeeping -- the
//    by-value spelling copies the enum through a stack temporary and shifts
//    the whole body. The mangled name __QAEXW4ObjectID@@@Z (E = by
//    reference, X = void return) is what the bank and the ledger carry, so
//    the reference spelling is also the name.
//
// 2. THE LIST IS NOT AT OFFSET 0. Retail reaches the sentinel through
//    `lea esi,[ecx+0x754]`, so the member list sits at this+0x754. The bank
//    read the sentinel off `this` itself, which is the same register as the
//    list address and cannot produce retail's `mov ecx,[esi]` /
//    `cmp ecx,[eax]` compare.
//
// What still differs, and why it is not reachable from this body: retail holds
// the sentinel in ecx across the call and compares it against the result
// pointer call leaves in eax (`mov ecx,[esi] / cmp ecx,[eax]`). Every source
// spelling measured here reloads the sentinel from [esi] at the compare
// instead, which needs one extra load: naming begin() (live range across the
// call), naming the list by reference, and the banked spelling all give
// `cmp eax,[esi]`. MSVC 7.1 re-materialises the member rather than keeping it
// in a register, and no register is spare -- esi already holds the list
// address and ecx is the thiscall receiver. This is the same register-pinning
// limit recorded for 0x004CA6F3, and the last 2 of the 4 remaining diffs are
// call relocations the gate resolves.
//
// Evidence: callees rowed find 0x0029B694 and append 0x002A1B6F; the find is
// the ObjectID-list instantiation already placed at 0x29B694 by
// SpawnBehavior.cpp, so the element type and list flavour are established by
// that row rather than assumed here. Body is 0x002AE3F4..0x002AE432 with
// `ret 4` at 0x2AE432 and 0xCC padding after.
#include <list>

enum ObjectID
{
	OBJECTID_NONE = 0
};

// ?rva002AE3F4@Rva002AE3F4@@QAEXW4ObjectID@@@Z present-unmatched
class Rva002AE3F4
{
public:
	void rva002AE3F4(ObjectID val);

private:
	char _pad[0x754];
	std::list<ObjectID> m_list;  // sentinel at this+0x754
};

void Rva002AE3F4::rva002AE3F4(ObjectID val)
{
	std::list<ObjectID> &lst = m_list;
	std::list<ObjectID>::iterator it = std::find(lst.begin(), lst.end(), val);
	if (it == lst.end())
		lst.push_back(val);
}

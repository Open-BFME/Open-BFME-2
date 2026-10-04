// cl: -DNDEBUG -DWIN32 -MD -D_STLP_USE_STATIC_LIB /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/RTS
// stlport
// ?m@Gen_00581350@@QAEXPAX@Z
// retail 0x002007A7, 23 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/RTS/Gen_guarded_list_push_back.cpp
// (reference/open-bfme-1 @ 6d943426). Compiled /Os the donor body is
// byte-identical to retail once relocations are masked (unique hit on unclaimed
// .text). Only the placed body is defined here; the donor's other five
// definitions are omitted.
//
// The guarded push_back, over a _STL::list of 4-byte elements:
//
//     if (x == NULL) return;  m_list.push_back(x);
//
// The list sits at this+0x08, which the class's two pad words establish: retail
// reaches it with `add ecx, 8` immediately before the insert call. The lever
// that makes this shape reproducible is _STLP_NO_EXCEPTIONS; see
// ResourceGatheringManager_addSupply.cpp in this directory for the mechanism.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Native 2007B6 calls 5548F, not the other list<void*> body at 526103.
// This external ABI view names only the observed 4-byte element append.
// The complete 26-byte provider is already rowed as list<int>::push_back;
// its native insert target differs from the other pointer-list instance.
class Rva0005548FNativeList { public: void append(void *const &value); };
#pragma comment(linker, "/alternatename:?append@Rva0005548FNativeList@@QAEXABQAX@Z=?push_back@?$list@HV?$allocator@H@_STL@@@_STL@@QAEXABH@Z")

// ?m@Gen_00581350@@QAEXPAX@Z  -- list at this+0x08
struct Gen_00581350
{
	void m(void *x);
	void *m_slice_vtbl;
	void *m_slice_word1;
	_STL::list<void *> m_list;
};

void Gen_00581350::m(void *x)
{
	if (x == NULL)
		return;

	reinterpret_cast<Rva0005548FNativeList *>(&m_list)->append(x);
}

// Reference lead: Gen_002e0dd0::m in the same six-body donor at
// Open-BFME-1 revision 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24.
// Target evidence: Ghidra entry 3320C7/63 and its complete RET4 body;
// the receiver's list is at +8, find at 3320E7 reaches rowed 29B694/42,
// and append at 3320FC reaches the distinct rowed 2A1B6F/26 provider.
// The source carries the donor's find-then-append semantics and named
// iterator shape. Neither the original owner nor the element purpose is
// established; this is only an observed pointer-width list prefix view.
// The native find ABI copies two node iterators and returns an iterator
// through a hidden result pointer. Declare its existing provider instead
// of emitting incompatible private STL iterator COMDAT copies.
struct Rva003320C7Iterator
{
    // ?Rva003320C7Iterator::Rva003320C7Iterator present-unmatched
    explicit Rva003320C7Iterator(void *p) : node(p) {}
    // ?Rva003320C7Iterator::Rva003320C7Iterator present-unmatched
    Rva003320C7Iterator(const Rva003320C7Iterator &other) : node(other.node) {}
    void *node;
};
Rva003320C7Iterator __cdecl Rva003320C7Find(
    Rva003320C7Iterator first, Rva003320C7Iterator last, void *const &value);
#pragma comment(linker, "/alternatename:?Rva003320C7Find@@YA?AURva003320C7Iterator@@U1@0ABQAX@Z=??$find@U?$_List_iterator@W4ObjectID@@U?$_Nonconst_traits@W4ObjectID@@@_STL@@@_STL@@W4ObjectID@@@_STL@@YA?AU?$_List_iterator@W4ObjectID@@U?$_Nonconst_traits@W4ObjectID@@@_STL@@@0@U10@0ABW4ObjectID@@@Z")
class Rva003320C7AppendABI
{
public:
    void append(void *const &value);
};
#pragma comment(linker, "/alternatename:?append@Rva003320C7AppendABI@@QAEXABQAX@Z=?append@Rva002A1B6FNativeList@@QAEXABQAX@Z")

class Rva003320C7ListOwner
{
public:
    void appendIfAbsent(void *value);
private:
    // ?Rva003320C7ListOwner::begin present-unmatched
    Rva003320C7Iterator begin() { return Rva003320C7Iterator(*(void **)head); }
    // ?Rva003320C7ListOwner::end present-unmatched
    Rva003320C7Iterator end() { return Rva003320C7Iterator(head); }
    unsigned char prefix[8];
    void *head;
};

void Rva003320C7ListOwner::appendIfAbsent(void *value)
{
    Rva003320C7Iterator position = Rva003320C7Find(begin(), end(), value);
    if (position.node == head)
        reinterpret_cast<Rva003320C7AppendABI *>(&head)->append(value);
}

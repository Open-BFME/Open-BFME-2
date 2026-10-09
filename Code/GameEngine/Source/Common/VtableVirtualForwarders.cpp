// cl: /MD /Ob0
//
// Unnamed vtable slot targets that are pure virtual forwarders: each loads its
// own vptr and TAIL-JUMPS to another slot on the same object. Found with
// tools/vtable_gaps.py -- they are unnamed slots of vtable-shaped runs that
// also carry named slots, so the vtable is the only evidence that reaches them.
//
//  0x001FF3A9   4B   8b 01 ff 20        mov eax,[ecx] ; jmp [eax]      slot 0
//  0x005CC208   5B   8b 01 ff 60 08     mov eax,[ecx] ; jmp [eax+0x8]  slot 2
//  0x000D20D6   5B   8b 01 ff 60 24     mov eax,[ecx] ; jmp [eax+0x24] slot 9
//
// Identity is not recoverable and the caller set is empty, so each class keeps
// an address-derived name (AGENTS.md permits an address token where a guessed
// class is prohibited). The declared-but-undefined virtuals exist only to
// place the forwarder at the right slot; the call itself is indirect, so no
// callee address is encoded, and the vtable's own slots are DIR32 auto-patches
// taken from retail -- the same arrangement OpaqueSingleInheritanceDtors.cpp
// uses for its bases.

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9_slot0();
	virtual void rva001FF3A9();
};

void Rva001FF3A9::rva001FF3A9()
{
	rva001FF3A9_slot0();
}

class Rva005CC208
{
public:
	virtual void rva005CC208_slot0();
	virtual void rva005CC208_slot1();
	virtual void rva005CC208_slot2();
	virtual void rva005CC208();
};

void Rva005CC208::rva005CC208()
{
	rva005CC208_slot2();
}

class Rva000D20D6
{
public:
	virtual void rva000D20D6_slot0();
	virtual void rva000D20D6_slot1();
	virtual void rva000D20D6_slot2();
	virtual void rva000D20D6_slot3();
	virtual void rva000D20D6_slot4();
	virtual void rva000D20D6_slot5();
	virtual void rva000D20D6_slot6();
	virtual void rva000D20D6_slot7();
	virtual void rva000D20D6_slot8();
	virtual void rva000D20D6_slot9();
	virtual void rva000D20D6();
};

void Rva000D20D6::rva000D20D6()
{
	rva000D20D6_slot9();
}

// Target 5CCAB3..5CCACA RET leaf beside 5CCA98 on the same receiver: a
// nonnull word4 answers through the slot-10 (+0x28) vcall thunk 001F34BA,
// reached by a pointer to virtual member as the retail direct call requires.
// 5CCB4C..5CCB54 forwards the +8 holder to it by tail jump; its caller
// 0057544B tests AL. Owner and slot identities unknown (address names).
class Rva005CCAB3Target
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual bool query();
};

struct Rva005CCAB3Holder {
    unsigned char prefix00[4];
    Rva005CCAB3Target *target;
    bool query();
};
bool Rva005CCAB3Holder::query() {
    bool (Rva005CCAB3Target::*method)()=&Rva005CCAB3Target::query;
    return target && (target->*method)();
}

class Rva005CCB4CCall {
public:
    bool rva005CCB4C();
private:
    unsigned char prefix00[8];
    Rva005CCAB3Holder *holder;
};
bool Rva005CCB4CCall::rva005CCB4C() {
    return holder->query();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva001FF3A9@Rva001FF3A9@@QAEXABUTreeHintRef00217D4C@@@Z=?rva001FF3A9@Rva001FF3A9@@UAEXXZ")
#pragma comment(linker, "/alternatename:?rva005CC208@Rva005CC208@@UAE_NXZ=?rva005CC208@Rva005CC208@@UAEXXZ")

// /Ob0 preserves the native direct call to the existing tiny forwarder.
// Complete target5CCA98..5CCAB3 RET leaf: when byte22 is set, invoke
// the rowed slot-9 forwarderD20D6 on a nonnull word4, then clear byte22.
// The qualified call is deliberately direct: retail calls the forwarder,
// which performs virtual dispatch. No new virtual-table shape is inferred.
// Only accessed prefixes are modeled; original owner and full size unknown.
struct Rva005CCA98Guard {
    unsigned char prefix00[4];
    Rva000D20D6 *target;
    unsigned char prefix08[0x1A];
    bool active;
    void invokeAndClear();
};
void Rva005CCA98Guard::invokeAndClear() {
    if (active) {
        if (target) target->Rva000D20D6::rva000D20D6();
        active=false;
    }
}

// Complete 00129440..0012944E entry between INT3 runs, after the independent
// 00129430..00129439 RET body. Native receiver word0 is nullable; a nonnull
// receiver supplies vptr word0 and tail dispatch through byte offset28. The
// null branch clears AL and RETs without stack cleanup. Only the observed
// receiver and low-byte result channel are modeled; original owner, full
// object layout, remaining slots and complete prototype are unasserted.
// BFME1 f98983a7 WW3D2/Rva0090C6A0VirtualFlag.cpp O2/SSE2/G7 is a clean
// reference lead, not an identity. Explicit returns avoid integer promotion
// of a raw byte through the donor's bool ternary. No compiler override.
struct Rva00129440Target;
struct Rva00129440Table {
    void *unknownSlots[10];
    unsigned char (__fastcall *query)(Rva00129440Target *);
};
struct Rva00129440Target { Rva00129440Table *table; };
class Rva00129440 {
    Rva00129440Target *target;
public:
    unsigned char query() const;
};
unsigned char Rva00129440::query() const {
    if (target) return target->table->query(target);
    return 0;
}

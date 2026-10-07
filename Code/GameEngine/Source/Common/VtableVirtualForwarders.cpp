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

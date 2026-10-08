// cl: /MD
//
// ?rva005CB26A@Rva005CB26A@@QAEHXZ @0x005CB26A 5B.
// Evidence: retail mov eax,[ecx]; jmp [eax+0x10] (slot 4 forwarder); LINK BONUS
// requires ?Rva005CB26A@@YAXXZ; vcall thunk ??_9@$BBA@AE at same address;
// sibling 0x005CB260 precedent Rva005CB260Forwarder.cpp slot1 forwarder with
// alternatename; SidesListNotifier dispatch calls it with ecx=listener.

class Rva005CB26A
{
public:
	virtual void rva005CB26A_slot0();
	virtual void rva005CB26A_slot1();
	virtual void rva005CB26A_slot2();
	virtual void rva005CB26A_slot3();
	virtual int rva005CB26A_slot4();
	int rva005CB26A();
};

int Rva005CB26A::rva005CB26A()
{
	return rva005CB26A_slot4();
}

// Native Checklist Impl Update at 0x005CCE7D tests EAX from this thunk.
// Preserve that return contract; existing void callback users discard it.
// Callers elsewhere reach this body through the free-function spelling;
// retail's call sites land on this address (same ABI). Bind it.
#pragma comment(linker, "/alternatename:?Rva005CB26A@@YAXXZ=?rva005CB26A@Rva005CB26A@@QAEHXZ")

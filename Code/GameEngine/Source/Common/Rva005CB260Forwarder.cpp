// cl: /MD
//
// ?rva005CB260@Rva005CB260@@QAEXXZ @0x005CB260 5B.
// Evidence: retail mov eax,[ecx]; jmp [eax+4] (slot 1 forwarder); LINK BONUS
// requires exactly QAEXXZ; twin pins at 0x005CB260; caller
// RadarWindowOverrideSource::rva002D370A passes +0xC8 pointer as this.

class Rva005CB260
{
public:
	virtual void rva005CB260_slot0();
	virtual void rva005CB260_slot1();
	void rva005CB260();
};

void Rva005CB260::rva005CB260()
{
	rva005CB260_slot1();
}

// ?rva005CB265@Rva005CB265@@UAEHXZ @0x005CB265 5B: the slot-3 twin,
// mov eax,[ecx]; jmp [eax+0xC]. Retail ICF-folds it with
// ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow (rowed in
// ProcessAnimateWindowBottomTimedReverse.cpp), but its callers push no
// argument and read an int (call site 0x005796CE: no push, cmp eax,edi), so
// they cannot call that one-argument spelling. This is the fold's no-argument
// spelling those callers use.
class Rva005CB265
{
public:
	virtual int rva005CB265();
	virtual void rva005CB265_slot1();
	virtual void rva005CB265_slot2();
	virtual int rva005CB265_slot3();
};

// ?Rva005CB265::rva005CB265 present-unmatched
int Rva005CB265::rva005CB265()
{
	return rva005CB265_slot3();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva005CB260@@YAXXZ=?rva005CB260@Rva005CB260@@QAEXXZ")

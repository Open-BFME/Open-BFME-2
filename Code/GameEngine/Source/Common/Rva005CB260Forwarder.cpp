// cl: /MD
//
// ?rva005CB260@Rva005CB260@@QAEXXZ @0x005CB260 5B.
// Evidence: retail mov eax,[ecx]; jmp [eax+4] (slot 1 forwarder); LINK BONUS
// requires exactly QAEXXZ; twin pins at 0x005CB260; caller
// RadarWindowOverrideSource::rva002D370A passes +0xC8 pointer as this.

#include "../../Include/Common/Rva005CB260.h"

void Rva005CB260::rva005CB260()
{
	rva005CB260_slot1();
}

// ?rva005CB260@Rva005CB260@@QAEXH@Z: the same fold's one-argument spelling.
// Its callers push one int before calling 0x005CB260 (0x005E0B0F pushes 0),
// which the forwarder passes on to slot 1 untouched.
class Rva005CB260IntSlots
{
public:
	virtual void slot0();
	virtual void slot1(int value);
};

void Rva005CB260::rva005CB260(int value)
{
	((Rva005CB260IntSlots *)this)->slot1(value);
}

// ?rva005CB260@Rva005CB260Properties@@QAEXHIIABVUnicodeString@@@Z: the fold's
// four-argument spelling. StrategicHUD::BattlePromptMovieClip::Impl::OnAllyTabsLoaded
// pushes (index, two record words, the record's string) before calling
// 0x005CB260, which passes them on to slot 1 untouched.
class UnicodeString;
class Rva005CB260PropertiesSlots
{
public:
	virtual void slot0();
	virtual void slot1(int index, unsigned int word0, unsigned int word1, const UnicodeString &text);
};

class Rva005CB260Properties
{
public:
	void rva005CB260(int index, unsigned int word0, unsigned int word1, const UnicodeString &text);
};

void Rva005CB260Properties::rva005CB260(int index, unsigned int word0, unsigned int word1, const UnicodeString &text)
{
	((Rva005CB260PropertiesSlots *)this)->slot1(index, word0, word1, text);
}

// ?rva005CB265@Rva005CB265@@UAEHXZ @0x005CB265 5B: the slot-3 twin,
// mov eax,[ecx]; jmp [eax+0xC]. Retail ICF-folds it with
// ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow (rowed in
// ProcessAnimateWindowBottomTimedReverse.cpp), but its callers push no
// argument and read an int (call site 0x005796CE: no push, cmp eax,edi), so
// they cannot call that one-argument spelling. This is the fold's no-argument
// spelling those callers use.
#include "../../Include/Common/Rva005CB265.h"

// ?Rva005CB265::rva005CB265 present-unmatched
int Rva005CB265::rva005CB265()
{
	return rva005CB265_slot3();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva005CB260@@YAXXZ=?rva005CB260@Rva005CB260@@QAEXXZ")

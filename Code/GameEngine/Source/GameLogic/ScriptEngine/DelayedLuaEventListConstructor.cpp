// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
#include "Common/Snapshot.h"

// DelayedLuaEventList::DelayedLuaEventList, retail 0x000B6D8B, 65 bytes, and
// the element constructor ??0EventParameter it hands to the iterator, retail
// 0x000B694C, 31 bytes.
//
// The constructor's whole job is the vtable store at +0 and one call to the EH
// vector constructor iterator at 0x009F6EE4. Its five arguments spell the
// member out: the array starts at +4, the elements are 0x18 bytes, there are
// three of them, and each has both a constructor and a destructor -- which is
// why this is the EH iterator rather than a plain loop.

// The element is the class of vftable 0x007C9CD0, whose slot 3 is the
// ?xfer@EventParameter row 0x003318F7 and slot 2 a getter returning the
// "EventParameter" literal. Its constructor 0x000B694C (the iterator's first
// pointer) stores that vftable, zeroes a float at +4 and a byte at +8 and the
// dwords at +0x0C, +0x10 (the string the dtor releases) and +0x14; its
// destructor 0x000B6971 (the second pointer) is the EventParameter dtor row.
class EventParameter
{
public:
	EventParameter(void) : m_f04(0.0f), m_b08(false), m_i0C(0), m_string10(0), m_i14(0)
	{
	}

	virtual ~EventParameter(void);			// row 0x000B6971

private:
	float m_f04;
	bool m_b08;
	int m_i0C;
	const char *m_string10;
	int m_i14;
};

// The frame is an unwind frame with one state: if the array constructor
// throws, the Snapshot base is torn down (the funclet 0x00761537 jumps to
// ??1Snapshot 0x0049B47C). Snapshot has no data, so the array starts at +4.
class DelayedLuaEventList : public Snapshot
{
public:
	DelayedLuaEventList(void);

	virtual ~DelayedLuaEventList(void);

private:
	EventParameter m_bfmeEvents[3];		// +0x04
};

// ??0DelayedLuaEventList@@QAE@XZ
DelayedLuaEventList::DelayedLuaEventList(void)
{
}

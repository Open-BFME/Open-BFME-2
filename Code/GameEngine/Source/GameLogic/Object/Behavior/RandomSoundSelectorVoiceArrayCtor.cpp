// cl: /O1 /DNDEBUG /MD
//
// ??0Rva00254FE4Member@@QAE@XZ, retail 0x00254FE4, 27 bytes. Voice-slot
// array member ctor: 56 eight-byte elements built in place through the
// rowed 5-arg ehvec helper at 0x629512 (push order dtor, ctor, count,
// size, first matches its stdcall convention; the two address pushes are
// DIR32 slots the patcher copies from retail). The element is an 8-byte
// voice pair (retail element ctor at 0x4CEE6E inits it via or-minus-1
// plus and-zero); modeled TU-locally with declared-only ctor/dtor so the
// compiler emits the bare addresses with zero extra code. Single member,
// nothing after it can throw, so no EH frame (retail is frameless).
// Called from the rowed RandomSoundSelector MD ctor 0x25785C at +0x08
// plus four sibling member-position callers (shared fold, SlotToLock
// precedent; rowed once under this name).

struct VoiceSlot
{
	VoiceSlot();
	~VoiceSlot();

	unsigned char m_data[8];
};

class Rva00254FE4Member
{
public:
	Rva00254FE4Member();

private:
	VoiceSlot m_slots[56]; // +0x00 (0x1C0 bytes)
};

// ??0Rva00254FE4Member@@QAE@XZ @0x254FE4
Rva00254FE4Member::Rva00254FE4Member()
{
}

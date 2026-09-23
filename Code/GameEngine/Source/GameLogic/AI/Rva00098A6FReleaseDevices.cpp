// cl: /O1 /DNDEBUG /MD
//
// ?releaseDevices@Rva00098A6F@@QAEXXZ, retail 0x00098A6F, 61 bytes.
// Device teardown for the 0xE28-byte input class whose constructor (0x98B55)
// reads CapsLock via GetKeyState, whose slot-1 virtual (0x98BD4) creates a
// DirectInput object plus device into +0xE20/+0xE24, and whose destructor
// (0x98B8B, with scalar-deleting destructor at 0x98C90) calls this on the way
// out. Also called on the creator's two failure paths (0x98C02/0x98C2A). The
// body bytes are unique in .text, prev is a C2 ret, next is a frame prologue,
// and only the two internal je arms target the interior.
//
// The two slots hold COM-style objects behind an explicit stdcall function
// table (9 slots): each object publishes its table pointer at +0 and takes
// itself as an explicit argument (push obj / call [table+slot]), so the
// callees need no pins and leave no relocs. Slot 2 (+8) is Release on both;
// slot 8 (+0x20) is Unacquire, run first on the +0xE24 device only. The
// +0xE24 pointer is reloaded for the second call (a call clobbers it and
// frameless code keeps no callee-saved copy), and both slots are nulled with
// the and-zero idiom (= 0 compiles to AND at /O1). The +0xE20 slot goes
// through a (char *)this + 0xE20 pointer, which is what emits the mid-body
// add esi,0xE20; after that this is dead.
//
// IDENTITY NOTE: this body previously landed as AIPlayer::clearTeamsInQueue
// on a BFME1-donor shape resemblance (EH dtor plus two calls). That identity
// is refuted: the owning class reads CapsLock, creates DirectInput devices,
// and is factory-built at 0xE28 bytes (not the donor's 0xA0); Unacquire plus
// Release is device teardown, not team-queue removal. The verdict is logged
// so the name is not re-landed here. The class name stays address-derived
// until the input class is identified; the vtable is 0xBC8688.

struct Rva00098A6FQueue;

typedef void (__stdcall *Rva00098A6FSlotFn)(Rva00098A6FQueue *obj);

struct Rva00098A6FTable
{
	Rva00098A6FSlotFn slot0;
	Rva00098A6FSlotFn slot1;
	Rva00098A6FSlotFn release;
	Rva00098A6FSlotFn slot3;
	Rva00098A6FSlotFn slot4;
	Rva00098A6FSlotFn slot5;
	Rva00098A6FSlotFn slot6;
	Rva00098A6FSlotFn slot7;
	Rva00098A6FSlotFn unacquire;
};

struct Rva00098A6FQueue
{
	Rva00098A6FTable *m_table;
};

class Rva00098A6F
{
public:
	void releaseDevices();

private:
	unsigned char m_pad[0xE20];
	Rva00098A6FQueue *m_slotE20; // +0xE20
	Rva00098A6FQueue *m_slotE24; // +0xE24
};

// ?releaseDevices@Rva00098A6F@@QAEXXZ @0x00098A6F
void Rva00098A6F::releaseDevices()
{
	if (m_slotE24 != 0)
	{
		m_slotE24->m_table->unacquire(m_slotE24);
		m_slotE24->m_table->release(m_slotE24);
		m_slotE24 = 0;
	}
	Rva00098A6FQueue **slot = (Rva00098A6FQueue **)((char *)this + 0xE20);
	if (*slot != 0)
	{
		(*slot)->m_table->release(*slot);
		*slot = 0;
	}
}

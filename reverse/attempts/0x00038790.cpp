// ?SkipNext@Debug@@SA_N_N@Z
// partial score=0.9 date=2026-09-03
// cl: /Oy- /MD
//
// WWDebug Debug::SkipNext. It records the call site for the crash or assert
// that follows: it captures its own return address and hands that, with its
// argument, to slot 0x5C of the Debug singleton at 0x00DE0880.
//
// Identified from ProfileAllocMemory, which calls it out of line here where
// _heap_abort in debug_debug.cpp inlines it - the same body seen from both
// sides. This engine takes a bool where the reference header declares it void.
//
// /Oy- puts the ebp frame back; without it cl reads the return address off esp
// with no frame at all. The captured address is held volatile because retail
// stores it to its slot and reloads it rather than keeping it in a register,
// which is the push ecx in the prologue.

extern "C" void *_ReturnAddress(void);
#pragma intrinsic(_ReturnAddress)

class Debug
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual bool SetCrashAddress(void *address, bool set);

	static bool SkipNext(bool set);
};

Debug *theDebug;

bool Debug::SkipNext(bool set)
{
	void *volatile address = _ReturnAddress();

	return theDebug->SetCrashAddress(address, set);
}

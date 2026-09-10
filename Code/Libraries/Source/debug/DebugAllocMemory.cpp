// cl: /Oy- /MD
//
// DebugAllocMemory, retail 0x0003E450, 83 bytes.
// Same GlobalAlloc + DCRASH_RELEASE arm as ProfileAllocMemory; this copy
// keeps the ebp frame retail uses for the size argument.

extern "C" __declspec(dllimport) void *__stdcall GlobalAlloc(unsigned int flags,
		unsigned int bytes);

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
	virtual Debug &operator<<(const char *text);
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void CrashDone(bool fatal);
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void SetCrashAddress(void *address, bool set);
	virtual void SkipNext();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual Debug &CrashBegin(const char *file, int line, const char *group);

	static bool SkipNext(bool set);
};

Debug *theDebug;

void *DebugAllocMemory(unsigned int numBytes)
{
	void *h = GlobalAlloc(0, numBytes);
	if (!h)
	{
		Debug::SkipNext(true);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "Debug mem alloc failed").CrashDone(true);
	}
	return h;
}

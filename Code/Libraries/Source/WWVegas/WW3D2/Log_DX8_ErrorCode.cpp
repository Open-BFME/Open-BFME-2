// cl: /O2 /MD
//
// Log_DX8_ErrorCode, retail 0x0011F450, 88 bytes.
// Dedicated TU. Retail is a typed crash dump (fourcc DXER plus the HRESULT)
// followed by the same SkipNext / CrashBegin / CrashDone arm as DebugAllocMemory.

extern "C" void *__cdecl realloc(void *block, unsigned size);
extern "C" void *__cdecl memcpy(void *dest, const void *source, unsigned size);
#pragma intrinsic(memcpy)

struct DebugTypedLog
{
	unsigned tag;
	void *data;
	unsigned size;
};

DebugTypedLog *g_debugTypedLogs;
unsigned g_debugTypedLogCount;

#pragma optimize("y", off)
void DebugLogTyped(unsigned tag, void *data, unsigned size)
{
	unsigned index = 0;
	while (index < g_debugTypedLogCount && g_debugTypedLogs[index].tag != tag)
		++index;

	if (index == g_debugTypedLogCount)
	{
		++g_debugTypedLogCount;
		g_debugTypedLogs = static_cast<DebugTypedLog *>(realloc(
			g_debugTypedLogs, g_debugTypedLogCount * sizeof(DebugTypedLog)));
		g_debugTypedLogs[index].tag = tag;
		g_debugTypedLogs[index].data = 0;
		g_debugTypedLogs[index].size = 0;
	}

	g_debugTypedLogs[index].data = realloc(g_debugTypedLogs[index].data, size);
	memcpy(g_debugTypedLogs[index].data, data, size);
	g_debugTypedLogs[index].size = size;
}
#pragma optimize("y", on)

class Debug
{
public:
	virtual Debug &LogUnsigned(unsigned value);
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

void Log_DX8_ErrorCode(unsigned res)
{
	DebugLogTyped(0x44584552, &res, 4);
	Debug::SkipNext(true);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Direct3D error ").LogUnsigned(res).CrashDone(true);
}

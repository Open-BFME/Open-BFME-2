// cl: /DNDEBUG /MD /EHs-c-
//
// Debug::StaticExit, retail 0x000399C0 (147 bytes).
//
// Zero Hour's body shuts the I/O classes down on exit. BFME2 pairs it with
// the reference-counted PreStaticInit (0x000385F0): every call drops the
// count at +0x9C7C and only the last one flushes pending output and deletes
// the I/O interfaces (DebugIOInterface::Delete, vtable slot 0x18). Both
// paths delete the Debug critical section; the last one also opens
// errors.txt in the shell when the +0x9F57 "log errors to file" flag is
// set. The command-group loop of Zero Hour is gone.

typedef void *HWND;

struct DebugCriticalSection
{
	unsigned char m_data[0x18];
};

extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(DebugCriticalSection *lock);
extern "C" __declspec(dllimport) void *__stdcall ShellExecuteA(HWND window, const char *operation,
	const char *file, const char *parameters, const char *directory, int showCommand);

extern DebugCriticalSection g_bfmeCsDWC;

class DebugIOInterface
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void Delete();
};

class Debug
{
public:
	virtual ~Debug();

private:
	struct IOFactoryListEntry
	{
		IOFactoryListEntry *next;
		const char *ioID;
		const char *descr;
		DebugIOInterface *(*factory)(void);
		DebugIOInterface *io;
	};

	static void StaticExit();

	virtual void FlushOutput(bool defaultLog);

	unsigned char m_pad04[8];
	IOFactoryListEntry *firstIOFactory;  // +0x0C
	unsigned char m_pad10[0x9C6C];
	int refCount;                        // +0x9C7C
	unsigned char m_pad9C80[0x74];
	int curType;                         // +0x9CF4
	unsigned char m_pad9CF8[0x25F];
	bool logErrorsToFile;                // +0x9F57
};

extern Debug *theDebug;

// ?StaticExit@Debug@@CAXXZ
void Debug::StaticExit()
{
	if (--theDebug->refCount)
	{
		DeleteCriticalSection(&g_bfmeCsDWC);
		return;
	}

	// I/O classes must be actively shut down
	if (theDebug->curType != 7)
		theDebug->Debug::FlushOutput(true);
	for (IOFactoryListEntry *io = theDebug->firstIOFactory; io; io = io->next)
		if (io->io)
		{
			io->io->Delete();
			io->io = 0;
		}

	DeleteCriticalSection(&g_bfmeCsDWC);
	if (theDebug->logErrorsToFile)
		ShellExecuteA(0, "open", "errors.txt", 0, 0, 1);
}

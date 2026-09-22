// cl: /DNDEBUG /MD /EHa /Oy-
//
// Debug::PostStaticInit, retail 0x0003A250 (962 bytes). BFME 1 has it only
// as a lift (b1 0x0088AF60).
//
// Zero Hour's body, with the BFME2 changes read from the retail bytes:
// - It runs once (static guard) and works on the theDebug singleton;
//   InstallExceptionHandler, AddIOFactory and AddCommands are virtuals
//   (Debug vtable slots 0x58, 0x80, 0x84).
// - The command file comes from the _EA_RTS_FILENAME environment variable,
//   else from a -dbgcmd:<file> command-line switch, else from the
//   executable's name; whichever it is gets its extension replaced (or
//   extended) by ".dbgcmd", and it is opened shared for reading.
// The default-command walk keeps Zero Hour's shape, including the endless
// loop on an empty line (DebugGetDefaultCommands returns NULL here anyway).

#include <string.h>

typedef void *HANDLE;
typedef unsigned long DWORD;

extern "C"
{
	__declspec(dllimport) DWORD __stdcall GetEnvironmentVariableA(const char *name, char *buffer,
		DWORD size);
	__declspec(dllimport) char *__stdcall GetCommandLineA(void);
	__declspec(dllimport) DWORD __stdcall GetModuleFileNameA(void *module, char *name, DWORD size);
	__declspec(dllimport) HANDLE __stdcall CreateFileA(const char *fileName, DWORD access,
		DWORD shareMode, void *security, DWORD disposition, DWORD flags, HANDLE templateFile);
	__declspec(dllimport) int __stdcall ReadFile(HANDLE file, void *buffer, DWORD bytes, DWORD *read,
		void *overlapped);
	__declspec(dllimport) int __stdcall CloseHandle(HANDLE handle);
	__declspec(dllimport) char *__cdecl strstr(const char *text, const char *pattern);
	__declspec(dllimport) char *__cdecl strchr(const char *text, int ch);
	__declspec(dllimport) char *__cdecl strrchr(const char *text, int ch);
	__declspec(dllimport) char *__cdecl strncpy(char *dest, const char *src, unsigned int count);
}

#include <new>      // placement new, as the debug library uses it

void *DebugAllocMemory(unsigned int numBytes);
const char *DebugGetDefaultCommands(void);

class DebugIOInterface
{
public:
	enum StringType { Assert, Check, Crash, Exception, Log, CmdReply, Other };
};

class DebugCmdInterface
{
public:
	virtual void Execute();
};

class DebugCmdInterfaceDebug : public DebugCmdInterface
{
public:
	DebugCmdInterfaceDebug();
};

class DebugIOCon
{
public:
	static DebugIOInterface *Create(void);
};

class DebugIOFlat
{
public:
	static DebugIOInterface *Create(void);
};

class DebugIONet
{
public:
	static DebugIOInterface *Create(void);
};

class DebugIOOds
{
public:
	static DebugIOInterface *Create(void);
};

class DebugStackwalk
{
public:
	static void *GetDbghelpHandle(void);
	static bool IsOldDbghelp(void);
};

class Debug
{
public:
	class RepeatChar
	{
		char m_char;
		int m_count;

	public:
		RepeatChar(char ch, int count) : m_char(ch), m_count(count) {}
	};

	// The stream writers form one overload group placed, in reverse
	// declaration order, from slot 0x04 to RepeatChar at 0x3C.
	virtual ~Debug();
	virtual Debug &operator<<(const RepeatChar &c);
	virtual Debug &operator<<(const char *str);
	virtual Debug &operator<<(int val);
	virtual Debug &operator<<(unsigned val);
	virtual Debug &operator<<(long val);
	virtual Debug &operator<<(unsigned long val);
	virtual Debug &operator<<(bool val);
	virtual Debug &operator<<(float val);
	virtual Debug &operator<<(double val);
	virtual Debug &operator<<(short val);
	virtual Debug &operator<<(unsigned short val);
	virtual Debug &operator<<(__int64 val);
	virtual Debug &operator<<(unsigned __int64 val);
	virtual Debug &operator<<(const void *ptr);
	virtual Debug &operator<<(const class MemDump &dump);
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void InstallExceptionHandler();                         // slot 0x58
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual bool AddIOFactory(const char *io_id, const char *descr,
		DebugIOInterface *(*func)(void));                       // slot 0x80
	virtual bool AddCommands(const char *cmdgroup, DebugCmdInterface *cmdif); // slot 0x84

private:
	static void PostStaticInit();

	virtual void StartOutput(DebugIOInterface::StringType type, const char *fmt, ...);
	virtual void FlushOutput(bool defaultLog);
	bool ExecCommand(const char *cmdstart, const char *cmdend);
};

extern Debug *theDebug;

// ?PostStaticInit@Debug@@CAXXZ
void Debug::PostStaticInit()
{
	static bool initialized;
	if (initialized)
		return;
	initialized = true;

	theDebug->InstallExceptionHandler();

	// register our default IO classes
	theDebug->AddIOFactory("con", "Console window", DebugIOCon::Create);
	theDebug->AddIOFactory("flat", "Flat local file(s)", DebugIOFlat::Create);
	theDebug->AddIOFactory("net", "Network via named pipe", DebugIONet::Create);
	theDebug->AddIOFactory("ods", "OutputDebugString function", DebugIOOds::Create);

	// add debug command handler
	theDebug->AddCommands("debug",
		new (DebugAllocMemory(sizeof(DebugCmdInterfaceDebug))) DebugCmdInterfaceDebug);

	/// exec dbgcmd file
	char ioBuffer[2048];
	if (!GetEnvironmentVariableA("_EA_RTS_FILENAME", ioBuffer, sizeof(ioBuffer)))
	{
		const char *commandLine = GetCommandLineA();
		const char *arg = strstr(commandLine, "-dbgcmd:");
		if (arg)
		{
			const char *end = strchr(arg, ' ');
			arg += 8;
			if (!end)
				end = arg + strlen(arg);
			strncpy(ioBuffer, arg, end - arg);
			ioBuffer[end - arg] = 0;
		}
		else
			GetModuleFileNameA(0, ioBuffer, sizeof(ioBuffer));
	}
	char *q = strrchr(ioBuffer, '.');
	if (q)
		strcpy(q, ".dbgcmd");
	else
		strcat(q, ".dbgcmd"); // sic: retail appends to the NULL pointer
	HANDLE h = CreateFileA(ioBuffer, 0x80000000, 1, 0, 3, 0x80, 0);
	if (h == (HANDLE)-1)
		h = CreateFileA("default.dbgcmd", 0x80000000, 1, 0, 3, 0x80, 0);
	if (h != (HANDLE)-1)
	{
		char cmdBuffer[512];
		unsigned long ioCur = 0, ioUsed = 0, cmdCur = 0;
		ReadFile(h, ioBuffer, sizeof(ioBuffer), &ioUsed, 0);
		for (;;)
		{
			if (ioCur == ioUsed)
			{
				ReadFile(h, ioBuffer, sizeof(ioBuffer), &ioUsed, 0);
				ioCur = 0;
			}
			if (ioCur == ioUsed || ioBuffer[ioCur] == '\n' || ioBuffer[ioCur] == '\r')
			{
				if (cmdCur)
				{
					theDebug->ExecCommand(cmdBuffer, cmdBuffer + cmdCur);
					cmdCur = 0;
				}
				if (ioCur == ioUsed)
					break;
				ioCur++;
			}
			else
			{
				if (cmdCur < sizeof(cmdBuffer))
					cmdBuffer[cmdCur++] = ioBuffer[ioCur];
				ioCur++;
			}
		}
		CloseHandle(h);
	}
	else
	{
		// exec default commands
		const char *p = DebugGetDefaultCommands();
		while (p && *p)
		{
			const char *q = strchr(p, '\n');
			if (!q)
				q = p + strlen(p);
			if (p != q)
			{
				theDebug->ExecCommand(p, q);
				p = *q ? q + 1 : 0;
			}
		}
	}

	// check: are we using an old dbghelp.dll?
	if (DebugStackwalk::IsOldDbghelp())
	{
		// give a serious hint
		theDebug->Debug::StartOutput(DebugIOInterface::Other, "");
		*theDebug << RepeatChar('=', 79) <<
			"\nYou are using an older version of the DBGHELP.DLL library.\n"
			"Please update to the newest available version in order to\n"
			"get reliable stack and symbol information.\n\n";

		char buf[256];
		GetModuleFileNameA(DebugStackwalk::GetDbghelpHandle(), buf, sizeof(buf));
		*theDebug <<
			"Hint: The DLL got loaded as:\n" << buf << "\n" << RepeatChar('=', 79) << "\n\n";

		// flush output only if there is already an active I/O class
		theDebug->Debug::FlushOutput(false);
	}
}

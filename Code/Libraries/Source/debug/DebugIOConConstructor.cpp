// cl: /DNDEBUG /MD /EHa /Oy-
// readable body of ??0DebugIOCon@@QAE@XZ: Code/Libraries/Source/debug/debug_io_con.cpp
//
// DebugIOCon::DebugIOCon, retail 0x00040C40 (466 bytes). Local class
// view as in DebugIOConDestructorThunk.cpp: the base vtable store and the
// EH frame come from the base class's virtual destructor.
//
// Zero Hour's constructor, with the BFME2 changes read from the retail
// bytes: the screen buffer is left alone; Ctrl-C, Ctrl-Break and the close
// event are swallowed; the console window is found through a temporary
// unique title ("CON@<this>") so its close button can be removed; the
// greeting goes straight to the output handle; and the console is titled
// "<executable> [debug console]".

typedef void *HANDLE;
typedef void *HWND;
typedef void *HMENU;
typedef unsigned long DWORD;
typedef int BOOL;

struct COORD
{
	short X;
	short Y;
};

struct SMALL_RECT
{
	short Left;
	short Top;
	short Right;
	short Bottom;
};

struct CONSOLE_SCREEN_BUFFER_INFO
{
	COORD dwSize;
	COORD dwCursorPosition;
	unsigned short wAttributes;
	SMALL_RECT srWindow;
	COORD dwMaximumWindowSize;
};

struct CONSOLE_CURSOR_INFO
{
	DWORD dwSize;
	BOOL bVisible;
};

extern "C"
{
	__declspec(dllimport) BOOL __stdcall AllocConsole(void);
	__declspec(dllimport) HANDLE __stdcall GetStdHandle(DWORD handle);
	__declspec(dllimport) BOOL __stdcall SetConsoleMode(HANDLE console, DWORD mode);
	__declspec(dllimport) BOOL __stdcall GetConsoleScreenBufferInfo(HANDLE console,
		CONSOLE_SCREEN_BUFFER_INFO *info);
	__declspec(dllimport) BOOL __stdcall SetConsoleCursorInfo(HANDLE console,
		const CONSOLE_CURSOR_INFO *info);
	__declspec(dllimport) BOOL __stdcall SetConsoleCtrlHandler(BOOL(__stdcall *handler)(DWORD),
		BOOL add);
	__declspec(dllimport) DWORD __stdcall GetConsoleTitleA(char *title, DWORD size);
	__declspec(dllimport) BOOL __stdcall SetConsoleTitleA(const char *title);
	__declspec(dllimport) void __stdcall Sleep(DWORD milliseconds);
	__declspec(dllimport) HWND __stdcall FindWindowA(const char *className, const char *windowName);
	__declspec(dllimport) HMENU __stdcall GetSystemMenu(HWND wnd, BOOL revert);
	__declspec(dllimport) BOOL __stdcall DeleteMenu(HMENU menu, unsigned int position,
		unsigned int flags);
	__declspec(dllimport) BOOL __stdcall DrawMenuBar(HWND wnd);
	__declspec(dllimport) BOOL __stdcall WriteFile(HANDLE file, const void *buffer, DWORD bytes,
		DWORD *written, void *overlapped);
	__declspec(dllimport) DWORD __stdcall GetModuleFileNameA(void *module, char *name, DWORD size);
	__declspec(dllimport) int __cdecl wsprintfA(char *out, const char *fmt, ...);
	__declspec(dllimport) char *__cdecl strrchr(const char *text, int ch);
	char *strcpy(char *dest, const char *src);
	char *strcat(char *dest, const char *src);
}

class DebugIOConBase
{
public:
	virtual ~DebugIOConBase() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal_io.h
class DebugIOCon : public DebugIOConBase
{
public:
	DebugIOCon();
	virtual ~DebugIOCon();

private:
	bool m_allocatedConsole;             // +0x04
	char m_input[256];                   // +0x08
	unsigned m_inputUsed;                // +0x108
	unsigned m_inputRead;                // +0x10C
};

// The console control handler at 0x00040830 (Bfme5FiftyOne.cpp, landed from
// a BFME 1 byte donor under that name): returns TRUE for Ctrl-C, Ctrl-Break
// and close so they cannot kill the game through the debug console.
int __stdcall bfmeIsBasic(int kind);

// ??0DebugIOCon@@QAE@XZ
DebugIOCon::DebugIOCon()
	: m_inputUsed(0), m_inputRead(0)
{
	// check: is there already a console window open?
	m_allocatedConsole = AllocConsole() != 0;
	if (m_allocatedConsole)
	{
		HANDLE h = GetStdHandle((DWORD)-10); // STD_INPUT_HANDLE
		SetConsoleMode(h, 0);

		h = GetStdHandle((DWORD)-11); // STD_OUTPUT_HANDLE
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(h, &info);

		// hide cursor
		CONSOLE_CURSOR_INFO ci;
		ci.dwSize = 1;
		ci.bVisible = 0;
		SetConsoleCursorInfo(h, &ci);

		SetConsoleCtrlHandler((BOOL(__stdcall *)(DWORD))bfmeIsBasic, 1);

		// find our console window by a unique title and remove its close button
		char oldTitle[100];
		GetConsoleTitleA(oldTitle, sizeof(oldTitle));
		char uniqueTitle[50];
		wsprintfA(uniqueTitle, "CON@%08x", this);
		SetConsoleTitleA(uniqueTitle);
		Sleep(40);
		HWND wnd = FindWindowA(0, uniqueTitle);
		if (wnd)
		{
			HMENU menu = GetSystemMenu(wnd, 0);
			DeleteMenu(menu, 0xF060, 0); // SC_CLOSE, MF_BYCOMMAND
			DrawMenuBar(wnd);
		}
		SetConsoleTitleA(oldTitle);

		DWORD written;
		WriteFile(GetStdHandle((DWORD)-11), "\n\nEA/Debug console open\n\n", 25, &written, 0);
	}

	// title the console after the executable
	char path[512];
	GetModuleFileNameA(0, path, sizeof(path));
	char *name = strrchr(path, '\\');
	name = name ? name + 1 : path;
	char title[512];
	strcpy(title, name);
	strcat(title, " [debug console]");
	SetConsoleTitleA(title);
}

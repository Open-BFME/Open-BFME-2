// cl: /DNDEBUG /MD
// ?initDbghelp@Rva006C4CD0Helper@@QAEXXZ
// retail 0x006C4CD0, 124 bytes. Dedicated TU.
//
// Opaque helper-class row: loads DbgHelp.dll once and resolves seven dbghelp
// entry points (SymInitialize, SymCleanup, StackWalk, SymFunctionTableAccess,
// SymGetModuleBase, SymGetSymFromAddr, SymGetLineFromAddr) into slots
// +8..+0x20, with the module handle at +0. Same-cluster callers at
// 0x6C4D8F/0x6C4FBC/0x6C5108; the cleanup sibling (~0x6C4D80) reads the flag
// at +4 and SymCleanup at +0xC before freeing the library. The true class
// name is unknown, so the RvaHelper name claims nothing beyond the address;
// the method name describes the proven behavior. Imports resolve by name
// (LoadLibraryA, GetProcAddress).

#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

typedef void *HMODULE;

extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *name);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *name);
extern "C" __declspec(dllimport) void *__stdcall GetCurrentProcess(void);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE module);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dst, const char *src, unsigned int n);

class Rva006C4CD0Helper
{
public:
	void initDbghelp(void);
	void uninitDbghelp(void);
	bool getSymbolName(unsigned long addr, char *buf, unsigned long maxlen);

	HMODULE m_hLib;			// +0x00
	unsigned char m_flag;		// +0x04 (byte-wide per retail mov al;
					// the 0x6C4D80 sibling stores it by byte)
	void *m_symInitialize;		// +0x08
	void *m_symCleanup;		// +0x0C
	void *m_stackWalk;		// +0x10
	void *m_symFunctionTableAccess;	// +0x14
	void *m_symGetModuleBase;	// +0x18
	void *m_symGetSymFromAddr;	// +0x1C
	void *m_symGetLineFromAddr;	// +0x20
};

// IMAGEHLP_SYMBOL prefix: only the header fields plus enough name bytes to
// make the 0x218 total the retail frame proves (4 displacement + 0x218).
struct DbgSymbolInfo
{
	unsigned long m_sizeOfStruct;	// +0x00
	unsigned long m_address;	// +0x04
	unsigned long m_size;		// +0x08
	unsigned long m_flags;		// +0x0C
	unsigned long m_maxNameLength;	// +0x10
	char m_name[0x204];		// +0x14
};

// ?initDbghelp@Rva006C4CD0Helper@@QAEXXZ
void Rva006C4CD0Helper::initDbghelp(void)
{
	if (m_hLib != NULL) {
		return;
	}
	m_hLib = LoadLibraryA("DbgHelp.dll");
	if (m_hLib == NULL) {
		return;
	}
	m_symInitialize = GetProcAddress(m_hLib, "SymInitialize");
	m_symCleanup = GetProcAddress(m_hLib, "SymCleanup");
	m_stackWalk = GetProcAddress(m_hLib, "StackWalk");
	m_symFunctionTableAccess = GetProcAddress(m_hLib, "SymFunctionTableAccess");
	m_symGetModuleBase = GetProcAddress(m_hLib, "SymGetModuleBase");
	m_symGetSymFromAddr = GetProcAddress(m_hLib, "SymGetSymFromAddr");
	m_symGetLineFromAddr = GetProcAddress(m_hLib, "SymGetLineFromAddr");
}

// ?uninitDbghelp@Rva006C4CD0Helper@@QAEXXZ
// retail 0x006C4D50, 43 bytes. Same TU: runs SymCleanup through the slot at
// +0xC when the flag at +4 says the table initialized, then frees the library.
void Rva006C4CD0Helper::uninitDbghelp(void)
{
	if (m_hLib == NULL) {
		return;
	}
	if (m_flag && m_symCleanup != NULL) {
		((int (__stdcall *)(void *))m_symCleanup)(GetCurrentProcess());
	}
	FreeLibrary(m_hLib);
}

// ?rva006C4E30@@YAXXZ
// retail 0x006C4E30, 27 bytes. Same TU: one-shot guard around initDbghelp;
// the first call through tail-jumps into initDbghelp on the TU-global
// helper object. Guard and object are adjacent in retail's image, so they
// are declared adjacently here.
static int g_rva006C4E30Guard = 0;
static Rva006C4CD0Helper g_rva006C4CD0Object;
void rva006C4E30(void)
{
	if (++g_rva006C4E30Guard == 1) {
		g_rva006C4CD0Object.initDbghelp();
	}
}

// ?rva006C4E50@@YAXXZ
// retail 0x006C4E50, 61 bytes. Same TU: guarded teardown twin of rva006C4E30;
// when the last user leaves it runs the SymCleanup slot, then frees the
// library. Mirrors uninitDbghelp's call shapes on the TU-global object.
void rva006C4E50(void)
{
	if (--g_rva006C4E30Guard != 0) {
		return;
	}
	if (g_rva006C4CD0Object.m_hLib == NULL) {
		return;
	}
	if (g_rva006C4CD0Object.m_flag && g_rva006C4CD0Object.m_symCleanup != NULL) {
		((int (__stdcall *)(void *))g_rva006C4CD0Object.m_symCleanup)(GetCurrentProcess());
	}
	FreeLibrary(g_rva006C4CD0Object.m_hLib);
}
// ?getSymbolName@Rva006C4CD0Helper@@QAE_NKPADK@Z
// retail 0x006C4D80, 167 bytes. Same TU: resolve an address to its symbol
// name through the slot at +0x1C, copying at most maxlen bytes into buf.
// SymInitialize runs once through the slot at +8 (flag at +4); the strncpy
// import resolves by name.
bool Rva006C4CD0Helper::getSymbolName(unsigned long addr, char *buf, unsigned long maxlen)
{
	if (m_hLib == NULL) {
		initDbghelp();
	}
	void *proc = GetCurrentProcess();
	if (!m_flag && m_symInitialize != NULL) {
		if (((int (__stdcall *)(void *, const char *, int))m_symInitialize)(proc, NULL, TRUE) != 0) {
			m_flag = 1;
		}
	}
	DbgSymbolInfo sym;
	sym.m_sizeOfStruct = 0x218;
	sym.m_maxNameLength = 0x200;
	unsigned long disp = 0;
	if (m_symGetSymFromAddr == NULL) {
		return false;
	}
	if (((int (__stdcall *)(void *, unsigned long, unsigned long *, DbgSymbolInfo *))m_symGetSymFromAddr)(proc, addr, &disp, &sym) != 0) {
		strncpy(buf, sym.m_name, maxlen);
		return true;
	}
	return false;
}

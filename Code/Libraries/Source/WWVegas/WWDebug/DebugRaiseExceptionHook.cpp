// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// C++-throw reporting through an import hook, retail 0x0003E1C0 (hook,
// 160 bytes) and 0x0003E260 (installer, 249 bytes). BFME 1 carries both
// byte for byte (b1 0x0088E8D0 / 0x0088E970) only as generated dumps.
//
// The installer finds kernel32's RaiseException, walks msvcrt.dll's import
// descriptors for the IAT slot holding it, keeps the original in
// g_originalRaiseException (0x00DE08D8) and patches the slot to the hook
// with a temporary read/write page protection. The walk is the classic
// Bugslayer HookImportedFunction shape, down to its "imports section?"
// test comparing the descriptor pointer against the NT headers.
//
// While the game runs windowed the hook reports every throw to
// DebugExceptionhandler::ExceptionFilter as a C++ exception (0xE06D7363)
// with a context holding the hook's own eip/ebp/esp, then forwards to the
// original. Those three registers can only be read with inline assembly;
// MSVC places the three locals by name, and these names give retail's slots.
// The saved pointer is called caller-cleaned (retail adds esp after it),
// so its type is spelled without __stdcall as in the original source.

typedef unsigned long DWORD;
typedef void *HMODULE;

struct EXCEPTION_RECORD
{
	DWORD ExceptionCode;
	DWORD ExceptionFlags;
	EXCEPTION_RECORD *ExceptionRecord;
	void *ExceptionAddress;
	DWORD NumberParameters;
	DWORD ExceptionInformation[15];
};

struct CONTEXT
{
	DWORD ContextFlags;
	DWORD Dr[6];
	unsigned char FloatSave[112];
	DWORD SegGs, SegFs, SegEs, SegDs;
	DWORD Edi, Esi, Ebx, Edx, Ecx, Eax;
	DWORD Ebp, Eip, SegCs, EFlags, Esp, SegSs;
	unsigned char ExtendedRegisters[512];
};

struct _EXCEPTION_POINTERS
{
	EXCEPTION_RECORD *ExceptionRecord;
	CONTEXT *ContextRecord;
};

struct MEMORY_BASIC_INFORMATION
{
	void *BaseAddress;
	void *AllocationBase;
	DWORD AllocationProtect;
	DWORD RegionSize;
	DWORD State;
	DWORD Protect;
	DWORD Type;
};

struct IMAGE_DOS_HEADER
{
	unsigned short e_magic;
	unsigned short e_pad[29];
	long e_lfanew;
};

struct IMAGE_DATA_DIRECTORY
{
	DWORD VirtualAddress;
	DWORD Size;
};

struct IMAGE_NT_HEADERS
{
	DWORD Signature;
	unsigned char FileHeader[20];
	unsigned char OptionalHeaderFields[96];
	IMAGE_DATA_DIRECTORY DataDirectory[16];
};

struct IMAGE_IMPORT_DESCRIPTOR
{
	DWORD OriginalFirstThunk;
	DWORD TimeDateStamp;
	DWORD ForwarderChain;
	DWORD Name;
	DWORD FirstThunk;
};

struct IMAGE_THUNK_DATA
{
	DWORD Function;
};

#define MakePtr(cast, ptr, addValue) (cast)((DWORD)(ptr) + (DWORD)(addValue))

extern "C"
{
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *procName);
	__declspec(dllimport) HMODULE __stdcall GetModuleHandleA(const char *moduleName);
	__declspec(dllimport) int __stdcall IsBadReadPtr(const void *ptr, unsigned int size);
	__declspec(dllimport) DWORD __stdcall VirtualQuery(const void *address,
		MEMORY_BASIC_INFORMATION *buffer, DWORD length);
	__declspec(dllimport) int __stdcall VirtualProtect(void *address, DWORD size,
		DWORD newProtect, DWORD *oldProtect);
	void *memset(void *dest, int value, unsigned int count);
}

class DebugExceptionhandler
{
public:
	static long __stdcall ExceptionFilter(_EXCEPTION_POINTERS *pExPtrs);
};

bool DebugIsWindowed();

typedef void (*RaiseExceptionProc)(DWORD code, DWORD flags, DWORD numArgs, const DWORD *args);

RaiseExceptionProc g_originalRaiseException;

// ?RaiseExceptionHook@@YGXKKKPBK@Z
void __stdcall RaiseExceptionHook(DWORD code, DWORD flags, DWORD numArgs, const DWORD *args)
{
	if (DebugIsWindowed())
	{
		EXCEPTION_RECORD record;
		memset(&record, 0, sizeof(record));
		record.ExceptionCode = 0xE06D7363;

		DWORD raiseEbp, raiseEip, raiseEsp;
		__asm
		{
		here:
			lea eax, here
			mov raiseEip, eax
			mov raiseEbp, ebp
			mov raiseEsp, esp
		}

		CONTEXT context;
		memset(&context, 0, sizeof(context));
		context.Eip = raiseEip;
		context.Ebp = raiseEbp;
		context.Esp = raiseEsp;

		_EXCEPTION_POINTERS pointers;
		pointers.ExceptionRecord = &record;
		pointers.ContextRecord = &context;
		DebugExceptionhandler::ExceptionFilter(&pointers);
	}
	g_originalRaiseException(code, flags, numArgs, args);
}

// ?InstallRaiseExceptionHook@@YA_NXZ
bool InstallRaiseExceptionHook()
{
	DWORD raiseException = (DWORD)GetProcAddress(LoadLibraryA("kernel32.dll"), "RaiseException");
	if (!raiseException)
		return false;

	HMODULE msvcrt = GetModuleHandleA("msvcrt.dll");
	if (IsBadReadPtr(msvcrt, 4))
		return false;

	IMAGE_DOS_HEADER *dosHeader = (IMAGE_DOS_HEADER *)msvcrt;
	if (dosHeader->e_magic != 0x5A4D)
		return false;

	IMAGE_NT_HEADERS *ntHeader = MakePtr(IMAGE_NT_HEADERS *, dosHeader, dosHeader->e_lfanew);
	if (ntHeader->Signature != 0x4550)
		return false;

	IMAGE_IMPORT_DESCRIPTOR *importDesc = MakePtr(IMAGE_IMPORT_DESCRIPTOR *, dosHeader,
		ntHeader->DataDirectory[1].VirtualAddress);
	if (importDesc == (IMAGE_IMPORT_DESCRIPTOR *)ntHeader)
		return false;

	for (; importDesc->Name; importDesc++)
	{
		IMAGE_THUNK_DATA *thunk = MakePtr(IMAGE_THUNK_DATA *, dosHeader, importDesc->FirstThunk);
		for (; thunk->Function; thunk++)
		{
			if (thunk->Function == raiseException)
			{
				g_originalRaiseException = (RaiseExceptionProc)raiseException;
				MEMORY_BASIC_INFORMATION info;
				VirtualQuery(thunk, &info, sizeof(info));

				DWORD protect = (info.Protect & ~0x22) | 4;
				DWORD oldProtect;
				VirtualProtect(thunk, 4, protect, &oldProtect);
				thunk->Function = (DWORD)RaiseExceptionHook;
				VirtualProtect(thunk, 4, oldProtect, &protect);
				return true;
			}
		}
	}
	return false;
}

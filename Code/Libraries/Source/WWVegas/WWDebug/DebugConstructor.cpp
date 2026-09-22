// cl: /DNDEBUG /MD /EHa /Oy-
//
// Debug::Debug, retail 0x00038440 (408 bytes). Called only from
// Debug::PreStaticInit (0x000385F0) on a DebugAllocMemory(0x9F68) block.
//
// Ported from Open-BFME-1 DebugConstructor_00889370.cpp (b1 0x00889370).
// BFME2 changes, all read from the retail bytes:
// - sizeof(Debug) grows from 0x9F5C to 0x9F68: the frame-delayed command
//   array (+0x9E08..+0x9E10) moves curCommandGroup to +0x9E14, a
//   "no stack walk" flag joins the output flags at +0x9E79, and the
//   assert-dialog flag (+0x9F64) follows mutex/thread id.
// - The no-stack-walk flag is raised when DebugIsDebuggerAttached()
//   (0x0003E3E0) reports a debugger.
// - The call BFME1 makes after SetUnhandledExceptionFilter is gone.
// - The "\\errors.txt" copy is the strcpy MSVC inlines as three dword
//   moves; "errors.txt" in the working directory is the fallback.

#include <string.h>

typedef void *HANDLE;

extern "C" __declspec(dllimport) HANDLE __stdcall CreateMutexA(void *, int, const char *);
extern "C" __declspec(dllimport) void *__stdcall SetUnhandledExceptionFilter(void *);
extern "C" __declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(
	void *, char *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall DeleteFileA(const char *);
extern "C" __declspec(dllimport) char *__cdecl strrchr(const char *, int);

class DebugExceptionhandler
{
public:
	static long __stdcall ExceptionFilter(struct _EXCEPTION_POINTERS *pExPtrs);
};

// Only Debug may construct its stack walker (private, as in debug_stack.h).
class DebugStackwalk
{
	friend class Debug;

	DebugStackwalk();
	~DebugStackwalk();
};

bool DebugIsDebuggerAttached();

struct DebugIoBuffer
{
	char *buffer;
	unsigned used;
	unsigned alloc;
	bool lastWasCR;
};

class Debug
{
public:
	virtual ~Debug();

private:
	Debug();

	struct FrameCommand
	{
		int frame;
		const char *command;
	};

	void *hrTranslators;                 // +0x04
	unsigned numHrTranslators;           // +0x08
	void *firstIOFactory;                // +0x0C
	void *firstCmdGroup;                 // +0x10
	unsigned curStackFrame;              // +0x14
	void *frameHash[10007];              // +0x18
	void *nextUnusedFrameHash;           // +0x9C74
	unsigned numAvailableFrameHash;      // +0x9C78
	int refCount;                        // +0x9C7C, PreStaticInit's counter
	void *firstLogGroup;                 // +0x9C80
	DebugIoBuffer ioBuffer[7];           // +0x9C84
	int curType;                         // +0x9CF4
	char curSource[256];                 // +0x9CF8
	int disableAssertsEtc;               // +0x9DF8
	void *curFrameEntry;                 // +0x9DFC
	void *firstPatternEntry;             // +0x9E00
	void *lastPatternEntry;              // +0x9E04
	FrameCommand *frameCommands;         // +0x9E08
	unsigned numFrameCommands;           // +0x9E0C
	unsigned frameCommandsAlloc;         // +0x9E10
	char curCommandGroup[100];           // +0x9E14
	bool alwaysFlush;                    // +0x9E78
	bool noStackWalk;                    // +0x9E79
	bool timeStamp;                      // +0x9E7A
	DebugStackwalk stackWalk;            // +0x9E7B
	char prefix[16];                     // +0x9E7C
	int radix;                           // +0x9E8C
	char version[64];                    // +0x9E90
	char internalVersion[64];            // +0x9ED0
	char buildDate[64];                  // +0x9F10
	int width;                           // +0x9F50
	char fillChar;                       // +0x9F54
	bool isWindowed;                     // +0x9F55
	bool field9F56;                      // +0x9F56
	bool logErrorsToFile;                // +0x9F57
	bool noAssertDialog;                 // +0x9F58
	HANDLE mutex;                        // +0x9F5C
	unsigned threadId;                   // +0x9F60
	bool inAssertDialog;                 // +0x9F64
};

// ??0Debug@@AAE@XZ
Debug::Debug()
	: stackWalk()
{
	curStackFrame = 0;
	hrTranslators = 0;
	numHrTranslators = 0;
	firstIOFactory = 0;
	firstCmdGroup = 0;
	memset(frameHash, 0, sizeof(frameHash));
	nextUnusedFrameHash = 0;
	numAvailableFrameHash = 0;
	firstLogGroup = 0;
	memset(ioBuffer, 0, sizeof(ioBuffer));
	curType = 7;
	curSource[0] = 0;
	disableAssertsEtc = 0;
	curFrameEntry = 0;
	firstPatternEntry = 0;
	lastPatternEntry = 0;
	curCommandGroup[0] = 0;
	alwaysFlush = false;
	noStackWalk = false;
	if (DebugIsDebuggerAttached())
		noStackWalk = true;
	timeStamp = false;
	radix = 10;
	fillChar = ' ';
	field9F56 = false;
	logErrorsToFile = false;
	noAssertDialog = false;
	isWindowed = false;
	refCount = 0;
	inAssertDialog = false;
	frameCommands = 0;
	frameCommandsAlloc = 0;
	numFrameCommands = 0;
	mutex = CreateMutexA(0, 0, 0);
	SetUnhandledExceptionFilter(DebugExceptionhandler::ExceptionFilter);

	char path[512];
	GetModuleFileNameA(0, path, sizeof(path));
	char *slash = strrchr(path, '\\');
	const char *errorLog;
	if (slash)
	{
		strcpy(slash, "\\errors.txt");
		errorLog = path;
	}
	else
		errorLog = "errors.txt";
	DeleteFileA(errorLog);
}

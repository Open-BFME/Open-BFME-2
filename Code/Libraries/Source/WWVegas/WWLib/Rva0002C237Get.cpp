// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// ?Rva0002C237Get@@YAXPAVINI@@@Z @0x0002C237 144B: GetCurrentDirectoryA + INI::rva0002BFE5 filename + rva0002BBDE line + AsciiString::format into local.
#include "ascii_string.h"

extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentDirectoryA(unsigned long nBufferLength, char *lpBuffer);

// Retail's own 92-byte literal at RVA 0x007BDC80 (.rdata, file offset
// 0x007BD8C0): the INI error banner the rowed body below formats into the
// destination with the current directory, the block name and the line number.
// The three conversion specifications are %s (directory), %s (block) and %d
// (line), and the 92-byte extent including the terminating NUL is the ledger's
// own bound, ending exactly where retail's next literal begins.
// Symbol ?g_00BBDC80@@3QBDB, transcribed below.
extern const char g_00BBDC80[] =
	"\nINI ERROR:\n"
	"===================================================================\n"
	"\n%s\\%s(%d):\n";

class INI
{
public:
	int rva0002BBDE(void) const;
	AsciiString rva0002BFE5(void) const;
};

void __cdecl Rva0002C237Get(INI *ini)
{
	char curdir[260];
	GetCurrentDirectoryA(260, curdir);
	AsciiString dest;
	dest.format(g_00BBDC80, curdir, ini->rva0002BFE5().str(), ini->rva0002BBDE());
}

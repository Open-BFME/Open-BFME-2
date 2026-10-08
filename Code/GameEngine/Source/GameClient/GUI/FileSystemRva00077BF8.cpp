// cl: /Ireference/shims/bfme2_ascii /MD
// Candidate identity ?getFileInfo@FileSystem@@QBE_NABVAsciiString@@PAUFileInfo@@@Z
// @0x00077BF8 33B. The 0x77D0F caller loads TheFileSystem into ECX and passes
// an AsciiString plus its FileInfo output. The target body extracts the string
// and forwards both arguments to the BFME2 path resolver at 0x00600E3A.
#include "ascii_string.h"
struct FileInfo;
class FileSystem
{
public:
	bool getFileInfo(const AsciiString &filename, FileInfo *fileInfo) const;
};

bool __stdcall Rva00600E3AGet(const char *a, const char *b);
bool FileSystem::getFileInfo(const AsciiString &a, FileInfo *b) const
{
	return Rva00600E3AGet(a.str(), (const char *)b);
}

// Three 17-byte shape twins (push 0x00BC668C; call [OutputDebugStringA IAT];
// mov eax, imm32; ret). Retail's imm32 is a VA of code, the continuation of
// the catch that these funclets end, so each returns that address. Parents
// are not recovered; names are address-derived.
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA( const char *text );

int Rva00077CFE()
{
	OutputDebugStringA( "Error opening file \n" );
	return 0x00477CE6;
}

int Rva00077DF4()
{
	OutputDebugStringA( "Error opening file \n" );
	return 0x00477DDC;
}

int Rva00077F5E()
{
	OutputDebugStringA( "Error opening file \n" );
	return 0x00477E53;
}

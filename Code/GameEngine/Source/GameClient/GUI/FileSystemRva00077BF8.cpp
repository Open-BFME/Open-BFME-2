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

// cl: /Ireference/shims/bfme2_ascii /MD
// Candidate identity ?getFileInfo@FileSystem@@QBE_NABVAsciiString@@PAUFileInfo@@@Z
// @0x00077BF8 33B. The 0x77D0F caller loads TheFileSystem into ECX and passes
// an AsciiString plus its FileInfo output. The target body extracts the string
// and forwards both arguments, ECX unchanged, to the const char * overload at
// 0x00600E3A.
#include "ascii_string.h"
struct FileInfo;
#include "../../../Include/Common/FileSystem.h"

bool FileSystem::getFileInfo(const AsciiString &a, FileInfo *b) const
{
	return getFileInfo(a.str(), b);
}

// The 17-byte catch at 0x00077CFE is Rva00077C19Load's own catch(...) block
// (W3DShaderManager.cpp), rowed with its parent.

// cl: /Ireference/shims/bfme2_ascii /MD
// ?openFile@@YAPAVFile@@PBVAsciiString@@@Z @0x000A9F48 61B
// Free file-open helper: AsciiString m_data ? m_data+8 : empty, then loop
// TheFileSystem->openFile(s,1,0) stripping leading path via strchr(s,'\\').
// Evidence: callers 0x000AA557 (AsciiString+".apt") and 0x000AB96D pass string
// object in eax (mov eax,[eax]; lea esi,[eax+8]); empty global
// g_Rva0107301CEmptyString; IAT strchr; rowed openFile 0x00600C34.
#include "ascii_string.h"

class File;
class FileSystem
{
public:
	File *openFile(const char *filename, int access, int unk);
};
extern FileSystem *TheFileSystem;
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *, int);

static File *openFile(const AsciiString *fname)
{
	char *t = *(char * const *)fname;
	const char *s = t ? t + 8 : "";
	for (;;) {
		File *f = TheFileSystem->openFile(s, 1, 0);
		if (f)
			return f;
		s = strchr(s, '\\');
		if (!s)
			return 0;
		++s;
	}
}

// absent-from-retail: keeps the static alive with the EAX argument convention.
File *Rva000A9F48GetCaller(const AsciiString *fname)
{
	if (fname)
		return openFile(fname);
	return 0;
}

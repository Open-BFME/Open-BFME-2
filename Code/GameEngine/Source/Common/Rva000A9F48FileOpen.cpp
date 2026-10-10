// cl: /Ireference/shims/bfme2_ascii /MD /O1 /G7 /arch:SSE /EHsc
// ?openFile@@YAPAVFile@@PBVAsciiString@@@Z @0x000A9F48 61B
// Free file-open helper: AsciiString m_data ? m_data+8 : empty, then loop
// TheFileSystem->openFile(s,1,0) stripping leading path via strchr(s,'\\').
// Evidence: callers 0x000AA557 (AsciiString+".apt") and 0x000AB96D pass string
// object in eax (mov eax,[eax]; lea esi,[eax+8]); empty global
// g_Rva0107301CEmptyString; IAT strchr; rowed openFile 0x00600C34.
#include "ascii_string.h"

// File virtual slot34 is readEntireAndClose: the matched RAMFile provider
// at605682 independently proves the char* result and slot13. NativeAA557
// saves that entire-file buffer at owner+4.
class File {public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();
 virtual char *readEntireAndClose();
};
class FileSystem
{
public:
	File *openFile(const char *filename, int access, int unk);
};
extern FileSystem *TheFileSystem;
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *, int);

static __declspec(noinline) File *openFile(const AsciiString *fname)
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


// NativeAA557..AA5B2 RET0: construct name+".apt", open with the private
// EAX-argument61B helper, read the entire buffer through virtual34 and store at owner+4.
// Owned AB910 ctor independently proves the AsciiString0/word4 prefix;
// the rest of the owner (including its two hash maps) is not accessed here.
class Rva000AB910 {public:
 AsciiString name; char *data;
 void rva000AA557();
};
void Rva000AB910::rva000AA557(){
 AsciiString path(name);path.concat(".apt");
 File *input=openFile(&path);
 data=input?input->readEntireAndClose():0;
}

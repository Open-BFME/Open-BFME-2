// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /Ob0
// Native AB96D..ABA2F; WB8A63F0 w3dLoadAnimation lead.
// The nonthrowing loader contract retains outgoing ESP bookkeeping without
// an EH frame. See reverse/attempt_support/animation-loader-ab96d-20261019.md.
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"

// File virtual slot34 is readEntireAndClose: the matched RAMFile provider
// at605682 independently proves the char* result and slot13. NativeAA557
// saves that entire-file buffer at owner+4.
#include "../../Include/Common/File.h"
#include "../../Include/Common/FileSystem.h"
extern FileSystem *TheFileSystem;
#include <string.h>

// Native DAT temporary is destroyed without an extra unwind state; the
// already-owned render-data parser also carries this helper exception contract.
static __declspec(noinline) __declspec(nothrow) File *openFile(const AsciiString *fname)
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
class Rva000AB910 {
public:
    Rva000AB910(const AsciiString &);
    AsciiString name;
    char *data;
    char remainingMaps[0x28];
    void rva000AB956();
};

#include "../../Include/Common/BfmeRefVGO.h"
void Rva00893030(BfmeRefVGO, void *, void *, void *);
int g_aptConstResetState0 = 0;
int g_aptConstResetState1 = 0;
void Rva000AB96DLoadAnimation(const char *name, BfmeRefVGO value) throw()
{
    Rva000AB910 *owner = new Rva000AB910(name);
    owner->rva000AB956();
    AsciiString path;
    path.format("%s.const", name);
    File *file = openFile(&path);
    char *constants = file ? file->readEntireAndClose() : 0;
    g_aptConstResetState0 = -1;
    g_aptConstResetState1 = -1;
    char *data = owner->data;
    Rva00893030(value, data, constants, owner);
}

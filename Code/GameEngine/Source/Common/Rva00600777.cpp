// cl: /MD
// ?Rva00600777Set@@YAXPAD@Z @0x00600777 46B free cdecl copy into TheLangDir.
// Retail push esi; push arg; mov esi TheLangDir; push esi; call _mbscpy;
// pop ecx twice; mov ecx G00A06E54; push 1; push "*.BIG"; store
// BFME2PreferLocalFiles=1; mov eax [ecx]; push esi; call [eax+0x20].
// Evidence: caller 0x003BA046 push eax call pop ecx (cdecl 1 arg);
// extern names in use TheLangDir BFME2PreferLocalFiles G00A06E54; "*.BIG" literal.
extern char TheLangDir[];
extern bool BFME2PreferLocalFiles;

class Rva0060061AHelper
{
public:
	virtual void *v0(int a1);
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8(char *a1, const char *a2, int a3);
};

extern class LocalFileSystem *TheLocalFileSystem;
extern "C" char *__cdecl _mbscpy(char *dst, const char *src);

void __cdecl Rva00600777Set(char *src)
{
	_mbscpy(TheLangDir, src);
	BFME2PreferLocalFiles = true;
	(*(Rva0060061AHelper **)&TheLocalFileSystem)->v8(TheLangDir, "*.BIG", 1);
}

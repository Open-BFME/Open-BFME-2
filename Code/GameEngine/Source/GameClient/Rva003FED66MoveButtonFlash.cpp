// cl: /DNDEBUG /MD
//
// ?Rva003FED66MoveButtonFlash@@YAXPAPAXMM@Z @0x003FED66 117B. Free __cdecl UI
// firer (same pattern as UiCallbackFirers.cpp): formats two floats with "%g"
// via rowed _snprintf into 16B stack buffers, selects the label from *(pp)
// (+8) or the rowed empty string, and invokes MoveButtonFlash with (3, s,
// buf1, buf2, 0, 0) through the pinned target/owner. Evidence: caller
// 0x005C65D0 pushes (ptr, float, float) __cdecl; IAT snprintf cached in esi;
// literals link; invoke declared to the landed UiCallbackFirers shape.
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *fmt, ...);


class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
// 0x00DC1A0C, the owner setUiCallbackOwner stores (UiCallbackFirers.cpp); the
// tooltip firers read a different global at 0x00DC06A0.
extern void *TheRva009C1A0COwner;

void __cdecl Rva003FED66MoveButtonFlash(void **pp, float f1, float f2)
{
	char buf1[16];
	char buf2[16];
	_snprintf(buf1, 16, "%g", f1);
	_snprintf(buf2, 16, "%g", f2);
	void *p = *pp;
	const char *s;
	if (p)
		s = (const char *)p + 8;
	else
		s = "";
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "MoveButtonFlash", 3, s, buf1, buf2, 0, 0);
}

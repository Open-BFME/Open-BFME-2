// cl: /MD
// ?Rva002B29BDFire@@YAXXZ, retail 0x002B29BD, 27 bytes.
// Fires HideEndGame UI callback through the global target: invoke with
// owner (void*)13, name "HideEndGame", rest 0. Same recipe as the landed
// UiCallbackFirers. Callers at 0x002B8922 0x002B99F3. Honest address name.
class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};
// The slot at VA 0x00DFE4CC is the Apt window manager pointer, defined as
// g_bfmeAptWindowManager in Rva005832D0MapName.cpp; this TU's facade name for
// the same object binds to that definition rather than defining it twice.
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
#pragma comment(linker, "/alternatename:?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
void __cdecl Rva002B29BDFire()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke((void *)13, "HideEndGame", 0, 0, 0, 0, 0, 0);
}

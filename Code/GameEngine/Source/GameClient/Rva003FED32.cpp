// cl: /DNDEBUG /MD
//
// ?Rva003FED32DeleteButtonFlash@@YAXPAPAX@Z @0x003FED32 52B. Free __cdecl UI
// firer (same pattern as Rva003FECFECreateButtonFlash): selects the label from
// *(pp) (+8) or the empty string, and invokes DeleteButtonFlash with (1, s,
// 0, 0, 0, 0) through the rowed target/owner. Evidence: caller 0x005C66CB;
// literals link; invoke declared to the landed UiCallbackFirers shape.
class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;
// Native DIR32 at body+0x2A reads VA 0x00DC1A0C, the owner defined
// by UiCallbackFirers.cpp; tooltip callbacks use VA 0x00DC06A0.
extern void *TheRva009C1A0COwner;

void __cdecl Rva003FED32DeleteButtonFlash(void **pp)
{
	void *p = *pp;
	const char *s;
	if (p)
		s = (const char *)p + 8;
	else
		s = "";
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "DeleteButtonFlash", 1, s, 0, 0, 0, 0);
}

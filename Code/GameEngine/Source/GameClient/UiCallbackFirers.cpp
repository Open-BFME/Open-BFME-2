// cl: /DNDEBUG /MD /O1
// BFME1 Q2NamedScriptCallbacks.cpp donor pattern: free functions firing one
// named UI callback with one string argument through a global target and a
// global owner. Retail passes (owner, callback, 1, arg, 0, 0, 0, 0) with the
// target in ecx; the BFME1 donor has owner and target swapped.

class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern void *TheRva00222A8BOwner;

void showMovieButton()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "SetMovieButtonState", 1, "_show", 0, 0, 0, 0);
}

void hideMovieButton()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "SetMovieButtonState", 1, "_hide", 0, 0, 0, 0);
}

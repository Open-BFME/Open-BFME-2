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

void setUiCallbackOwner(void *owner)
{
	TheRva00222A8BOwner = owner;
}

void showMovieButton()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "SetMovieButtonState", 1, "_show", 0, 0, 0, 0);
}

void hideMovieButton()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "SetMovieButtonState", 1, "_hide", 0, 0, 0, 0);
}

void fadePalantirButtonsZero()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "FadePalantirButtons", 1, "0", 0, 0, 0, 0);
}

void fadePalantirButtonsOne()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "FadePalantirButtons", 1, "1", 0, 0, 0, 0);
}

void showObserverStuff()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "SetObserverStuffState", 1, "_show", 0, 0, 0, 0);
}

void hideObserverStuff()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "SetObserverStuffState", 1, "_hide", 0, 0, 0, 0);
}

void setResourceIconState(bool show)
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "SetResourceIconState", 1, show ? "_show" : "_hide", 0, 0, 0, 0);
}

void setFlashObjectivesButton(bool show)
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "FlashObjectivesButton", 1, show ? "_show" : "_hide", 0, 0, 0, 0);
}

void enablePlayerMagicButton(bool enable)
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "EnablePlayerMagicButton", 1, enable ? "1" : "0", 0, 0, 0, 0);
}

void highlightPlayerMagicButton(bool highlight)
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "HighlightPlayerMagicButton", 1, highlight ? "1" : "0", 0, 0, 0, 0);
}

void setPlayerButtonsState(bool ring)
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "SetPlayerButtonsState", 1, ring ? "_ring" : "_evenstar", 0, 0, 0, 0);
}

class Rva002D3627Host
{
	char m_pad[0x10];

public:
	bool check();
};

extern Rva002D3627Host *TheRva002D3627Host;

void setHideScroll()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "HideScroll", 1, TheRva002D3627Host->check() ? "0" : "1", 0, 0, 0, 0);
}

void hideSpellBook()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "HideSpellBook", 0, 0, 0, 0, 0, 0);
}

void playCommandPointEffect()
{
	TheRva00222A8BTarget->invoke(TheRva00222A8BOwner, "PlayCommandPointEffect", 0, 0, 0, 0, 0, 0);
}

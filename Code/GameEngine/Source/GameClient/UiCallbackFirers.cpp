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
// Retail writes THIS global at absolute 0x00DC1A0C (RVA 0x9C1A0C) -- see
// setUiCallbackOwner at 0x3FE881, `mov ds:0xdc1a0c,eax`, and all twenty rows in
// this file encode that address. The tooltip firers in TooltipMove/TooltipHide
// read a DIFFERENT global at absolute 0x00DC06A0 (RVA 0x9C06A0), which is what
// their own comments record. The two are not the same object, so this one
// carries its own address-derived name; sharing one name made
// verify_dir32_consistency fail with bases ['0xdc06a0', '0xdc1a0c'].
extern void *TheRva009C1A0COwner;

void setUiCallbackOwner(void *owner)
{
	TheRva009C1A0COwner = owner;
}

void showMovieButton()
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "SetMovieButtonState", 1, "_show", 0, 0, 0, 0);
}

void hideMovieButton()
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "SetMovieButtonState", 1, "_hide", 0, 0, 0, 0);
}

void fadePalantirButtonsZero()
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "FadePalantirButtons", 1, "0", 0, 0, 0, 0);
}

void fadePalantirButtonsOne()
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "FadePalantirButtons", 1, "1", 0, 0, 0, 0);
}

void showObserverStuff()
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "SetObserverStuffState", 1, "_show", 0, 0, 0, 0);
}

void hideObserverStuff()
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "SetObserverStuffState", 1, "_hide", 0, 0, 0, 0);
}

void setResourceIconState(bool show)
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "SetResourceIconState", 1, show ? "_show" : "_hide", 0, 0, 0, 0);
}

void setFlashObjectivesButton(bool show)
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "FlashObjectivesButton", 1, show ? "_show" : "_hide", 0, 0, 0, 0);
}

void enablePlayerMagicButton(bool enable)
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "EnablePlayerMagicButton", 1, enable ? "1" : "0", 0, 0, 0, 0);
}

void highlightPlayerMagicButton(bool highlight)
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "HighlightPlayerMagicButton", 1, highlight ? "1" : "0", 0, 0, 0, 0);
}

void setPlayerButtonsState(bool ring)
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "SetPlayerButtonsState", 1, ring ? "_ring" : "_evenstar", 0, 0, 0, 0);
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
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "HideScroll", 1, TheRva002D3627Host->check() ? "0" : "1", 0, 0, 0, 0);
}

void hideSpellBook()
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "HideSpellBook", 0, 0, 0, 0, 0, 0);
}

void playCommandPointEffect()
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "PlayCommandPointEffect", 0, 0, 0, 0, 0, 0);
}

void playPlayerSpellPointEffect()
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "PlayPlayerSpellPointEffect", 0, 0, 0, 0, 0, 0);
}

void playPlayerLevelUpEffect()
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "PlayPlayerLevelUpEffect", 0, 0, 0, 0, 0, 0);
}

static const char * const PalantirFrameStates[] = {"_hide", "_good", "_goodSingle", "_evil", "_evilSingle"};

void setPalantirFrameState(int state)
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "SetPalantirFrameState", 1, PalantirFrameStates[state], 0, 0, 0, 0);
}

void setPlayerPowerCapState(bool ring)
{
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "SetPlayerPowerCapState", 1, ring ? "_ring" : "_evenstar", 0, 0, 0, 0);
}

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

void setPlayerMagicProgress(int progress)
{
	if (progress < 1 && progress > 100)
		return;
	sprintf((char *)&progress, "%d", progress);
	TheRva00222A8BTarget->invoke(TheRva009C1A0COwner, "SetPlayerMagicProgress", 1, (char *)&progress, 0, 0, 0, 0);
}

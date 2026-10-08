// cl: /DNDEBUG /MD
// BFME1 Q2NamedScriptCallbacks.cpp donor pattern: free functions firing one
// named UI callback with one string argument through a global target and a
// global owner. Retail passes (owner, callback, 1, arg, 0, 0, 0, 0) with the
// target in ecx; the BFME1 donor has owner and target swapped.

class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
// Retail writes THIS global at absolute 0x00DC1A0C (RVA 0x9C1A0C) -- see
// setUiCallbackOwner at 0x3FE881, `mov ds:0xdc1a0c,eax`, and all twenty rows in
// this file encode that address. The tooltip firers in TooltipMove/TooltipHide
// read a DIFFERENT global at absolute 0x00DC06A0 (RVA 0x9C06A0), which is what
// their own comments record. The two are not the same object, so this one
// carries its own address-derived name; sharing one name made
// verify_dir32_consistency fail with bases ['0xdc06a0', '0xdc1a0c'].
// TheRva009C1A0COwner: VA 0xdc1a0c (.data); retail's initial value is -1.
void *TheRva009C1A0COwner = (void *)-1;

void setUiCallbackOwner(void *owner)
{
	TheRva009C1A0COwner = owner;
}

void showMovieButton()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "SetMovieButtonState", 1, "_show", 0, 0, 0, 0);
}

void hideMovieButton()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "SetMovieButtonState", 1, "_hide", 0, 0, 0, 0);
}

void fadePalantirButtonsZero()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "FadePalantirButtons", 1, "0", 0, 0, 0, 0);
}

void fadePalantirButtonsOne()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "FadePalantirButtons", 1, "1", 0, 0, 0, 0);
}

void showObserverStuff()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "SetObserverStuffState", 1, "_show", 0, 0, 0, 0);
}

void hideObserverStuff()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "SetObserverStuffState", 1, "_hide", 0, 0, 0, 0);
}

void setResourceIconState(bool show)
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "SetResourceIconState", 1, show ? "_show" : "_hide", 0, 0, 0, 0);
}

void setFlashObjectivesButton(bool show)
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "FlashObjectivesButton", 1, show ? "_show" : "_hide", 0, 0, 0, 0);
}

void enablePlayerMagicButton(bool enable)
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "EnablePlayerMagicButton", 1, enable ? "1" : "0", 0, 0, 0, 0);
}

void highlightPlayerMagicButton(bool highlight)
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "HighlightPlayerMagicButton", 1, highlight ? "1" : "0", 0, 0, 0, 0);
}

void setPlayerButtonsState(bool ring)
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "SetPlayerButtonsState", 1, ring ? "_ring" : "_evenstar", 0, 0, 0, 0);
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
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "HideScroll", 1, TheRva002D3627Host->check() ? "0" : "1", 0, 0, 0, 0);
}

void hideSpellBook()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "HideSpellBook", 0, 0, 0, 0, 0, 0);
}

void playCommandPointEffect()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "PlayCommandPointEffect", 0, 0, 0, 0, 0, 0);
}

void playPlayerSpellPointEffect()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "PlayPlayerSpellPointEffect", 0, 0, 0, 0, 0, 0);
}

void playPlayerLevelUpEffect()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "PlayPlayerLevelUpEffect", 0, 0, 0, 0, 0, 0);
}

static const char * const PalantirFrameStates[] = {"_hide", "_good", "_goodSingle", "_evil", "_evilSingle"};

void setPalantirFrameState(int state)
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "SetPalantirFrameState", 1, PalantirFrameStates[state], 0, 0, 0, 0);
}

void setPlayerPowerCapState(bool ring)
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "SetPlayerPowerCapState", 1, ring ? "_ring" : "_evenstar", 0, 0, 0, 0);
}

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

void setPlayerMagicProgress(int progress)
{
	if (progress < 1 && progress > 100)
		return;
	sprintf((char *)&progress, "%d", progress);
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva009C1A0COwner, "SetPlayerMagicProgress", 1, (char *)&progress, 0, 0, 0, 0);
}

// ?TheRva002D3627Host@@3PAVRva002D3627Host@@A: matched references place it at VA 0xdff028; also referenced as ?theRadarWindowOverrideSource@@3PAVRadarWindowOverrideSource@@A.
Rva002D3627Host * TheRva002D3627Host = 0;
#pragma comment(linker, "/alternatename:?theRadarWindowOverrideSource@@3PAVRadarWindowOverrideSource@@A=?TheRva002D3627Host@@3PAVRva002D3627Host@@A")

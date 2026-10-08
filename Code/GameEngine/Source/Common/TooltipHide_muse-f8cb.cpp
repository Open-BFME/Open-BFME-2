// cl: /DNDEBUG /MD
// ?Rva003807B7Hide@@YAXXZ @ 0x003807B7 (60B): HideToolTip firer plus tooltip DisplayString free.
// Retail fires "HideToolTip" through Rva00222A8BTarget invoker with owner in ecx pattern
// matching Code/GameEngine/Source/GameClient/UiCallbackFirers.cpp hideSpellBook (6x push 0
// plus name plus owner). Then frees global DisplayString at 0x00A022E4 through
// DisplayStringManager slot 0x3c (new at 0x38 per WinInstanceDataDisplayStrings) and clears it.
// Callers 0x001EE618 0x001EEC73 0x001EF276 0x00380902; unblocks 0x003808F0 0x001EEC4B 0x001EE5EE.
// String "HideToolTip" at 0x00818EE4 proves Hide verb; free-function honest-address name.
class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
// TheRva00222A8BOwner: VA 0x00DC06A0 (.data), retail initial value -1.
void *TheRva00222A8BOwner = (void *)-1;

class DisplayString;

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager() {}
	virtual void s04() = 0;
	virtual void s08() = 0;
	virtual void s0C() = 0;
	virtual void s10() = 0;
	virtual void s14() = 0;
	virtual void s18() = 0;
	virtual void s1C() = 0;
	virtual void s20() = 0;
	virtual void s24() = 0;
	virtual void s28() = 0;
	virtual void s2C() = 0;
	virtual void s30() = 0;
	virtual void s34() = 0;
	virtual DisplayString *newDisplayString() = 0;
	virtual void freeDisplayString(DisplayString *s) = 0;
};

extern DisplayStringManager *TheDisplayStringManager;
extern DisplayString *TheTooltipString;
// TheTooltipString: matched references place it at VA 0xe022e4 (zero-filled .bss).
DisplayString * TheTooltipString;

void Rva003807B7Hide()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva00222A8BOwner, "HideToolTip", 0, 0, 0, 0, 0, 0);
	if (TheTooltipString != 0)
	{
		TheDisplayStringManager->freeDisplayString(TheTooltipString);
		TheTooltipString = 0;
	}
}

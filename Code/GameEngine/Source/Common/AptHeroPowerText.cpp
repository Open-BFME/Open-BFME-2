// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// Hero power panel texts. Each builds a UnicodeString through a formatter
// and hands it to the rowed bfmeSetText. Both formatters return a
// UnicodeString by value through a hidden pointer; 0x005B2376 and
// 0x005B2446 are defined below.
//
// ?Rva005B23D7HeroPowersDescription@@YAXPAXHABVAsciiString@@@Z @0x005B23D7 111B
//   APT:HeroPowersDescription with the description text
// ?Rva005B24CDHeroPowerText@@YAXPAXPBDH@Z                      @0x005B24CD 114B
//   APT:%s_%d keyed by the prefix and the 1-based index
// Names are address-derived; the keys are the retail strings.
#include <stdio.h>
#include "ascii_string.h"
#include "unicode_string.h"

#ifndef NULL
#define NULL 0
#endif

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &value, bool b);
};

class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;

UnicodeString __cdecl Rva005B2376Describe(void *power, int unused, const AsciiString &fallback);
UnicodeString __cdecl Rva005B2446Describe(void *power);

void __cdecl Rva005B23D7HeroPowersDescription(void *power, int unused, const AsciiString &fallback)
{
	UnicodeString text = Rva005B2376Describe(power, unused, fallback);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(AsciiString("APT:HeroPowersDescription"), text, true);
}

void __cdecl Rva005B24CDHeroPowerText(void *power, const char *prefix, int index)
{
	AsciiString key;
	key.format("APT:%s_%d", prefix, index + 1);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, Rva005B2446Describe(power), false);
}

// ?rva005B2295@@YA_NPBVCommandButton@@PBDHH@Z @0x005B2295 225B: points the
// Apt image key "%s_%d" (or "%s_%d_%d" for a page >= 0; both 1-based) at the
// button's image, falling back to CircleRed_42x42, and returns whether the
// key changed; with no button the key is cleared. Callers: the level labeller
// AptMyHero::rva005B0416 and the AptCreateAHero power panel. WorldBuilder's
// twin 0x0157F330 is unnamed; the name is address-derived.
class Image;
class CommandButton
{
public:
	const Image *rva0035B19E() const;
	const AsciiString &rva0035B26F() const;
};
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;
class Rva00223A9F
{
public:
	void *rva00223A9F(const AsciiString *key);
};
class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *key);
};
class Rva002239B2
{
public:
	void rva002239E2(const AsciiString &key, const Image *image);
};

bool __cdecl rva005B2295(const CommandButton *button, const char *prefix, int index, int page)
{
	AsciiString key;
	++index;
	if (page >= 0)
		key.format("%s_%d_%d", prefix, index, ++page);
	else
		key.format("%s_%d", prefix, index);
	bool changed = false;
	if (button != NULL)
	{
		const Image *image = button->rva0035B19E();
		if (image == NULL)
			image = TheMappedImageCollection->findImageByName(AsciiString("CircleRed_42x42"));
		if (((Rva00223A9F *)TheRva00222A8BTarget)->rva00223A9F(&key) != image)
		{
			((Rva002239B2 *)TheRva00222A8BTarget)->rva002239E2(key, image);
			changed = true;
		}
	}
	else
	{
		((Rva00223A94 *)TheRva00222A8BTarget)->rva00223A94(&key);
		changed = true;
	}
	return changed;
}

// ?rva005B9378@Rva005B9378@@QAEXHABVUnicodeString@@@Z @0x005B9378 178B: one
// ticker row. The field text is the game-text label for the row's entry in
// the label table at VA 0x00DD3B90, fetched through TheGameText's
// fetch(const char *, bool *) (slot 0x3C), with L":" appended. It is set under
// APT:TickerField_%d, then the caller's value under APT:TickerValue_%d. Callers
// (0x005B945D and four more) pass this in ecx, which the body never reads.
class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	// ZH's two fetch overloads; MSVC 7.1 lays an overload set out in reverse
	// declaration order, so the AsciiString one lands at 0x38.
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
	virtual const UnicodeString *fetchFormat(const AsciiString &label, int a) = 0;
};

extern GameTextInterface *TheGameText;

// ?Rva005B2376Describe@@YA?AVUnicodeString@@PAXHABVAsciiString@@@Z @0x005B2376
// 97B: the game text for the button's current description label (rowed
// CommandButton getter 0x0035B26F), else for the caller's fallback label,
// else L" ". The early push of 0 is fetch's exists argument, evaluated
// before the label. WorldBuilder's twin 0x0157F520 is unnamed.
UnicodeString __cdecl Rva005B2376Describe(void *power, int unused, const AsciiString &fallback)
{
	if (power != NULL)
		return TheGameText->fetch(((const CommandButton *)power)->rva0035B26F());
	if (!fallback.isEmpty())
		return TheGameText->fetch(fallback);
	return UnicodeString((const unsigned short *)L" ");
}

// ?Rva005B2446Describe@@YA?AVUnicodeString@@PAX@Z @0x005B2446 135B: the
// game text for "CAH:" + the power's +0x10 name + "_Name", or L" " without
// a power. WorldBuilder's twin 0x0157F670 (strings CAH:, _Name) is unnamed.
UnicodeString __cdecl Rva005B2446Describe(void *power)
{
	if (power == NULL)
		return UnicodeString((const unsigned short *)L" ");
	AsciiString label("CAH:");
	label += *(const AsciiString *)((const char *)power + 0x10);
	label += "_Name";
	return TheGameText->fetch(label);
}
extern const char *g_00DD3B90[];
extern const unsigned short g_Va007C9260[];

class Rva005B9378
{
public:
	void rva005B9378(int index, const UnicodeString &value);
	void rva005B942A(int index, int value);
};

void Rva005B9378::rva005B9378(int index, const UnicodeString &value)
{
	AsciiString key;
	key.format("APT:TickerField_%d", index);
	UnicodeString field = TheGameText->fetch(g_00DD3B90[index], 0);
	field.concat(L":");
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, field, false);
	key.format("APT:TickerValue_%d", index);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, value, false);
}

// ?rva005B942A@Rva005B9378@@QAEXHH@Z @0x005B942A 83B: one ticker numeric row.
// Formats the integer value with L"%d" (g_Va007C9260) into a UnicodeString
// temp, then hands it to rva005B9378 under the same index. Callers
// (0x005B9591 with index 2 and 0x005B95A4 with index 3, plus 0x005BA0CB/E3)
// pass this in ecx, which both bodies forward untouched.
void Rva005B9378::rva005B942A(int index, int value)
{
	UnicodeString text;
	text.format(g_Va007C9260, value);
	rva005B9378(index, text);
}

// ?rva00513497@Rva00513497@@QAEXHVUnicodeString@@@Z @0x00513497 193B: the
// disconnect screen's player name. It is set under
// DisconnectScreen::PlayerName%d, or L" " when the name is null or empty
// (inline length test at +4). The slot then goes through the rowed bar update
// 0x00513040 with 0 or, for a real name, the rowed 0x00512CE9 (false) and the
// bar update with 100. Both helpers are rowed as methods of their own
// address-named views of this same object.
class Rva00512CE9
{
public:
	void rva00512CE9(int slot, bool b);
};

class Rva00513040
{
public:
	void rva00513040(int v1, int v2);
};

// StringBase<unsigned short>::isEmpty, inline here as retail expands it.
static inline bool Rva00513497IsEmpty(const UnicodeString &s)
{
	const char *data = *(const char *const *)&s;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

class Rva00513497
{
public:
	void rva00513497(int slot, UnicodeString name);
};

void Rva00513497::rva00513497(int slot, UnicodeString name)
{
	AsciiString key;
	key.format("DisconnectScreen::PlayerName%d", slot);
	if (Rva00513497IsEmpty(name))
	{
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, UnicodeString(L" "), false);
		((Rva00513040 *)this)->rva00513040(slot, 0);
	}
	else
	{
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, name, false);
		((Rva00512CE9 *)this)->rva00512CE9(slot, false);
		((Rva00513040 *)this)->rva00513040(slot, 100);
	}
}

// ?rva0057F538@Rva0057F538@@QAEXVUnicodeString@@@Z @0x0057F538 181B: the clan
// error text. An unchanged message is skipped. Otherwise it runs the Apt
// ResetClanErrorMessage callback on the owner (virtual slot 2) through the
// rowed Rva0043DB23, keeps the message at +0xB0, and sets CLAN:Error to it
// (L" " when empty).
void Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);

class Rva0057F538
{
public:
	virtual void v00();
	virtual void v04();
	virtual void *v08();
	void rva0057F538(UnicodeString message);
private:
	char m_pad04[0xAC];
	UnicodeString m_error;		// +0xB0
};

void Rva0057F538::rva0057F538(UnicodeString message)
{
	if (message.compare(m_error) == 0)
		return;
	Rva0043DB23(TheRva00222A8BTarget, v08(), "ResetClanErrorMessage");
	m_error = message;
	if (Rva00513497IsEmpty(message))
		message = L" ";
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(AsciiString("CLAN:Error"), message, false);
}

// ?rva0051C2E2@Rva0051C2E2@@QAEXPAHABVAsciiString@@H@Z @0x0051C2E2 201B: one
// score-screen region bonus row, APT:ScoreRegionBonus%d keyed by the running
// row counter. A positive bonus formats the label's game-text format string
// (TheGameText slot 0x40, as in Rva0052906BUpdate.cpp) with it. A negative
// bonus sets L" ". Either way the counter advances. A zero bonus sets
// nothing. Callers pass this in ecx, which the body never reads.
class Rva0051C2E2
{
public:
	void rva0051C2E2(int *row, const AsciiString &label, int bonus);
};

void Rva0051C2E2::rva0051C2E2(int *row, const AsciiString &label, int bonus)
{
	AsciiString key;
	key.format("APT:ScoreRegionBonus%d", *row);
	if (bonus > 0)
	{
		UnicodeString text;
		text.format(TheGameText->fetchFormat(label, 0), bonus);
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, false);
		++*row;
	}
	else if (bonus < 0)
	{
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, UnicodeString(L" "), false);
		++*row;
	}
}

// ?ProcessProgress@AptFileTransferPopup@@QAEXHHVUnicodeString@@@Z @0x00583121 225B: one
// file-transfer row. For a valid player (0..7) whose Apt slot at +0x5C is
// assigned (-1 means none), it sets FileTransfer::Status%d to the text, then
// calls SetBarTo with the slot and the percentage as "%d" strings through
// the rowed Rva00222A8BTarget::invoke (owner 13, two arguments).

class AptFileTransferPopup
{
public:
	void ProcessProgress(int player, int percent, UnicodeString text);
private:
	char m_pad00[0x5C];
	int m_slots[8];				// +0x5C
};

void AptFileTransferPopup::ProcessProgress(int player, int percent, UnicodeString text)
{
	if (player < 0 || player >= 8)
		return;
	int slot = m_slots[player];
	if (slot == -1)
		return;
	AsciiString key;
	key.format("FileTransfer::Status%d", slot);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, false);
	char slotText[64];
	char percentText[64];
	sprintf(slotText, "%d", slot);
	sprintf(percentText, "%d", percent);
	TheRva00222A8BTarget->invoke((void *)13, "SetBarTo", 2, slotText, percentText, 0, 0, 0);
}

// ?rva0057C7BA@Rva0057E3DB@@QAEXH@Z @0x0057C7BA 216B: the lobby map title
// (the existing pin's class, the AptMpGameSetup panel's +0x60 member). It keeps
// the game type at +0x1C and sets APT:LobbyMapTiltle (the retail spelling)
// to that label's own game text for type 0 and GUI:GameTypeScenario for
// type 1.
class Rva0057E3DB
{
public:
	void rva0057C7BA(int type);
private:
	char m_pad00[0x1C];
	int m_type;					// +0x1C
};

void Rva0057E3DB::rva0057C7BA(int type)
{
	m_type = type;
	switch (type)
	{
	case 0:
		{
			AsciiString key("APT:LobbyMapTiltle");
			((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, TheGameText->fetch("APT:LobbyMapTiltle", 0), false);
		}
		break;
	case 1:
		{
			AsciiString key("APT:LobbyMapTiltle");
			((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, TheGameText->fetch("GUI:GameTypeScenario", 0), false);
		}
		break;
	}
}

// ?rva0043C8E4@Rva0043C8E4@@QAEXHH@Z @0x0043C8E4 79B: one spell button's
// state. SetSpellButtonState receives the 1-based button number as "%d" and
// the state's name from the table at VA 0x00C3D700. It goes through the
// rowed invoke on the owner the rowed Rva00222547Get resolves for this
// window. The number buffer reuses the index parameter's slot, as in retail.
class GameWindow;
GameWindow *Rva00222547Get(GameWindow *window);
extern const char *g_00C3D700[];

class Rva0043C8E4
{
public:
	void rva0043C8E4(int index, int state);
};

void Rva0043C8E4::rva0043C8E4(int index, int state)
{
	char number[4];
	sprintf(number, "%d", index + 1);
	TheRva00222A8BTarget->invoke(Rva00222547Get((GameWindow *)this), "SetSpellButtonState", 2, number, (void *)g_00C3D700[state], 0, 0, 0);
}

// ??1Rva00582FC1@@UAE@XZ @0x00582FC1 84B (the existing pin's name): the file
// transfer popup's destructor. It closes the popup through the rowed invoke
// (owner 13, FileTransferPopUpClose, no arguments), clears the instance
// global at VA 0x00E06398, then the rowed base destructor 0x005248D0 runs.
class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

class Rva00582FC1 : public Rva005248D0
{
public:
	virtual ~Rva00582FC1();
};

// The ledger's name for VA 0x00E06398 (ColdGlobalDwordGetters.cpp).
extern int g_Va00E06398;

Rva00582FC1::~Rva00582FC1()
{
	TheRva00222A8BTarget->invoke((void *)13, "FileTransferPopUpClose", 0, 0, 0, 0, 0, 0);
	g_Va00E06398 = 0;
}

// ?processProgress@AptLoadScreen@@QAEXHH@Z @0x0043A15D 99B: SetBarTo on the panel's
// Apt owner (+0x8C) with the slot's id from the table at +0xB0 and the
// percentage, both formatted by sprintf "%d".
class AptLoadScreen
{
public:
	void processProgress(int slot, int percent);
private:
	char m_pad00[0x8C];
	void *m_owner;				// +0x8C
	char m_pad90[0x20];
	int m_ids[1];				// +0xB0
};

void AptLoadScreen::processProgress(int slot, int percent)
{
	char idText[64];
	char percentText[64];
	sprintf(idText, "%d", m_ids[slot]);
	sprintf(percentText, "%d", percent);
	TheRva00222A8BTarget->invoke(m_owner, "SetBarTo", 2, idText, percentText, 0, 0, 0);
}

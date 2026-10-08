// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
// ?getXFromAlignment@GameSubTitle@@SAHHHHMM@Z @0x0025FF8F 175B.
// WB 0x00DA61E0 names GameSubTitle::getXFromAlignment in GameSubTitles.cpp;
// the full retail boundary ends at 0x0026003E. Five stack arguments, caller
// cleanup, and no receiver use establish this utility's cdecl ABI. Original
// alignment enum spelling is unknown; retain its 32-bit integer representation.
// Donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngineDevice/Source/VideoDevice/Bink/SubtitleEntryAlignment.cpp.
// The clean donor compiled under BFME2 /O1 /arch:SSE /G7 placed no bodies.
// Target adaptations: the owned theDebug pointer and the observed three-zero
// argument report factory at slot 0x6C. Math, cases, reference-returning minimum
// and diagnostic text are retained; all 175 bytes match under region flags.

#include <math.h>

typedef int Int;
typedef float Real;

class BfmeDebugReport
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeDebugReport *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(Int value);
};

class BfmeDebugManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeDebugReport *slot6C(void *first, void *second, void *third);
};

class Debug;
extern Debug *theDebug;
extern void _bfme_debugRecordCallsite(Int kind);

static const Int &bfmeMin(const Int &first, const Int &second)
{
	return first < second ? first : second;
}

// ?getXFromAlignment@GameSubTitle@@SAHHHHMM@Z
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
typedef int Int;



#include "unicode_string.h"
#include <string.h>
#pragma intrinsic(memset)

class GameFont;

class SubtitleEntry
{
public:
	SubtitleEntry(const UnicodeString &text, UnsignedInt color, Int style,
		Int alignment, Int line, Int startFrame, Int endFrame);
protected:
	virtual ~SubtitleEntry();

private:
	UnicodeString m_text;
	UnsignedInt m_color;
	Int m_style;
	Int m_alignment;
	Int m_line;
	Int m_startFrame;
	Int m_endFrame;
	bool m_displayed;
};

class DisplayString
{
public:
	virtual ~DisplayString();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
	virtual Int getTextLength();
	virtual void notifyTextChanged();
	virtual void reset();
	virtual void setFont(GameFont *font);
};

// The VA 0x00DFEAD8 singleton is DisplayStringManager *TheDisplayStringManager,
// reused through its existing owned symbol. This TU keeps its own view of
// the vtable and casts at the use.
class DisplayStringManager;

class SubtitleDisplayFactoryView
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual DisplayString *newDisplayString();
};

extern DisplayStringManager *TheDisplayStringManager;
static inline SubtitleDisplayFactoryView *theDisplayStringManagerView()
{
	return (SubtitleDisplayFactoryView *)TheDisplayStringManager;
}

extern "C" __declspec(dllimport) WideChar *__cdecl wcscpy(
	WideChar *destination, const WideChar *source);
extern "C" __declspec(dllimport) WideChar *__cdecl wcstok(
	WideChar *string, const WideChar *control);

class GameSubTitle : public SubtitleEntry
{
public:
	static Int getXFromAlignment(Int alignment, Int base, Int unused, Real low, Real high);
	virtual ~GameSubTitle();
	GameSubTitle(GameFont *font, const UnicodeString &text,
		UnsignedInt color, Int style, Int alignment, Int line,
		Int startFrame, Int endFrame);

private:
	DisplayString *m_displayStrings[3];
	Int m_displayStringCount;
	Int m_displayStringCapacity;
};


Int GameSubTitle::getXFromAlignment(Int alignment, Int base, Int unused, Real low, Real high)
{
	Int difference = (Int)fabs(high - low);

	switch (alignment)
	{
	case 1:
		return 0;
	case 0:
	{
		Int highInt = (Int)high;
		Int lowInt = (Int)low;
		const Int &minimum = bfmeMin(highInt, lowInt);
		return minimum + ((difference - base) >> 1);
	}
	case 2:
	{
		Int highInt = (Int)high;
		Int lowInt = (Int)low;
		const Int &minimum = bfmeMin(highInt, lowInt);
		return minimum - base + difference;
	}
	default:
		_bfme_debugRecordCallsite(1);
		reinterpret_cast<BfmeDebugManager *>(theDebug)->slot60();
		BfmeDebugReport *report = reinterpret_cast<BfmeDebugManager *>(theDebug)->slot6C(0, 0, 0);
		report = report->slot38("Invalid Subtitle alignment!");
		report->slot4C(1);
		return 0;
	}
}

// ??0GameSubTitle@@QAE@PAVGameFont@@ABVUnicodeString@@IHHHHH@Z @0x002603D1 233B.
// WB0x00DA5EF0 identifies the derived subtitle constructor; base at 0x00688550,
// members 0x24..0x34, DisplayString slots 0x18/0x04 and manager slot 0x38 are
// independently read from retail. Donor: Open-BFME-1 ba7ddda7,
// game/GameEngine/Source/GameClient/SubtitleEntryConstructor.cpp.
// Use the shared UnicodeString and owned manager global, protected base dtor,
// target slot 0x38, and actual newline delimiter. Target's three STOSD writes
// establish intrinsic memset for the pointer array; the donor's three scalar
// stores do not emit it. Full 233-byte constructor and prior alignment helper
// are verified together; no donor address is used as a target address.
GameSubTitle::GameSubTitle(GameFont *font,
	const UnicodeString &text, UnsignedInt color, Int style, Int alignment,
	Int line, Int startFrame, Int endFrame) :
	SubtitleEntry(text, color & 0x00FFFFFF, style, alignment, line, startFrame,
		endFrame),
	m_displayStrings(),
	m_displayStringCount(0),
	m_displayStringCapacity(0)
{
	memset(m_displayStrings, 0, sizeof(m_displayStrings));
	WideChar buffer[0x400];
	wcscpy(buffer, text.str());
	WideChar *token = wcstok(buffer, (const WideChar *)L"\n");
	while (token)
	{
		m_displayStrings[m_displayStringCount] =
			theDisplayStringManagerView()->newDisplayString();
		m_displayStrings[m_displayStringCount]->setFont(font);
		m_displayStrings[m_displayStringCount]->setText(UnicodeString(token));
		token = wcstok(0, (const WideChar *)L"\n");
		++m_displayStringCount;
	}
}

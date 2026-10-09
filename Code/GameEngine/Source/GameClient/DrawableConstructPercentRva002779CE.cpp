// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva002779CE@Rva002779CEHost@@QAEXXZ retail 0x002779CE..0x00277C42
// (628 bytes thiscall no args; Drawable draw-phase switch 0x002796D9 case
// 0). Drawable::drawConstructPercent by its Zero Hour shape; the
// WorldBuilder twin 0xCACAE0 has the same flow. Without an object or
// unless the object is under construction (status 2) and not sold (status
// 0x13) and not flagged at +0x438 bit 0 it frees the display string at
// +0x340 through TheDisplayStringManager (vtable +0x3C). Otherwise it
// creates one (+0x38) set to TheInGameUI's caption font (name getter
// 0x00274DB6 with point size +0x7A0 through GlobalLanguage::adjustFontSize
// and bold +0x7A4 into FontLibrary::getFont) and when the object's
// percent (+0x280) differs from the one shown (+0x33C) formats
// CONTROLBAR:CouncilDesc (template name ending in moot whose 0x0028BD17
// interface answers vtable +0x2C) or CONTROLBAR:UnderConstructionDesc
// (unless KindOf bit 0xBD or 0x3D) into it. It then projects the icon
// anchor (Drawable::rva002775C9) lowered a third of the way to the
// drawable position (0x00276470) through TheTacticalView (vtable +0x160)
// and draws the string centred in white over black. Slot and field names
// follow Zero Hour; the host name stays pinned.
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned int Color;

struct ICoord2D
{
	Int x;
	Int y;
};

class GameFont;

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text); // +0x04
	virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void setFont(GameFont *font); // +0x18
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void setColor(Color color, Color dropColor); // +0x28
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void draw(Int x, Int y, Int scaleX, Int scaleY); // +0x38
	virtual void slot15();
	virtual Int getWidth(Int line); // +0x40
};

class DisplayStringManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual DisplayString *newDisplayString(); // +0x38
	virtual void freeDisplayString(DisplayString *string); // +0x3C
};
extern DisplayStringManager *TheDisplayStringManager;

class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, Real pointSize, Bool bold);
};
extern FontLibrary *TheFontLibrary;

class GlobalLanguage
{
public:
	Int adjustFontSize(Int size);
};
extern GlobalLanguage *TheGlobalLanguageData;

class Rva00274DB6AsciiField
{
public:
	AsciiString get() const;
};

class InGameUI
{
public:
	Int getDrawableCaptionPointSize() const { return m_drawableCaptionPointSize; }
	Bool isDrawableCaptionBold() const { return m_drawableCaptionBold; }

private:
	char m_pad000[0x7a0];
	Int m_drawableCaptionPointSize; // +0x7A0
	Bool m_drawableCaptionBold; // +0x7A4
};
extern InGameUI *TheInGameUI;

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual const UnicodeString *fetchFormat(const char *label, Bool *exists = 0); // +0x44
};
extern GameTextInterface *TheGameText;

class View
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual Int worldToScreen(const Coord3D *world, ICoord2D *screen); // +0x160
};
extern View *TheTacticalView;

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	__forceinline UnsignedInt isKindOf(Int bit) const { return m_kindOf[bit >> 5] & (1 << (bit & 31)); }

private:
	char m_pad000[0x64];
	AsciiString m_name; // +0x64
	char m_pad068[0x108 - 0x68];
	UnsignedInt m_kindOf[8]; // +0x108
};

class CouncilInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual Bool isCouncil(); // +0x2C
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_SOLD = 0x13
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028BD17() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	Real getConstructionPercent() const { return m_constructionPercent; }
	Bool isFlag438() const { return (m_438 & 1) != 0; }

private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	char m_pad008[0x280 - 8];
	Real m_constructionPercent; // +0x280
	char m_pad284[0x438 - 0x284];
	unsigned char m_438; // +0x438
};

class Rva00276470Drawable
{
public:
	const Coord3D *rva00276470() const;
};

class Drawable
{
public:
	void rva002775C9(Coord3D *pos);
};

class Rva002779CEHost
{
public:
	void rva002779CE();

	Object *getObject() const { return m_object; }

private:
	char m_pad000[0xfc];
	Object *m_object; // +0xFC
	char m_pad100[0x33c - 0x100];
	Real m_lastConstructDisplayed; // +0x33C
	DisplayString *m_constructDisplayString; // +0x340
};

void Rva002779CEHost::rva002779CE()
{
	Object *obj = getObject();

	if (obj == 0 || !obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) || obj->testStatus(OBJECT_STATUS_SOLD)
		|| obj->isFlag438())
	{
		if (m_constructDisplayString)
		{
			TheDisplayStringManager->freeDisplayString(m_constructDisplayString);
			m_constructDisplayString = 0;
		}
		return;
	}

	if (m_constructDisplayString == 0)
	{
		m_constructDisplayString = TheDisplayStringManager->newDisplayString();
		m_constructDisplayString->setFont(TheFontLibrary->getFont(&reinterpret_cast<const Rva00274DB6AsciiField *>(TheInGameUI)->get(),
			TheGlobalLanguageData->adjustFontSize(TheInGameUI->getDrawableCaptionPointSize()),
			TheInGameUI->isDrawableCaptionBold()));
	}

	if (m_lastConstructDisplayed != obj->getConstructionPercent())
	{
		UnicodeString buffer;
		if (obj->getTemplate()->getName().endsWithNoCase("moot") && obj->rva0028BD17()
			&& static_cast<CouncilInterface *>(obj->rva0028BD17())->isCouncil())
		{
			buffer.format(TheGameText->fetchFormat("CONTROLBAR:CouncilDesc"), obj->getConstructionPercent());
		}
		else if (!obj->getTemplate()->isKindOf(0xbd) && !obj->getTemplate()->isKindOf(0x3d))
		{
			buffer.format(TheGameText->fetchFormat("CONTROLBAR:UnderConstructionDesc"), obj->getConstructionPercent());
		}
		m_constructDisplayString->setText(buffer);
		m_lastConstructDisplayed = obj->getConstructionPercent();
	}

	Coord3D pos;
	reinterpret_cast<Drawable *>(this)->rva002775C9(&pos);
	Real drawZ = reinterpret_cast<const Rva00276470Drawable *>(this)->rva00276470()->z;
	pos.z -= (pos.z - drawZ) * 0.333f;

	ICoord2D screen;
	if (TheTacticalView->worldToScreen(&pos, &screen) == 0)
	{
		screen.x += m_constructDisplayString->getWidth(-1) / -2;
		m_constructDisplayString->setColor(0xffffffff, 0xff000000);
		m_constructDisplayString->draw(screen.x, screen.y, 1, 1);
	}
}

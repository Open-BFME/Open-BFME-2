// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// InGameUI::postDraw [0x002A0161, 2854 B], vftable 0x7FD410 slot 85 after preDraw: the UI messages,
// superweapon timers per player map, named timers and RMB scroll anchor. Shape from the
// WorldBuilder twin InGameUI::postDraw (InGameUI.cpp asserts 5356..5490) and Zero Hour's postDraw.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <list>
#include <map>

// Use the typed node comparison here; the iterator-base out-of-line wrapper
// belongs to the retail STLport owner compiled with its own settings.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
#undef free
#include "ascii_string.h"
#include "unicode_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/ICoord2D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef int Color;

extern "C" __declspec(dllimport) double __cdecl floor(double);

inline float floor(float x)
{
	return (float)floor((double)x);
}

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

void GameGetColorComponents(Color color, UnsignedByte *red, UnsignedByte *green, UnsignedByte *blue, UnsignedByte *alpha);


class GameFont
{
public:
	char m_opaque00[0x10];
	Int height;									// +0x10
};

class DisplayString
{
public:
	virtual ~DisplayString();
	virtual void setText(UnicodeString text);	// slot 1
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void setFont(GameFont *font);		// slot 6
	virtual GameFont *getFont();				// slot 7
	virtual void slot08();
	virtual void slot09();
	virtual void setColors(Color color, Color dropColor);	// slot 10
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void drawAtOffsets(Int x, Int y, Int xDrop, Int yDrop);	// slot 14
	virtual void getSize(Int *width, Int *height);	// slot 15
	virtual Int getWidth(Int charPos);			// slot 16
};

class Display
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
#undef SLOT
	virtual UnsignedInt getWidth();				// slot 16
	virtual UnsignedInt getHeight();			// slot 17
};
extern Display *TheDisplay;

// TheDisplay's fill rectangle (0x0004263F), rowed under its address.
class Rva0004263F
{
public:
	void rva0004263F(float x, float y, float width, float height, int color);
};

class View
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16)
#undef SLOT
	virtual Int getHeight();					// slot 17
};
extern View *TheTacticalView;

class GameTextInterface
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
#undef SLOT
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);	// slot 15
};
extern GameTextInterface *TheGameText;

struct ScriptCounter
{
	Int value;
};

#include "../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class GlobalLanguage
{
public:
	Int adjustFontSize(Int point);

	char m_opaque00[0x14];
	AsciiString m_timeSeparator;				// +0x14
};
extern GlobalLanguage *TheGlobalLanguageData;

class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, Real pointSize, Bool bold);
};
extern FontLibrary *TheFontLibrary;

class LookAtTranslator
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual const ICoord2D *getRMBScrollAnchor();	// slot 2
};
extern LookAtTranslator *TheLookAtTranslator;

class Rva002D3627Host
{
public:
	char m_opaque00[0x18];
	Bool m_18;									// +0x18
};
class LivingWorld;
extern LivingWorld *TheLivingWorld;

extern Int BfmeLogicFramesPerSecond;			// LOGICFRAMES_PER_SECOND
extern float g_secondsPerLogicFrame;			// SECONDS_PER_LOGICFRAME_REAL

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class SpecialPowerTemplate : public Overridable
{
public:
	Bool isSharedNSync() const
	{
		return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_sharedNSync;
	}

	char m_opaque00[0x59];
	Bool m_sharedNSync;							// +0x59
};

class SpecialPowerModuleInterface
{
public:
	virtual void slot00();
	virtual Bool isReady() const;				// slot 1
	virtual void slot02();
	virtual void slot03();
	virtual UnsignedInt getReadyFrame() const;	// slot 4
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *specialPowerTemplate) const;
};

extern GameLogic *TheGameLogic;

class SuperweaponInfo
{
public:
	void setFont(const AsciiString &fontName, Int pointSize, Bool bold);
	void setText(const UnicodeString &name, const UnicodeString &time);
	void drawName(Int x, Int y, Color color, Color dropColor);
	void drawTime(Int x, Int y, Color color, Color dropColor);
	Real getHeight() const;
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_powerTemplate; }

	virtual ~SuperweaponInfo();

	DisplayString *m_nameDisplayString;			// +0x04
	DisplayString *m_timeDisplayString;			// +0x08
	Color m_color;								// +0x0C
	const SpecialPowerTemplate *m_powerTemplate;	// +0x10
	AsciiString m_powerName;					// +0x14
	ObjectID m_id;								// +0x18
	Int m_timestamp;							// +0x1C
	Bool m_hiddenByScript;						// +0x20
	Bool m_hiddenByScience;						// +0x21
	Bool m_ready;								// +0x22
	Bool m_forceUpdateText;						// +0x23
};

struct NamedTimerInfo
{
	AsciiString m_timerName;					// +0x00
	Int m_04;									// +0x04
	UnicodeString timerText;					// +0x08
	DisplayString *displayString;				// +0x0C
	Int timestamp;								// +0x10
	Color color;								// +0x14
	Bool isCountdown;							// +0x18
};

struct UIMessage
{
	UnicodeString fullText;						// +0x00
	DisplayString *displayString;				// +0x04
	UnsignedInt timestamp;						// +0x08
	Color color;								// +0x0C
};

class InGameUIHelper7F4
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11)
#undef SLOT
	virtual void draw();						// slot 12
};

enum { MAX_PLAYER_COUNT = 20, MAX_UI_MESSAGES = 6 };

typedef _STL::list<SuperweaponInfo *> SuperweaponList;
typedef _STL::map<AsciiString, SuperweaponList> SuperweaponMap;
typedef _STL::map<AsciiString, NamedTimerInfo *> NamedTimerMap;

class InGameUI
{
public:
	virtual ~InGameUI();
#define SLOT(N) virtual void slot##N();
	SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08)
	SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16)
	SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
	SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32)
	SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40)
	SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48)
	SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56)
	SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64)
	SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71) SLOT(72)
	SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79) SLOT(80)
	SLOT(81) SLOT(82) SLOT(83)
#undef SLOT
	virtual void preDraw();						// slot 84
	virtual void postDraw();					// slot 85

protected:
	char m_opaque004[0x14 - 0x4];
	Bool m_superweaponHiddenByScript;			// +0x14
	char m_opaque015[0x5D0 - 0x15];
	UIMessage m_uiMessages[MAX_UI_MESSAGES];	// +0x5D0
	SuperweaponMap m_superweapons[MAX_PLAYER_COUNT];	// +0x630
	Real m_superweaponPositionX;				// +0x720
	Real m_superweaponPositionY;				// +0x724
	Real m_superweaponFlashDuration;			// +0x728
	AsciiString m_superweaponNormalFont;		// +0x72C
	Int m_superweaponNormalPointSize;			// +0x730
	Bool m_superweaponNormalBold;				// +0x734
	AsciiString m_superweaponReadyFont;			// +0x738
	Int m_superweaponReadyPointSize;			// +0x73C
	Bool m_superweaponReadyBold;				// +0x740
	UnsignedInt m_superweaponLastFlashFrame;	// +0x744
	Color m_superweaponFlashColor;				// +0x748
	Bool m_superweaponUsedFlashColor;			// +0x74C
	NamedTimerMap m_namedTimers;				// +0x750
	Real m_namedTimerPositionX;					// +0x75C
	Real m_namedTimerPositionY;					// +0x760
	Real m_namedTimerOffsetX;					// +0x764
	Bool m_namedTimerCentered;					// +0x768
	Real m_namedTimerFlashDuration;				// +0x76C
	UnsignedInt m_namedTimerLastFlashFrame;		// +0x770
	Color m_namedTimerFlashColor;				// +0x774
	Bool m_namedTimerUsedFlashColor;			// +0x778
	Bool m_showNamedTimers;						// +0x779
	AsciiString m_namedTimerNormalFont;			// +0x77C
	Int m_namedTimerNormalPointSize;			// +0x780
	Bool m_namedTimerNormalBold;				// +0x784
	Int m_788;									// +0x788
	AsciiString m_namedTimerReadyFont;			// +0x78C
	Int m_namedTimerReadyPointSize;				// +0x790
	Bool m_namedTimerReadyBold;					// +0x794
	char m_opaque795[0x7F4 - 0x795];
	InGameUIHelper7F4 *m_7F4;					// +0x7F4
	char m_opaque7F8[0x811 - 0x7F8];
	Bool m_messagesOn;							// +0x811
	char m_opaque812[0x81C - 0x812];
	ICoord2D m_messagePosition;					// +0x81C
	ICoord2D m_messagePositionAlt;				// +0x824
	char m_opaque82C[0x8C3 - 0x82C];
	Bool m_drawRMBScrollAnchor;					// +0x8C3
};

// ?postDraw@InGameUI@@UAEXXZ
/** This is called after the UI has been drawn. */
void InGameUI::postDraw()
{
	// render our display strings for the messages if on
	if (m_messagesOn) {
		ICoord2D pos = (TheLivingWorld && ((Rva002D3627Host *)TheLivingWorld)->m_18) ? m_messagePositionAlt : m_messagePosition;
		Int y = fast_float2long_round(floor((Real)TheDisplay->getHeight() * pos.y * (1.0f / 768.0f) + 0.5f));
		Int x = fast_float2long_round(floor((Real)TheDisplay->getWidth() * pos.x * (1.0f / 1024.0f) + 0.5f));
		for (Int i = MAX_UI_MESSAGES - 1; i >= 0; i--) {
			DisplayString *displayString = m_uiMessages[i].displayString;
			if (displayString) {
				Int drawX = x;
				if (x < 0) {
					Int width, height;
					displayString->getSize(&width, &height);
					drawX = TheDisplay->getWidth() + (x - width);
				}
				UnsignedByte r, g, b, a;
				// make drop color black, but use the alpha setting of the fill color specified (for fading)
				GameGetColorComponents(m_uiMessages[i].color, &r, &g, &b, &a);
				Color dropColor = GameMakeColor(0, 0, 0, a);
				// draw the text
				displayString->setColors(m_uiMessages[i].color, dropColor);
				displayString->drawAtOffsets(drawX, y, 1, 1);
				// increment text spot to next location
				y += displayString->getFont()->height;
			}
		}
	}

	m_7F4->draw();

	// draw superweapon timers
	if (TheGameLogic->getFrame() > 0 && !m_superweaponHiddenByScript) {
		Int startX = (Int)(TheDisplay->getWidth() * m_superweaponPositionX);
		Int startY = (Int)(TheDisplay->getHeight() * m_superweaponPositionY);
		Int bottomMargin = (Int)((Real)TheTacticalView->getHeight() * 0.82f);
		Bool marginExceeded = false;
		for (Int i = 0; i < MAX_PLAYER_COUNT; ++i) {
			if (marginExceeded)
				break;
			Color bgColor = GameMakeColor(0, 0, 0, 255);
			for (SuperweaponMap::iterator mapIt = m_superweapons[i].begin(); mapIt != m_superweapons[i].end(); ++mapIt) {
				if (marginExceeded)
					break;
				AsciiString templateName = mapIt->first;
				for (SuperweaponList::iterator listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt) {
					if (marginExceeded)
						break;
					SuperweaponInfo *info = *listIt;
					if (info && !info->m_hiddenByScript && !info->m_hiddenByScience) {
						//enforce bottom margin of tactical view
						if (startY >= bottomMargin) {
							UnicodeString ellipsis;
							ellipsis.format(L"...");
							info->setText(ellipsis, ellipsis);
							info->setFont(m_superweaponReadyFont, m_superweaponNormalPointSize, m_superweaponNormalBold);
							info->drawTime(startX, startY, m_superweaponFlashColor, bgColor);
							marginExceeded = true;
						}
						if (marginExceeded)
							break;

						Object *owningObject = TheGameLogic->findObjectByID(info->m_id);
						if (owningObject) {
							// We don't draw our timers until we are finished with construction.
							// It is important that let the SpecialPowerUpdate is add its timer in its contructor,,
							// since the science for it could be added before construction is finished,
							// And thus the timer set to READY before the timer is first drawn, here
							if (owningObject->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
								continue;

							SpecialPowerModuleInterface *module = owningObject->getSpecialPowerModule(info->getSpecialPowerTemplate());
							if (module) {
								// found one - draw it
								Bool isReady = module->isReady();
								Int readySecs;
								// IsReady includes disabledness, so if you have a 0 timer disabled super, you don't want
								// the UnsignedInt to wrap around to hundreds of millions of seconds.
								if (module->getReadyFrame() < TheGameLogic->getFrame())
									readySecs = 0;
								else
									readySecs = (module->getReadyFrame() - TheGameLogic->getFrame()) / BfmeLogicFramesPerSecond;
								// Yes, integer math.  We can't have float imprecision display 4:01 on a disabled superweapon.

								// Similarly, only checking timers is not truly indicitive of readyness.
								Bool changeBolding = (readySecs != info->m_timestamp) || (isReady != info->m_ready) || info->m_forceUpdateText;
								if (changeBolding) {
									if (isReady) {
										// go bold - we're good to go
										info->setFont(m_superweaponReadyFont, m_superweaponReadyPointSize, m_superweaponReadyBold);
									} else {
										// if we were at 0, we've just fired - kill the bold
										if (info->m_timestamp == 0)
											info->setFont(m_superweaponNormalFont, m_superweaponNormalPointSize, m_superweaponNormalBold);
									}

									info->m_forceUpdateText = false;
									info->m_ready = isReady;
									info->m_timestamp = readySecs;
									Int min = readySecs / 60;
									Int sec = readySecs - min * 60;
									AsciiString strIndex;
									strIndex.format("GUI:%s", templateName.str());
									UnicodeString name, time;
									name.format(L"%ls: ", TheGameText->fetch(strIndex.str()).str());
									time.format(L"%d:%2.2d", min, sec);
									info->setText(name, time);
								}

								if (isReady) {
									if (m_superweaponFlashDuration != 0.0f) {
										if (TheGameLogic->getFrame() >= m_superweaponLastFlashFrame + (Int)(m_superweaponFlashDuration)) {
											m_superweaponUsedFlashColor = !m_superweaponUsedFlashColor;
											m_superweaponLastFlashFrame = TheGameLogic->getFrame();
										}
										info->drawName(startX, startY, (m_superweaponUsedFlashColor) ? 0 : m_superweaponFlashColor, bgColor);
										info->drawTime(startX, startY, (m_superweaponUsedFlashColor) ? 0 : m_superweaponFlashColor, bgColor);
									} else {
										info->drawName(startX, startY, 0, bgColor);
										info->drawTime(startX, startY, 0, bgColor);
									}
								} else {
									info->drawName(startX, startY, 0, bgColor);
									info->drawTime(startX, startY, 0, bgColor);
								}

								// increment text spot to next location
								startY += info->getHeight();

								if (info->getSpecialPowerTemplate()->isSharedNSync())
									break; // Wow, it is almost too easy!
								// This prevents redundant timers for shared powers/superweapons
								// No matter how many specialpowermodules register their timers with me,
								// I will only draw the timer of the first valid one in my list,
								// since they all have the same template, ans they all
								// use the Player::getReadyFrame() functions to stay in sync.
							}
						}
					}
				}
			}
		}
	}

	// draw named timers
	if (TheGameLogic->getFrame() > 0 && m_showNamedTimers) {
		Bool reverseXDir = !m_namedTimerCentered && m_namedTimerPositionX >= 0.5f;
		Int startX = (Int)(TheDisplay->getWidth() * (m_namedTimerOffsetX + m_namedTimerPositionX));
		Int startY = (Int)(TheDisplay->getHeight() * m_namedTimerPositionY);
		Color bgColor = GameMakeColor(0, 0, 0, 255);
		for (NamedTimerMap::iterator mapIt = m_namedTimers.begin(); mapIt != m_namedTimers.end(); ++mapIt) {
			AsciiString timerName = mapIt->first;
			NamedTimerInfo *info = mapIt->second;
			if (info) {
				// found one - draw it
				UnicodeString line;
				Int framesLeft = 0;
				ScriptCounter *counter = (ScriptCounter *)TheScriptEngine->rva002086C5(timerName);
				if (counter)
					framesLeft = counter->value;
				UnsignedInt readyFrame = TheGameLogic->getFrame();
				if (framesLeft > 0)
					readyFrame += framesLeft;
				Int readySecs = (Int)(g_secondsPerLogicFrame * (readyFrame - TheGameLogic->getFrame()));
				if ((info->isCountdown && readySecs != info->timestamp) || (!info->isCountdown && framesLeft != info->timestamp)) {
					if (!readySecs && info->isCountdown) {
						// go bold - we're good to go
						info->displayString->setFont(TheFontLibrary->getFont(&m_namedTimerReadyFont,
							TheGlobalLanguageData->adjustFontSize(m_namedTimerReadyPointSize), m_namedTimerReadyBold));
					} else {
						// if we were at 0, we've just fired - kill the bold
						if (info->timestamp == 0 || info->isCountdown) {
							info->displayString->setFont(TheFontLibrary->getFont(&m_namedTimerNormalFont,
								TheGlobalLanguageData->adjustFontSize(m_namedTimerNormalPointSize), m_namedTimerNormalBold));
						}
					}

					Int min = readySecs / 60;
					Int sec = readySecs - min * 60;

					if (!info->isCountdown) {
						line.format(L"%s %d", info->timerText.str(), framesLeft);
						info->timestamp = framesLeft;
					} else {
						info->timestamp = readySecs;
						UnicodeString separator(L":");
						if (TheGlobalLanguageData)
							separator.translate(TheGlobalLanguageData->m_timeSeparator);
						if (sec >= 10)
							line.format(L"%s %d%s%d", info->timerText.str(), min, separator.str(), sec);
						else
							line.format(L"%s %d%s0%d", info->timerText.str(), min, separator.str(), sec);
					}
					info->displayString->setText(line);
				}

				// draw the text
				Int drawX = startX;
				if (m_namedTimerCentered)
					drawX -= info->displayString->getWidth(-1) / 2;
				else if (reverseXDir)
					drawX -= info->displayString->getWidth(-1);

				if (!readySecs && info->isCountdown) {
					if (m_namedTimerFlashDuration != 0.0f) {
						if (TheGameLogic->getFrame() >= m_namedTimerLastFlashFrame + (Int)(m_namedTimerFlashDuration)) {
							m_namedTimerUsedFlashColor = !m_namedTimerUsedFlashColor;
							m_namedTimerLastFlashFrame = TheGameLogic->getFrame();
						}
						info->displayString->setColors((m_namedTimerUsedFlashColor) ? info->color : m_namedTimerFlashColor, bgColor);
						info->displayString->drawAtOffsets(drawX, startY, 1, 1);
					} else {
						info->displayString->setColors(info->color, bgColor);
						info->displayString->drawAtOffsets(drawX, startY, 1, 1);
					}
				} else {
					info->displayString->setColors(info->color, bgColor);
					info->displayString->drawAtOffsets(drawX, startY, 1, 1);
				}

				// increment text spot to next location
				startY -= info->displayString->getFont()->height;
			}
		}
	}

	// draw RMB scroll anchor
	if (TheLookAtTranslator && m_drawRMBScrollAnchor) {
		const ICoord2D *anchor = TheLookAtTranslator->getRMBScrollAnchor();
		if (anchor) {
			static const Int w = 2;
			static const Int h = 2;
			static const Int r = 4; // ratio
			static const Color mainColor = GameMakeColor(0, 255, 0, 255);
			static const Color dropColor = GameMakeColor(0, 0, 0, 255);
			((Rva0004263F *)TheDisplay)->rva0004263F(anchor->x - w * r - 1, anchor->y - h - 1, w * 2 * r + 3, h * 2 + 3, dropColor);
			((Rva0004263F *)TheDisplay)->rva0004263F(anchor->x - w - 1, anchor->y - h * r - 1, w * 2 + 3, h * 2 * r + 3, dropColor);
			((Rva0004263F *)TheDisplay)->rva0004263F(anchor->x - w * r, anchor->y - h, w * 2 * r + 1, h * 2 + 1, mainColor);
			((Rva0004263F *)TheDisplay)->rva0004263F(anchor->x - w, anchor->y - h * r, w * 2 + 1, h * 2 * r + 1, mainColor);
		}
	}
}  // end postDraw


// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii
// readable body of ?setFont@SuperweaponInfo@@QAEXABVAsciiString@@H_N@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// readable body of ?drawName@SuperweaponInfo@@QAEXHHHH@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// readable body of ?drawTime@SuperweaponInfo@@QAEXHHHH@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// readable body of ??1SuperweaponInfo@@MAE@XZ: Code/GameEngine/Source/GameClient/InGameUI.cpp
//
// Four members of one class, so they need one declaration of it. Each body used
// to sit in its own file with its own partial view of SuperweaponInfo and of
// DisplayString, and the four views disagreed: three called the vtable pointer
// m_vtable while the destructor let the virtual destructor place it, and the
// same word at +0x0c was `Color m_color` in one file and `unsigned int m_color`
// in another.
//
// The layout below is the union those four views describe. The vtable pointer
// comes from the virtual destructor rather than a named m_vtable field, which
// puts the two DisplayString pointers at +0x04 and +0x08, the color at +0x0c,
// and the power template, name and tail that only the destructor sees after
// them. Every offset any of the four bodies touches is unchanged.
//
// DisplayString comes from its canonical header. The slots the bodies reach
// are setFont at +0x18, setColors at +0x28, draw(x, y, xDrop, yDrop) at +0x38
// and getWidth at +0x40.

#include "../../Include/Common/ScalarTypes.h"
typedef int Color;



class GameFont;

#include "ascii_string.h"

#include "../../Include/GameClient/DisplayString.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
#include "../../Include/GameClient/DisplayStringManager.h"

#include "../../Include/Common/GlobalLanguageClass.h"

#include "../../Include/GameClient/FontLibrary.h"

extern DisplayStringManager *TheDisplayStringManager;
extern GlobalLanguage *TheGlobalLanguageData;
// TheGlobalLanguageData: matched references place it at VA 0xdfdc84 (zero-filled .bss).
GlobalLanguage * TheGlobalLanguageData;
extern FontLibrary *TheFontLibrary;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class SuperweaponInfo
{
public:
	void setFont(const AsciiString &fontName, Int pointSize, Bool bold);
	void drawName(Int x, Int y, Color color, Color dropColor);
	void drawTime(Int x, Int y, Color color, Color dropColor);
	Real getHeight() const;

protected:
	virtual ~SuperweaponInfo();

private:
	DisplayString *m_nameDisplayString;
	DisplayString *m_timeDisplayString;
	Color m_color;
	const void *m_powerTemplate;
	AsciiString m_powerName;
	unsigned int m_tail[4];
};

// ?setFont@SuperweaponInfo@@QAEXABVAsciiString@@H_N@Z
// Both strings take the same font, and the point size passes through the
// language data's adjustment on the way in.
void SuperweaponInfo::setFont(const AsciiString &fontName, Int pointSize, Bool bold)
{
	m_nameDisplayString->setFont(TheFontLibrary->getFont(
		const_cast<AsciiString *>(&fontName),
		(Real)TheGlobalLanguageData->adjustFontSize(pointSize), bold));
	m_timeDisplayString->setFont(TheFontLibrary->getFont(
		const_cast<AsciiString *>(&fontName),
		(Real)TheGlobalLanguageData->adjustFontSize(pointSize), bold));
}

// ?drawName@SuperweaponInfo@@QAEXHHHH@Z
// x is the RIGHT edge: the name is drawn right-aligned by subtracting its own
// width, and a zero color means the one the info was built with.
void SuperweaponInfo::drawName(Int x, Int y, Color color, Color dropColor)
{
	if (color == 0)
		color = m_color;

	m_nameDisplayString->setColors(color, dropColor);
	m_nameDisplayString->draw(x - m_nameDisplayString->getWidth(-1), y, 1, 1);
}

// ?drawTime@SuperweaponInfo@@QAEXHHHH@Z
// The countdown hangs off the NAME's width, not its own, so it stays put as the
// digits change.
void SuperweaponInfo::drawTime(Int x, Int y, Color color, Color dropColor)
{
	if (color == 0)
		color = m_color;

	m_timeDisplayString->setColors(color, dropColor);
	m_timeDisplayString->draw(x - m_nameDisplayString->getWidth(-1), y, 1, 1);
}

// SuperweaponInfo::~SuperweaponInfo: defined in InGameUI.cpp (its unit).

// Readable BF1 f989 InGameUI.cpp supplies SuperweaponInfo::getHeight.
// Native29A5CA..29A5D6 follows RET16 at29A5C7; caller2A0664 passes the
// same ESI as rowed drawName29A541/drawTime29A585 and adds the result to y.
// Native DisplayString tables BCF900/C15338 slot1C both select30F45F,
// the font pointer getter at+8. Native W3DFontLibraryLoadFontData902A6
// independently stores font height at+10. Keep the forward GameFont type
// and read that proven signed word without adding another private class view.
// ?getHeight@SuperweaponInfo@@QBEMXZ
Real SuperweaponInfo::getHeight() const
{
    return reinterpret_cast<const Int *>(m_nameDisplayString->getFont())[4];
}

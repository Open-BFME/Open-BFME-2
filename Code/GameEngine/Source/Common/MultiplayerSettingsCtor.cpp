// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// MultiplayerSettings constructor (retail RVA 0x003811D8, 159 bytes).
// The native 0xC4 object has the 0x0C SubsystemInterface base, a 0x0C map at
// +0x34 and two 0x40-byte color definitions at +0x44/+0x84. Its table at
// RVA 0x008191B8 has fourteen slots; slot zero is the virtual deleting
// destructor at RVA 0x00381277. The compiler supplies this table and the
// implicit virtual lifetime bodies from the same native view as the seed TU.
#include <stl/_algobase.h>
#include <map>
#include <cstddef>
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"

typedef bool Bool;
typedef int Int;
typedef int Color;
#include "../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"

// The native base has fourteen virtual slots and occupies 0x0C bytes.
// Avoid PreRTS.h: its Zero Hour SubsystemInterface and inline RGBColor
// declarations conflict with the target interfaces used by this TU.
#define _MULTIPLAYERSETTINGS_H_

// Only static parser callbacks are needed here; no INI object is constructed.
// Signatures and FieldParse's four-word layout are the existing INI contract.
class INI
{
public:
    static void parseAsciiString(INI *, void *, void *, const void *);
    static void parseRGBColor(INI *, void *, void *, const void *);
    static void parseInt(INI *, void *, void *, const void *);
    static void parseBool(INI *, void *, void *, const void *);
};

typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse
{
    const char *token;
    INIFieldParseProc parse;
    const void *userData;
    Int offset;
};

// The existing GameInfo constants, also selected by getColor's retail tests.
enum { PLAYERTEMPLATE_RANDOM = -1, PLAYERTEMPLATE_OBSERVER = -2 };

class MultiplayerColorDefinition
{
public:
    MultiplayerColorDefinition();
    // The pair copy at 0x00380DA3 calls the native color copy out of line.
    MultiplayerColorDefinition(const MultiplayerColorDefinition &other);
    static const FieldParse m_colorFieldParseTable[];
    const FieldParse *getFieldParse() const { return m_colorFieldParseTable; }

    AsciiString getTooltipName() const { return m_tooltipName; }
    RGBColor getRGBValue() const { return m_rgbValue; }
    RGBColor getRGBNightValue() const { return m_rgbValueNight; }
    Color getColor() const { return m_color; }
    Color getNightColor() const { return m_colorNight; }
    void setColor(RGBColor rgb);
    void setNightColor(RGBColor rgb);
    MultiplayerColorDefinition *operator=(const MultiplayerColorDefinition &other);

private:
    AsciiString m_tooltipName; // +0x00
    RGBColor m_rgbValue; // +0x04
    Color m_color; // +0x10
    RGBColor m_rgbValueNight; // +0x14
    Color m_colorNight; // +0x20
    RGBColor m_rgbExtra1; // +0x24, LivingWorldColor in the native parse table
    RGBColor m_rgbExtra2; // +0x30, LivingWorldBannerColor in the native table
    Bool m_extraFlag; // +0x3C, AvailableInWotR in the native table
};

typedef _STL::pair<const int, MultiplayerColorDefinition> ColorMapValue;
typedef _STL::map<int, MultiplayerColorDefinition, _STL::less<int>, _STL::allocator<_STL::pair<const int, MultiplayerColorDefinition> > > MultiplayerColorList;
typedef MultiplayerColorList::iterator MultiplayerColorIter;

// Existing providers: map constructor3811A2 and tree destructor38103F.
namespace _STL
{
template <> map<int, MultiplayerColorDefinition>::map();
template <> _Rb_tree<int, ColorMapValue, _Select1st<ColorMapValue>, less<int>, allocator<ColorMapValue> >::~_Rb_tree();
}

class MultiplayerSettings : public SubsystemInterface
{
public:
    MultiplayerSettings();
    virtual void init() {}
    virtual void reset() {}
    virtual void update() {}

    static const FieldParse m_multiplayerSettingsFieldParseTable[];
    const FieldParse *getFieldParse() const { return m_multiplayerSettingsFieldParseTable; }
    MultiplayerColorDefinition *findMultiplayerColorDefinitionByName(AsciiString name);
    MultiplayerColorDefinition *newMultiplayerColorDefinition(AsciiString name);
    Int getStartCountdownTimerSeconds() { return m_startCountdownTimerSeconds; }
    Int getMaxBeaconsPerPlayer() { return m_maxBeaconsPerPlayer; }
    Bool isShroudInMultiplayer() { return m_isShroudInMultiplayer; }
    Bool showRandomPlayerTemplate() { return m_showRandomPlayerTemplate; }
    Bool showRandomStartPos() { return m_showRandomStartPos; }
    Bool showRandomColor() { return m_showRandomColor; }
    Int getNumColors()
    {
        if (m_numColors == 0)
            m_numColors = m_colorList.size();
        return m_numColors;
    }
    MultiplayerColorDefinition *getColor(Int which);

private:
    Int m_unknown0C; // +0x0C, zeroed by the native constructor
    Int m_unknown10; // +0x10, native constructor stores 0x2710
    Int m_startCountdownTimerSeconds; // +0x14, native parse table and zero store
    Int m_maxBeaconsPerPlayer; // +0x18
    Bool m_isShroudInMultiplayer; // +0x1C
    Bool m_showRandomPlayerTemplate; // +0x1D
    Bool m_showRandomStartPos; // +0x1E
    Bool m_showRandomColor; // +0x1F
    Int m_initialCredits[5]; // +0x20, VeryLow through VeryHigh
    MultiplayerColorList m_colorList; // +0x34, node count at +0x38
    Int m_numColors; // +0x40, lazy refill
    MultiplayerColorDefinition m_observerColor; // +0x44
    MultiplayerColorDefinition m_randomColor; // +0x84
};

typedef char MultiplayerBaseSize[sizeof(SubsystemInterface) == 0x0C ? 1 : -1];
typedef char MultiplayerMapSize[sizeof(MultiplayerColorList) == 0x0C ? 1 : -1];
typedef char MultiplayerColorSize[sizeof(MultiplayerColorDefinition) == 0x40 ? 1 : -1];
typedef char MultiplayerSettingsSize[sizeof(MultiplayerSettings) == 0xC4 ? 1 : -1];
typedef char MultiplayerFieldParseSize[sizeof(FieldParse) == 0x10 ? 1 : -1];


MultiplayerSettings::MultiplayerSettings()
	: SubsystemInterface()
{
	m_unknown0C = 0;
	m_startCountdownTimerSeconds = 0;
	m_numColors = 0;
	m_unknown10 = 0x2710;
	m_maxBeaconsPerPlayer = 3;
	m_isShroudInMultiplayer = true;
	m_showRandomPlayerTemplate = true;
	m_showRandomStartPos = true;
	m_showRandomColor = true;
	m_initialCredits[0] = 0x1F4;
	m_initialCredits[1] = 0x3E8;
	m_initialCredits[2] = 0x5DC;
	m_initialCredits[3] = 0x7D0;
	m_initialCredits[4] = 0x9C4;
}

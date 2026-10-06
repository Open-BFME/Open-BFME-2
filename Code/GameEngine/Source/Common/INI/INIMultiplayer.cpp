// cl: /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/multiplayer /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/iniexception /Ireference/open-bfme-1/inputs/reference/shims/ini_noinline /DBFME_STLP_NODE_ALLOC /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/INI/INIMultiplayer.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// INI::parseMultiplayerColorDefinition 0x001EF3BF (178B). Callee addresses are
// read off retail's call sites (reverse/symbols.csv). Only the placed bodies
// are carried; the donor's other definitions are omitted.
// One adaptation read off retail: the AsciiString assignment from a C string
// calls StringBase<char>::set (0x000055F5) directly rather than the rowed
// operator= at 0x000065B8, so it is spelled as set().
//
// The "MultiplayerSettings" and "MultiplayerColor" blocks. Both are Zero Hour's
// INIMultiplayer.cpp bodies unchanged, and MultiplayerColorDefinition's layout
// is identical too: retail reaches m_rgbValue at +4 and m_rgbValueNight at +0x14,
// which is exactly where ZH's AsciiString/RGBColor/Color/RGBColor/Color ordering
// puts them.
//
// MultiplayerSettings itself is NOT ZH's -- retail news 0x88 bytes for it where
// ZH compiles to 0x90, and its INI fields land at different offsets. The BFME
// layout, decoded from the retail field table, is in inputs/reference/shims/multiplayer.
#include "PreRTS.h"
#include "Common/INI.h"
#include "GameClient/Color.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition();
	static const FieldParse m_colorFieldParseTable[];
	const FieldParse *getFieldParse() const { return m_colorFieldParseTable; }
	AsciiString getTooltipName() const;
	RGBColor getRGBValue() const { return m_rgbValue; }
	RGBColor getRGBNightValue() const { return m_rgbValueNight; }
	void setColor( RGBColor rgb );
	void setNightColor( RGBColor rgb );
	MultiplayerColorDefinition *operator=( const MultiplayerColorDefinition &other );

private:
	AsciiString m_tooltipName;
	RGBColor m_rgbValue;
	Color m_color;
	RGBColor m_rgbValueNight;
	Color m_colorNight;
};

typedef std::map<Int, MultiplayerColorDefinition> MultiplayerColorList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerSettings : public SubsystemInterface
{
public:
	MultiplayerSettings();
	virtual void init() {}
	virtual void update() {}
	virtual void reset() {}
	static const FieldParse m_multiplayerSettingsFieldParseTable[];
	const FieldParse *getFieldParse() const { return m_multiplayerSettingsFieldParseTable; }
	MultiplayerColorDefinition *findMultiplayerColorDefinitionByName( AsciiString name );
	MultiplayerColorDefinition *newMultiplayerColorDefinition( AsciiString name );
	Int getNumColors()
	{
		if( m_numColors == 0 ) m_numColors = m_colorList.size();
		return m_numColors;
	}

private:
	Int m_unknown08;
	Int m_unknown0C;
	Int m_startCountdownTimerSeconds;
	Int m_maxBeaconsPerPlayer;
	Bool m_isShroudInMultiplayer;
	Bool m_showRandomPlayerTemplate;
	Bool m_showRandomStartPos;
	Bool m_showRandomColor;
	Int m_initialCredits[ 5 ];
	MultiplayerColorList m_colorList;
	Int m_numColors;
	MultiplayerColorDefinition m_observerColor;
	MultiplayerColorDefinition m_randomColor;
};

extern MultiplayerSettings *TheMultiplayerSettings;


void INI::parseMultiplayerColorDefinition( INI* ini )
{
	const char *c;
	AsciiString name;
	MultiplayerColorDefinition *multiplayerColorDefinition;

	c = ini->getNextToken();
	// BFME assigns rather than calling set(c): retail inlines strlen and calls
	// the two-argument set, which is what operator=(const char *) expands to.
	name.set( c );	// retail calls StringBase::set (0x000055F5), not the operator= thunk

	multiplayerColorDefinition = TheMultiplayerSettings->findMultiplayerColorDefinitionByName( name );
	if( multiplayerColorDefinition == NULL )
		multiplayerColorDefinition = TheMultiplayerSettings->newMultiplayerColorDefinition( name );

	ini->initFromINI( multiplayerColorDefinition, multiplayerColorDefinition->getFieldParse() );

	multiplayerColorDefinition->setColor(multiplayerColorDefinition->getRGBValue());
	multiplayerColorDefinition->setNightColor(multiplayerColorDefinition->getRGBNightValue());
}

// cl: /O1 /Ireference/shims/ini_bfme2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// ?init@ControlBarSchemeManager@@QAEXXZ, retail 0x00320205 (140 bytes).
//
// Identity (target family): worldbuilder.exe's assert names its partner
// ControlBarSchemeManager::init in
// Code\GameEngine\Source\GameClient\GUI\ControlBar\ControlBarScheme.cpp
// (the only function in each image referencing both ControlBarScheme.ini
// paths).
//
// Body (donor): Zero Hour / BFME1 ControlBarSchemeManager::init with BFME2's
// INI::loadFile. The empty-list check stays: its DEBUG_ASSERTCRASH is compiled
// out, but the STLport list::size() node walk it calls is still emitted.
// Layout: m_schemeList at +0xC, after m_currentScheme and the Coord2D
// m_multiplyer, as in the Zero Hour header.
#include <list>
#include "PreRTS.h"
#include "Common/INI/INI.h"

class ControlBarScheme;

struct Coord2D
{
	Real x, y;
};

class ControlBarSchemeManager
{
public:
	void init( void );

private:
	ControlBarScheme *m_currentScheme;
	Coord2D m_multiplyer;
	typedef std::list< ControlBarScheme * > ControlBarSchemeList;
	ControlBarSchemeList m_schemeList;
};

void ControlBarSchemeManager::init( void )
{
	INI ini;
	// Read from INI all the ControlBarSchemes
	ini.loadFile( AsciiString( "Data\\INI\\Default\\ControlBarScheme.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.loadFile( AsciiString( "Data\\INI\\ControlBarScheme.ini" ), INI_LOAD_OVERWRITE, NULL );

	if( m_schemeList.size() <= 0 )
	{
		DEBUG_ASSERTCRASH( FALSE, ("There's no ControlBarScheme in the ControlBarSchemeList:m_schemeList that was just read from the INI file") );
		return;
	}
}

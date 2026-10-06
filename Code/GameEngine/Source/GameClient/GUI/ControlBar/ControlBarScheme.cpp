// cl: /Ireference/shims/ini_bfme2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
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

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

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

// Target extent: 0x005F8376..0x005F8387, bounded by Ghidra functions
// [0x005F835A,0x005F8376) and [0x005F8388,...). The body copies the two
// dwords at this+0x18 and this+0x1C to its stack argument. Its thiscall ABI
// could be a hidden ICoord2D return buffer or an explicit output reference;
// no target caller resolves that distinction, so keep the address-derived
// identity and the raw machine-level contract.
//
// BFME1 lead: ControlBarSchemeAnimation::getStartPos at b1 0x003D4D30 is
// ICF-folded with AnimateWindow::getCurPos and PathfindLayer::getStartCellIndex
// plus three thunk names; it supplies shape only and no target name is used.
class Rva005F8376
{
	unsigned char m_prefix[0x18];
	unsigned int m_word18;
	unsigned int m_word1C;

public:
	void rva005F8376(unsigned int *out) const;
};

void Rva005F8376::rva005F8376(unsigned int *out) const
{
	out[0] = m_word18;
	out[1] = m_word1C;
}

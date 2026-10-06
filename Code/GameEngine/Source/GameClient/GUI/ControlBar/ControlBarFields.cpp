// ControlBar::hideSpecialPowerShortcut ported from BFME1 donor
// reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarFields.cpp
// (// cl: /DNDEBUG /DWIN32 /MD /EHsc, stlport).
//
// Two BFME2-local repairs versus the donor, both hard retail evidence:
// - m_specialPowerShortcutParent sits at this+0xD8 here (retail 0x31AFCC:
//   `mov ecx,[ecx+0xD8]`), not the donor shim's this+0xFC which BFME1's
//   0x49D4A0 proves over there. The TU-local ControlBar view below keeps the
//   BFME1 member name at the BFME2 offset; the shared controlbar shim is
//   untouched (40+ ControlBar.cpp rows depend on its pre-boundary layout).
// - The hide call lands on ?winHide@GameWindow@@QAEH_N@Z (pinned 0x00313C64,
//   117B: bool param flips bit 0x10 on [esi+8] with window-manager notify).

class GameWindow
{
public:
	int winHide( bool hide );
};

class ControlBar
{
public:
	void hideSpecialPowerShortcut( void );

	unsigned char m_pad[ 0xD8 ];
	GameWindow *m_specialPowerShortcutParent;			///< retail this+0xD8 (BFME1 header has this+0xFC)
};

// Matched DIR32 at 0x003E73E7 establishes TheControlBar at VA 0x00E01CFC.
// This address is in the PE .data zero-fill tail, so retail starts it null.
extern class ControlBar *TheControlBar;

// ?hideSpecialPowerShortcut@ControlBar@@QAEXXZ
void ControlBar::hideSpecialPowerShortcut( void )
{
	if( !m_specialPowerShortcutParent )
		return;

	m_specialPowerShortcutParent->winHide( true );
}

// cl: /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/GUI/window_layout.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// WindowLayout::removeWindow 0x00538B95 (121B), WindowLayout::addWindow
// 0x00538B48 (77B), WindowLayout::bringForward 0x00538B07 (40B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
// WindowLayout (Generals GameClient/GUI/WindowLayout.cpp). The original was
// compiled with exception handling; BFME's set(str) wrapper folds strlen of
// the literal into the two-arg set call.
#include "../../../Include/GameClient/GameWindowManager.h"
#include "../../../Include/GameClient/WindowLayout.h"

  // end hide

void WindowLayout::addWindow( GameWindow *window )
{
	GameWindow *win = findWindow( window );

	// only add window if window is not in this layout already
	if( win == 0 )
	{

		window->winSetPrevInLayout( 0 );
		window->winSetNextInLayout( m_windowList );
		if( m_windowList )
			m_windowList->winSetPrevInLayout( window );
		m_windowList = window;

		// set layout into window
		window->winSetLayout( this );

		// if no tail pointer, this is it
		if( m_windowTail == 0 )
			m_windowTail = window;

		// we gots another window now
		m_windowCount++;

	}  // end if

}  // end addWindow

void WindowLayout::removeWindow( GameWindow *window )
{
	GameWindow *win = findWindow( window );

	// can't remove window unless it's really part of this layout
	if( win )
	{
		GameWindow *prev, *next;

		prev = win->winGetPrevInLayout();
		next = win->winGetNextInLayout();

		if( next )
			next->winSetPrevInLayout( prev );
		if( prev )
			prev->winSetNextInLayout( next );
		else
			m_windowList = next;

		// set window as having no layout info
		win->winSetLayout( 0 );
		win->winSetNextInLayout( 0 );
		win->winSetPrevInLayout( 0 );

		// if we removed the tail, set the new tail
		if( m_windowTail == win )
			m_windowTail = prev;

		// we lost one sir!
		m_windowCount--;

	}  // end if

}  // end removeWindow

void WindowLayout::bringForward( void )
{
	GameWindow *window, *prev;
	int countLeft = m_windowCount;

	for( window = m_windowTail; countLeft; window = prev )
	{

		prev = window->winGetPrevInLayout();
		window->winBringToTop();
		countLeft--;

	}  // end for window

}


  // end destroyWindows

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0023C4EB reads ?set@Rva0023C4EBDwordSlot@@QAEXH@Z
#pragma comment(linker, "/alternatename:?winSetLayout@GameWindow@@QAEHPAVWindowLayout@@@Z=?set@Rva0023C4EBDwordSlot@@QAEXH@Z")
//   0x0031410C reads ?set@Rva0031410CDwordSlot@@QAEXH@Z
#pragma comment(linker, "/alternatename:?winSetNextInLayout@GameWindow@@QAEHPAV1@@Z=?set@Rva0031410CDwordSlot@@QAEXH@Z")
//   0x00314119 reads ?Set_Subdivision_Level@ParticleEmitterDefClass@@UAEXH@Z
#pragma comment(linker, "/alternatename:?winSetPrevInLayout@GameWindow@@QAEHPAV1@@Z=?Set_Subdivision_Level@ParticleEmitterDefClass@@UAEXH@Z")
//   0x00538B2F reads ?rva00538B2F@Rva00538B2F@@QAEPAURva0052A28EDwordField@@PAU2@@Z
#pragma comment(linker, "/alternatename:?findWindow@WindowLayout@@AAEPAVGameWindow@@PAV2@@Z=?rva00538B2F@Rva00538B2F@@QAEPAURva0052A28EDwordField@@PAU2@@Z")
//   0x0052A28E reads ?get@Rva0052A28EDwordField@@QBEHXZ
#pragma comment(linker, "/alternatename:?winGetNextInLayout@GameWindow@@QAEPAV1@XZ=?get@Rva0052A28EDwordField@@QBEHXZ")
//   0x0031412D reads ?get@Rva0031412DDwordField@@QBEHXZ
#pragma comment(linker, "/alternatename:?winGetPrevInLayout@GameWindow@@QAEPAV1@XZ=?get@Rva0031412DDwordField@@QBEHXZ")

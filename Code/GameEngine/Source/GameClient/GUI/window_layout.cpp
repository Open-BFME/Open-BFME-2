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
#include "../../../../../reference/open-bfme-1/game/GameEngine/Source/GameClient/window_layout.h"

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

// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /MD /EHsc /DNDEBUG
// platformsdk
// Reference: ZH GameWindow::winPointInChild through open-bfme-1 revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76. Target boundary3141BC-3142E1
// independently proves status+8, size+C/+10, region+14..20, next1F8,
// parent200 and child204. Signed bounds and parent accumulation follow donor;
// native adds status20000000 to enabled recursion. Its original flag name
// is unknown. Disabled-click sound uses native MiscAudio reference+88 and
// shared136-byte event; constructor value30=2 purpose remains unproven.
// Window/manager view names disclaim original owner identity and full sizes.
#include <windows.h>
#include "Common/BfmeAudioEventPrefix136.h"
typedef int Int; typedef bool Bool;
#define BitTest(value,mask) (((value)&(mask))!=0)
enum { WIN_STATUS_ABOVE=0x20, WIN_STATUS_BELOW=0x40, WIN_STATUS_ENABLED=8, WIN_STATUS_NO_INPUT=0x200 };
enum { WIN_STATUS_HIDDEN = 0x10 };
struct CursorCoord { int x,y; };
struct CursorRegion { CursorCoord lo,hi; };
class Rva003141BCWindowView {
public:
 unsigned char opaque0[8]; unsigned m_status; CursorCoord m_size;
 CursorRegion m_region; unsigned char opaque24[0x1F8-0x24];
 Rva003141BCWindowView*m_next; void*unknown1FC; Rva003141BCWindowView*m_parent; Rva003141BCWindowView*m_child;
 Rva003141BCWindowView*rva003142E1(int,int,bool,bool);
};
class GameWindow { public: GameWindow *winPointInChild(int,int,bool,bool=false); };
class AudioManager; extern AudioManager *TheAudio;
// Native2C1629-2C176C; capture/grab/modal precedence and three status passes
// follow ZH GameWindowManager donor; manager accessed prefix only.
struct CursorModalView { void*unknown0; Rva003141BCWindowView*window; };
class CursorManagerView {
public:
 unsigned char opaque0[12]; Rva003141BCWindowView*m_windowList;
 unsigned char opaque10[12]; Rva003141BCWindowView*m_mouseCaptor;
 void*unknown20; CursorModalView*m_modalHead; Rva003141BCWindowView*m_grabWindow;
 Rva003141BCWindowView*getWindowUnderCursor(int,int,bool);
};
Rva003141BCWindowView *CursorManagerView::getWindowUnderCursor( Int x, Int y, Bool ignoreEnabled )
{
	if( m_mouseCaptor )
	{
		// in what what window within the captured window are we?
		return reinterpret_cast<Rva003141BCWindowView *>(reinterpret_cast<GameWindow *>(m_mouseCaptor)->winPointInChild( x, y, ignoreEnabled ));
	}

	if( m_grabWindow )
	{
		// in what what window within the grabbed window are we?
		return reinterpret_cast<Rva003141BCWindowView *>(reinterpret_cast<GameWindow *>(m_grabWindow)->winPointInChild( x, y, ignoreEnabled ));
	}

	Rva003141BCWindowView *window = NULL;
	if( m_modalHead && m_modalHead->window )
	{
		return reinterpret_cast<Rva003141BCWindowView *>(reinterpret_cast<GameWindow *>(m_modalHead->window)->winPointInChild( x, y, ignoreEnabled ));
	}
	else
	{
		// search for top-level window which contains pointer
		for( window = m_windowList; window; window = window->m_next )
		{

			if( BitTest( window->m_status, WIN_STATUS_ABOVE ) &&
					!BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
					x >= window->m_region.lo.x &&
					x <= window->m_region.hi.x &&
					y >= window->m_region.lo.y &&
					y <= window->m_region.hi.y)
			{
				if( BitTest( window->m_status, WIN_STATUS_ENABLED ) || ignoreEnabled )
				{
					// determine which child window the mouse is in
					window = reinterpret_cast<Rva003141BCWindowView *>(reinterpret_cast<GameWindow *>(window)->winPointInChild( x, y, ignoreEnabled ));
					break;  // exit for
				}
			}  // end if
		}  // end for window

		// check !above, below and hidden
		if( window == NULL )
		{
			for( window = m_windowList; window; window = window->m_next )
			{
				if( !BitTest( window->m_status, WIN_STATUS_ABOVE | 
																				WIN_STATUS_BELOW | 
																				WIN_STATUS_HIDDEN ) &&
						x >= window->m_region.lo.x &&
						x <= window->m_region.hi.x &&
						y >= window->m_region.lo.y &&
						y <= window->m_region.hi.y)
				{
					if( BitTest( window->m_status, WIN_STATUS_ENABLED )|| ignoreEnabled)
					{								
						// determine which child window the mouse is in
						window = reinterpret_cast<Rva003141BCWindowView *>(reinterpret_cast<GameWindow *>(window)->winPointInChild( x, y, ignoreEnabled ));
						break;  // exit for
					}
				}
			}
		}  // end if, window == NULL

		// check below and !hidden
		if( window == NULL )
		{
			for( window = m_windowList; window; window = window->m_next )
			{
				if( BitTest( window->m_status, WIN_STATUS_BELOW ) &&
						!BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
						x >= window->m_region.lo.x &&
						x <= window->m_region.hi.x &&
						y >= window->m_region.lo.y &&
						y <= window->m_region.hi.y)
				{
					if( BitTest( window->m_status, WIN_STATUS_ENABLED )|| ignoreEnabled)
					{
						// determine which child window the mouse is in
						window = reinterpret_cast<Rva003141BCWindowView *>(reinterpret_cast<GameWindow *>(window)->winPointInChild( x, y, ignoreEnabled ));
						break;  // exit for
					}
				}
			}
		}  // end if
	}  // end else, no modal head

	if( window )
	{
		if( BitTest( window->m_status, WIN_STATUS_NO_INPUT ))
		{
			// this window does not accept input, discard
			window = NULL;
		}
		else if( ignoreEnabled && !( BitTest( window->m_status, WIN_STATUS_ENABLED ) ))
		{
			window = NULL;
		}
	}

	return window;
}

// BF1 9cbfb551fe GameWindowManager.cpp testGrab is a semantic guide only.
// Native 002C176C..002C1777 is independently complete: previous CursorSearch
// RET12 ends here; the next body starts with its own prologue. This leaf reads
// stack argument8 and returns an EAX dword0-or1 with RET0. No literal native
// function-pointer references were found. Original name, full argument count
// and callback role remain unknown; this address-owned function states only
// the observed two-slot prefix. The donor callback identity is not asserted.
unsigned int __cdecl rva002C176C(unsigned int unused, unsigned int value)
{
    return value == 5;
}

// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /MD /EHsc /DNDEBUG
// Reference: ZH GameWindow::winPointInChild through open-bfme-1 revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76. Target boundary3141BC-3142E1
// independently proves status+8, size+C/+10, region+14..20, next1F8,
// parent200 and child204. Signed bounds and parent accumulation follow donor;
// native adds status20000000 to enabled recursion. Its original flag name
// is unknown. Disabled-click sound uses native MiscAudio reference+88 and
// shared136-byte event; constructor value30=2 purpose remains unproven.
// Window/manager view names disclaim original owner identity and full sizes.
#include "Common/BfmeAudioEventPrefix136.h"
typedef int Int; typedef bool Bool;
#define NULL 0
#define BitTest(value,mask) (((value)&(mask))!=0)
enum { WIN_STATUS_ABOVE=0x20, WIN_STATUS_BELOW=0x40, WIN_STATUS_HIDDEN=0x10, WIN_STATUS_ENABLED=8, WIN_STATUS_NO_INPUT=0x200 };
struct CursorCoord { int x,y; };
struct CursorRegion { CursorCoord lo,hi; };
class Rva003141BCWindowView {
public:
 unsigned char opaque0[8]; unsigned m_status; CursorCoord m_size;
 CursorRegion m_region; unsigned char opaque24[0x1F8-0x24];
 Rva003141BCWindowView*m_next; void*unknown1FC; Rva003141BCWindowView*m_parent; Rva003141BCWindowView*m_child;
 Rva003141BCWindowView*winPointInChild(int,int,bool,bool=false);
 Rva003141BCWindowView*rva003142E1(int,int,bool,bool);
};
class AudioManager; extern AudioManager *TheAudio;
struct Rva003141BCMiscView { char unknown[0x88]; OpaqueRefElement4 disabledClick; };
class Rva003141BCAudioView { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void addAudioEvent(const BfmeAudioEventPrefix136 *);
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual const Rva003141BCMiscView *getMiscAudio();
};
Rva003141BCWindowView *Rva003141BCWindowView::winPointInChild(int x,int y,bool ignoreEnableCheck,bool playDisabledSound)
{
    for (Rva003141BCWindowView *child=m_child;child;child=child->m_next) {
        CursorCoord origin=child->m_region.lo;
        Rva003141BCWindowView *parent=child->m_parent;
        while(parent) {
            origin.x+=parent->m_region.lo.x;
            origin.y+=parent->m_region.lo.y;
            parent=parent->m_parent;
        }
        if (x>=origin.x && x<=origin.x+child->m_size.x && y>=origin.y && y<=origin.y+child->m_size.y) {
            bool enabled=ignoreEnableCheck || BitTest(child->m_status,WIN_STATUS_ENABLED);
            bool hidden=BitTest(child->m_status,WIN_STATUS_HIDDEN);
            if (!hidden) {
                if (enabled || BitTest(child->m_status,0x20000000))
                    return child->winPointInChild(x,y,ignoreEnableCheck,playDisabledSound);
                else if (playDisabledSound && TheAudio) {
                    BfmeAudioEventPrefix136 disabledClick(reinterpret_cast<Rva003141BCAudioView *>(TheAudio)->getMiscAudio()->disabledClick,2);
                    reinterpret_cast<Rva003141BCAudioView *>(TheAudio)->addAudioEvent(&disabledClick);
                }
            }
        }
    }
    return this;
}

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
		return m_mouseCaptor->winPointInChild( x, y, ignoreEnabled );
	}

	if( m_grabWindow )
	{
		// in what what window within the grabbed window are we?
		return m_grabWindow->winPointInChild( x, y, ignoreEnabled );
	}

	Rva003141BCWindowView *window = NULL;
	if( m_modalHead && m_modalHead->window )
	{
		return m_modalHead->window->winPointInChild( x, y, ignoreEnabled );
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
					window = window->winPointInChild( x, y, ignoreEnabled );
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
						window = window->winPointInChild( x, y, ignoreEnabled );
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
						window = window->winPointInChild( x, y, ignoreEnabled );
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

Rva003141BCWindowView *Rva003141BCWindowView::rva003142E1(int x, int y, bool a3, bool a4)
{
	for (Rva003141BCWindowView *child = m_child; child; child = child->m_next) {
		int ox = child->m_region.lo.x;
		int oy = child->m_region.lo.y;
		Rva003141BCWindowView *parent = child->m_parent;
		while (parent) {
			ox += parent->m_region.lo.x;
			oy += parent->m_region.lo.y;
			parent = parent->m_parent;
		}
		if (x >= ox && x <= ox + child->m_size.x && y >= oy && y <= oy + child->m_size.y) {
			if (a3 != true || !BitTest(child->m_status, WIN_STATUS_HIDDEN)) {
				return child->winPointInChild(x, y, a4, false);
			}
		}
	}
	return this;
}

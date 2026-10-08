// ?winProcessMouseEvent@GameWindowManager@@UAE?AW4WinInputReturnCode@@W4GameWindowMessage@@PAUICoord2D@@PAX@Z
// partial score=0.9927227074 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Isolated portable trial, from the entire ZH GameWindowManager.cpp reviewed
// at BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
// Target native 2C1FD5..2C2533 proves the accessed prefixes, child/point-test
// providers, virtual-call slots, one-pass UI-layer search and grabbed-position case.
// Unknown layout gaps and virtual slots remain neutral; no complete class ABI asserted.
#include "unicode_string.h"
typedef int Int; typedef unsigned int UnsignedInt; typedef bool Bool;
#define NULL 0
#define TRUE true
#define FALSE false
#define BitTest(v,m) (((v)&(m))!=0)
#define BitClear(v,m) ((v)&=~(m))
#define SHORTTOLONG(a,b) ((unsigned short)(a)|((unsigned short)(b)<<16))
enum GameWindowMessage { GWM_NONE=0, GWM_LEFT_DOWN=5,GWM_LEFT_UP=6,GWM_LEFT_DRAG=8,GWM_MIDDLE_UP=10,GWM_RIGHT_UP=14,GWM_MOUSE_ENTERING=17,GWM_MOUSE_LEAVING=18,GWM_MOUSE_POS=24 };
enum { MOUSE_EVENT_NONE=0, WIN_STATUS_ACTIVE=1,WIN_STATUS_DRAGABLE=4,WIN_STATUS_HIDDEN=0x10,WIN_STATUS_ABOVE=0x20,WIN_STATUS_BELOW=0x40,WIN_STATUS_NO_INPUT=0x200,GWS_COMBO_BOX=0x8000 };
enum WinInputReturnCode { WIN_INPUT_NOT_USED=0, WIN_INPUT_USED=1 };
enum WindowMsgHandledType { MSG_IGNORED=0, MSG_HANDLED=1 };
struct ICoord2D { Int x,y; }; struct IRegion2D { ICoord2D lo,hi; };
class GameWindow;
class WinInstanceData {
public:
 char opaque00[0x0C]; UnsignedInt m_style; char opaque10[0x198-0x10];
 Int m_tooltipDelay; void *m_text, *m_tooltip, *m_videoBuffer;
 UnsignedInt getStyle() { return m_style; }
 UnicodeString getTooltipText(); Int getTooltipTextLength();
};
class Rva003141BCWindowView { public: Rva003141BCWindowView *winPointInChild(int,int,bool=false,bool=false); };
class Rva002C027B { public: void *rva002C027B(); };
class Rva003140AB { public: bool rva003140AB(Rva003140AB*); };
class GameWindow {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
 virtual void invokeTooltip(WinInstanceData*, UnsignedInt);
 virtual void slot14(); virtual void slot18(); virtual void slot1C(); virtual void slot20(); virtual Bool hasTooltip();
 void *callback04; UnsignedInt m_status; ICoord2D m_size; IRegion2D m_region;
 char opaque24[0x30-0x24]; WinInstanceData m_instData;
 char opaque1D8[0x1F4-0x1D8]; Int bfmeLayer;
 GameWindow *m_next,*m_prev,*m_parent,*m_child;
 GameWindow *winGetParent(); WinInstanceData *winGetInstanceData();
 GameWindow *winPointInAnyChild(int,int,bool,bool);
 unsigned char rva003147F6(int,int);
 Int winGetPosition(Int*,Int*); Int winGetSize(Int*,Int*); Int winSetPosition(Int,Int);
};
struct ModalWindow { void *unknown0; GameWindow *window; };
class GameWindowManager { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5C();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual void slot6C();
 virtual void slot70();
 virtual void slot74();
 virtual void slot78();
 virtual void slot7C();
 virtual void slot80();
 virtual void slot84();
 virtual void slot88();
 virtual void slot8C();
 virtual void slot90();
 virtual void slot94();
 virtual void slot98();
 virtual void slot9C();
 virtual void slotA0();
 virtual void slotA4();
 virtual void slotA8();
 virtual void slotAC();
 virtual void slotB0();
 virtual void slotB4();
 virtual WinInputReturnCode winProcessMouseEvent(GameWindowMessage,ICoord2D*,void*);
 virtual void slotBC();
 virtual void slotC0();
 virtual void slotC4();
 virtual void slotC8();
 virtual void slotCC();
 virtual void winSetLoneWindow(GameWindow*);
 virtual void slotD4(); virtual void slotD8(); virtual Bool isHidden(GameWindow*);
 virtual void slotE0(); virtual void slotE4(); virtual void slotE8();
 virtual WindowMsgHandledType winSendInputMsg(GameWindow*,UnsignedInt,UnsignedInt,UnsignedInt);
 char opaque04[8]; GameWindow *m_windowList,*m_windowTail,*m_destroyList,*m_currMouseRgn,*m_mouseCaptor,*m_keyboardFocus;
 ModalWindow *m_modalHead; GameWindow *m_grabWindow,*m_loneWindow;
 void *tabNode30,*cursorBitmap34; unsigned captureFlags38; int bfmeCurrentLayer;
};
class Display;
class BfmeMouseDisplayView { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual unsigned int getWidth(); virtual unsigned int getHeight();
};
struct RGBColor;
class Mouse { public: void rva001EEA6D(UnicodeString,int=-1,const RGBColor * =0,float=1.0f); };
extern Mouse *TheMouse; extern Display *TheDisplay;
static Bool sendMousePosMessages=TRUE;
WinInputReturnCode GameWindowManager::winProcessMouseEvent( GameWindowMessage msg,
																														ICoord2D *mousePos,
																														void *data )
{
	WinInputReturnCode returnCode = WIN_INPUT_NOT_USED;
	Bool objectTooltip = FALSE;
	UnsignedInt packedMouseCoords;
	GameWindow *window = NULL;
	GameWindow *toolTipWindow = NULL;
	GameWindow *childWindow;
	Int dx, dy;
	Bool clearGrabWindow = FALSE;

	// pack mouse coords into one entity for message passing
	packedMouseCoords = SHORTTOLONG( mousePos->x, mousePos->y );

	// clear tooltip ... it will be reset if necessary
	TheMouse->rva001EEA6D( UnicodeString::TheEmptyString );

	// Check for mouse capture
	if( m_mouseCaptor )
	{

		// no window grabbed as of yet
		m_grabWindow = NULL;

		// what what window within the captured window are we in
		window = reinterpret_cast<GameWindow*>(reinterpret_cast<Rva003141BCWindowView*>(m_mouseCaptor)->winPointInChild( mousePos->x, mousePos->y ));

		//
		// send buttons, drags, wheels to the windows, we don't continually
		// send mouse positions
		//
		if( sendMousePosMessages == TRUE || msg != GWM_MOUSE_POS )
		{
			GameWindow *win = window;

			if( win )
			{
				while( win != NULL )
				{

					if( winSendInputMsg( win, msg, packedMouseCoords, 0 ) == MSG_HANDLED )
					{

						// if used clear the event
						returnCode = WIN_INPUT_USED;
						break;

					}

					// if we just tested mouseCaptor don't go any higher in the chain
					if( win == m_mouseCaptor )
						break;

					win = win->winGetParent();

				}  // end while

			}  // end if
			else
			{

				// if used clear the event
				if(	winSendInputMsg( m_mouseCaptor, msg, packedMouseCoords, 0 ) == MSG_HANDLED )
					returnCode = WIN_INPUT_USED;

			}  // end else

		}  // end if

	}  // end if, mouse captor window present
	else
	{

		if( m_grabWindow )
		{
			GameWindow *parent;

			switch( msg )
			{

				// Native 2C20DD..2C210B: grabbed-window position messages.
				case GWM_MOUSE_POS:
					if( sendMousePosMessages && m_grabWindow->rva003147F6(mousePos->x, mousePos->y) )
						winSendInputMsg(m_grabWindow, GWM_MOUSE_POS, packedMouseCoords, 0);
					break;

				// --------------------------------------------------------------------
				case GWM_LEFT_UP:
				{
					//Play a beep sound if the window is disabled.
					reinterpret_cast<GameWindow*>(reinterpret_cast<Rva003141BCWindowView*>(m_grabWindow)->winPointInChild( mousePos->x, mousePos->y, FALSE, TRUE ));

					BitClear( m_grabWindow->m_status, WIN_STATUS_ACTIVE );
					if( m_grabWindow->rva003147F6( mousePos->x, mousePos->y ) )
						winSendInputMsg( m_grabWindow, GWM_LEFT_UP, packedMouseCoords, 0 );
					else if( BitTest( m_grabWindow->m_status, WIN_STATUS_DRAGABLE ))
					{
						winSendInputMsg( m_grabWindow, GWM_LEFT_UP, packedMouseCoords, 0 );
					}

					clearGrabWindow = TRUE;
					break;

				}  // end left up

				// --------------------------------------------------------------------
				case MOUSE_EVENT_NONE:
				case GWM_LEFT_DRAG:
				{

					if( BitTest( m_grabWindow->m_status, WIN_STATUS_DRAGABLE ) )
					{
						ICoord2D *mouseDelta = (ICoord2D *)data;
						dx = mouseDelta->x;
						dy = mouseDelta->y;

						// Clip window to parent
						if( m_grabWindow->winGetParent() )
						{

							parent = m_grabWindow->winGetParent();

							if( m_grabWindow->m_region.lo.x + dx < 0 )
								dx = 0 - m_grabWindow->m_region.lo.x;
							else if( m_grabWindow->m_region.hi.x + dx > parent->m_size.x )
								dx = parent->m_size.x - m_grabWindow->m_region.hi.x;

							if( m_grabWindow->m_region.lo.y + dy < 0 )
								dy = 0 - m_grabWindow->m_region.lo.y;
							else if( m_grabWindow->m_region.hi.y + dy > parent->m_size.y )
								dy = parent->m_size.y - m_grabWindow->m_region.hi.y;
						}

						// Move the window, but keep it completely visible within screen boundaries
						IRegion2D newRegion;
						ICoord2D grabSize;

						m_grabWindow->winGetPosition( &newRegion.lo.x, &newRegion.lo.y );
						m_grabWindow->winGetSize( &grabSize.x, &grabSize.y );

						newRegion.lo.x += dx;
						newRegion.lo.y += dy;
						if( newRegion.lo.x < 0 )
							newRegion.lo.x = 0;
						if( newRegion.lo.y < 0 )
							newRegion.lo.y = 0;
						
						newRegion.hi.x = grabSize.x + newRegion.lo.x;
						newRegion.hi.y = grabSize.y + newRegion.lo.y;
						if( newRegion.hi.x > (Int)reinterpret_cast<BfmeMouseDisplayView*>(TheDisplay)->getWidth() )
							newRegion.hi.x = (Int)reinterpret_cast<BfmeMouseDisplayView*>(TheDisplay)->getWidth();
						if( newRegion.hi.y > (Int)reinterpret_cast<BfmeMouseDisplayView*>(TheDisplay)->getHeight() )
							newRegion.hi.y = (Int)reinterpret_cast<BfmeMouseDisplayView*>(TheDisplay)->getHeight();
						
						newRegion.lo.x = newRegion.hi.x - grabSize.x;
						newRegion.lo.y = newRegion.hi.y - grabSize.y;

						m_grabWindow->winSetPosition( newRegion.lo.x, newRegion.lo.y );

					}  // end if, draggable window

					// Send mouse drag message
					winSendInputMsg( m_grabWindow, msg, packedMouseCoords, 0 );
					break;

				}  // end mouse event none or left drag

			}  // end switch

			// mark event handled
			returnCode = WIN_INPUT_USED;

		}  // end if, m_grabWindow
		else
		{

			if( m_modalHead && m_modalHead->window )
			{
				window = reinterpret_cast<GameWindow*>(reinterpret_cast<Rva003141BCWindowView*>(m_modalHead->window)->winPointInChild( mousePos->x, mousePos->y ));
			}
			else
			{
			
				GameWindow *normalWindow = NULL;
				GameWindow *belowWindow = NULL;
				for( window = m_windowList; window; window = window->m_next )
				{
					if( !BitTest(window->m_status, WIN_STATUS_HIDDEN) &&
						window->bfmeLayer == bfmeCurrentLayer &&
						mousePos->x >= window->m_region.lo.x &&
						mousePos->x <= window->m_region.hi.x &&
						mousePos->y >= window->m_region.lo.y &&
						mousePos->y <= window->m_region.hi.y )
					{
						if( BitTest(window->m_status, WIN_STATUS_ABOVE) ) break;
						if( BitTest(window->m_status, WIN_STATUS_BELOW) )
						{
							if( belowWindow == NULL ) belowWindow = window;
						}
						else if( normalWindow == NULL ) normalWindow = window;
					}
				}
				if( window == NULL ) window = normalWindow ? normalWindow : belowWindow;
				if( window )
				{
					childWindow = window->winPointInAnyChild(mousePos->x, mousePos->y, TRUE, TRUE);
					if( childWindow->hasTooltip() ||
						reinterpret_cast<Rva002C027B*>(&childWindow->m_instData)->rva002C027B() ) toolTipWindow = childWindow;
					window = reinterpret_cast<GameWindow*>(reinterpret_cast<Rva003141BCWindowView*>(window)->winPointInChild(mousePos->x, mousePos->y));
				}

			}  // end else, no modal head

			if( window )
				if( BitTest( window->m_status, WIN_STATUS_NO_INPUT ) )
				{
					if(window->winGetParent() && BitTest( window->winGetParent()->winGetInstanceData()->getStyle(), GWS_COMBO_BOX ))
						window = window->winGetParent();
					else
						window = NULL;
				}

			if( window )
			{
				GameWindow *tempWin;

				//
				// only send messages for button states, wheel states, we do not
				// continually send messages for mouse positions
				//
				if( sendMousePosMessages == TRUE || msg != GWM_MOUSE_POS )
				{

					tempWin = window;
	
					// Give everyone a chance to do something with the clicks
					GameWindow *oldLoneWindow = m_loneWindow;
					while( winSendInputMsg( tempWin, msg, packedMouseCoords, 0 ) == MSG_IGNORED )
					{

						tempWin = tempWin->m_parent;
						if( tempWin == NULL )
							break;

					}  // end while

						
					// First check to see if m_loneWindow is set if so, close the window
					if( m_loneWindow && m_loneWindow == oldLoneWindow 
					&&( msg == GWM_LEFT_UP || msg == GWM_MIDDLE_UP || msg == GWM_RIGHT_UP || tempWin))
					{
						if(!reinterpret_cast<Rva003140AB*>(m_loneWindow)->rva003140AB(reinterpret_cast<Rva003140AB*>(tempWin)))
							winSetLoneWindow( NULL );
						/*
								ComboBoxData *cData = (ComboBoxData *)m_comboBoxOpen->winGetUserData();
															// verify that the window that ate the message wasn't one of our own
															if(cData->dropDownButton != tempWin &&
																cData->editBox != tempWin &&
																cData->listBox != tempWin &&
																cData->listboxData->upButton != tempWin &&
																cData->listboxData->downButton != tempWin &&
																cData->listboxData->slider != tempWin &&
																cData->listboxData->slider != tempWin->winGetParent())
																	winSetOpenComboBoxWindow( NULL );*/
								
					}
					if( tempWin )
					{
					
						//
						// Someone cares, if this is a left button down event
						// it should get "grabbed"
						/// @todo should allow for left handed mouse configs here?
						//
						if( msg == GWM_LEFT_DOWN )
						{

//						if( tempWin != windowList ) 
//							WinActivate( tempWin );
							m_grabWindow = tempWin;

						}  // end if

						// event is used
						returnCode = WIN_INPUT_USED;

					}  // end if, tempWin

				}  // end if

			}  // end if( window ) 

			if( toolTipWindow == NULL )
			{

				if( isHidden( window ) == FALSE )
					toolTipWindow = window;

			}  // end if

			// if tooltips are on set them into the window
			Bool tooltipsOn = TRUE;
			if( tooltipsOn )
			{
//				if( toolTipWindow && toolTipWindow->winGetParent() && BitTest( toolTipWindow->winGetParent()->winGetInstanceData()->getStyle(), GWS_COMBO_BOX ))
//					toolTipWindow = toolTipWindow->winGetParent();
				if( toolTipWindow )
				{
					// do we have a callback to call for the tooltip
					if( toolTipWindow->hasTooltip() )
						toolTipWindow->invokeTooltip(
                          &toolTipWindow->m_instData, packedMouseCoords );

					// else, do we have a normal tooltip to set
					else if( reinterpret_cast<Rva002C027B*>(&toolTipWindow->m_instData)->rva002C027B() )
						TheMouse->rva001EEA6D( toolTipWindow->m_instData.getTooltipText(), toolTipWindow->m_instData.m_tooltipDelay );

				}  // end if
				else
				{

					//
					// not pointing at a window... perhaps we are pointing at a valid
					// tooltip-able object in the game world ... let's set a flag so 
					// during the object testing we can set the tooltip, we can do
					// whatever we like now that we know no other tooltip was set from
					// a window
					//
					objectTooltip = TRUE;

				}  // end else

			}  // end if

		}  // end if grabWindow not present

	}  // end else (mouseCaptor) 

	//
	// check if new current window is different from the last
	// but only if both windows fall within the mouseCaptor if one exists
	//
	if( (m_grabWindow == NULL) && (window != m_currMouseRgn) )
	{
		if( m_mouseCaptor )
		{
			if( reinterpret_cast<Rva003140AB*>(m_mouseCaptor)->rva003140AB(reinterpret_cast<Rva003140AB*>(m_currMouseRgn)) )
				winSendInputMsg( m_currMouseRgn, GWM_MOUSE_LEAVING, packedMouseCoords, 0 );
		}
		else if( m_currMouseRgn )
			winSendInputMsg( m_currMouseRgn, GWM_MOUSE_LEAVING, packedMouseCoords, 0 );

		if( window )
			winSendInputMsg( window, GWM_MOUSE_ENTERING, packedMouseCoords, 0 );

		m_currMouseRgn = window;

	}  // end if

	// clear grabWindow if necessary
	if( clearGrabWindow == TRUE )
	{

		m_grabWindow = NULL;
		clearGrabWindow = FALSE;

	}  // end if

	return returnCode;

}  // end winProcessMouseEvent

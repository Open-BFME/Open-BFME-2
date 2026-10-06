// cl: /DNDEBUG /MD /EHsc- /Ireference/shims/bfme2_ascii
// Clean BFME1 6d9434269164392c5ba62aaa7c15a86b5b020d76 GadgetPushButtonBodies donor.
// Callback table and native328639/199 establish the four message cases.
// Native facts: instance state+8/owner14, display pointer30/free slot3C,
// manager slotE8, direct text setter31484A and cleanup327E50. Donor carries names.
// The userdata field1C is opaque here; retail dtor releases its referenced owner.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "../GameWindowManagerRecordView.h"
#include <stddef.h>
#include <wchar.h>
#include "unicode_string.h"
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
enum
{
	GWM_CREATE			= 1,
	GWM_DESTROY			= 2,
	GWM_INPUT_FOCUS		= 23,
	GGM_SET_LABEL		= 16385,
	GGM_FOCUS_CHANGE	= 16387
};
enum { WIN_STATE_HILITED = 0x00000002 };
class DisplayString;
class DisplayStringManager;
class BfmeDisplayStringManager
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_0C() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_1C() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _native_pad_28() = 0;
	virtual void _native_pad_2C() = 0;
	virtual void _native_pad_30() = 0;
	virtual void _native_pad_34() = 0;
	virtual void _native_pad_38() = 0;
	virtual void freeDisplayString( DisplayString *string ) = 0;
};
extern DisplayStringManager *TheDisplayStringManager;
static inline BfmeDisplayStringManager *theDisplayStringManagerView()
{
	return (BfmeDisplayStringManager *)TheDisplayStringManager;
}
struct PushButtonData
{
	unsigned char m_unmodelled_00[ 0x1C ];
	void *m_owner1C;
	unsigned char m_unmodelled_20[ 0x10 ];
	DisplayString *m_displayString;
	~PushButtonData();
};
class WinInstanceData
{
public:
	class GameWindow *getOwner() { return m_owner; }
	unsigned char m_unmodelled_00[ 8 ];
	UnsignedInt m_state;
	unsigned char m_unmodelled_0C[ 8 ];
	class GameWindow *m_owner;
};
class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
	void *winGetUserData();
	void winSetUserData( void *data );
	Int winGetWindowId();
	virtual Int winSetText( UnicodeString text );
};
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
WindowMsgHandledType GadgetPushButtonSystem( GameWindow *window, UnsignedInt msg,
											 WindowMsgData mData1, WindowMsgData mData2 )
{
	WinInstanceData *instData = window->winGetInstanceData();
	switch( msg )
	{
		case GGM_SET_LABEL:
		{
			window->GameWindow::winSetText( *(UnicodeString *)mData1 );
			break;
		}
		case GWM_CREATE:
			break;
		case GWM_DESTROY:
		{
			PushButtonData *pData = (PushButtonData *)window->winGetUserData();
			if( pData )
			{
				theDisplayStringManagerView()->freeDisplayString( pData->m_displayString );
				delete pData;
			}
			window->winSetUserData( NULL );
		}
			break;
		case GWM_INPUT_FOCUS:
			if( mData1 == 0 )
				instData->m_state &= ~WIN_STATE_HILITED;
			else
				instData->m_state |= WIN_STATE_HILITED;
			typedef void (TabWindowManagerView::*SendMsg)(GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData);
			(((TabWindowManagerView *)TheWindowManager)->*(*(SendMsg *)&(*(void ***)TheWindowManager)[58]))( instData->getOwner(),
												GGM_FOCUS_CHANGE,
												(WindowMsgData)mData1,
												window->winGetWindowId() );
			if( mData1 == 0 )
				*(Bool *)mData2 = false;
			else
				*(Bool *)mData2 = true;
			break;
		default:
			return MSG_IGNORED;
	}
	return MSG_HANDLED;
}

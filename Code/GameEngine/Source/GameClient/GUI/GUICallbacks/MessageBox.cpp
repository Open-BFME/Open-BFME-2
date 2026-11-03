// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// platformsdk
//
// Zero Hour's GUICallbacks/MessageBox.cpp window system for the generic WND
// message box: retail 0x0044BA8B, 491B. BFME2 leaves GWM_CREATE to the
// default (ignored) arm; the four buttons' name keys are function statics
// (guard bits at VA 0x00E0337C) and each button runs its callback, if any,
// before the box is destroyed.

#include <windows.h>
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;

typedef void (*GameWinMsgBoxFunc)(void);
struct WindowMessageBoxData
{
	GameWinMsgBoxFunc yesCallback;
	GameWinMsgBoxFunc noCallback;
	GameWinMsgBoxFunc okCallback;
	GameWinMsgBoxFunc cancelCallback;
};

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
enum
{
	GWM_DESTROY = 2,
	GWM_INPUT_FOCUS = 0x17,
	GBM_SELECTED = 0x4008
};

WindowMsgHandledType MessageBoxSystem( GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2 )
{
	switch( msg )
	{
		case GWM_DESTROY:
		{
			delete (WindowMessageBoxData *)window->winGetUserData();
			window->winSetUserData( NULL );
			break;
		}

		case GWM_INPUT_FOCUS:
		{
			if( mData1 == true )
				*(Bool *)mData2 = true;
			break;
		}

		case GBM_SELECTED:
		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();
			static NameKeyType buttonOkID = TheNameKeyGenerator->nameToKey( AsciiString( "MessageBox.wnd:ButtonOk" ) );
			static NameKeyType buttonYesID = TheNameKeyGenerator->nameToKey( AsciiString( "MessageBox.wnd:ButtonYes" ) );
			static NameKeyType buttonNoID = TheNameKeyGenerator->nameToKey( AsciiString( "MessageBox.wnd:ButtonNo" ) );
			static NameKeyType buttonCancelID = TheNameKeyGenerator->nameToKey( AsciiString( "MessageBox.wnd:ButtonCancel" ) );
			WindowMessageBoxData *MsgBoxCallbacks = (WindowMessageBoxData *)window->winGetUserData();

			if( controlID == buttonOkID )
			{
				if (MsgBoxCallbacks->okCallback)
					MsgBoxCallbacks->okCallback();
				TheWindowManager->winDestroy(window);
			}
			else if( controlID == buttonYesID )
			{
				if (MsgBoxCallbacks->yesCallback)
					MsgBoxCallbacks->yesCallback();
				TheWindowManager->winDestroy(window);
			}
			else if( controlID == buttonNoID )
			{
				if (MsgBoxCallbacks->noCallback)
					MsgBoxCallbacks->noCallback();
				TheWindowManager->winDestroy(window);
			}
			else if( controlID == buttonCancelID )
			{
				if (MsgBoxCallbacks->cancelCallback)
					MsgBoxCallbacks->cancelCallback();
				TheWindowManager->winDestroy(window);
			}
			break;
		}

		default:
			return MSG_IGNORED;
	}
	return MSG_HANDLED;
}

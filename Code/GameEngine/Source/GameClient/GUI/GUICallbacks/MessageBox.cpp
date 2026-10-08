// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// Zero Hour's GUICallbacks/MessageBox.cpp window system for the generic WND
// message box: retail 0x0044BA8B, 491B. BFME2 leaves GWM_CREATE to the
// default (ignored) arm; the four buttons' name keys are function statics
// (guard bits at VA 0x00E0337C) and each button runs its callback, if any,
// before the box is destroyed.

#include "ascii_string.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;
#ifndef NULL
#define NULL 0
#endif

enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow
{
public:
	Int winGetWindowId(void);
	void *winGetUserData(void);
	void winSetUserData(void *data);
};

class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
	virtual Int winDestroy(GameWindow *window);
};
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

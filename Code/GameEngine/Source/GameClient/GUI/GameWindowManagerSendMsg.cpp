// cl: /O1 /Oy- /DNDEBUG /MD
// GameWindowManager::winSendSystemMsg (0x002C0E7D, 44B) and winSendInputMsg
// (0x002C0EA9, 44B): adjacent slots of the GameWindowManager vftable (rdata
// 0x007C7D78/0x007C7D7C) and of W3DGameWindowManager's (0x007FF740/0x007FF744).
// Zero Hour's guards are unchanged - a NULL window, or a destroyed one
// (WIN_STATUS_DESTROYED 0x800 in m_status, which BFME 2 keeps at +0x08) for
// anything but GWM_DESTROY, is ignored - but BFME 2 replaced the m_system /
// m_input callbacks with GameWindow members (0x0031452F / 0x00314511, pinned
// from these call sites) that dispatch through the window's handler object at
// +0x1DC or its own vftable. Retail keeps a frame pointer here, hence /Oy-.
// The Zero Hour bodies left GameWindowManager.cpp for these.

typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

enum
{
	GWM_DESTROY = 2
};

enum
{
	WIN_STATUS_DESTROYED = 0x00000800
};

class GameWindow
{
public:
	WindowMsgHandledType winSendSystemMsg( UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );
	WindowMsgHandledType winSendInputMsg( UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );

private:
	friend class GameWindowManager;
	void *m_vtable;
	unsigned int m_unrecovered04;
	UnsignedInt m_status;	///< 0x08
};

class GameWindowManager
{
public:
	virtual WindowMsgHandledType winSendSystemMsg( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );
	virtual WindowMsgHandledType winSendInputMsg( GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2 );
};

//-------------------------------------------------------------------------------------------------
/** Send a system message to the specified window */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType GameWindowManager::winSendSystemMsg( GameWindow *window, 
																					UnsignedInt msg,
																					WindowMsgData mData1, 
																					WindowMsgData mData2 )
{

	if( window == 0 )
		return MSG_IGNORED;

	if( msg != GWM_DESTROY && (window->m_status & WIN_STATUS_DESTROYED) )
		return MSG_IGNORED;

	return window->winSendSystemMsg( msg, mData1, mData2 );

}  // end winSendSystemMsg

//-------------------------------------------------------------------------------------------------
/** Send a system message to the specified window */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType GameWindowManager::winSendInputMsg( GameWindow *window, 
																				 UnsignedInt msg,
																				 WindowMsgData mData1, 
																				 WindowMsgData mData2 )
{

	if( window == 0 )
		return MSG_IGNORED;

	if( msg != GWM_DESTROY && (window->m_status & WIN_STATUS_DESTROYED) )
		return MSG_IGNORED;

	return window->winSendInputMsg( msg, mData1, mData2 );

}  // end winSendInputMsg

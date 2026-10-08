// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// Mouse event processing from Zero Hour's Mouse.cpp, with BFME 1's
// conversions (reference/open-bfme-1/game/GameEngine/Source/GameClient/Input/
// Mouse_processMouseEvent.cpp, Mouse_createStreamMessages.cpp) as the donors.
//
//   0x001EDCB1 updateMouseData        107B  getMouseEvent is vtable slot 29 (+0x74)
//   0x001EDE3A update                  11B  tail jump to updateMouseData
//   0x001EDC41 moveMouse              112B
//   0x001EDD1C checkForDrag           100B
//   0x001EE069 processMouseEvent      608B  calls checkForDrag and moveMouse
//   0x001EE630 createStreamMessages  1085B  Win32Mouse vtable 0x007C2478 slot 16
//
// Identity: createStreamMessages sits in the Mouse vtable between parseIni
// and setPosition, as in Zero Hour, and is the only caller of
// processMouseEvent; that body calls checkForDrag only for event 0 and passes
// the event position and the absolute/relative mode to moveMouse, as in both
// donors. moveMouse and checkForDrag were rowed earlier under address-derived
// names with exactly these bodies.
//
// Target layout, read off these bodies and Mouse::reset 0x001EE4DC (which
// clears the event array and both records): m_buttonActivity byte +0x1288;
// m_mouseEvents[256] from +0x130C (stride 0x3C); m_currMouse +0x4F0C;
// m_prevMouse +0x4F48; clamp bounds min/max X then Y from +0x4F84;
// m_inputFrame +0x4F94; m_deadInputFrame +0x4F98; m_inputMovesAbsolute byte +0x4F9C; m_eventsThisFrame
// +0x4FFC; the left/right click ages +0x5000/+0x5004. TheKeyboard's modifier
// word is at +0x0C. BFME 2 moves the raw mouse position message (3) after
// the click-age messages, where both Zero Hour and BFME 1 send it first.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

class GameMessage
{
public:
	void appendPixelArgument( const ICoord2D &position );
	void appendIntegerArgument( Int value );
};

class MessageStream
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17();
	virtual GameMessage *appendMessage( Int type );	// slot 18 (+0x48)
};
// The singleton is defined by Common/MessageStream.cpp. Native accesses
// read the same cell (RVA 0x00A00950, VA 0x00E00950).
extern MessageStream *TheMessageStream;

class Keyboard
{
public:
	Int getModifierFlags( void ) { return m_modifiers; }
private:
	char m_pad[0x0C];
	UnsignedShort m_modifiers;
};
extern Keyboard *TheKeyboard;

enum MouseButtonState
{
	MBS_Up = 0,
	MBS_Down,
	MBS_DoubleClick
};

enum GameWindowMessage
{
	GWM_LEFT_DOWN = 5,
	GWM_LEFT_UP,
	GWM_LEFT_DOUBLE_CLICK,
	GWM_LEFT_DRAG,
	GWM_MIDDLE_DOWN,
	GWM_MIDDLE_UP,
	GWM_MIDDLE_DOUBLE_CLICK,
	GWM_MIDDLE_DRAG,
	GWM_RIGHT_DOWN,
	GWM_RIGHT_UP,
	GWM_RIGHT_DOUBLE_CLICK,
	GWM_RIGHT_DRAG
};

#define MOUSE_NONE		0x00
#define MOUSE_LOST		0xFF

enum
{
	MOUSE_EVENT_NONE = 0,
	MOUSE_MOVE_RELATIVE = 0,
	MOUSE_MOVE_ABSOLUTE = 1
};

// BFME 2's GameMessage types for the mouse, read off createStreamMessages.
enum
{
	MSG_RAW_MOUSE_POSITION = 3,
	MSG_RAW_MOUSE_LEFT_BUTTON_DOWN,
	MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK,
	MSG_RAW_MOUSE_LEFT_BUTTON_UP,
	MSG_RAW_MOUSE_7,				// not sent from here
	MSG_RAW_MOUSE_LEFT_DRAG,
	MSG_RAW_MOUSE_LEFT_CLICK,
	MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN,
	MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK,
	MSG_RAW_MOUSE_MIDDLE_BUTTON_UP,
	MSG_RAW_MOUSE_MIDDLE_DRAG,
	MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN,
	MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK,
	MSG_RAW_MOUSE_RIGHT_BUTTON_UP,
	MSG_RAW_MOUSE_RIGHT_CLICK,
	MSG_RAW_MOUSE_RIGHT_DRAG,
	MSG_RAW_MOUSE_WHEEL
};

struct MouseIO
{
	ICoord2D pos;
	UnsignedInt time;
	Int wheelPos;
	ICoord2D deltaPos;
	MouseButtonState leftState;
	Int leftEvent;
	Int leftFrame;
	MouseButtonState rightState;
	Int rightEvent;
	Int rightFrame;
	MouseButtonState middleState;
	Int middleEvent;
	Int middleFrame;
};

class Mouse
{
public:
	enum { NUM_MOUSE_EVENTS = 256 };
	enum { CLICK_SENSITIVITY = 5 };

	virtual ~Mouse();
	virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06();
	virtual void vslot07(); virtual void vslot08(); virtual void vslot09();
	virtual void update( void );													// slot 10
	virtual void vslot11(); virtual void vslot12(); virtual void vslot13();
	virtual void vslot14(); virtual void vslot15();
	virtual void createStreamMessages( void );						// slot 16
	virtual void vslot17(); virtual void vslot18(); virtual void vslot19();
	virtual void vslot20(); virtual void vslot21(); virtual void vslot22();
	virtual void vslot23(); virtual void vslot24(); virtual void vslot25();
	virtual void vslot26(); virtual void vslot27(); virtual void vslot28();

protected:
	virtual UnsignedByte getMouseEvent( MouseIO *result, Bool flush ) = 0;	// slot 29 (+0x74)

	void updateMouseData( void );
	void checkForDrag( void );
	void moveMouse( Int x, Int y, Int relOrAbs );

private:
	void processMouseEvent( Int index );

	char m_pad0004[0x1288 - 0x0004];
	UnsignedByte m_buttonActivity;
	char m_pad1289[0x130C - 0x1289];
	MouseIO m_mouseEvents[ NUM_MOUSE_EVENTS ];
	MouseIO m_currMouse;
	MouseIO m_prevMouse;
	Int m_minX;
	Int m_maxX;
	Int m_minY;
	Int m_maxY;
	UnsignedInt m_inputFrame;
	UnsignedInt m_deadInputFrame;
	UnsignedByte m_inputMovesAbsolute;
	char m_pad4F9D[0x4FFC - 0x4F9D];
	Int m_eventsThisFrame;
	Int m_leftClickAge;
	Int m_rightClickAge;
};

//-------------------------------------------------------------------------------------------------
/** Get the latest mouse events from the device */
//-------------------------------------------------------------------------------------------------
void Mouse::updateMouseData( )
{
	static Bool busy = false;
	Int index = 0;
	UnsignedByte result;

	// prevent reentrancy in the event we make this mouse multi-threaded
	if( busy == false )
	{

		busy = true;

		// Get latest mouse events from DirectX
		do
		{
			do
			{
				result = getMouseEvent( &m_mouseEvents[ index ], true );
			}
			while( result == MOUSE_LOST );
			index++;
		}
		while( (result != MOUSE_NONE) &&
					 (index < sizeof( m_mouseEvents ) / sizeof( MouseIO )) );

		busy = false;

	}  // end if

	if( index > 0 )
		m_eventsThisFrame = index - 1;
	else
		m_eventsThisFrame = 0;

	if( index != 0 )
		m_deadInputFrame = m_inputFrame;

}  // end updateMouseData

//-------------------------------------------------------------------------------------------------
/** Move the mouse in either relative or absolute coords */
//-------------------------------------------------------------------------------------------------
void Mouse::moveMouse( Int x, Int y, Int relOrAbs )
{

	if( relOrAbs == MOUSE_MOVE_RELATIVE )
	{

		m_currMouse.pos.x += x;
		m_currMouse.pos.y += y;

	}
	else
	{

		m_currMouse.pos.x = x;
		m_currMouse.pos.y = y;

	}

	// clip mouse
	if( m_currMouse.pos.x > m_maxX )
		m_currMouse.pos.x = m_maxX;
	else if( m_currMouse.pos.x < m_minX )
		m_currMouse.pos.x = m_minX;

	if( m_currMouse.pos.y > m_maxY )
		m_currMouse.pos.y = m_maxY;
	else if( m_currMouse.pos.y < m_minY )
		m_currMouse.pos.y = m_minY;

}

//-------------------------------------------------------------------------------------------------
/** Check for mouse drag */
//-------------------------------------------------------------------------------------------------
void Mouse::checkForDrag( void )
{

	if( m_currMouse.leftState &&
			( (m_prevMouse.leftEvent == GWM_LEFT_DOWN) ||
				(m_prevMouse.leftEvent == GWM_LEFT_DRAG) ) )
		m_currMouse.leftEvent = GWM_LEFT_DRAG;

	if( m_currMouse.rightState &&
			( (m_prevMouse.rightEvent == GWM_RIGHT_DOWN) ||
				(m_prevMouse.rightEvent == GWM_RIGHT_DRAG) ) )
		m_currMouse.rightEvent = GWM_RIGHT_DRAG;

	if( m_currMouse.middleState &&
			( (m_prevMouse.middleEvent == GWM_MIDDLE_DOWN) ||
				(m_prevMouse.middleEvent == GWM_MIDDLE_DRAG) ) )
		m_currMouse.middleEvent = GWM_MIDDLE_DRAG;

}

//-------------------------------------------------------------------------------------------------
/** Get the current information for the mouse from the device */
//-------------------------------------------------------------------------------------------------
void Mouse::processMouseEvent( Int index )
{
	Int movementType;

	// assume no mouse buttons are going to be pressed or released
	m_currMouse.leftEvent = MOUSE_EVENT_NONE;
	m_currMouse.rightEvent = MOUSE_EVENT_NONE;
	m_currMouse.middleEvent = MOUSE_EVENT_NONE;
	m_currMouse.wheelPos = 0;

	if( m_inputMovesAbsolute == 1 )
		movementType = MOUSE_MOVE_ABSOLUTE;
	else
		movementType = MOUSE_MOVE_RELATIVE;

	m_currMouse.time = m_mouseEvents[ index ].time;

	// Check for drags (since that means that mouse button is down and mouse has moved)
	if( index == 0 )
		checkForDrag();

	// update the mouse position
	moveMouse( m_mouseEvents[ index ].pos.x,
						 m_mouseEvents[ index ].pos.y,
						 movementType );

	// update the mouse wheel
	m_currMouse.wheelPos += m_mouseEvents[ index ].wheelPos;

	// Check Left Mouse State
	if( m_mouseEvents[ index ].leftFrame )
	{
		m_buttonActivity = 1;
		if( m_currMouse.leftState != m_mouseEvents[ index ].leftState )
		{
			if( m_mouseEvents[ index ].leftState == MBS_Down )
			{
				m_currMouse.leftEvent = GWM_LEFT_DOWN;
				m_currMouse.leftState = MBS_Down;
				m_currMouse.leftFrame = m_inputFrame;
			}
			else if( m_mouseEvents[ index ].leftState == MBS_DoubleClick )
			{
				m_currMouse.leftEvent = GWM_LEFT_DOUBLE_CLICK;
				m_currMouse.leftState = MBS_DoubleClick;
				m_currMouse.leftFrame = m_inputFrame;
			}
			else
			{
				m_currMouse.leftEvent = GWM_LEFT_UP;
				m_currMouse.leftState = MBS_Up;
				m_currMouse.leftFrame = m_inputFrame;
			}
		}
	}
	else if( m_currMouse.leftState != MBS_Up &&
					 ( (m_prevMouse.leftEvent == GWM_LEFT_DOWN) ||
						 (m_prevMouse.leftEvent == GWM_LEFT_DRAG) ) )
	{
		m_currMouse.leftEvent = GWM_LEFT_DRAG;
	}

	// Check Right Mouse State
	if( m_mouseEvents[ index ].rightFrame )
	{
		m_buttonActivity = 1;
		if( m_currMouse.rightState != m_mouseEvents[ index ].rightState )
		{
			if( m_mouseEvents[ index ].rightState == MBS_Down )
			{
				m_currMouse.rightEvent = GWM_RIGHT_DOWN;
				m_currMouse.rightState = MBS_Down;
				m_currMouse.rightFrame = m_inputFrame;
			}
			else if( m_mouseEvents[ index ].rightState == MBS_DoubleClick )
			{
				m_currMouse.rightEvent = GWM_RIGHT_DOUBLE_CLICK;
				m_currMouse.rightState = MBS_DoubleClick;
				m_currMouse.rightFrame = m_inputFrame;
			}
			else
			{
				m_currMouse.rightEvent = GWM_RIGHT_UP;
				m_currMouse.rightState = MBS_Up;
				m_currMouse.rightFrame = m_inputFrame;
			}
		}
	}
	else if( m_currMouse.rightState != MBS_Up &&
					 ( (m_prevMouse.rightEvent == GWM_RIGHT_DOWN) ||
						 (m_prevMouse.rightEvent == GWM_RIGHT_DRAG) ) )
	{
		m_currMouse.rightEvent = GWM_RIGHT_DRAG;
	}

	// Check Middle Mouse State
	if( m_mouseEvents[ index ].middleFrame )
	{
		m_buttonActivity = 1;
		if( m_currMouse.middleState != m_mouseEvents[ index ].middleState )
		{
			if( m_mouseEvents[ index ].middleState == MBS_Down )
			{
				m_currMouse.middleEvent = GWM_MIDDLE_DOWN;
				m_currMouse.middleState = MBS_Down;
				m_currMouse.middleFrame = m_inputFrame;
			}
			else if( m_mouseEvents[ index ].middleState == MBS_DoubleClick )
			{
				m_currMouse.middleEvent = GWM_MIDDLE_DOUBLE_CLICK;
				m_currMouse.middleState = MBS_DoubleClick;
				m_currMouse.middleFrame = m_inputFrame;
			}
			else
			{
				m_currMouse.middleEvent = GWM_MIDDLE_UP;
				m_currMouse.middleState = MBS_Up;
				m_currMouse.middleFrame = m_inputFrame;
			}
		}
	}
	else if( m_currMouse.middleState != MBS_Up &&
					 ( (m_prevMouse.middleEvent == GWM_MIDDLE_DOWN) ||
						 (m_prevMouse.middleEvent == GWM_MIDDLE_DRAG) ) )
	{
		m_currMouse.middleEvent = GWM_MIDDLE_DRAG;
	}

	m_currMouse.deltaPos.x = m_currMouse.pos.x - m_prevMouse.pos.x;
	m_currMouse.deltaPos.y = m_currMouse.pos.y - m_prevMouse.pos.y;

	// Keep these around so we can figure out whether we're dragging
	m_prevMouse = m_currMouse;

}

//-------------------------------------------------------------------------------------------------
/** Update the states of the mouse position and buttons */
//-------------------------------------------------------------------------------------------------
void Mouse::update( void )
{

	// increment input frame
	m_inputFrame++;

	// update the mouse data
	updateMouseData( );

}  // end update

//-------------------------------------------------------------------------------------------------
/** Create the stream messages for the mouse events of this frame */
//-------------------------------------------------------------------------------------------------
void Mouse::createStreamMessages( void )
{
	// santiy
	if( TheMessageStream == 0 )
		return;  // no place to put messages

	GameMessage *msg;

	for( Int i = 0; i < m_eventsThisFrame; ++i )
	{
		processMouseEvent( i );

		// button messages
		switch( m_currMouse.leftEvent )
		{
			case GWM_LEFT_DOWN:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_LEFT_BUTTON_DOWN );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				msg->appendIntegerArgument( m_currMouse.time );
				m_leftClickAge = 0;
				break;

			case GWM_LEFT_DOUBLE_CLICK:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				msg->appendIntegerArgument( m_currMouse.time );
				break;

			case GWM_LEFT_UP:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_LEFT_BUTTON_UP );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				msg->appendIntegerArgument( m_currMouse.time );
				m_leftClickAge = -1;
				break;

			case GWM_LEFT_DRAG:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_LEFT_DRAG );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendPixelArgument( m_currMouse.deltaPos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				break;
		}

		switch( m_currMouse.middleEvent )
		{
			case GWM_MIDDLE_DOWN:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				msg->appendIntegerArgument( m_currMouse.time );
				break;

			case GWM_MIDDLE_DOUBLE_CLICK:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				msg->appendIntegerArgument( m_currMouse.time );
				break;

			case GWM_MIDDLE_UP:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_MIDDLE_BUTTON_UP );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				msg->appendIntegerArgument( m_currMouse.time );
				break;

			case GWM_MIDDLE_DRAG:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_MIDDLE_DRAG );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendPixelArgument( m_currMouse.deltaPos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				break;
		}

		switch( m_currMouse.rightEvent )
		{
			case GWM_RIGHT_DOWN:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				msg->appendIntegerArgument( m_currMouse.time );
				m_rightClickAge = 0;
				break;

			case GWM_RIGHT_DOUBLE_CLICK:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				msg->appendIntegerArgument( m_currMouse.time );
				break;

			case GWM_RIGHT_UP:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_RIGHT_BUTTON_UP );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				msg->appendIntegerArgument( m_currMouse.time );
				m_rightClickAge = -1;
				break;

			case GWM_RIGHT_DRAG:
				msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_RIGHT_DRAG );
				msg->appendPixelArgument( m_currMouse.pos );
				msg->appendPixelArgument( m_currMouse.deltaPos );
				msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
				break;
		}

		// mouse wheel
		if( m_currMouse.wheelPos != 0 )
		{
			msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_WHEEL );
			msg->appendPixelArgument( m_currMouse.pos );
			msg->appendIntegerArgument( m_currMouse.wheelPos / 120 );	// wheel delta
			msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
		}
	}

	// age the pending clicks
	if( m_leftClickAge != -1 && m_leftClickAge < CLICK_SENSITIVITY )
		++m_leftClickAge;
	if( m_rightClickAge != -1 && m_rightClickAge < CLICK_SENSITIVITY )
		++m_rightClickAge;

	if( m_leftClickAge >= CLICK_SENSITIVITY )
	{
		msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_LEFT_CLICK );
		msg->appendPixelArgument( m_currMouse.pos );
		msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
		msg->appendIntegerArgument( m_currMouse.time );
		m_leftClickAge = -1;
	}

	if( m_rightClickAge >= CLICK_SENSITIVITY )
	{
		msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_RIGHT_CLICK );
		msg->appendPixelArgument( m_currMouse.pos );
		msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );
		msg->appendIntegerArgument( m_currMouse.time );
		m_rightClickAge = -1;
	}

	// the raw position is always sent
	msg = TheMessageStream->appendMessage( MSG_RAW_MOUSE_POSITION );
	msg->appendPixelArgument( m_currMouse.pos );
	msg->appendIntegerArgument( TheKeyboard->getModifierFlags() );

}

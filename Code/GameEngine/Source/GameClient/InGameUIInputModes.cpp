// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// InGameUI's mouse and input modes (vftable 0x7FD410), from ZH
// GameEngine/Source/GameClient/InGameUI.cpp unless noted:
// setMouseCursor (0x0029A5D6, non-virtual), beginAreaSelectHint (slot 26,
// 0x0029A79F), createGarrisonHint (slot 33, 0x0029A7C4), setScrolling
// (slot 41, 0x0029A7F1), setGUICommand (slot 47, 0x0029A889), the
// input-gate setter (slot 82, 0x0029AB48) and slot 94 (0x0029AC03).
//
// setMouseCursor is ZH's text: TheMouse (0x00DFDCA0) slot 19, then the mode
// cursor at +0x800 while the mouse mode at +0x7FC is GUI command (2) and the
// cursor is neither ARROW (2) nor SCROLL (3). BFME 1 rows it at 0x0043AA10.
// beginAreaSelectHint gains a null message check; setScrolling drops ZH's
// camera-lock breaks; createGarrisonHint calls the rowed 0x002754E3 on the
// drawable where ZH calls onSelected.
//
// setGUICommand: BFME 1 rows the same body (0x0043ADE0) with the recorder
// null check. TheRecorder (0x00A02290) is null-checked before getMode
// 0x0030F2C7 == playback; the pending command is stored at +0x238, the mouse
// mode at +0x7FC and the mode cursor at +0x800 from TheMouse +0x4FA4
// (getMouseCursor). The option mask is 0x227, ZH's COMMAND_OPTION_NEED_TARGET;
// a command of type 0x35 at CommandButton +0x14 sets the default mode without
// the need-target test. CommandButton::isContextCommand is 0x0035B140 (BFME
// 1's 0x0049AE80). The radius cursor (slot 80, +0x140) takes the type +0x4C,
// special power +0x44, weapon slot +0x80 and a fourth TRUE argument; slot 81
// is setRadiusCursorNone.
//
// Slot 82 is BFME 1's virtual InGameUI::setInputEnabled(bool, bool *)
// (0x0043B2A0, InGameUIInputState.cpp): the two public gates (the rowed
// setEngineInputEnabled 0x0029AB22 and setInputEnabled 0x0029AB35) forward
// here with the address of the flag they own, +0x15 or +0x16. On an
// enabled-to-disabled edge it calls setSelecting (slot 43, FALSE) and
// setRadiusCursorNone, clears the mode flags at +0x8B0 and +0x8B8..+0x8C2 in retail's
// order, and BFME 2 adds an appended message 0x469 with integers 0 and 1.
//
// Slot 94 (0x0029AC03, ret 4) stores its flag at +0x810 and on a
// disabled-to-enabled edge resets TheSelectionTranslator (0x00A03220)
// through setDragSelecting 0x0042FA01, calls setSelecting (slot 43) and
// endAreaSelectHint (slot 27) with FALSE/NULL, setRadiusCursorNone, then
// clears the same mode flags. Its name is unknown, so it keeps its address.

#define NULL 0

#include "../../../Libraries/Include/Lib/Coord2D.h"

class SpecialPowerTemplate;

enum RadiusCursorType { RADIUSCURSOR_NONE = 0 };
enum WeaponSlotType { PRIMARY_WEAPON = 0 };

class CommandButton
{
public:
	int getCommandType() const { return m_command; }
	unsigned int getOptions() const { return m_options; }
	bool isContextCommand() const;
	RadiusCursorType getRadiusCursorType() const { return m_radiusCursor; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	WeaponSlotType getWeaponSlot() const { return m_weaponSlot; }
private:
	char m_unknown00[0x14];
	int m_command;									// +0x14
	char m_unknown18[0x1C - 0x18];
	unsigned int m_options;							// +0x1C
	char m_unknown20[0x44 - 0x20];
	const SpecialPowerTemplate *m_specialPower;		// +0x44
	char m_unknown48[0x4C - 0x48];
	RadiusCursorType m_radiusCursor;				// +0x4C
	char m_unknown50[0x80 - 0x50];
	WeaponSlotType m_weaponSlot;					// +0x80
};

const unsigned int COMMAND_OPTION_NEED_TARGET = 0x227;

enum RecorderModeType { RECORDERMODETYPE_RECORD, RECORDERMODETYPE_PLAYBACK };

class RecorderClass
{
public:
	RecorderModeType getMode();
};

extern RecorderClass *TheRecorder;

class Mouse
{
public:
	enum MouseCursor { NONE = 0, NORMAL, ARROW, SCROLL };
#define V(n) virtual void r##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18)
#undef V
	virtual void setCursor( MouseCursor cursor );	// slot 19
	virtual void capture( void );					// slot 20
	virtual void releaseCapture( void );			// slot 21
	MouseCursor getMouseCursor() { return m_currentCursor; }
private:
	char m_unknown04[0x4FA4 - 0x4];
	MouseCursor m_currentCursor;					// +0x4FA4
};

extern Mouse *TheMouse;

class SelectionTranslator;
extern SelectionTranslator *TheSelectionTranslator;

class BfmeSelectionTranslator
{
public:
	void setDragSelecting( void );
};

struct IRegion2D { int loX, loY, hiX, hiY; };
typedef unsigned int DrawableID;

union GameMessageArgumentType
{
	int integer;
	DrawableID drawableID;
	IRegion2D pixelRegion;
};

class GameMessage
{
public:
	enum Type { MSG_RVA469 = 0x469 };	// unnamed BFME 2 message, also posted by 0x002D2F32 and 0x002D37BD
	const GameMessageArgumentType *getArgument( int argIndex ) const;
	void appendIntegerArgument( int arg );
};

class MessageStream
{
public:
#define V(n) virtual void r##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17)
#undef V
	virtual GameMessage *appendMessage( GameMessage::Type type );	// slot 18
};

extern MessageStream *MessageStreamSubsystem;

class Drawable
{
public:
	void rva002754E3( void );
};

class ClientFrameSubsystem
{
public:
#define V(n) virtual void r##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
#undef V
	virtual Drawable *findDrawableByID( DrawableID id );	// slot 16
};

extern ClientFrameSubsystem *TheGameClient;

enum MouseMode { MOUSEMODE_DEFAULT = 0, MOUSEMODE_BUILD_PLACE, MOUSEMODE_GUI_COMMAND };

class InGameUI
{
public:
#define V(n) virtual void r##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25)
#undef V
	virtual void beginAreaSelectHint( const GameMessage *msg );	// slot 26
	virtual void endAreaSelectHint( const GameMessage *msg );	// slot 27
#define V(n) virtual void r##n();
	V(28) V(29) V(30) V(31) V(32)
#undef V
	virtual void createGarrisonHint( const GameMessage *msg );	// slot 33
#define V(n) virtual void r##n();
	V(34) V(35) V(36) V(37) V(38) V(39) V(40)
#undef V
	virtual void setScrolling( bool isScrolling );	// slot 41
	virtual bool isScrolling( void );				// slot 42
	virtual void setSelecting( bool isSelecting );	// slot 43
	virtual bool isSelecting( void );				// slot 44
	virtual void setScrollAmount( Coord2D amt );	// slot 45
	virtual void r46();
	virtual void setGUICommand( const CommandButton *command );	// slot 47
#define V(n) virtual void r##n();
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
#undef V
	virtual void setRadiusCursor( RadiusCursorType r, const SpecialPowerTemplate *sp, WeaponSlotType wslot, bool flag );	// slot 80
	virtual void setRadiusCursorNone();				// slot 81
	virtual void setInputEnabled( bool enabled, bool *gate );	// slot 82
#define V(n) virtual void r##n();
	V(83) V(84) V(85) V(86) V(87)
	V(88) V(89) V(90) V(91) V(92) V(93)
#undef V
	virtual void rva0029AC03( bool enable );		// slot 94

	bool getInputEnabled() { return m_engineInputEnabled && m_scriptInputEnabled; }

protected:
	void setMouseCursor( Mouse::MouseCursor c );

	char m_unknown004[0x15 - 0x4];
	bool m_engineInputEnabled;						// +0x15
	bool m_scriptInputEnabled;						// +0x16
	char m_unknown017[0x28 - 0x17];
	bool m_isDragSelecting;							// +0x28
	IRegion2D m_dragSelectRegion;					// +0x2C
	char m_unknown3C[0x238 - 0x3C];
	const CommandButton *m_pendingGUICommand;		// +0x238
	char m_unknown23C[0x7F8 - 0x23C];
	bool m_isScrolling;								// +0x7F8
	bool m_isSelecting;								// +0x7F9
	MouseMode m_mouseMode;							// +0x7FC
	int m_mouseModeCursor;							// +0x800
	char m_unknown804[0x808 - 0x804];
	Coord2D m_scrollAmt;							// +0x808
	bool m_inputEnabled;							// +0x810, BFME 1's virtual setInputEnabled
	char m_unknown811[0x8B0 - 0x811];
	bool m_mode0;									// +0x8B0
	char m_unknown8B1[0x8B8 - 0x8B1];
	bool m_modes[11];								// +0x8B8
};

void InGameUI::setMouseCursor( Mouse::MouseCursor c )
{
	if( !TheMouse )
		return;

	TheMouse->setCursor( c );

	if( m_mouseMode == MOUSEMODE_GUI_COMMAND && c != Mouse::ARROW && c != Mouse::SCROLL )
		m_mouseModeCursor = c;
}

void InGameUI::setGUICommand( const CommandButton *command )
{
	if (TheRecorder && TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK)
		return;

	// sanity
	if( command && command->getCommandType() != 0x35 )
	{
		if( (command->getOptions() & COMMAND_OPTION_NEED_TARGET) == 0 )
		{
			m_pendingGUICommand = 0;
			m_mouseMode = MOUSEMODE_DEFAULT;
			return;
		}

		m_mouseMode = MOUSEMODE_GUI_COMMAND;
	}
	else
	{
		m_mouseMode = MOUSEMODE_DEFAULT;
	}

	// set the command
	m_pendingGUICommand = command;

	// set the mouse cursor for commands that need a targeting or to normal with no command
	if( command && (command->getOptions() & COMMAND_OPTION_NEED_TARGET) && !command->isContextCommand() )
	{
		setMouseCursor( Mouse::ARROW );
		setRadiusCursor( command->getRadiusCursorType(),
						 command->getSpecialPowerTemplate(),
						 command->getWeaponSlot(), true );
	}
	else
	{
		if (TheMouse)
		{
			setMouseCursor( Mouse::ARROW );
		}
		setRadiusCursorNone();
	}

	m_mouseModeCursor = TheMouse->getMouseCursor();
}

void InGameUI::rva0029AC03( bool enable )
{
	bool wasEnabled = m_inputEnabled;
	m_inputEnabled = enable;

	if( !wasEnabled && enable )
	{
		if( TheSelectionTranslator )
			reinterpret_cast<BfmeSelectionTranslator *>( TheSelectionTranslator )->setDragSelecting();
		setSelecting( false );
		endAreaSelectHint( NULL );
		setRadiusCursorNone();
		m_modes[0] = false;
		m_modes[1] = false;
		m_mode0 = false;
		m_modes[2] = false;
		m_modes[3] = false;
		m_modes[4] = false;
		m_modes[5] = false;
		m_modes[6] = false;
		m_modes[7] = false;
		m_modes[8] = false;
		m_modes[9] = false;
		m_modes[10] = false;
	}
}

void InGameUI::beginAreaSelectHint( const GameMessage *msg )
{
	m_isDragSelecting = true;
	if( msg )
		m_dragSelectRegion = msg->getArgument( 0 )->pixelRegion;
}

void InGameUI::createGarrisonHint( const GameMessage *msg )
{
	Drawable *draw = TheGameClient->findDrawableByID( msg->getArgument( 0 )->drawableID );
	if( draw )
		draw->rva002754E3();
}

void InGameUI::setScrolling( bool isScrolling )
{
	if( m_isScrolling == isScrolling )
		return;

	if( isScrolling )
	{
		TheMouse->capture();
		setMouseCursor( Mouse::SCROLL );
	}
	else
	{
		setMouseCursor( Mouse::ARROW );
		TheMouse->releaseCapture();
	}

	m_isScrolling = isScrolling;
}

bool InGameUI::isScrolling( void )
{
	return m_isScrolling;
}

void InGameUI::setSelecting( bool isSelecting )
{
	if( m_isSelecting == isSelecting )
		return;

	m_isSelecting = isSelecting;
}

bool InGameUI::isSelecting( void )
{
	return m_isSelecting;
}

void InGameUI::setScrollAmount( Coord2D amt )
{
	m_scrollAmt = amt;
}

void InGameUI::setInputEnabled( bool enabled, bool *gate )
{
	bool wasEnabled = getInputEnabled();
	*gate = enabled;

	if( wasEnabled && !getInputEnabled() )
	{
		setSelecting( false );
		setRadiusCursorNone();
		m_modes[0] = false;
		m_modes[1] = false;
		m_mode0 = false;
		m_modes[2] = false;
		m_modes[3] = false;
		m_modes[4] = false;
		m_modes[5] = false;
		m_modes[6] = false;
		m_modes[7] = false;
		m_modes[8] = false;
		m_modes[9] = false;
		m_modes[10] = false;

		GameMessage *msg = MessageStreamSubsystem->appendMessage( GameMessage::MSG_RVA469 );
		msg->appendIntegerArgument( 0 );
		msg->appendIntegerArgument( 1 );
	}
}

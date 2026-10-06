// cl: /O1 /DNDEBUG /MD /EHsc /G7
//
// ?initKeyNames@Keyboard@@QAEXXZ, retail 0x002306B8, 8023 bytes with its 10-entry
// language jump table at 0x002325E7, up to Keyboard::init 0x0023260F.
//
// Target evidence: the body ends where the Keyboard unit's rowed functions
// begin (init 0x0023260F, isShift 0x00232683, ctor 0x00232920; vtable
// 0x00BE81F0, see Keyboard.cpp) and writes three WideChars per key into the
// table at +0x81C that getPrintableKey (KeyboardKeyAccessors.cpp) reads; it
// stores a byte m_shift2Key at +0x0E (KEY_RALT 0xB8 in the localized cases),
// calls GetKeyboardLayout(0), and switches on the global at 0x00E01E54.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameClient/Input/Keyboard.cpp
// Keyboard::initKeyNames (itself Zero Hour's), carried unchanged apart from
// the BFME 2 layout above. Key indices are Zero Hour's KeyDefs.h DIK codes;
// LanguageID is Zero Hour's Language.h, and the global is named OurLanguage
// after the donor. BFME 2 adds the German-layout block after the switch
// (target bytes 0x00232585..0x002325E4): it swaps the Y and Z names and
// stores LANGUAGE_ID_GERMAN to that global.

typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) void *__stdcall GetKeyboardLayout(unsigned long threadId);
typedef void *HKL;

enum LanguageID
{
	LANGUAGE_ID_US = 0,
	LANGUAGE_ID_UK,
	LANGUAGE_ID_GERMAN,
	LANGUAGE_ID_FRENCH,
	LANGUAGE_ID_SPANISH,
	LANGUAGE_ID_ITALIAN,
	LANGUAGE_ID_JAPANESE,
	LANGUAGE_ID_JABBER,
	LANGUAGE_ID_KOREAN,
	LANGUAGE_ID_UNKNOWN
};
extern LanguageID OurLanguage;

// Zero Hour's KeyDefs.h values (DirectInput DIK_* scan codes).
enum KeyDefType
{
	KEY_NONE = 0x00,
	KEY_ESC = 0x01, KEY_1 = 0x02, KEY_2 = 0x03, KEY_3 = 0x04, KEY_4 = 0x05,
	KEY_5 = 0x06, KEY_6 = 0x07, KEY_7 = 0x08, KEY_8 = 0x09, KEY_9 = 0x0A,
	KEY_0 = 0x0B, KEY_MINUS = 0x0C, KEY_EQUAL = 0x0D, KEY_BACKSPACE = 0x0E,
	KEY_TAB = 0x0F, KEY_Q = 0x10, KEY_W = 0x11, KEY_E = 0x12, KEY_R = 0x13,
	KEY_T = 0x14, KEY_Y = 0x15, KEY_U = 0x16, KEY_I = 0x17, KEY_O = 0x18,
	KEY_P = 0x19, KEY_LBRACKET = 0x1A, KEY_RBRACKET = 0x1B, KEY_ENTER = 0x1C,
	KEY_LCTRL = 0x1D, KEY_A = 0x1E, KEY_S = 0x1F, KEY_D = 0x20, KEY_F = 0x21,
	KEY_G = 0x22, KEY_H = 0x23, KEY_J = 0x24, KEY_K = 0x25, KEY_L = 0x26,
	KEY_SEMICOLON = 0x27, KEY_APOSTROPHE = 0x28, KEY_TICK = 0x29,
	KEY_LSHIFT = 0x2A, KEY_BACKSLASH = 0x2B, KEY_Z = 0x2C, KEY_X = 0x2D,
	KEY_C = 0x2E, KEY_V = 0x2F, KEY_B = 0x30, KEY_N = 0x31, KEY_M = 0x32,
	KEY_COMMA = 0x33, KEY_PERIOD = 0x34, KEY_SLASH = 0x35, KEY_RSHIFT = 0x36,
	KEY_KPSTAR = 0x37, KEY_LALT = 0x38, KEY_SPACE = 0x39, KEY_CAPS = 0x3A,
	KEY_F1 = 0x3B, KEY_F2 = 0x3C, KEY_F3 = 0x3D, KEY_F4 = 0x3E, KEY_F5 = 0x3F,
	KEY_F6 = 0x40, KEY_F7 = 0x41, KEY_F8 = 0x42, KEY_F9 = 0x43, KEY_F10 = 0x44,
	KEY_NUM = 0x45, KEY_SCROLL = 0x46, KEY_KP7 = 0x47, KEY_KP8 = 0x48,
	KEY_KP9 = 0x49, KEY_KPMINUS = 0x4A, KEY_KP4 = 0x4B, KEY_KP5 = 0x4C,
	KEY_KP6 = 0x4D, KEY_KPPLUS = 0x4E, KEY_KP1 = 0x4F, KEY_KP2 = 0x50,
	KEY_KP3 = 0x51, KEY_KP0 = 0x52, KEY_KPDEL = 0x53, KEY_102 = 0x56,
	KEY_F11 = 0x57, KEY_F12 = 0x58, KEY_KPENTER = 0x9C, KEY_RCTRL = 0x9D,
	KEY_KPSLASH = 0xB5, KEY_SYSREQ = 0xB7, KEY_RALT = 0xB8, KEY_HOME = 0xC7,
	KEY_UP = 0xC8, KEY_PGUP = 0xC9, KEY_LEFT = 0xCB, KEY_RIGHT = 0xCD,
	KEY_END = 0xCF, KEY_DOWN = 0xD0, KEY_PGDN = 0xD1, KEY_INS = 0xD2,
	KEY_DEL = 0xD3
};

class Keyboard
{
public:
	enum { KEY_NAMES_COUNT = 256 };

	void initKeyNames( void );

private:
	char m_unmodelled00[0x0E];
	UnsignedByte m_shift2Key;							// +0x0E
	char m_unmodelled0F[0x81C - 0x0F];
	struct
	{
		WideChar stdKey;
		WideChar shifted;
		WideChar shifted2;
	} m_keyNames[KEY_NAMES_COUNT];						// +0x81C
};

//-------------------------------------------------------------------------------------------------
/** Initialize the keyboard key-names array */
//-------------------------------------------------------------------------------------------------
void Keyboard::initKeyNames( void )
{
	Int i;

	#define _set_keyname_(k,s,s2,z) (m_keyNames[z].stdKey = k, m_keyNames[z].shifted = s, m_keyNames[z].shifted2 = s2)

	/*
	 * Initialize the keyboard key-names array.
	 */
	for( i = 0; i < KEY_NAMES_COUNT; i++ )
	{

		m_keyNames[ i ].stdKey =		L'\0';
		m_keyNames[ i ].shifted =		L'\0';
		m_keyNames[ i ].shifted2 =	L'\0';

	}  // end for i

	m_shift2Key = KEY_NONE;

	// generic to all languages
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_UP );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_DOWN );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_LEFT );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_RIGHT );

	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_HOME );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_END );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_PGUP );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_PGDN );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_INS );
	_set_keyname_(L'\b',	L'\b',	L'\0',	KEY_DEL );

	_set_keyname_(L'\b',	L'\b',	L'\0',	KEY_BACKSPACE  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_ESC  );
	_set_keyname_(L'\t',	L'\t',	L'\0',	KEY_TAB  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_CAPS  );
	_set_keyname_(L'\n',	L'\n',	L'\0',	KEY_ENTER  );

	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_RALT );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_RCTRL );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_RSHIFT  );

	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_LALT  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_LCTRL  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_LSHIFT  );

	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_NUM );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_SCROLL );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_SYSREQ );

	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F1  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F2  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F3  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F4  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F5  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F6  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F7  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F8  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F9  );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F10 );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F11 );
	_set_keyname_(L'\0',	L'\0',	L'\0',	KEY_F12 );

	_set_keyname_(L'1',		L'1',		L'\0',	KEY_KP1 );
	_set_keyname_(L'2',		L'2',		L'\0',	KEY_KP2 );
	_set_keyname_(L'3',		L'3',		L'\0',	KEY_KP3 );
	_set_keyname_(L'4',		L'4',		L'\0',	KEY_KP4 );
	_set_keyname_(L'5',		L'5',		L'\0',	KEY_KP5 );
	_set_keyname_(L'6',		L'6',		L'\0',	KEY_KP6 );
	_set_keyname_(L'7',		L'7',		L'\0',	KEY_KP7 );
	_set_keyname_(L'8',		L'8',		L'\0',	KEY_KP8 );
	_set_keyname_(L'9',		L'9',		L'\0',	KEY_KP9 );
	_set_keyname_(L'0',		L'0',		L'\0',	KEY_KP0 );

	_set_keyname_(L' ',		L' ',		L'\0',	KEY_SPACE  );

	HKL kLayout = GetKeyboardLayout(0);

	Int low = (UnsignedInt)kLayout & 0xFFFF;
	LanguageID currentLanguage = OurLanguage;
	if(low == 0x040c
		 || low == 0x080c
		 || low == 0x0c0c
		 || low == 0x100c
		 || low == 0x140c)
		currentLanguage = LANGUAGE_ID_FRENCH;

	switch( currentLanguage )
	{
		case LANGUAGE_ID_US:
		case LANGUAGE_ID_JAPANESE:
		case LANGUAGE_ID_KOREAN:
		case LANGUAGE_ID_JABBER:
		case LANGUAGE_ID_UNKNOWN:
		case LANGUAGE_ID_SPANISH:		// not localized
			_set_keyname_(L'-',				L'-',				L'\0',	KEY_KPMINUS );
			_set_keyname_(L'+',				L'+',				L'\0',	KEY_KPPLUS );
			_set_keyname_(L'\n',			L'\n',			L'\0',	KEY_KPENTER );
			_set_keyname_(L'/',				L'/',				L'\0',	KEY_KPSLASH );
			_set_keyname_(L'.',				L'.',				L'\0',	KEY_KPDEL );
			_set_keyname_(L'*',				L'*',				L'\0',	KEY_KPSTAR );

			_set_keyname_(L'a',				L'A',				L'\0',	KEY_A  );
			_set_keyname_(L'b',				L'B',				L'\0',	KEY_B  );
			_set_keyname_(L'c',				L'C',				L'\0',	KEY_C  );
			_set_keyname_(L'd',				L'D',				L'\0',	KEY_D  );
			_set_keyname_(L'e',				L'E',				L'\0',	KEY_E  );
			_set_keyname_(L'f',				L'F',				L'\0',	KEY_F  );
			_set_keyname_(L'g',				L'G',				L'\0',	KEY_G  );
			_set_keyname_(L'h',				L'H',				L'\0',	KEY_H  );
			_set_keyname_(L'i',				L'I',				L'\0',	KEY_I  );
			_set_keyname_(L'j',				L'J',				L'\0',	KEY_J  );
			_set_keyname_(L'k',				L'K',				L'\0',	KEY_K  );
			_set_keyname_(L'l',				L'L',				L'\0',	KEY_L  );
			_set_keyname_(L'm',				L'M',				L'\0',	KEY_M  );
			_set_keyname_(L'n',				L'N',				L'\0',	KEY_N  );
			_set_keyname_(L'o',				L'O',				L'\0',	KEY_O  );
			_set_keyname_(L'p',				L'P',				L'\0',	KEY_P  );
			_set_keyname_(L'q',				L'Q',				L'\0',	KEY_Q  );
			_set_keyname_(L'r',				L'R',				L'\0',	KEY_R  );
			_set_keyname_(L's',				L'S',				L'\0',	KEY_S  );
			_set_keyname_(L't',				L'T',				L'\0',	KEY_T  );
			_set_keyname_(L'u',				L'U',				L'\0',	KEY_U  );
			_set_keyname_(L'v',				L'V',				L'\0',	KEY_V  );
			_set_keyname_(L'w',				L'W',				L'\0',	KEY_W  );
			_set_keyname_(L'x',				L'X',				L'\0',	KEY_X  );
			_set_keyname_(L'y',				L'Y',				L'\0',	KEY_Y  );
			_set_keyname_(L'z',				L'Z',				L'\0',	KEY_Z  );

			_set_keyname_(L'1',				L'!',				L'\0',	KEY_1  );
			_set_keyname_(L'2',				L'@',				L'\0',	KEY_2  );
			_set_keyname_(L'3',				L'#',				L'\0',	KEY_3  );
			_set_keyname_(L'4',				L'$',				L'\0',	KEY_4  );
			_set_keyname_(L'5',				L'%',				L'\0',	KEY_5  );
			_set_keyname_(L'6',				L'^',				L'\0',	KEY_6  );
			_set_keyname_(L'7',				L'&',				L'\0',	KEY_7  );
			_set_keyname_(L'8',				L'*',				L'\0',	KEY_8  );
			_set_keyname_(L'9',				L'(',				L'\0',	KEY_9  );
			_set_keyname_(L'0',				L')',				L'\0',	KEY_0  );

			_set_keyname_(L',',				L'<',				L'\0',	KEY_COMMA  );
			_set_keyname_(L'.',				L'>',				L'\0',	KEY_PERIOD  );
			_set_keyname_(L'/',				L'?',				L'\0',	KEY_SLASH  );

			_set_keyname_(L'[',				L'{',				L'\0',	KEY_LBRACKET  );
			_set_keyname_(L']',				L'}',				L'\0',	KEY_RBRACKET  );

			_set_keyname_(L';',				L':',				L'\0',	KEY_SEMICOLON  );
			_set_keyname_(L'\'',			L'\"',			L'\0',	KEY_APOSTROPHE  );
			_set_keyname_(L'`',				L'~',				L'\0',	KEY_TICK  );
			_set_keyname_(L'\\',			L'|',				L'\0',	KEY_BACKSLASH  );

			_set_keyname_(L'-',				L'_',				L'\0',	KEY_MINUS  );
			_set_keyname_(L'=',				L'+',				L'\0',	KEY_EQUAL  );

			break;

		case LANGUAGE_ID_UK:
			_set_keyname_(L'-',				L'-',				L'\0',	KEY_KPMINUS );
			_set_keyname_(L'+',				L'+',				L'\0',	KEY_KPPLUS );
			_set_keyname_(L'\n',			L'\n',			L'\0',	KEY_KPENTER );
			_set_keyname_(L'/',				L'/',				L'\0',	KEY_KPSLASH );
			_set_keyname_(L'.',				L'.',				L'\0',	KEY_KPDEL );
			_set_keyname_(L'*',				L'*',				L'\0',	KEY_KPSTAR );

			_set_keyname_(L'a',				L'A',				L'\0',	KEY_A  );
			_set_keyname_(L'b',				L'B',				L'\0',	KEY_B  );
			_set_keyname_(L'c',				L'C',				L'\0',	KEY_C  );
			_set_keyname_(L'd',				L'D',				L'\0',	KEY_D  );
			_set_keyname_(L'e',				L'E',				L'\0',	KEY_E  );
			_set_keyname_(L'f',				L'F',				L'\0',	KEY_F  );
			_set_keyname_(L'g',				L'G',				L'\0',	KEY_G  );
			_set_keyname_(L'h',				L'H',				L'\0',	KEY_H  );
			_set_keyname_(L'i',				L'I',				L'\0',	KEY_I  );
			_set_keyname_(L'j',				L'J',				L'\0',	KEY_J  );
			_set_keyname_(L'k',				L'K',				L'\0',	KEY_K  );
			_set_keyname_(L'l',				L'L',				L'\0',	KEY_L  );
			_set_keyname_(L'm',				L'M',				L'\0',	KEY_M  );
			_set_keyname_(L'n',				L'N',				L'\0',	KEY_N  );
			_set_keyname_(L'o',				L'O',				L'\0',	KEY_O  );
			_set_keyname_(L'p',				L'P',				L'\0',	KEY_P  );
			_set_keyname_(L'q',				L'Q',				L'\0',	KEY_Q  );
			_set_keyname_(L'r',				L'R',				L'\0',	KEY_R  );
			_set_keyname_(L's',				L'S',				L'\0',	KEY_S  );
			_set_keyname_(L't',				L'T',				L'\0',	KEY_T  );
			_set_keyname_(L'u',				L'U',				L'\0',	KEY_U  );
			_set_keyname_(L'v',				L'V',				L'\0',	KEY_V  );
			_set_keyname_(L'w',				L'W',				L'\0',	KEY_W  );
			_set_keyname_(L'x',				L'X',				L'\0',	KEY_X  );
			_set_keyname_(L'y',				L'Y',				L'\0',	KEY_Y  );
			_set_keyname_(L'z',				L'Z',				L'\0',	KEY_Z  );

			_set_keyname_(L'1',				L'!',				L'\0',	KEY_1  );
			_set_keyname_(L'2',				L'\"',			L'\0',	KEY_2  );
			_set_keyname_(L'3',				0x00A3,			L'\0',	KEY_3  );
			_set_keyname_(L'4',				L'$',				0x20AC,			KEY_4  );
			_set_keyname_(L'5',				L'%',				L'\0',	KEY_5  );
			_set_keyname_(L'6',				L'^',				L'\0',	KEY_6  );
			_set_keyname_(L'7',				L'&',				L'\0',	KEY_7  );
			_set_keyname_(L'8',				L'*',				L'\0',	KEY_8  );
			_set_keyname_(L'9',				L'(',				L'\0',	KEY_9  );
			_set_keyname_(L'0',				L')',				L'\0',	KEY_0  );

			_set_keyname_(L',',				L'<',				L'\0',	KEY_COMMA  );
			_set_keyname_(L'.',				L'>',				L'\0',	KEY_PERIOD  );
			_set_keyname_(L'/',				L'?',				L'\0',	KEY_SLASH  );

			_set_keyname_(L'[',				L'{',				L'\0',	KEY_LBRACKET  );
			_set_keyname_(L']',				L'}',				L'\0',	KEY_RBRACKET  );

			_set_keyname_(L';',				L':',				L'\0',	KEY_SEMICOLON  );
			_set_keyname_(L'\'',			L'@',				L'\0',	KEY_APOSTROPHE  );
			_set_keyname_(L'`',				0x00AC,			0x00A6,	KEY_TICK  );
			_set_keyname_(L'#',				L'~',				L'\0',	KEY_BACKSLASH  );

			_set_keyname_(L'-',				L'_',				L'\0',	KEY_MINUS  );
			_set_keyname_(L'=',				L'+',				L'\0',	KEY_EQUAL  );

			_set_keyname_(L'\\',			L'|',				L'\0',	KEY_102  );

			m_shift2Key = KEY_RALT;
			break;

		case LANGUAGE_ID_GERMAN:
			_set_keyname_(L'-',				L'-',				L'\0',	KEY_KPMINUS );
			_set_keyname_(L'+',				L'+',				L'\0',	KEY_KPPLUS );
			_set_keyname_(L'\n',			L'\n',			L'\0',	KEY_KPENTER );
			_set_keyname_(L'/',				L'/',				L'\0',	KEY_KPSLASH );
			_set_keyname_(L',',				L',',				L'\0',	KEY_KPDEL );
			_set_keyname_(L'*',				L'*',				L'\0',	KEY_KPSTAR );

			_set_keyname_(L'a',				L'A',				L'\0',	KEY_A  );
			_set_keyname_(L'b',				L'B',				L'\0',	KEY_B  );
			_set_keyname_(L'c',				L'C',				L'\0',	KEY_C  );
			_set_keyname_(L'd',				L'D',				L'\0',	KEY_D  );
			_set_keyname_(L'e',				L'E',				L'\0',	KEY_E  );
			_set_keyname_(L'f',				L'F',				L'\0',	KEY_F  );
			_set_keyname_(L'g',				L'G',				L'\0',	KEY_G  );
			_set_keyname_(L'h',				L'H',				L'\0',	KEY_H  );
			_set_keyname_(L'i',				L'I',				L'\0',	KEY_I  );
			_set_keyname_(L'j',				L'J',				L'\0',	KEY_J  );
			_set_keyname_(L'k',				L'K',				L'\0',	KEY_K  );
			_set_keyname_(L'l',				L'L',				L'\0',	KEY_L  );
			_set_keyname_(L'm',				L'M',				0x00B5,	KEY_M  );
			_set_keyname_(L'n',				L'N',				L'\0',	KEY_N  );
			_set_keyname_(L'o',				L'O',				L'\0',	KEY_O  );
			_set_keyname_(L'p',				L'P',				L'\0',	KEY_P  );
			_set_keyname_(L'q',				L'Q',				L'@',		KEY_Q  );
			_set_keyname_(L'r',				L'R',				L'\0',	KEY_R  );
			_set_keyname_(L's',				L'S',				L'\0',	KEY_S  );
			_set_keyname_(L't',				L'T',				L'\0',	KEY_T  );
			_set_keyname_(L'u',				L'U',				L'\0',	KEY_U  );
			_set_keyname_(L'v',				L'V',				L'\0',	KEY_V  );
			_set_keyname_(L'w',				L'W',				L'\0',	KEY_W  );
			_set_keyname_(L'x',				L'X',				L'\0',	KEY_X  );
			_set_keyname_(L'z',				L'Z',				L'\0',	KEY_Y  );
			_set_keyname_(L'y',				L'Y',				L'\0',	KEY_Z  );

			_set_keyname_(L'1',				L'!',				L'\0',	KEY_1  );
			_set_keyname_(L'2',				L'"',				0x00B2,	KEY_2  );
			_set_keyname_(L'3',				0x00A7,			0x00B3,	KEY_3  );
			_set_keyname_(L'4',				L'$',				L'\0',	KEY_4  );
			_set_keyname_(L'5',				L'%',				L'\0',	KEY_5  );
			_set_keyname_(L'6',				L'&',				L'\0',	KEY_6  );
			_set_keyname_(L'7',				L'/',				L'{',		KEY_7  );
			_set_keyname_(L'8',				L'(',				L'[',		KEY_8  );
			_set_keyname_(L'9',				L')',				L']',		KEY_9  );
			_set_keyname_(L'0',				L'=',				L'}',		KEY_0  );

			_set_keyname_(L',',				L';',				L'\0',	KEY_COMMA  );
			_set_keyname_(L'.',				L':',				L'\0',	KEY_PERIOD  );
			_set_keyname_(L'-',				L'_',				L'\0',	KEY_SLASH  );

			_set_keyname_(0x00FC,			0x00DC,			L'\0',	KEY_LBRACKET  );
			_set_keyname_(L'+',				L'*',				L'~',		KEY_RBRACKET  );

			_set_keyname_(0x00F6,			0x00D6,			L'\0',	KEY_SEMICOLON  );
			_set_keyname_(0x00E4,			0x00C4,			L'\0',	KEY_APOSTROPHE  );
			_set_keyname_(L'^',				0x00B0,			L'\0',	KEY_TICK  );
			_set_keyname_(L'#',				L'\'',			L'\0',	KEY_BACKSLASH  );

			_set_keyname_(0x00DF,			L'?',				L'\\',	KEY_MINUS  );
			_set_keyname_(0x00B4,			L'`',				L'\0',	KEY_EQUAL  );

			_set_keyname_(L'<',				L'>',				L'|',		KEY_102  );

			m_shift2Key = KEY_RALT;
			break;

		case LANGUAGE_ID_FRENCH:
			_set_keyname_(L'-',				L'-',				L'\0',	KEY_KPMINUS );
			_set_keyname_(L'+',				L'+',				L'\0',	KEY_KPPLUS );
			_set_keyname_(L'\n',			L'\n',			L'\0',	KEY_KPENTER );
			_set_keyname_(L'/',				L'/',				L'\0',	KEY_KPSLASH );
			_set_keyname_(L'.',				L'.',				L'\0',	KEY_KPDEL );
			_set_keyname_(L'*',				L'*',				L'\0',	KEY_KPSTAR );

			_set_keyname_(L'q',				L'Q',				L'\0',	KEY_A  );
			_set_keyname_(L'b',				L'B',				L'\0',	KEY_B  );
			_set_keyname_(L'c',				L'C',				L'\0',	KEY_C  );
			_set_keyname_(L'd',				L'D',				L'\0',	KEY_D  );
			_set_keyname_(L'e',				L'E',				L'\0',	KEY_E  );
			_set_keyname_(L'f',				L'F',				L'\0',	KEY_F  );
			_set_keyname_(L'g',				L'G',				L'\0',	KEY_G  );
			_set_keyname_(L'h',				L'H',				L'\0',	KEY_H  );
			_set_keyname_(L'i',				L'I',				L'\0',	KEY_I  );
			_set_keyname_(L'j',				L'J',				L'\0',	KEY_J  );
			_set_keyname_(L'k',				L'K',				L'\0',	KEY_K  );
			_set_keyname_(L'l',				L'L',				L'\0',	KEY_L  );
			_set_keyname_(L',',				L'?',				L'\0',	KEY_M  );
			_set_keyname_(L'n',				L'N',				L'\0',	KEY_N  );
			_set_keyname_(L'o',				L'O',				L'\0',	KEY_O  );
			_set_keyname_(L'p',				L'P',				L'\0',	KEY_P  );
			_set_keyname_(L'a',				L'A',				L'\0',	KEY_Q  );
			_set_keyname_(L'r',				L'R',				L'\0',	KEY_R  );
			_set_keyname_(L's',				L'S',				L'\0',	KEY_S  );
			_set_keyname_(L't',				L'T',				L'\0',	KEY_T  );
			_set_keyname_(L'u',				L'U',				L'\0',	KEY_U  );
			_set_keyname_(L'v',				L'V',				L'\0',	KEY_V  );
			_set_keyname_(L'z',				L'Z',				L'\0',	KEY_W  );
			_set_keyname_(L'x',				L'X',				L'\0',	KEY_X  );
			_set_keyname_(L'y',				L'Y',				L'\0',	KEY_Y  );
			_set_keyname_(L'w',				L'W',				L'\0',	KEY_Z  );

			_set_keyname_(L'&',				L'1',				L'\0',	KEY_1  );
			_set_keyname_(0x00E9,			L'2',				L'~',		KEY_2  );
			_set_keyname_(L'"',				L'3',				L'#',		KEY_3  );
			_set_keyname_(L'\'',			L'4',				L'{',		KEY_4  );
			_set_keyname_(L'(',				L'5',				L'[',		KEY_5  );
			_set_keyname_(L'-',				L'6',				L'|',		KEY_6  );
			_set_keyname_(0x00E8,			L'7',				L'`',		KEY_7  );
			_set_keyname_(L'_',				L'8',				L'\\',	KEY_8  );
			_set_keyname_(0x00E7,			L'9',				L'\0',	KEY_9  );
			_set_keyname_(0x00E0,			L'0',				L'@',		KEY_0  );

			_set_keyname_(L';',				L'.',				L'\0',	KEY_COMMA  );
			_set_keyname_(L':',				L'/',				L'\0',	KEY_PERIOD  );
			_set_keyname_(L'!',				0x00A7,			L'\0',	KEY_SLASH  );

			_set_keyname_(L'^',				0x00A8,			L'\0',	KEY_LBRACKET  );
			_set_keyname_(L'$',				0x00A3,			0x00A4,	KEY_RBRACKET  );

			_set_keyname_(L'm',				L'M',				L'\0',	KEY_SEMICOLON  );
			_set_keyname_(0x00F9,			L'%',				L'\0',	KEY_APOSTROPHE  );
			_set_keyname_(0x00B2,			L'\0',			L'\0',	KEY_TICK  );
			_set_keyname_(L'*',				0x00B5,			L'\0',	KEY_BACKSLASH  );

			_set_keyname_(L')',				0x00B0,			L']',		KEY_MINUS  );
			_set_keyname_(L'=',				L'+',				L'}',		KEY_EQUAL  );

			_set_keyname_(L'<',				L'>',				L'\0',	KEY_102  );

			m_shift2Key = KEY_RALT;
			break;

		case LANGUAGE_ID_ITALIAN:
			_set_keyname_(L'-',				L'-',				L'\0',	KEY_KPMINUS );
			_set_keyname_(L'+',				L'+',				L'\0',	KEY_KPPLUS );
			_set_keyname_(L'\n',			L'\n',			L'\0',	KEY_KPENTER );
			_set_keyname_(L'/',				L'/',				L'\0',	KEY_KPSLASH );
			_set_keyname_(L'.',				L'.',				L'\0',	KEY_KPDEL );
			_set_keyname_(L'*',				L'*',				L'\0',	KEY_KPSTAR );

			_set_keyname_(L'a',				L'A',				L'\0',	KEY_A  );
			_set_keyname_(L'b',				L'B',				L'\0',	KEY_B  );
			_set_keyname_(L'c',				L'C',				L'\0',	KEY_C  );
			_set_keyname_(L'd',				L'D',				L'\0',	KEY_D  );
			_set_keyname_(L'e',				L'E',				L'\0',	KEY_E  );
			_set_keyname_(L'f',				L'F',				L'\0',	KEY_F  );
			_set_keyname_(L'g',				L'G',				L'\0',	KEY_G  );
			_set_keyname_(L'h',				L'H',				L'\0',	KEY_H  );
			_set_keyname_(L'i',				L'I',				L'\0',	KEY_I  );
			_set_keyname_(L'j',				L'J',				L'\0',	KEY_J  );
			_set_keyname_(L'k',				L'K',				L'\0',	KEY_K  );
			_set_keyname_(L'l',				L'L',				L'\0',	KEY_L  );
			_set_keyname_(L'm',				L'M',				L'\0',	KEY_M  );
			_set_keyname_(L'n',				L'N',				L'\0',	KEY_N  );
			_set_keyname_(L'o',				L'O',				L'\0',	KEY_O  );
			_set_keyname_(L'p',				L'P',				L'\0',	KEY_P  );
			_set_keyname_(L'q',				L'Q',				L'\0',	KEY_Q  );
			_set_keyname_(L'r',				L'R',				L'\0',	KEY_R  );
			_set_keyname_(L's',				L'S',				L'\0',	KEY_S  );
			_set_keyname_(L't',				L'T',				L'\0',	KEY_T  );
			_set_keyname_(L'u',				L'U',				L'\0',	KEY_U  );
			_set_keyname_(L'v',				L'V',				L'\0',	KEY_V  );
			_set_keyname_(L'w',				L'W',				L'\0',	KEY_W  );
			_set_keyname_(L'x',				L'X',				L'\0',	KEY_X  );
			_set_keyname_(L'y',				L'Y',				L'\0',	KEY_Y  );
			_set_keyname_(L'z',				L'Z',				L'\0',	KEY_Z  );

			_set_keyname_(L'1',				L'!',				L'\0',	KEY_1  );
			_set_keyname_(L'2',				L'"',				L'\0',	KEY_2  );
			_set_keyname_(L'3',				0x00A3,			L'\0',	KEY_3  );
			_set_keyname_(L'4',				L'$',				L'\0',	KEY_4  );
			_set_keyname_(L'5',				L'%',				L'\0',	KEY_5  );
			_set_keyname_(L'6',				L'&',				L'\0',	KEY_6  );
			_set_keyname_(L'7',				L'/',				L'\0',	KEY_7  );
			_set_keyname_(L'8',				L'(',				L'\0',	KEY_8  );
			_set_keyname_(L'9',				L')',				L'\0',	KEY_9  );
			_set_keyname_(L'0',				L'=',				L'\0',	KEY_0  );

			_set_keyname_(L',',				L';',				L'\0',	KEY_COMMA  );
			_set_keyname_(L'.',				L':',				L'\0',	KEY_PERIOD  );
			_set_keyname_(L'-',				L'_',				L'\0',	KEY_SLASH  );

			_set_keyname_(0x00E8,			0x00E9,			L'[',		KEY_LBRACKET  );
			_set_keyname_(L'+',				L'*',				L']',		KEY_RBRACKET  );

			_set_keyname_(0x00F2,			0x00E7,			L'@',		KEY_SEMICOLON  );
			_set_keyname_(0x00E0,			0x00B0,			L'#',		KEY_APOSTROPHE  );
			_set_keyname_(L'\\',			L'|',				L'\0',	KEY_TICK  );
			_set_keyname_(0x00F9,			0x00A7,			L'\0',	KEY_BACKSLASH  );

			_set_keyname_(L'\'',			L'?',				L'\0',	KEY_MINUS  );
			_set_keyname_(0x00EC,			L'^',				L'\0',	KEY_EQUAL  );

			_set_keyname_(L'<',				L'>',				L'\0',	KEY_102  );

			m_shift2Key = KEY_RALT;
			break;

	}  // end switch( Language )

	// BFME 2: a German layout swaps the Y and Z names whatever language was
	// chosen above, and forces the German language.
	if( low == 0x0407
		 || low == 0x0807
		 || low == 0x0c07
		 || low == 0x1007
		 || low == 0x1407 )
	{
		_set_keyname_(L'z',				L'Z',				L'\0',	KEY_Y  );
		_set_keyname_(L'y',				L'Y',				L'\0',	KEY_Z  );
		OurLanguage = LANGUAGE_ID_GERMAN;
	}


}  // end initKeyNames

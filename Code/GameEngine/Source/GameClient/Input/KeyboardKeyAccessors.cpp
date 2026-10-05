// cl: /O1 /DNDEBUG /MD /EHsc /G7
//
// Two Keyboard key-table accessors (formerly rowed as AIPlayer::rva002326AE
// and AIPlayer::rva00232643; the class is Keyboard, see Keyboard.cpp):
//
//   0x002326AE  77B  getPrintableKey: Zero Hour's
//                    Keyboard::getPrintableKey(UnsignedByte key, Int state)
//                    over m_keyNames[256] at +0x81C (three WideChars per
//                    key), returning 0 out of range. The name and signature
//                    are Zero Hour's and fit the body exactly (inferred).
//                    Callers 0x00325AC6 and 0x0035962B.
//   0x00232643  17B  rva00232643: bit KEY_STATE_DOWN of m_keyStatus[key]'s
//                    state (+0x1C, 8-byte KeyboardIO). Zero Hour has no
//                    one-argument key-down query, so the name stays
//                    address-derived. Callers 0x0042F8AF and 0x005B1FFA.
//
// The imul by 6 for the key-name stride needs /G7.

typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

// upstream layout: GeneralsMD/Code/GameEngine/Include/GameClient/Keyboard.h
struct KeyboardIO
{
	UnsignedByte key;
	UnsignedByte status;
	UnsignedShort state;
	UnsignedInt sequence;
};

class Keyboard
{
public:
	enum { MAX_KEY_STATES = 3 };
	enum { KEY_NAMES_COUNT = 256 };

	WideChar getPrintableKey(UnsignedByte key, Int state);
	bool rva00232643(UnsignedByte key);

private:
	char m_unmodelled00[0x1C];
	KeyboardIO m_keyStatus[256];						// +0x1C
	struct
	{
		WideChar stdKey;
		WideChar shifted;
		WideChar shifted2;
	} m_keyNames[KEY_NAMES_COUNT];						// +0x81C
};

WideChar Keyboard::getPrintableKey(UnsignedByte key, Int state)
{
	if (key >= KEY_NAMES_COUNT)
		return 0;
	if (state < 0 || state >= MAX_KEY_STATES)
		return 0;
	if (state == 0)
		return m_keyNames[key].stdKey;
	if (state == 1)
		return m_keyNames[key].shifted;
	return m_keyNames[key].shifted2;
}

bool Keyboard::rva00232643(UnsignedByte key)
{
	return (((unsigned char)m_keyStatus[key].state) >> 1) & 1;
}

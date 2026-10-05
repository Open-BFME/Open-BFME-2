// cl: /O1 /DNDEBUG /MD /EHsc
//
// Keyboard constructor (retail 0x00232920, 86 bytes), destructor
// ??1Keyboard@@UAE@XZ (0x00232976, 65 bytes), its scalar deleting
// destructor (0x002329B7, 28 bytes) and Keyboard::isShift (0x00232683,
// 19 bytes). These rows were labelled AIPlayer until the vtable they install,
// 0x00BE81F0, was identified as Keyboard's: its slots 1/10/15 are the matched
// Keyboard::init/update/createStreamMessages (KeyboardInitUpdate.cpp), slots
// 14 and 16 are pure (Zero Hour's getCapsState and getKey), and the derived
// table 0x00BC8688 (DirectInputKeyboard, Win32DIKeyboard.cpp) fills them with
// GetKeyState(VK_CAPITAL) and the DirectInput getKey. The real AIPlayer is the
// vtable 0x00C62DC8 family at 0x004F....
//
// Layout (read off retail; member names are Zero Hour's
// GameEngine/Include/GameClient/Keyboard.h, matched by role):
// - +0x0C m_modifiers (KEY_STATE_* word; the DirectInputKeyboard constructor
//   sets KEY_STATE_CAPSLOCK 0x0200 there), +0x0E m_shift2Key.
// - +0x10 the key list. Zero Hour has KeyboardIO m_keys[256]; BFME2 keeps a
//   vector instead (createStreamMessages walks +0x10..+0x14 and
//   checkKeyRepeat push_backs 8-byte KeyboardIO records). It is modelled as
//   its _Vector_base subobject with a minimal local allocator: retail inlines
//   vector() and only the _Base call (folded 0x00211E58) remains out of line.
//   The allocator needs a user-provided empty constructor; an implicit one
//   makes the compiler zero the stack temp (extra stosb plus a frame). The
//   element type keeps its pinned placeholder spelling (BfmeE16).
// - +0x1C m_keyStatus[256] (8-byte KeyboardIO), +0x81C m_keyNames[256]
//   (three WideChars each), +0xE1C m_inputFrame.
// - The destructor frees the vector's start pointer with the C++-linkage free
//   (0x00030830): the inlined POD-vector deallocate. It then chains to the
//   SubsystemInterface destructor (ledger GameEngineDeletingBase,
//   0x001B4E74). The C++ linkage is load-bearing: it emits the unwind state
//   stores retail carries, while an extern "C" import would call through
//   the IAT.
// - isShift is Zero Hour's (LSHIFT 0x10 | RSHIFT 0x20, or SHIFT2 0x0400);
//   the name is inferred from that body shape, and BFME2 returns a byte bool
//   here where Zero Hour's Bool is an Int.

// ??0?$allocator@UBfmeE16@@@_STL@@QAE@XZ present-unmatched
extern "C" void *memset(void *s, int c, unsigned n) throw();
extern "C" void __cdecl free(void *block) throw(...);

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

// Ledger name of SubsystemInterface (vptr, +0x04, AsciiString at +0x08).
class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase() throw();
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

struct BfmeE16 { float x, y, z, w; };

namespace _STL
{

template <class Element> class allocator
{
public:
	allocator() {}
};

template <class Item, class Alloc> class _Vector_base
{
public:
	_Vector_base(const Alloc &alloc) throw();
	void *_M_start;
	void *_M_finish;
	void *_M_end;
};

}

enum
{
	KEY_STATE_NONE = 0x0000,
	KEY_STATE_LSHIFT = 0x0010,
	KEY_STATE_RSHIFT = 0x0020,
	KEY_STATE_SHIFT2 = 0x0400
};

enum { KEY_NONE = 0x00 };

class Keyboard : public GameEngineDeletingBase
{
public:
	Keyboard();
	virtual ~Keyboard();

	bool isShift();

protected:
	unsigned short m_modifiers;									// +0x0C
	unsigned char m_shift2Key;									// +0x0E
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_keys;	// +0x10
	unsigned char m_keyStatus[0x800];							// +0x1C, KeyboardIO[256]
	unsigned char m_keyNames[0x600];							// +0x81C, 256 x 3 WideChar
	int m_inputFrame;											// +0xE1C
};

Keyboard::Keyboard()
	: GameEngineDeletingBase(), m_keys(_STL::allocator<BfmeE16>())
{
	memset(m_keyStatus, 0, sizeof(m_keyStatus));
	m_modifiers = KEY_STATE_NONE;
	m_shift2Key = KEY_NONE;
	memset(m_keyNames, 0, sizeof(m_keyNames));
	m_inputFrame = 0;
}

Keyboard::~Keyboard()
{
	if (m_keys._M_start)
		free(m_keys._M_start);
}

bool Keyboard::isShift()
{
	unsigned short modifiers = m_modifiers;
	if (((modifiers & (KEY_STATE_LSHIFT | KEY_STATE_RSHIFT)) != 0) || ((modifiers & KEY_STATE_SHIFT2) != 0))
		return true;
	return false;
}

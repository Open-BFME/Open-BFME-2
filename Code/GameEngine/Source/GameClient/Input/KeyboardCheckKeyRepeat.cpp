// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?checkKeyRepeat@Keyboard@@IAE_NXZ, retail 0x002329D3, 111 bytes (formerly
// rowed as AIPlayer::rva002329D3; the class is Keyboard, see Keyboard.cpp).
// Zero Hour's Keyboard::checkKeyRepeat (GameClient/Input/Keyboard.cpp), name
// inferred from the body: scan m_keyStatus for the first key whose state has
// KEY_STATE_DOWN and whose sequence is more than KEY_REPEAT_DELAY (10) input
// frames old, append it as KEY_STATE_DOWN | KEY_STATE_AUTOREPEAT (0x102),
// stamp every key with the input frame and the repeated key with frame - 12.
// BFME2 appends to its key vector (+0x10, push_back 0x00539A2E, element type
// kept at its pinned placeholder spelling BfmeE8 = 8-byte KeyboardIO) where
// Zero Hour writes into m_keys[] before a KEY_NONE terminator. Caller is
// 0x00232A42 (Keyboard::update's second step).

typedef bool Bool;

struct BfmeE8 {
	unsigned char key;
	unsigned char status;
	unsigned short state;
	int sequence;
};
namespace _STL {
template <class T> class allocator {
public:
	allocator() {}
};
template <class T, class A> class vector {
	void *_M_start;
	void *_M_finish;
	void *_M_end;
public:
	void push_back(const T &);
};
}

enum
{
	KEY_STATE_DOWN = 0x0002,
	KEY_STATE_AUTOREPEAT = 0x0100
};

class Keyboard {
	enum { KEY_REPEAT_DELAY = 10 };
	enum { NUM_KEYS = 256 };

	char m_pad00[0x10];
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_keys;		// +0x10
	BfmeE8 m_keyStatus[NUM_KEYS];								// +0x1C
	char m_keyNames[0x600];										// +0x81C
	int m_inputFrame;											// +0xE1C
protected:
	Bool checkKeyRepeat();
};

Bool Keyboard::checkKeyRepeat()
{
	Bool retVal = false;
	BfmeE8 *status = m_keyStatus;
	for (int key = 0; key < NUM_KEYS; ++key, ++status) {
		if ((status->state & KEY_STATE_DOWN) == 0)
			continue;
		if ((unsigned)(m_inputFrame - status->sequence) <= KEY_REPEAT_DELAY)
			continue;
		BfmeE8 e;
		e.key = (unsigned char)key;
		e.state = KEY_STATE_DOWN | KEY_STATE_AUTOREPEAT;
		e.status = 0;
		m_keys.push_back(e);
		for (int index = 0; index < NUM_KEYS; ++index)
			m_keyStatus[index].sequence = m_inputFrame;
		m_keyStatus[key].sequence = m_inputFrame - (KEY_REPEAT_DELAY + 2);
		retVal = true;
		break;
	}
	return retVal;
}

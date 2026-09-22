// cl: /O1 /DNDEBUG /MD /EHsc

// ?rva00085124@GameLogic@@QAE_NXZ @0x85124 (23B):
// GameLogic mode predicate called by RecorderClass::isMultiplayer.
// Returns whether the game mode at +0x110 is 4 or 7. Leaf, no pins.

typedef int Int;
typedef bool Bool;

class GameLogic
{
public:
	Bool rva00085124(void);
	char m_pad[0x110];
	Int m_gameMode;
};

// ?rva00085124@GameLogic@@QAE_NXZ
Bool GameLogic::rva00085124(void)
{
	return m_gameMode == 4 || m_gameMode == 7;
}

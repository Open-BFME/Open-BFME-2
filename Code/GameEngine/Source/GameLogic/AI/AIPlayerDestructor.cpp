// cl: /O1 /DNDEBUG /MD /EHsc
//
// AIPlayer::~AIPlayer, retail 0x00232976, 65 bytes, and its scalar
// deleting destructor ??_GAIPlayer@@MAEPAXI@Z, retail 0x002329B7,
// 28 bytes.
//
// Layout evidence (all read off retail; the BFME1 AIPlayer donor only
// proves the class name and the Player association):
// - The constructor next door (0x00232920) installs vtable 0x00BE81F0,
//   builds a vector base at +0x10 through the folded _Vector_base
//   constructor (0x00211E58), memsets the +0x1C and +0x81C blocks and
//   zeroes +0x0C/+0x0E, so the class is ~0xE20 bytes with a vector at
//   +0x10.
// - A sibling body toggles bit 2 of the byte at +0x0C, so +0x0C is a
//   flags field (provisional name).
// - This destructor frees the vector's start pointer at +0x10 with the
//   C++-linkage free (0x00030830): the inlined POD-vector deallocate.
//   It then chains to the GameEngineDeletingBase destructor (0x001B4E74).
//   The C++ linkage is load-bearing: it emits the unwind state stores
//   retail carries, while an extern "C" import would call through the IAT.

void free(void *block);

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class AIPlayer : public GameEngineDeletingBase
{
protected:
	virtual ~AIPlayer();

private:
	int m_flags0C;
	void *m_vectorStart10;
};

// ??1AIPlayer@@MAE@XZ
AIPlayer::~AIPlayer()
{
	if (m_vectorStart10)
		free(m_vectorStart10);
}

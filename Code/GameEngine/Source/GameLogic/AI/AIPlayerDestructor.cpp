// cl: /O1 /DNDEBUG /MD /EHsc
//
// AIPlayer constructor, retail 0x00232920, 86 bytes, destructor
// ??1AIPlayer@@MAE@XZ, retail 0x00232976, 65 bytes, and its scalar
// deleting destructor ??_GAIPlayer@@MAEPAXI@Z, retail 0x002329B7,
// 28 bytes.
//
// Layout evidence (all read off retail; the BFME1 AIPlayer donor only
// proves the class name and the Player association):
// - This constructor installs vtable 0x00BE81F0, builds a vector base at
//   +0x10 through the folded _Vector_base constructor (0x00211E58),
//   memsets the +0x1C and +0x81C blocks and zeroes +0x0C/+0x0E and
//   +0xE1C, so the class is ~0xE20 bytes with a BfmeE16 vector at +0x10.
// - A sibling body toggles bit 2 of the byte at +0x0C, so +0x0C/+0x0E
//   are flag bytes (provisional names, word+byte zeroing is retail's).
// - The destructor frees the vector's start pointer at +0x10 with the
//   C++-linkage free (0x00030830): the inlined POD-vector deallocate.
//   It then chains to the GameEngineDeletingBase destructor (0x001B4E74).
//   The C++ linkage is load-bearing: it emits the unwind state stores
//   retail carries, while an extern "C" import would call through the IAT.
// - The vector member is modeled as its _Vector_base subobject with a
//   minimal local allocator: retail inlines vector() itself and only the
//   _Base call remains out-of-line. The allocator needs a user-provided
//   empty constructor; an implicit one makes the compiler zero the stack
//   temp (extra stosb plus a frame) which retail does not have.

// ??0?$allocator@UBfmeE16@@@_STL@@QAE@XZ present-unmatched
extern "C" void *memset(void *s, int c, unsigned n) throw();
void free(void *block);

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

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

class AIPlayer : public GameEngineDeletingBase
{
public:
	AIPlayer();

protected:
	virtual ~AIPlayer();

private:
	unsigned short m_flags0C;
	unsigned char m_flag0E;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_items10;
	unsigned char m_block1C[0x800];
	unsigned char m_block81C[0x600];
	int m_tailE1C;
};

// ??0AIPlayer@@QAE@XZ
AIPlayer::AIPlayer()
	: GameEngineDeletingBase(), m_items10(_STL::allocator<BfmeE16>())
{
	memset(m_block1C, 0, 0x800);
	m_flags0C = 0;
	m_flag0E = 0;
	memset(m_block81C, 0, 0x600);
	m_tailE1C = 0;
}

// ??1AIPlayer@@MAE@XZ
AIPlayer::~AIPlayer()
{
	if (m_items10._M_start)
		free(m_items10._M_start);
}

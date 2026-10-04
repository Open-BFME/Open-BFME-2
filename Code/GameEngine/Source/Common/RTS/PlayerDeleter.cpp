// cl: /O1 /DNDEBUG /MD
//
// ??_GPlayer@@UAEPAXI@Z, retail 0x002B14CF (28 bytes): slot 0
// of vtable 0x00BFDF3C, whose slot-2 name getter returns "Player" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x002B11A7 and then the global operator delete when bit 0 of
// the flags is set. That destructor re-stores vtable 0x00BFDF3C, which
// identifies it as Player::~Player (pinned in reverse/symbols.csv).
// Class shape from Zero Hour's Common/Player.h (public virtual ~Player).
// BFME 2's form frees through the global operator delete.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;

// The this-adjusting deleting-destructor thunk (sub ecx, 0x8) in the
// secondary vtable proves a second base with a virtual destructor at +0x8;
// these two bases model only that.
class PlayerBase0
{
public:
	virtual ~PlayerBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

class PlayerBase8
{
public:
	virtual ~PlayerBase8();
};

class Player : public PlayerBase0, public PlayerBase8
{
public:
	Player(EmitVtableTag *);
	virtual ~Player();
};

// ?<Player::Player> absent-from-retail
Player::Player(EmitVtableTag *)
{
}

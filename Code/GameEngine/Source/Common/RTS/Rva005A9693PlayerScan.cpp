// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005A9693@Rva005A9693Owner@@QAEXXZ @0x005A9693 102B: thiscall, no args, void.
// Loops over ThePlayerList (count at +0x14, getNthPlayer per index). A player
// other than the owner's first pointer, that passes the byte-flag test from
// Rva002AA245MovzxByteChaseField::get, and whose relationship with the owner is
// ENEMIES (zero), gets a {index, 0.0f} record appended to the vector at +4.
// Layout and record meaning are address-derived views; the leaf names are the
// ledger's own spellings for the callees.
namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class Alloc>
class vector
{
public:
	void push_back(const T &value);
private:
	char m_pad[12];
};
}

typedef int Int;

struct BfmeE8
{
	int a;
	float b;
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

class Player
{
public:
	Relationship getRelationship(const Player *other) const;
};

class Rva002AA245MovzxByteChaseField
{
public:
	unsigned int get() const;
};

class PlayerList
{
public:
	Player *getNthPlayer(Int i);
	unsigned char m_pad[0x14];
	Int m_playerCount; // +0x14
};

extern PlayerList *ThePlayerList;

class Rva005A9693Owner
{
public:
	void rva005A9693();
private:
	Player *m_player;
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_vec;
};

// ?rva005A9693@Rva005A9693Owner@@QAEXXZ
void Rva005A9693Owner::rva005A9693()
{
	for (Int i = 0; i < ThePlayerList->m_playerCount; ++i) {
		Player *p = ThePlayerList->getNthPlayer(i);
		if (p && p != m_player && (unsigned char)((Rva002AA245MovzxByteChaseField *)p)->get()
			&& m_player->getRelationship(p) == ENEMIES) {
			BfmeE8 rec;
			rec.a = i;
			rec.b = 0.0f;
			m_vec.push_back(rec);
		}
	}
}

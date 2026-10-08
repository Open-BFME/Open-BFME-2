// cl: /DNDEBUG /MD /GX-
//
// ?rva003F036E@Rva003F02E4@@QAEHXZ, retail 0x003F036E, 32 bytes.
// Predicate: true when the pointer vector at +0x164 is non-empty, else when
// the rowed sibling rva003F02E4 0x003F02E4 returns true. The class layout,
// the rowed siblings rva003F02E4/rva003F0336 and the flags come from
// Code/GameEngine/Source/Common/Rva003F02E4.cpp. Evidence: callers
// 0x0020FCA4 0x00319637 0x003F0361 0x003F037E.
// The count is materialised as an unsigned local and compared `> 0`, which
// reproduces retail's sub/sar-2/jne count check; testing the pointer
// difference inline folds to the 3-byte-longer `test edx,0xFFFFFFFC`.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva004E0605ByteChaseField
{
public:
	unsigned char get() const;
};

class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;
};

class Rva002E2903Player : public Rva002E071E
{
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

struct Rva003F02E4Node
{
	char m_pad[0x20];
	Rva004E0605ByteChaseField *m_holder;
	char m_pad2[0x10];
	unsigned char m_34;
};

struct Rva003F02E4Vec
{
	int *begin;
	int *end;
	int *eos;
};

class Rva003F02E4
{
public:
	bool rva003F02E4();
	bool rva003F0336(const Rva002E071E *other);
	int rva003F036E();
private:
	unsigned char m_pad[0x11C];
	bool m_11C;
	char m_pad2[0x13C - 0x11D];
	int m_13C;
	char m_pad3[0x164 - 0x140];
	Rva003F02E4Vec m_164;
	Rva003F02E4Node **m_170;
	Rva003F02E4Node **m_174;
};

int Rva003F02E4::rva003F036E()
{
	Rva003F02E4Vec *v = &m_164;
	unsigned n = (unsigned)(v->end - v->begin);
	if (n > 0 || rva003F02E4())
		return 1;
	return 0;
}

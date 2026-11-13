// cl: /O1 /G7 /arch:SSE /GX- /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no ledger row covered (second
// file; see GapBodiesSeat1A.cpp). Retail bytes establish every shape; owning
// classes are not recovered unless named, so each keeps an address-derived
// name and a view of only the members it touches. Callees are the ledger's
// existing rows under their current spellings.
#include "ascii_string.h"

#include "../../../Libraries/Include/Lib/Coord3D.h"

// --- 0x002C1F6F (16B): unlinks the head node (next at +4) and returns it by
// value; the word argument is unused.
struct Rva002C1F6FNode
{
	int m_00;
	Rva002C1F6FNode *m_next;
};

struct Rva002C1F6FIterator
{
	Rva002C1F6FIterator(Rva002C1F6FNode *node) : m_node(node) {}
	Rva002C1F6FNode *m_node;
};

class Rva002C1F6F
{
public:
	Rva002C1F6FIterator rva002C1F6F(int unused);
private:
	Rva002C1F6FNode *m_head;
};

Rva002C1F6FIterator Rva002C1F6F::rva002C1F6F(int)
{
	Rva002C1F6FNode *node = m_head;
	m_head = node->m_next;
	return Rva002C1F6FIterator(node);
}

// --- 0x002C580F (17B): float setter +0x560; 0x002C5887 (20B): stores a
// by-value position at +0x554; 0x002CEF9B (15B): halfword setter +0x5D8.
class Rva002C580F
{
public:
	void rva002C580F(float value);
	void rva002C5887(Coord3D pos);
	void rva002CEF9B(short value);
private:
	char m_pad000[0x554];
	Coord3D m_554;
	float m_560;
	char m_pad564[0x5D8 - 0x564];
	short m_5D8;
};

void Rva002C580F::rva002C580F(float value)
{
	m_560 = value;
}

void Rva002C580F::rva002C5887(Coord3D pos)
{
	m_554 = pos;
}

void Rva002C580F::rva002CEF9B(short value)
{
	m_5D8 = value;
}

// --- 0x002C5DBD (19B, cdecl): whether the string equals the text.
int Rva002C5DBD(const char *text, const AsciiString *str)
{
	return str->compare(text) == 0;
}

// --- 0x002C71CA (23B): whether +0x439 has bits outside the mask;
// 0x002C7218 (17B): the +4 record's +0x128 word is clear; 0x002C75FA (17B):
// the +4 record's +0x35C flag, false without one; 0x002C7447 (19B) and
// 0x002C745A (15B): toggle / set the indexed flag of the +0x36 array;
// 0x002C74CB (14B) and 0x002C74EA (17B): the indexed 0x1C-byte record at
// +0x44 and 0x4C-byte record at +0x194.
struct Rva002C7218Record
{
	char m_pad000[0x128];
	int m_128;
	char m_pad12C[0x35C - 0x12C];
	bool m_35C;
};

struct Rva002C74CBRecord
{
	char m_data[0x1C];
};

struct Rva002C74EARecord
{
	char m_data[0x4C];
};

class Rva002C71CA
{
public:
	int rva002C71CA(int mask) const;
	bool rva002C7218() const;
	bool rva002C75FA() const;
	void rva002C7447(int index);
	void rva002C745A(int index, bool value);
	Rva002C74CBRecord *rva002C74CB(int index);
	Rva002C74EARecord *rva002C74EA(int index);
private:
	int m_00;
	Rva002C7218Record *m_04;
	char m_pad08[0x36 - 8];
	bool m_flags[0x44 - 0x36];
	Rva002C74CBRecord m_44[(0x194 - 0x44) / 0x1C];
	Rva002C74EARecord m_194[1];
	char m_pad1E0[0x439 - 0x194 - 0x4C];
	unsigned char m_439;
};

int Rva002C71CA::rva002C71CA(int mask) const
{
	return (m_439 & ~mask) != 0;
}

bool Rva002C71CA::rva002C7218() const
{
	return m_04->m_128 == 0;
}

bool Rva002C71CA::rva002C75FA() const
{
	if (m_04)
		return m_04->m_35C;
	return false;
}

void Rva002C71CA::rva002C7447(int index)
{
	m_flags[index] = !m_flags[index];
}

void Rva002C71CA::rva002C745A(int index, bool value)
{
	m_flags[index] = value;
}

Rva002C74CBRecord *Rva002C71CA::rva002C74CB(int index)
{
	return &m_44[index];
}

Rva002C74EARecord *Rva002C71CA::rva002C74EA(int index)
{
	return &m_194[index];
}

// --- 0x002C74C0 (11B, thiscall): indexed dword getter, array at +0x14.
// Retail placed ?Get_Tex_Offset@FVFInfoClass@@QBEII@Z here by masked search,
// but BFME 2's FVFInfoClass keeps texcoord_offset at +0x24 (the inline reads in
// the matched 0x00126433 and 0x00743700 RenderStreak bodies), and this body
// sits among game-logic getters with no FVF caller.
class Rva002C74C0
{
public:
	int rva002C74C0(int index) const;
private:
	char m_pad00[0x14];
	int m_14[1];
};

int Rva002C74C0::rva002C74C0(int index) const
{
	return m_14[index];
}

// --- 0x002C751E (17B, cdecl): zeroes a 0x1C-byte record through the CRT
// memset thunk 0x006291AE.
// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)

void Rva002C751E(Rva002C74CBRecord *record)
{
	memset(record, 0, 0x1C);
}

// --- 0x002C92B8 (36B) and 0x002C92DC (30B): the rowed 0x002C9217 with the
// height difference of two records (+0x40) or the negated +8 value.
struct Rva002C92B8Record
{
	char m_pad00[8];
	float m_08;
	char m_pad0C[0x40 - 0x0C];
	float m_40;
};

#include "../../Include/Common/BfmeRangedWeaponTemplate.h"

float BfmeRangedWeaponTemplate::rva002C92B8(void *arg, const Rva002C92B8Record *from, const Rva002C92B8Record *to)
{
	return rva002C9217(arg, to->m_40 - from->m_40);
}

float BfmeRangedWeaponTemplate::rva002C92DC(void *arg, const Rva002C92B8Record *rec)
{
	return rva002C9217(arg, 0.0f - rec->m_08);
}

// --- 0x002C9846 (16B) and 0x002C9856 (21B): Object distance helpers over
// this or the other object's +0x38 position.
class Object
{
public:
	float rva002C97E8(const Coord3D *a, const Coord3D *b) const;					// 0x002C97E8
	float rva002636F6(const Coord3D *pos, const void *other, const Coord3D *otherPos) const;	// 0x002636F6
	float rva002C9846(const Coord3D *pos) const;
	float rva002C9856(const Coord3D *pos, const Object *other) const;
	char m_pad00[0x38];
	Coord3D m_pos;
};

float Object::rva002C9846(const Coord3D *pos) const
{
	return rva002C97E8(&m_pos, pos);
}

float Object::rva002C9856(const Coord3D *pos, const Object *other) const
{
	return rva002636F6(pos, other, &other->m_pos);
}

// --- 0x002D2CED (18B, cdecl): two pointed-to characters are equal.
int Rva002D2CED(const char *a, const char *b)
{
	return *a == *b;
}

// --- 0x002D3609 (12B): bit 0 of the +0x24 byte of the +0x78 record of the
// +0x10 object.
struct Rva002D3609Inner
{
	char m_pad00[0x24];
	unsigned char m_bit0 : 1;
};

struct Rva002D3609Outer
{
	char m_pad00[0x78];
	Rva002D3609Inner *m_78;
};

class Rva002D3609
{
public:
	bool rva002D3609() const;
private:
	char m_pad00[0x10];
	Rva002D3609Outer *m_10;
};

bool Rva002D3609::rva002D3609() const
{
	return m_10->m_78->m_bit0;
}

// --- 0x002D3993 (10B): sum of +0x14, +0x0C and +4.
class Rva002D3993
{
public:
	int rva002D3993() const;
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

int Rva002D3993::rva002D3993() const
{
	return m_14 + m_0C + m_04;
}

// --- 0x002D948E..0x002D94BE (16B each): percentages at +0x20..+0x2C as
// multipliers (1 + p/100).
class Rva002D948E
{
public:
	float rva002D948E() const;
	float rva002D949E() const;
	float rva002D94AE() const;
	float rva002D94BE() const;
private:
	char m_pad00[0x20];
	float m_20;
	float m_24;
	float m_28;
	float m_2C;
};

float Rva002D948E::rva002D948E() const
{
	return m_20 * 0.01f + 1.0f;
}

float Rva002D948E::rva002D949E() const
{
	return m_24 * 0.01f + 1.0f;
}

float Rva002D948E::rva002D94AE() const
{
	return m_28 * 0.01f + 1.0f;
}

float Rva002D948E::rva002D94BE() const
{
	return m_2C * 0.01f + 1.0f;
}

// --- 0x002D955A..0x002D95F1: a one-of state at +0x38 with its value at
// +0x34: setters for states 1, 3, 4 and 5 (only from that state or the
// unset state 6) and getters for states 3, 4 and 5.
class Rva002D955A
{
public:
	void rva002D955A(int value);
	void rva002D9583(int value);
	int rva002D959F() const;
	void rva002D95AC(int value);
	int rva002D95C8() const;
	void rva002D95D5(int value);
	int rva002D95F1() const;
private:
	char m_pad00[0x34];
	int m_value;
	int m_state;
};

void Rva002D955A::rva002D955A(int value)
{
	if (m_state == 1 || m_state == 6)
	{
		m_value = value;
		m_state = 1;
	}
}

void Rva002D955A::rva002D9583(int value)
{
	if (m_state == 3 || m_state == 6)
	{
		m_value = value;
		m_state = 3;
	}
}

int Rva002D955A::rva002D959F() const
{
	if (m_state == 3)
		return m_value;
	return 0;
}

void Rva002D955A::rva002D95AC(int value)
{
	if (m_state == 4 || m_state == 6)
	{
		m_value = value;
		m_state = 4;
	}
}

int Rva002D955A::rva002D95C8() const
{
	if (m_state == 4)
		return m_value;
	return 0;
}

void Rva002D955A::rva002D95D5(int value)
{
	if (m_state == 5 || m_state == 6)
	{
		m_value = value;
		m_state = 5;
	}
}

int Rva002D955A::rva002D95F1() const
{
	if (m_state == 5)
		return m_value;
	return 0;
}

// --- 0x002DABD7 (11B) and 0x002DABE2 (14B): the indexed word of the +0x64
// and +0xD4 arrays; 0x002DAC08 (14B) float setter +0x18; 0x002DB995 (10B)
// byte setter +0x6F.
class Rva002DABD7
{
public:
	int *rva002DABD7(int index);
	int *rva002DABE2(int index);
	void rva002DAC08(float value);
	void rva002DB995(bool value);
private:
	char m_pad00[0x18];
	float m_18;
	char m_pad1C[0x64 - 0x1C];
	int m_64[(0x6F - 0x64) / 4];
	char m_pad70[0x6F - 0x64 - ((0x6F - 0x64) / 4) * 4];
	bool m_6F;
	char m_pad70b[0xD4 - 0x70];
	int m_D4[1];
};

int *Rva002DABD7::rva002DABD7(int index)
{
	return &m_64[index];
}

int *Rva002DABD7::rva002DABE2(int index)
{
	return &m_D4[index];
}

void Rva002DABD7::rva002DAC08(float value)
{
	m_18 = value;
}

void Rva002DABD7::rva002DB995(bool value)
{
	m_6F = value;
}

// --- 0x002D644C (20B): the rowed 0x002D563D lookup returned by value.
struct Rva0046AC52Key;
struct Rva0046AC52Pair
{
	int m_00;
	int m_04;
	int m_08;
};

class Rva0046AC52
{
public:
	Rva0046AC52Pair rva002D563D(const Rva0046AC52Key &key);	// 0x002D563D
	Rva0046AC52Pair rva002D644C(const Rva0046AC52Key &key);
};

Rva0046AC52Pair Rva0046AC52::rva002D644C(const Rva0046AC52Key &key)
{
	return rva002D563D(key);
}

#define GAP_V1(n) virtual void v##n();
#define GAP_V10(n) GAP_V1(n##0) GAP_V1(n##1) GAP_V1(n##2) GAP_V1(n##3) GAP_V1(n##4) GAP_V1(n##5) GAP_V1(n##6) GAP_V1(n##7) GAP_V1(n##8) GAP_V1(n##9)

// --- 0x002DBA07 (18B): opens a wide-named file through the rowed
// 0x00600676 with a zero third argument.
class File;

#include "../../Include/Common/FileSystem.h"

File *FileSystem::rva002DBA07(const unsigned short *name, int mode)
{
	return rva00600676(name, mode, 0);
}

// --- 0x002DBD64 (28B): assignment copying +4 and the +8 position (the
// vptr stays).
class Rva002DBD64
{
public:
	virtual ~Rva002DBD64();
	Rva002DBD64 &operator=(const Rva002DBD64 &other);
private:
	int m_04;
	Coord3D m_08;
};

Rva002DBD64 &Rva002DBD64::operator=(const Rva002DBD64 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	return *this;
}

// --- 0x002E060A (19B): the +0x24 position by value.
class Rva002E060A
{
public:
	Coord3D rva002E060A() const;
private:
	char m_pad00[0x24];
	Coord3D m_24;
};

Coord3D Rva002E060A::rva002E060A() const
{
	return m_24;
}

// --- 0x002E0F81 (16B): +0x298 plus the rowed 0x002E0C68 count.
class Rva002E0C68
{
public:
	int rva002E0C68();										// 0x002E0C68
	int rva002E0F81();
private:
	char m_pad000[0x298];
	int m_298;
};

int Rva002E0C68::rva002E0F81()
{
	int base = m_298;
	return rva002E0C68() + base;
}

// --- 0x002E37B1 (18B): the rowed 0x0030B7C2 test of a point against the
// +8 shape.
struct Rva0030B7C2Point;
class Rva0030B719Shape;
bool rva0030B7C2(const Rva0030B7C2Point *point, Rva0030B719Shape *shape);	// 0x0030B7C2

class Rva002E37B1
{
public:
	bool rva002E37B1(const Rva0030B7C2Point *point);
private:
	int m_00;
	int m_04;
	int m_shape;
};

bool Rva002E37B1::rva002E37B1(const Rva0030B7C2Point *point)
{
	return rva0030B7C2(point, (Rva0030B719Shape *)&m_shape);
}

// --- 0x002E3889 (22B, cdecl) and 0x002E3A67 (19B): more than two 8-byte
// records in the +8 vector.
struct Rva002E3889Record
{
	int m_00;
	int m_04;
};

struct Rva002E3889Vector
{
	char m_pad00[8];
	Rva002E3889Record *m_start;
	Rva002E3889Record *m_finish;
	bool rva002E3A67() const;
};

bool Rva002E3889(const Rva002E3889Vector *v)
{
	return v->m_finish - v->m_start > 2;
}

bool Rva002E3889Vector::rva002E3A67() const
{
	return m_finish - m_start > 2;
}

// --- 0x002E6B19 (23B): sets bit 0 of the +0x2C word of the +0 record;
// 0x002E6C60 (18B): bit 1 of it, 0 without a record.
struct Rva002E6B19Record
{
	char m_pad00[0x2C];
	unsigned int m_bit0 : 1;
	unsigned int m_bit1 : 1;
};

class Rva002E6B19
{
public:
	void rva002E6B19(unsigned char value);
	unsigned int rva002E6C60() const;
private:
	Rva002E6B19Record *m_record;
};

void Rva002E6B19::rva002E6B19(unsigned char value)
{
	m_record->m_bit0 = value != 0;
}

unsigned int Rva002E6B19::rva002E6C60() const
{
	if (m_record)
		return m_record->m_bit1;
	return 0;
}

// --- 0x002E6CBE (26B): constructor of a path record.
class Rva002E6CBE
{
public:
	Rva002E6CBE(int value);
private:
	int m_00;
	bool m_04;
	bool m_05;
	int m_08;
	bool m_0C;
};

Rva002E6CBE::Rva002E6CBE(int value) : m_00(value), m_04(false), m_05(false), m_08(-1), m_0C(false)
{
}

// --- 0x002E6DB8 (12B, cdecl): the indexed mask of the table at VA
// 0x00DBD33C.
extern unsigned int g_00DBD33C[16];

unsigned int Rva002E6DB8(int index)
{
	return g_00DBD33C[index];
}

// --- 0x002E73FB (25B): a pathfinding cell test over the cell's +0x0C flags
// word; only the cell argument is used.
struct Rva002E734ECell
{
	char m_pad00[0x0C];
	unsigned int m_flags;
};

class Rva002E734E
{
public:
	int rva002E73FB(int unused, const Rva002E734ECell *cell, int x, int y);
private:
	int m_00;
	int m_x;
	int m_y;
};

int Rva002E734E::rva002E73FB(int, const Rva002E734ECell *cell, int, int)
{
	return (cell->m_flags & 0x3F0) != 0x10;
}

// --- 0x002E7FC7 (19B, cdecl): the next index, wrapping 0x1FF to 0.
int Rva002E7FC7(int index)
{
	return index != 0x1FF ? index + 1 : 0;
}

// --- 0x002EEA5A, 0x002EEA72 (24B each): one node from the rowed pools at
// VA 0x00DBD4B0 and 0x00DBD4C8, none for a count above one.
#include "../../Include/Common/Rva002EB448.h"
class Rva002E8548;
extern Rva002E8548 g_IntKeyedTreeNodePool;
extern Rva002E8548 g_Va00DBD4C8;

class Rva002EEA5A
{
public:
	void *rva002EEA5A(unsigned int count, const void *hint);
	void *rva002EEA72(unsigned int count, const void *hint);
};

void *Rva002EEA5A::rva002EEA5A(unsigned int count, const void *)
{
	if (count > 1)
		return 0;
	return ((Rva002EB448 *)&g_IntKeyedTreeNodePool)->rva002EB448();
}

void *Rva002EEA5A::rva002EEA72(unsigned int count, const void *)
{
	if (count > 1)
		return 0;
	return ((Rva002EB448 *)&g_Va00DBD4C8)->rva002EB448();
}

// --- 0x002FD661 (10B): the +4 object's rowed 0x002CACD7 of this.
#include "../../Include/Common/Rva002CA9CA.h"

class Rva002FD661
{
public:
	float rva002FD661();
private:
	int m_00;
	Rva002CA9CA *m_04;
};

float Rva002FD661::rva002FD661()
{
	return m_04->getProjectileNuggetRadiusIfAlliesAffected(this);
}

// --- 0x002FD7DC (19B): AI::update, SubsystemInterface slot 10 of AI's table
// 0x00C073D0 (slot 9 is the rowed AI::reset): the +0x10 pathfinder's rowed
// ProcessPathfindQueue 0x002F0F07, then ThePlayerList's update (slot 10), as
// in ZH AI::update.
#include "../../Include/GameLogic/AIPathfind.h"

class PlayerList;
extern PlayerList *ThePlayerList;

class Rva002FD7DCPlayerListView
{
public:
	GAP_V10(0)
	virtual void slot10();
};

#include "../../Include/GameLogic/AI.h"

void AI::update()
{
	m_pathfinder->ProcessPathfindQueue();
	((Rva002FD7DCPlayerListView *)ThePlayerList)->slot10();
}

// --- 0x002FDEF1 (32B): the +0x104 word for indices 1..3, else the +0x110
// one.
class Rva002FDEF1
{
public:
	int rva002FDEF1(int index) const;
private:
	char m_pad000[0x104];
	int m_104[3];
	int m_110;
};

int Rva002FDEF1::rva002FDEF1(int index) const
{
	if (index >= 1 && index <= 3)
		return m_104[index];
	return m_110;
}

// --- 0x003004DC (11B): the first word returned by value.
struct Rva003004DCWord
{
	Rva003004DCWord(int v) : m_value(v) {}
	int m_value;
};

class Rva003004DC
{
public:
	Rva003004DCWord rva003004DC() const;
private:
	int m_00;
};

Rva003004DCWord Rva003004DC::rva003004DC() const
{
	return Rva003004DCWord(m_00);
}

// --- 0x00306BF4 (20B): stores the first word at +8 and +4, the second at
// +0x0C.
class Rva00306BF4
{
public:
	void rva00306BF4(int a, int b);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

void Rva00306BF4::rva00306BF4(int a, int b)
{
	m_08 = a;
	m_04 = a;
	m_0C = b;
}

// --- 0x0030C025 (13B): the first word of the indexed 8-byte record at
// *(+0x14); the first argument is unused.
class Rva0030C025
{
public:
	int rva0030C025(int unused, int index) const;
private:
	char m_pad00[0x14];
	Rva002E3889Record *m_14;
};

int Rva0030C025::rva0030C025(int, int index) const
{
	return m_14[index].m_00;
}

// --- 0x0030D692 (31B): stores the normalized angle at +0x1C, then the
// rowed 0x0030D65B.
float normalizeAngle(float angle);							// 0x00238954

class BfmeRetBWF;
#include "../../Include/Common/Rva0030D631.h"
class Rva0030D606 { public: void rva0030D606(); };			// 0x0030D606
// TheAudio (VA 0x00DFE6E8) viewed only through its slot 53 (+0xD4), which
// takes the sound handle and the position the 0x0030D631 member returns.
class Rva0030D65BAudio
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52();
	virtual void setPosition(unsigned int handle, const BfmeRetBWF *position);
};
class AudioManager;
extern AudioManager *TheAudio;

class BfmeThingEOC
{
public:
	void bfmeAfterEOC();									// 0x0030D65B
	void rva0030D692(float angle);
private:
	char m_pad00[0x1C];
	float m_1C;
	char m_pad20[0x54 - 0x20];
	unsigned int m_54;
};

// --- 0x0030D65B (55B, its tail jump ends at the 0x0030D692 body): with
// TheAudio up and a live handle at +0x54 (5 and above), moves the sound to
// the position 0x0030D631 returns; with no position, releases it through
// 0x0030D606 (tail jump). Name from the existing symbols.csv pin.
void BfmeThingEOC::bfmeAfterEOC()
{
	if (TheAudio != 0 && m_54 >= 5)
	{
		BfmeRetBWF *position = ((Rva0030D631 *)this)->rva0030D631();
		if (position != 0)
			((Rva0030D65BAudio *)TheAudio)->setPosition(m_54, position);
		else
			((Rva0030D606 *)this)->rva0030D606();
	}
}

void BfmeThingEOC::rva0030D692(float angle)
{
	m_1C = normalizeAngle(angle);
	bfmeAfterEOC();
}

// --- 0x0030DC73 (18B): the +0x18 choice's string, else the +0x14 one.
class Rva0030DA0BStringChoice
{
public:
	const AsciiString &choose() const;						// 0x0030DA0B
};

class Rva0030DC73
{
public:
	const AsciiString &rva0030DC73() const;
private:
	char m_pad00[0x14];
	AsciiString m_14;
	Rva0030DA0BStringChoice *m_18;
};

const AsciiString &Rva0030DC73::rva0030DC73() const
{
	if (m_18)
		return m_18->choose();
	return m_14;
}

// --- 0x0030E24E (33B): takes a template, copies its +0x64 name to +0x14,
// then the rowed 0x0030E09A refresh.
struct Rva0030E24ETemplate
{
	char m_pad00[0x64];
	AsciiString m_name;
};

class Rva0030E09A
{
public:
	void rva0030E09A();										// 0x0030E09A
	void rva0030E24E(const Rva0030E24ETemplate *tmpl);
private:
	char m_pad00[0x14];
	AsciiString m_14;
	const Rva0030E24ETemplate *m_18;
};

void Rva0030E09A::rva0030E24E(const Rva0030E24ETemplate *tmpl)
{
	m_18 = tmpl;
	m_14 = tmpl->m_name;
	rva0030E09A();
}

// --- 0x003182BC (17B): the +0x34 record's +0x1BC flag, false without one;
// 0x003182E1 (14B): zeroes the first word through the memset thunk;
// 0x00318B3F (29B): clears and detaches the +0x88 member, returning it;
// 0x00318CCD (30B): changes the +0x74 flag, refreshing the +0x90 army line
// when it turns on.
struct Rva003182BCRecord
{
	char m_pad000[0x1BC];
	bool m_1BC;
};

class Rva0023D2D8DwordClearer
{
public:
	void clear();											// 0x0023D2D8
};

#include "../../Include/Common/LivingWorldArmyLine.h"

class Rva003182BC
{
public:
	bool rva003182BC() const;
	void rva003182E1();
	Rva0023D2D8DwordClearer *rva00318B3F();
	void rva00318CCD(bool value);
private:
	int m_00;
	char m_pad04[0x34 - 4];
	Rva003182BCRecord *m_34;
	char m_pad38[0x74 - 0x38];
	bool m_74;
	char m_pad75[0x88 - 0x75];
	Rva0023D2D8DwordClearer *m_88;
	char m_pad8C[0x90 - 0x8C];
	LivingWorldArmyLine m_90;
};

bool Rva003182BC::rva003182BC() const
{
	if (m_34)
		return m_34->m_1BC;
	return false;
}

void Rva003182BC::rva003182E1()
{
	memset(this, 0, 4);
}

Rva0023D2D8DwordClearer *Rva003182BC::rva00318B3F()
{
	if (m_88)
	{
		m_88->clear();
		Rva0023D2D8DwordClearer *result = m_88;
		m_88 = 0;
		return result;
	}
	return 0;
}

void Rva003182BC::rva00318CCD(bool value)
{
	if (m_74 != value)
	{
		m_74 = value;
		if (value)
			m_90.rva00539141();
	}
}

// --- 0x00318E6B (17B) and 0x00318E7C (16B): whether the vector of 16-byte
// records at +0 has / lacks elements.
struct Rva00318E6BRecord
{
	char m_data[16];
};

class Rva00318E6B
{
public:
	int rva00318E6B() const;
	int rva00318E7C() const;
private:
	Rva00318E6BRecord *m_start;
	Rva00318E6BRecord *m_finish;
};

int Rva00318E6B::rva00318E6B() const
{
	return 0 < (unsigned int)(m_finish - m_start);
}

int Rva00318E6B::rva00318E7C() const
{
	return !(0 < (unsigned int)(m_finish - m_start));
}

// --- 0x00318E9E, 0x00318EAF (17B each): the +0x190 / +0x19C colour as an
// opaque ARGB word (rowed getAsInt).
#include "../../../Libraries/Include/Lib/RGBColor.h"

class Rva00318E9E
{
public:
	int rva00318E9E() const;
	int rva00318EAF() const;
private:
	char m_pad000[0x190];
	RGBColor m_190;
	RGBColor m_19C;
};

int Rva00318E9E::rva00318E9E() const
{
	return m_190.getAsInt() | 0xFF000000;
}

int Rva00318E9E::rva00318EAF() const
{
	return m_19C.getAsInt() | 0xFF000000;
}

// --- 0x0031911F (15B): stores +0x54, then the rowed 0x00318EC0 refresh.
#include "../../Include/GameLogic/LivingWorldArmy.h"

void LivingWorldArmy::rva0031911F(int value)
{
	m_54 = value;
	rva00318EC0();
}

// --- 0x0031A9F2 (14B): pushes this onto a singly linked list (next at
// +0x18).
class Rva0031A9F2
{
public:
	void rva0031A9F2(Rva0031A9F2 **head);
private:
	char m_pad00[0x18];
	Rva0031A9F2 *m_next;
};

void Rva0031A9F2::rva0031A9F2(Rva0031A9F2 **head)
{
	m_next = *head;
	*head = this;
}

// --- 0x00328A6B (10B, cdecl): sets the word at VA 0x00DBD0F0;
// 0x0033F9AA (10B, cdecl): sets the AI flag byte at VA 0x00E03624.
// VA 0x00DBD0F0 is PolygonTrigger's private ?s_currentID@PolygonTrigger@@0HA,
// defined in PolygonTrigger.cpp (initial 1); reached through a friend view.
#include "../../Include/GameLogic/PolygonTrigger.h"
extern bool BfmeAIExitDoorFlag;

void Rva00328A6B(int value)
{
	PolygonTrigger::s_currentID = value;
}

void Rva0033F9AA(bool value)
{
	BfmeAIExitDoorFlag = value;
}

// --- 0x003297B3 (17B): swaps the first word with another's;
// 0x003297C9 (14B): constructor building the +0 Dict with 0 (rowed).
class Rva003297B3
{
public:
	void rva003297B3(Rva003297B3 &other);
private:
	int m_00;
};

void Rva003297B3::rva003297B3(Rva003297B3 &other)
{
	int value = m_00;
	m_00 = other.m_00;
	other.m_00 = value;
}

#include "../../Include/Common/Dict.h"

class Rva003297C9
{
public:
	Rva003297C9();
private:
	Dict m_dict;
};

Rva003297C9::Rva003297C9() : m_dict(0)
{
}

// --- 0x0032A2A3 (12B): the indexed 128-byte record at *(+0);
// 0x0032A42B (13B): the indexed 16-byte record at *(+0x0C).
struct Rva0032A2A3Record
{
	char m_data[0x80];
};

class Rva0032A2A3
{
public:
	Rva0032A2A3Record *rva0032A2A3(int index);
	Rva00318E6BRecord *rva0032A42B(int index);
private:
	Rva0032A2A3Record *m_00;
	int m_04;
	int m_08;
	Rva00318E6BRecord *m_0C;
};

Rva0032A2A3Record *Rva0032A2A3::rva0032A2A3(int index)
{
	return &m_00[index];
}

Rva00318E6BRecord *Rva0032A2A3::rva0032A42B(int index)
{
	return &m_0C[index];
}

// --- 0x0032E013 (24B): assigns the other's +0xF44 teams record through the
// rowed TeamsInfoRec::operator=.
class TeamsInfoRec
{
public:
	TeamsInfoRec &operator=(const TeamsInfoRec &other);		// 0x0032DDB3
};

class Rva0032E013
{
public:
	void rva0032E013(const Rva0032E013 &other);
private:
	char m_pad000[0xF44];
	TeamsInfoRec m_F44;
};

void Rva0032E013::rva0032E013(const Rva0032E013 &other)
{
	m_F44 = other.m_F44;
}

// --- 0x00330450 (34B): the indexed pointer of the +0x10 vector, null out
// of range.
struct Rva00330450Vector
{
	void **m_start;
	void **m_finish;
	unsigned int size() const { return m_finish - m_start; }
	void *at(int index) const { return m_start[index]; }
};

class Rva00330450
{
public:
	void *rva00330450(int index) const;
private:
	char m_pad00[0x10];
	Rva00330450Vector m_10;
};

void *Rva00330450::rva00330450(int index) const
{
	if (index >= 0 && (unsigned int)index < m_10.size())
		return m_10.at(index);
	return 0;
}

// --- 0x00330AAE (16B): forwards a float to its own slot 9.
class Rva00330AAE
{
public:
	GAP_V1(0) GAP_V1(1) GAP_V1(2) GAP_V1(3) GAP_V1(4) GAP_V1(5) GAP_V1(6) GAP_V1(7) GAP_V1(8)
	virtual void slot9(float value);
	void rva00330AAE(float value);
};

void Rva00330AAE::rva00330AAE(float value)
{
	slot9(value);
}

// --- 0x0033162B (21B): stores a float at +4 and marks +0x14 set.
class Rva0033162B
{
public:
	void rva0033162B(float value);
private:
	int m_00;
	float m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

void Rva0033162B::rva0033162B(float value)
{
	m_04 = value;
	m_14 = 1;
}

// --- 0x00332E8F (14B): count of the 0x9C-byte records of the vector at +0.
struct Rva00332E8FRecord
{
	char m_data[0x9C];
};

class Rva00332E8F
{
public:
	int rva00332E8F() const;
private:
	Rva00332E8FRecord *m_start;
	Rva00332E8FRecord *m_finish;
};

int Rva00332E8F::rva00332E8F() const
{
	return m_finish - m_start;
}

// --- 0x0033B123 (24B): constructor of a zero word and two 50.0 floats.
class Rva0033B123
{
public:
	Rva0033B123();
private:
	int m_00;
	float m_04;
	float m_08;
};

Rva0033B123::Rva0033B123() : m_00(0), m_04(50.0f), m_08(50.0f)
{
}

// --- 0x0033B73C (14B): the rowed BitFlags<117> intersection count of the
// first argument with the second (cdecl).
template <int N> class BitFlags
{
public:
	int countIntersection(const BitFlags &other) const;
};

int Rva0033B73C(const BitFlags<117> *a, const BitFlags<117> &b)
{
	return a->countIntersection(b);
}

// --- 0x0033CCF2 (16B): appends a module data to the +0x18 vector.
class ModuleData;
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class vector
	{
	public:
		void push_back(const T &value);
	private:
		T *m_start;
		T *m_finish;
		T *m_end;
	};
}

class Rva0033CCF2
{
public:
	void rva0033CCF2(const ModuleData *data);
private:
	char m_pad00[0x18];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_18;
};

void Rva0033CCF2::rva0033CCF2(const ModuleData *data)
{
	m_18.push_back(data);
}

// --- Small template-region leaves: 0x0033F14C (17B) float setter +0x1C0;
// 0x0033F22B (14B) the +4 record's +0x1C flag, true without one;
// 0x0033F2DC (10B) byte setter +0x48; 0x0033F2E6 (17B) copies a position to
// +0x20; 0x0033F8F0 (17B) +0x1A0 to FLT_MAX; 0x0033F954 (15B) clears
// +0x198/+0x19C.
struct Rva0033F22BRecord
{
	char m_pad00[0x1C];
	bool m_1C;
};

class Rva0033F14C
{
public:
	void rva0033F14C(float value);
	bool rva0033F22B() const;
	void rva0033F2DC(bool value);
	void rva0033F2E6(const Coord3D *pos);
	void rva0033F8F0();
	void rva0033F954();
private:
	int m_00;
	Rva0033F22BRecord *m_04;
	char m_pad08[0x20 - 8];
	Coord3D m_20;
	char m_pad2C[0x48 - 0x2C];
	bool m_48;
	char m_pad49[0x198 - 0x49];
	int m_198;
	int m_19C;
	float m_1A0;
	char m_pad1A4[0x1C0 - 0x1A4];
	float m_1C0;
};

void Rva0033F14C::rva0033F14C(float value)
{
	m_1C0 = value;
}

bool Rva0033F14C::rva0033F22B() const
{
	if (m_04)
		return m_04->m_1C;
	return true;
}

void Rva0033F14C::rva0033F2DC(bool value)
{
	m_48 = value;
}

void Rva0033F14C::rva0033F2E6(const Coord3D *pos)
{
	m_20 = *pos;
}

void Rva0033F14C::rva0033F8F0()
{
	m_1A0 = 3.402823466e+38f;
}

void Rva0033F14C::rva0033F954()
{
	m_198 = 0;
	m_19C = 0;
}

// --- 0x0033F220 (11B, cdecl): non-positive values pass, positive become 0.
int Rva0033F220(int value)
{
	if (value > 0)
		return 0;
	return value;
}

// --- 0x00340FBF (14B): the +0x5C record's +0x4C count is positive.
struct Rva00340FBFRecord
{
	char m_pad00[0x4C];
	int m_4C;
};

class Rva00340FBF
{
public:
	bool rva00340FBF() const;
private:
	char m_pad00[0x5C];
	Rva00340FBFRecord *m_5C;
};

bool Rva00340FBF::rva00340FBF() const
{
	return m_5C->m_4C > 0;
}

// --- 0x003360F6, 0x00339F65, 0x0033EBAA (11B each): erase every element of
// the vector at +0 through its rowed range eraser.
class Rva00335C88
{
public:
	void *rva00335C88(void *first, void *last);				// 0x00335C88
	void rva003360F6();
private:
	void *m_start;
	void *m_finish;
};

void Rva00335C88::rva003360F6()
{
	rva00335C88(m_start, m_finish);
}

struct DynamicPortalLink;
#include "../../Include/Common/Rva00339E80.h"

void Rva00339E80::rva00339F65()
{
	rva00339E80(m_start, m_finish);
}

class Rva0033EB77Vec
{
public:
	void *erasePrereqVec(void *first, void *last);			// 0x0033EB77
	void rva0033EBAA();
private:
	void *m_start;
	void *m_finish;
};

void Rva0033EB77Vec::rva0033EBAA()
{
	erasePrereqVec(m_start, m_finish);
}

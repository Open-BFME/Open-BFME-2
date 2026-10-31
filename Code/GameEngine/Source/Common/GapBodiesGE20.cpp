// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (twentieth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include "ascii_string.h"
#include <stdio.h>
#include <string.h>

// Declaration-only views of the STLport containers whose rowed members these
// bodies call (vector operator= 0x0021C21B / 0x0040B61A, vector copy
// 0x004220CD, deque iterator advance 0x00421B9B, deque base 0x00421F87, list
// base 0x00280A8D); no container code is instantiated here.
struct Rva0021C21BElement;
struct BfmeRecord0040B61A;

namespace _STL {
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A = allocator<T> > class vector
{
public:
	vector(const vector<T, A> &that);
	vector<T, A> &operator=(const vector<T, A> &that);
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};

template <class T, class A = allocator<T> > class deque;

template <class T> struct _Deque_iterator_base
{
	void _M_advance(int n);
	T *_M_cur;
	T *_M_first;
	T *_M_last;
	T **_M_node;
};

template <class T, class A> class _Deque_base
{
public:
	_Deque_base(const A &a, unsigned count);
private:
	_Deque_iterator_base<T> _M_start;
	_Deque_iterator_base<T> _M_finish;
	T **_M_map;
	unsigned _M_map_size;
};

template <class T, class A> class _List_base
{
public:
	_List_base(const A &a);
private:
	void *_M_node;
};
}

// --- 0x00403137 (19B): copy a 19-word block into +0x1C.
struct Rva00403137Block
{
	int m_words[0x13];
};

class Rva00403137
{
public:
	void rva00403137(const Rva00403137Block &block);
private:
	char m_pad[0x1C];
	Rva00403137Block m_1C;
};

void Rva00403137::rva00403137(const Rva00403137Block &block)
{
	m_1C = block;
}

// --- 0x0040315E (18B): whether the value is below the record's +0x08 bound
// (the receiver is not read).
struct Rva0040315ERecord
{
	int m_00;
	int m_04;
	unsigned m_08;
};

class Rva0040315E
{
public:
	bool rva0040315E(unsigned value, const Rva0040315ERecord *record);
};

bool Rva0040315E::rva0040315E(unsigned value, const Rva0040315ERecord *record)
{
	return value < record->m_08;
}

// --- 0x0040332B (32B): how many 20-byte records of the [+0x00, +0x04) range
// carry the key in their first word.
struct Rva0040332BRecord
{
	int m_key;
	int m_rest[4];
};

class Rva0040332B
{
public:
	int rva0040332B(int key) const;
private:
	Rva0040332BRecord *m_begin;
	Rva0040332BRecord *m_end;
};

int Rva0040332B::rva0040332B(int key) const
{
	int count = 0;
	for (const Rva0040332BRecord *it = m_begin; it != m_end; ++it)
		if (it->m_key == key)
			++count;
	return count;
}

// --- 0x00406DA3 (15B) / 0x00406DB2 (26B) / 0x00406DCC (23B): default
// constructor, copy constructor and assignment of a word and a byte over an
// empty base (the base is value-initialised: retail's stosb).
struct Rva00406DA3Empty
{
};

class Rva00406DA3 : public Rva00406DA3Empty
{
public:
	Rva00406DA3();
	Rva00406DA3(const Rva00406DA3 &that);
	Rva00406DA3 &operator=(const Rva00406DA3 &that);
private:
	int m_00;
	bool m_04;
};

Rva00406DA3::Rva00406DA3() : Rva00406DA3Empty(), m_00(0), m_04(false)
{
}

Rva00406DA3::Rva00406DA3(const Rva00406DA3 &that) : Rva00406DA3Empty(), m_00(that.m_00), m_04(that.m_04)
{
}

Rva00406DA3 &Rva00406DA3::operator=(const Rva00406DA3 &that)
{
	if (&that != this)
	{
		m_00 = that.m_00;
		m_04 = that.m_04;
	}
	return *this;
}

// --- 0x0040A15B (19B): hand the record to TheCreateAHeroManager's rowed
// 0x0021929D release (the receiver is not read).
class CreateAHeroData;
class CreateAHeroManager;
extern CreateAHeroManager *TheCreateAHeroManager;

class Rva00219251
{
public:
	void rva0021929D(CreateAHeroData **data);				// 0x0021929D
};

class Rva0040A15B
{
public:
	void rva0040A15B(CreateAHeroData *data);
};

void Rva0040A15B::rva0040A15B(CreateAHeroData *data)
{
	((Rva00219251 *)TheCreateAHeroManager)->rva0021929D(&data);
}

// --- 0x0040B068 (104B): assignment of a word, two rowed 0x0021C21B vectors,
// two 7-word blocks, two strings and a byte.
struct Rva0040B068Block
{
	int m_words[7];
};

class Rva0040B068
{
public:
	Rva0040B068 &operator=(const Rva0040B068 &that);
private:
	int m_00;
	_STL::vector<Rva0021C21BElement> m_04;
	_STL::vector<Rva0021C21BElement> m_10;
	Rva0040B068Block m_1C;
	Rva0040B068Block m_38;
	AsciiString m_54;
	AsciiString m_58;
	int m_5C;
	int m_60;
	bool m_64;
};

Rva0040B068 &Rva0040B068::operator=(const Rva0040B068 &that)
{
	if (&that != this)
	{
		m_00 = that.m_00;
		m_04 = that.m_04;
		m_10 = that.m_10;
		m_1C = that.m_1C;
		m_38 = that.m_38;
		m_54 = that.m_54;
		m_58 = that.m_58;
		m_64 = that.m_64;
	}
	return *this;
}

// --- 0x0040B7E1 (83B): assignment of a word, a rowed 0x0021C21B vector,
// three strings and a rowed 0x0040B61A vector (the layout the rowed
// 0x0040B707 copy constructor copies).
class Rva0040B7E1
{
public:
	Rva0040B7E1 &operator=(const Rva0040B7E1 &that);
private:
	int m_00;
	_STL::vector<Rva0021C21BElement> m_04;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	_STL::vector<BfmeRecord0040B61A> m_1C;
};

Rva0040B7E1 &Rva0040B7E1::operator=(const Rva0040B7E1 &that)
{
	if (&that != this)
	{
		m_00 = that.m_00;
		m_04 = that.m_04;
		m_10 = that.m_10;
		m_14 = that.m_14;
		m_18 = that.m_18;
		m_1C = that.m_1C;
	}
	return *this;
}

// --- 0x0040C58C (12B): invert all 32 words of the mask.
class Rva0040C58C
{
public:
	void rva0040C58C();
private:
	unsigned m_words[32];
};

void Rva0040C58C::rva0040C58C()
{
	for (unsigned i = 0; i < 32; ++i)
		m_words[i] = ~m_words[i];
}

// --- 0x004135B5 (24B): no id and unit scales.
class Rva004135B5
{
public:
	Rva004135B5();
private:
	int m_id;
	float m_04;
	float m_08;
};

Rva004135B5::Rva004135B5() : m_id(-1), m_04(1.0f), m_08(1.0f)
{
}

// --- 0x00416072 (22B): two cleared ids, two zero words and a cleared id.
class Rva00416072
{
public:
	Rva00416072();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

Rva00416072::Rva00416072() : m_00(-1), m_04(-1), m_08(0), m_0C(0), m_10(-1)
{
}

// --- 0x00417AE9 (19B): field-parse callback reading the block into the
// store through table 0x00C3A658 (the table the rowed 0x00417FF0 parse uses).
struct FieldParse;


class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);	// 0x0002DE78
	static void parseInt(INI *, void *, void *, const void *);
	static void parsePercentToReal(INI *, void *, void *, const void *);
};

// Native BonusForLevel table C3A658..C3A6C8. The target supplies all six
// field names, parser addresses and offsets in the 24-byte level record.
struct FieldParse
{
 const char *token;
 void (*parse)(INI *, void *, void *, const void *);
 const void *userData;
 int offset;
};
extern const FieldParse BfmeBonusForLevelFieldTable[] = {
 { "MinLevel", INI::parseInt, 0, 0 },
 { "MaximumUnitsAffected", INI::parseInt, 0, 4 },
 { "Priority", INI::parseInt, 0, 8 },
 { "WeaponMultiplier", INI::parsePercentToReal, 0, 12 },
 { "ExperienceMultiplier", INI::parsePercentToReal, 0, 16 },
 { "ArmorMultiplier", INI::parsePercentToReal, 0, 20 },
 { 0, 0, 0, 0 }
};

void Rva00417AE9(INI *ini, void *instance, void *store, const void *userData)
{
	ini->initFromINI(store, BfmeBonusForLevelFieldTable);
}

// --- 0x0041B7F5 (12B): whether the +0x80 word is set.
class Rva0041B7F5
{
public:
	bool rva0041B7F5() const;
private:
	char m_pad[0x80];
	int m_80;
};

bool Rva0041B7F5::rva0041B7F5() const
{
	return m_80 != 0;
}

// --- 0x0041E6AA (14B): store the +0x3C float.
class Rva0041E6AA
{
public:
	void rva0041E6AA(float value);
private:
	char m_pad[0x3C];
	float m_3C;
};

void Rva0041E6AA::rva0041E6AA(float value)
{
	m_3C = value;
}

// --- 0x0041F344 (37B): the object's level slot (its +0x30 record's +0x2C8)
// picks one of three +0x34 counts, capped at 15; slots past 2 read zero.
struct Rva0041F344Record
{
	char m_pad[0x2C8];
	int m_slot;
};

struct Rva0041F344Object
{
	char m_pad[0x30];
	Rva0041F344Record *m_record;
};

class Rva0041F344
{
public:
	int rva0041F344(const Rva0041F344Object *object) const;
private:
	char m_pad[0x34];
	int m_counts[3];
};

int Rva0041F344::rva0041F344(const Rva0041F344Object *object) const
{
	int slot = object->m_record->m_slot;
	int count;
	if (slot < 3)
	{
		count = m_counts[slot];
		if (count >= 16)
			count = 15;
	}
	else
		count = 0;
	return count;
}

// --- 0x00421ECA (22B): the address of cell (row, column) in a table of
// 24-byte rows whose first word points at 12-byte cells.
struct Rva00421ECACell
{
	int m_words[3];
};

struct Rva00421ECARow
{
	Rva00421ECACell *m_cells;
	int m_rest[5];
};

class Rva00421ECA
{
public:
	Rva00421ECACell *rva00421ECA(int row, int column);
private:
	Rva00421ECARow *m_rows;
};

Rva00421ECACell *Rva00421ECA::rva00421ECA(int row, int column)
{
	return &m_rows[row].m_cells[column];
}

// --- 0x00425ED3 (29B, cdecl): build a word and a 13-word block in place.
struct Rva00425ED3Block
{
	int m_words[13];
};

struct Rva00425ED3Pair
{
	int m_first;
	Rva00425ED3Block m_second;
};

void Rva00425ED3(Rva00425ED3Pair *out, const int *first, const Rva00425ED3Block *second)
{
	out->m_first = *first;
	out->m_second = *second;
}

// --- 0x00427105 (15B): the value scaled by the indexed +0x04 factor.
class Rva00427105
{
public:
	float rva00427105(float value, int index) const;
private:
	int m_00;
	float m_factors[1];
};

float Rva00427105::rva00427105(float value, int index) const
{
	return value * m_factors[index];
}

// --- 0x00427C19 (19B, cdecl) / 0x00427D00 (14B, cdecl): distance between
// and advance of cursors over 24-byte records.
struct Rva00427C19Record
{
	int m_words[6];
};

struct Rva00427C19Cursor
{
	Rva00427C19Record *m_at;
};

int Rva00427C19(const Rva00427C19Cursor &from, const Rva00427C19Cursor &to)
{
	return to.m_at - from.m_at;
}

void Rva00427D00(Rva00427C19Cursor &cursor, int count)
{
	cursor.m_at += count;
}

// --- 0x00429276 (48B, cdecl): offer an entry to a two-slot holder: an empty
// second slot takes it into the first when its +0x04 template flag 0x04 is
// set (answering 0); an entry already in the second slot clears it.
struct Rva00429276Template
{
	char m_pad[0x113];
	unsigned char m_flags;
};

struct Rva00429276Entry
{
	int m_00;
	Rva00429276Template *m_template;
};

struct Rva00429276Holder
{
	Rva00429276Entry *m_first;
	Rva00429276Entry *m_second;
};

int Rva00429276(Rva00429276Entry *entry, Rva00429276Holder *holder)
{
	if (entry)
	{
		if (holder->m_second)
		{
			if (entry == holder->m_second)
				holder->m_second = 0;
		}
		else if (entry->m_template->m_flags & 4)
		{
			holder->m_first = entry;
			return 0;
		}
	}
	return 1;
}

// --- 0x004292A6 (80B, file-static): iterate the local player's objects with
// Rva00429276, offering the incoming entry; repeat once with second slot empty.
class Object;
typedef int (*ObjectIterateFunc)(Object *, void *);
class Player
{
public:
	int iterateObjects(ObjectIterateFunc func, void *userData) const;
};
class PlayerList;
extern PlayerList *ThePlayerList;
struct Rva004292A6PlayerListView
{
	char m_pad[0x10];
	Player *m_local;
};

static __declspec(noinline) Rva00429276Entry *Rva004292A6(Rva00429276Entry *second)
{
	Player *player = ((Rva004292A6PlayerListView *)ThePlayerList)->m_local;
	if (!player)
		return 0;
	Rva00429276Holder holder;
	holder.m_first = 0;
	holder.m_second = second;
	player->iterateObjects((ObjectIterateFunc)Rva00429276, &holder);
	if (!holder.m_first && second)
	{
		holder.m_second = 0;
		player->iterateObjects((ObjectIterateFunc)Rva00429276, &holder);
	}
	return holder.m_first;
}

// ?Rva004292A6Caller absent-from-retail
Rva00429276Entry *Rva004292A6Caller(Rva00429276Entry *arg)
{
	return Rva004292A6(arg);
}

// --- 0x0042C0A2 (12B): the +0x14 base of the object (null stays null).
struct Rva0042C0A2Head
{
	int m_words[5];
};

struct Rva0042C0A2Base
{
	int m_00;
};

class Rva0042C0A2 : public Rva0042C0A2Head, public Rva0042C0A2Base
{
public:
	Rva0042C0A2Base *rva0042C0A2();
};

Rva0042C0A2Base *Rva0042C0A2::rva0042C0A2()
{
	return this;
}

// --- 0x0042D67C (27B): whether the referenced record's +0x08 kind is 1, 2
// or 3.
struct Rva0042D67CRecord
{
	int m_00;
	int m_04;
	int m_kind;
};

class Rva0042D67C
{
public:
	int rva0042D67C() const;
private:
	Rva0042D67CRecord *m_record;
};

int Rva0042D67C::rva0042D67C() const
{
	int kind = m_record->m_kind;
	if (kind == 1 || kind == 2 || kind == 3)
		return 1;
	return 0;
}

// --- 0x004319AF (19B): whether fewer than 500 ticks passed since +0x18.
class Rva004319AF
{
public:
	bool rva004319AF(unsigned now) const;
private:
	char m_pad[0x18];
	unsigned m_18;
};

bool Rva004319AF::rva004319AF(unsigned now) const
{
	return now - m_18 < 500;
}

// --- 0x00432858 (38B, cdecl): whether TheMouse's +0x4F0C block has any of
// its +0x18 / +0x24 / +0x30 words set.
struct Rva00432858Block
{
	char m_pad[0x18];
	int m_18;
	char m_pad1C[0x24 - 0x1C];
	int m_24;
	char m_pad28[0x30 - 0x28];
	int m_30;
};

class Mouse;
extern Mouse *TheMouse;

struct Rva00432858Mouse
{
	char m_pad[0x4F0C];
	Rva00432858Block m_block;
};

// --- 0x00432968 (14B): the address of the +0x08 24-byte record the +0x1E8
// index selects.
struct Rva00432968Record
{
	int m_words[6];
};

class Rva00432968
{
public:
	Rva00432968Record *rva00432968();
private:
	int m_00;
	int m_04;
	Rva00432968Record m_records[20];
	int m_1E8;
};

// --- 0x00435B71 (17B) / 0x00435BA1 (18B) / 0x00435D70 (13B): the rowed
// obfuscated hooks fed one value twice (a sign-extended short, the argument,
// the +0x04 word); 0x00435B71 and 0x00435BA1 do not read the receiver.
int Rva004353E8Hook(int a, int b);							// 0x004353E8
int Rva0043549AHook(int a, int b);							// 0x0043549A

class Rva00435B71
{
public:
	int rva00435B71(short value);
	int rva00435BA1(int value);
	int rva00435D70();
private:
	int m_00;
	int m_04;
};

int Rva00435B71::rva00435B71(short value)
{
	return Rva004353E8Hook(value, value);
}

int Rva00435B71::rva00435BA1(int value)
{
	return Rva0043549AHook(value, value);
}

int Rva00435B71::rva00435D70()
{
	return Rva0043549AHook(m_04, m_04);
}

// --- 0x004361DC (22B): assign a 16-bit value through the rowed 0x00435CFE.
class Rva00435CFE
{
public:
	void rva00435CFE(unsigned short value);				// 0x00435CFE
};

class Rva004361DC : public Rva00435CFE
{
public:
	Rva004361DC &operator=(const unsigned short &value);
};

Rva004361DC &Rva004361DC::operator=(const unsigned short &value)
{
	rva00435CFE(value);
	return *this;
}

// --- 0x004395D3 (25B): the rowed 0x00439428 query with its three trailing
// arguments zero.
class Object;
struct Coord3D;
struct Rva004393D6Entry;
enum ObjectID;

class Rva00439E0C
{
public:
	bool rva00439428(Object *object, const Coord3D *pos, Rva004393D6Entry *entry, int a, int b, ObjectID *id);	// 0x00439428
	bool rva004395D3(Object *object, const Coord3D *pos, Rva004393D6Entry *entry);
};

bool Rva00439E0C::rva004395D3(Object *object, const Coord3D *pos, Rva004393D6Entry *entry)
{
	return rva00439428(object, pos, entry, 0, 0, 0);
}

// --- 0x0043A1C0 (130B) / 0x0043A242 (54B): text callbacks writing into the
// buffer unless the flag is set: the +0x90 slot map's player colour value
// (after a "0" default) from the +0x88 game info, and the +0x14 game mode's
// suffix ("_lan", "_skirmish", "_internetAdv").
class GameSlot
{
public:
	bool isOccupied() const;								// 0x003FF0FB
	int getApparentColor() const;							// 0x003FF838
};

class GameInfo
{
public:
	GameSlot *getSlot(int index);							// 0x003FF29F
};

class MultiplayerColorDefinition;

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int index);		// 0x00381373
};

extern MultiplayerSettings *TheMultiplayerSettings;

struct Rva0043A1C0ColorView
{
	char m_pad[0x10];
	int m_color;
};

// AptLoadScreen's Apt extern handlers: its constructor 0x0043AE44 registers 0x0043A1C0 as
// "GameLoading:PlayerColor:%d" and 0x0043A242 as "GameLoadingType" (AptLoadScreenCtor.cpp).
// Non-virtual members only; this TU's view covers the fields the two handlers read.
class AptLoadScreen
{
public:
	void PlayerColor(int index, char *buffer, bool skip);
	void GameLoadingType(int index, char *buffer, bool skip);
private:
	char m_pad[0x14];
	int m_mode;												// +0x14
	char m_pad18[0x88 - 0x18];
	GameInfo *m_gameInfo;									// +0x88
	int m_8C;
	int m_slots[8];											// +0x90
};

void AptLoadScreen::PlayerColor(int index, char *buffer, bool skip)
{
	if (skip || index >= 8)
		return;
	int slotIndex = m_slots[index];
	if (slotIndex < 0 || slotIndex >= 8)
		return;
	strcpy(buffer, "0");
	if (!m_gameInfo)
		return;
	GameSlot *slot = m_gameInfo->getSlot(slotIndex);
	if (!slot || !slot->isOccupied())
		return;
	sprintf(buffer, "%d", ((Rva0043A1C0ColorView *)TheMultiplayerSettings->getColor(slot->getApparentColor()))->m_color);
}

void AptLoadScreen::GameLoadingType(int index, char *buffer, bool skip)
{
	if (skip)
		return;
	switch (m_mode)
	{
	case 1:
		strcpy(buffer, "_lan");
		break;
	case 2:
		strcpy(buffer, "_skirmish");
		break;
	case 5:
		strcpy(buffer, "_internetAdv");
		break;
	}
}

// --- 0x0041FCD6 (20B): forward to the rowed 0x0041FC77 insert, returning its
// result record.
struct InsertRet0041FA92
{
	void *node;
	void *owner;
	unsigned char found;
};

class Rva000427195
{
public:
	InsertRet0041FA92 rva0041FC77(const void *value);		// 0x0041FC77
	InsertRet0041FA92 rva0041FCD6(const void *value);
};

InsertRet0041FA92 Rva000427195::rva0041FCD6(const void *value)
{
	return rva0041FC77(value);
}

// --- 0x00421392 (16B): look the name up in the +0x0C module vector through
// the rowed 0x00421263 (that row's notes name this wrapper's shape).
class ModuleData;

struct Rva00421263Vec
{
	const ModuleData **m_begin;
	const ModuleData **m_end;
};

class LightPointSystem
{
public:
	const ModuleData *rva00421263(const Rva00421263Vec *vec, const StringBase<char> &key) const;	// 0x00421263
	const ModuleData *rva00421392(const StringBase<char> &key) const;
private:
	char m_pad[0x0C];
	Rva00421263Vec m_levels;								// +0x0C
};

const ModuleData *LightPointSystem::rva00421392(const StringBase<char> &key) const
{
	return rva00421263(&m_levels, key);
}

// --- 0x00422035 (18B): a deque-of-pointers cursor advanced in place.
class Rva00422035 : public _STL::_Deque_iterator_base<void *>
{
public:
	Rva00422035 &operator+=(int count);
};

Rva00422035 &Rva00422035::operator+=(int count)
{
	_M_advance(count);
	return *this;
}

// --- 0x0042304A (18B): copy of a holder of the rowed 0x004220CD vector.
struct Rva004220CDRecord;

class Rva0042304A
{
public:
	Rva0042304A(const Rva0042304A &that);
private:
	_STL::vector<Rva004220CDRecord> m_records;
};

Rva0042304A::Rva0042304A(const Rva0042304A &that) : m_records(that.m_records)
{
}

// --- 0x00424CD7 (19B): an empty Coord3D list (rowed list base 0x00280A8D).
struct Coord3D;

class Rva00424CD7
{
public:
	Rva00424CD7();
private:
	_STL::_List_base<Coord3D, _STL::allocator<Coord3D> > m_list;
};

Rva00424CD7::Rva00424CD7() : m_list(_STL::allocator<Coord3D>())
{
}

// --- 0x00425806 (24B): an empty deque of word deques at +0x08 (rowed deque
// base 0x00421F87).
struct BfmeWordValue4;
typedef _STL::deque<BfmeWordValue4> Rva00425806Inner;

class Rva00425806
{
public:
	Rva00425806();
private:
	int m_00;
	int m_04;
	_STL::_Deque_base<Rva00425806Inner, _STL::allocator<Rva00425806Inner> > m_queue;
};

Rva00425806::Rva00425806() : m_queue(_STL::allocator<Rva00425806Inner>(), 0)
{
}

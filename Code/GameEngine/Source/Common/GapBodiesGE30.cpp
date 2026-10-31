// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (thirtieth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include <string.h>

// Declaration-only view of the STLport list member these bodies call; no
// container code is instantiated here.
namespace _STL {
template <class T> class allocator;
template <class T, class A = allocator<T> > class list
{
public:
	void push_back(const T &value);
private:
	void *_M_node;
};
}

// --- 0x00538EF5 (27B): the rowed 0x0031A129 insert then the rowed
// 0x00538D3B update on the same receiver.
class Rva00318B5C;

class Rva00319F5A
{
public:
	void rva0031A129(const Rva00318B5C &value);				// 0x0031A129
};

class Rva00538CEF
{
public:
	void rva00538D3B(int value);							// 0x00538D3B
};

class Rva00538EF5
{
public:
	void rva00538EF5(const Rva00318B5C &value, int key);
};

void Rva00538EF5::rva00538EF5(const Rva00318B5C &value, int key)
{
	((Rva00319F5A *)this)->rva0031A129(value);
	((Rva00538CEF *)this)->rva00538D3B(key);
}

// --- 0x00539152 (25B): a point count, no points yet, then the rowed
// LivingWorldArmyLine::allocatePoints.
class LivingWorldArmyLine
{
public:
	void allocatePoints(unsigned count);					// 0x005390AE
};

class Rva00539152
{
public:
	Rva00539152(unsigned count);
private:
	unsigned m_count;
	void *m_points;
};

Rva00539152::Rva00539152(unsigned count) : m_count(count), m_points(0)
{
	((LivingWorldArmyLine *)this)->allocatePoints(count);
}

// --- 0x0053B966 (15B): how many 216-byte records the +0x04 range holds.
struct Rva0053B966Record
{
	int m_words[54];
};

class Rva0053B966
{
public:
	int rva0053B966() const;
private:
	int m_00;
	Rva0053B966Record *m_begin;
	Rva0053B966Record *m_end;
};

int Rva0053B966::rva0053B966() const
{
	return m_end - m_begin;
}

// --- 0x0053B975 (23B): a copy of the +0x110 flag set (rowed copy
// constructor 0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &that);	// 0x0004543D
private:
	unsigned m_words[4];
};

class Rva0053B975
{
public:
	BfmeFixedStorage0004543D getFlags() const;
private:
	char m_pad[0x110];
	BfmeFixedStorage0004543D m_flags;
};

BfmeFixedStorage0004543D Rva0053B975::getFlags() const
{
	return m_flags;
}

// --- 0x0053EBF3 (46B, cdecl) / 0x0053EC21 (25B, cdecl): whether a shown
// button's data has a positive +0xF8 count; run slot 12 of a window's user
// data.
class GameWindow
{
public:
	bool winIsHidden();										// 0x00313CD9
	void *winGetUserData();									// 0x005C4ACD
};

void *GadgetButtonGetData(GameWindow *window);				// 0x00327D56

struct Rva0053EBF3Data
{
	char m_pad[0xF8];
	int m_F8;
};

bool Rva0053EBF3(GameWindow *window)
{
	if (window->winIsHidden())
		return false;
	Rva0053EBF3Data *data = (Rva0053EBF3Data *)GadgetButtonGetData(window);
	return data && data->m_F8 > 0;
}

class Rva0053EC21Data
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30();
};

void Rva0053EC21(GameWindow *window)
{
	if (window)
	{
		Rva0053EC21Data *data = (Rva0053EC21Data *)window->winGetUserData();
		if (data)
			data->slot30();
	}
}

// --- 0x0053FCEA (14B, cdecl): advance a cursor over 40-byte records.
struct Rva0053FCEARecord
{
	int m_words[10];
};

struct Rva0053FCEACursor
{
	Rva0053FCEARecord *m_at;
};

void advanceCursor(Rva0053FCEACursor &cursor, int count)
{
	cursor.m_at += count;
}

// --- 0x00541191 (18B): whether the referenced word is below the value (the
// receiver is not read).
class Rva00541191
{
public:
	bool isBelow(const int *a, int b);
};

bool Rva00541191::isBelow(const int *a, int b)
{
	return *a < b;
}

// --- 0x0054810B (12B): a handle of the +0x04 word.
struct Rva0054810BHandle
{
	Rva0054810BHandle(int value) : m_value(value) {}
	int m_value;
};

class Rva0054810B
{
public:
	Rva0054810BHandle getHandle() const;
private:
	int m_00;
	int m_04;
};

Rva0054810BHandle Rva0054810B::getHandle() const
{
	return Rva0054810BHandle(m_04);
}

// --- 0x0054A19C (15B): copy the +0x14 block over the +0x04 block.
struct Rva0054A19CBlock
{
	int m_words[4];
};

class Rva0054A19C
{
public:
	void copyBlock();
private:
	int m_00;
	Rva0054A19CBlock m_04;
	Rva0054A19CBlock m_14;
};

void Rva0054A19C::copyBlock()
{
	m_04 = m_14;
}

// --- 0x0054E8CF (13B): append the value to the receiver's list (rowed
// list<int>::push_back 0x0005548F).
class Rva0054E8CF : public _STL::list<int>
{
public:
	void pushValue(int value);
};

void Rva0054E8CF::pushValue(int value)
{
	push_back(value);
}

// --- 0x00552F42 (19B): byte ordering of two referenced values (the receiver
// is not read).
class Rva00552F42
{
public:
	bool isByteBelow(const unsigned char *a, const unsigned char *b);
};

bool Rva00552F42::isByteBelow(const unsigned char *a, const unsigned char *b)
{
	return *a < *b;
}

// --- 0x00559EFE (19B, cdecl): copy a 40-byte record.
void copyRecord(void *to, const void *from)
{
	memcpy(to, from, 0x28);
}

// --- 0x0055D988 (29B): a copy of the +0x188 float-led record.
struct Rva0055D988Value
{
	Rva0055D988Value(const Rva0055D988Value &that) : m_00(that.m_00), m_04(that.m_04), m_08(that.m_08) {}
	float m_00;
	int m_04;
	int m_08;
};

class Rva0055D988
{
public:
	Rva0055D988Value getValue() const;
private:
	char m_pad[0x188];
	Rva0055D988Value m_value;
};

Rva0055D988Value Rva0055D988::getValue() const
{
	return m_value;
}

// --- 0x005677D7 (20B): share a counted record (+0x04 count).
struct Rva005677D7Record
{
	int m_00;
	int m_refs;
};

class Rva005677D7
{
public:
	Rva005677D7(Rva005677D7Record *const *record, int unused);
private:
	Rva005677D7Record *m_record;
};

Rva005677D7::Rva005677D7(Rva005677D7Record *const *record, int unused) : m_record(*record)
{
	if (m_record)
		++m_record->m_refs;
}

// --- 0x0056783A (13B): zero the +0x00 / +0x08 words and the +0x0C flag.
class Rva0056783A
{
public:
	Rva0056783A();
private:
	int m_00;
	int m_04;
	int m_08;
	bool m_0C;
};

Rva0056783A::Rva0056783A() : m_00(0), m_08(0), m_0C(false)
{
}

// --- 0x00567B59 (20B, cdecl): build a pair from a referenced word and a
// word.
struct Rva00567B59Pair
{
	int m_first;
	int m_second;
};

void makePair(Rva00567B59Pair *out, const int *first, int second)
{
	out->m_first = *first;
	out->m_second = second;
}

// --- 0x00568651 (14B): whether the low nibble of +0x47 is set.
class Rva00568651
{
public:
	bool rva00568651() const;
private:
	char m_pad[0x47];
	unsigned char m_47 : 4;
};

bool Rva00568651::rva00568651() const
{
	return m_47 > 0;
}

// --- 0x0056AB09 (28B): whether the +0x10 / +0x14 pair matches.
class Rva0056AB09
{
public:
	int matchesPair(int a, int b) const;
private:
	char m_pad[0x10];
	int m_10;
	int m_14;
};

int Rva0056AB09::matchesPair(int a, int b) const
{
	return m_10 == a && m_14 == b;
}

// --- 0x0056C256 (16B): the indexed 168-byte record of the +0x14 table.
struct Rva0056C256Record
{
	int m_words[42];
};

class Rva0056C256
{
public:
	Rva0056C256Record *rva0056C256(int index);
private:
	char m_pad[0x14];
	Rva0056C256Record *m_records;
};

Rva0056C256Record *Rva0056C256::rva0056C256(int index)
{
	return &m_records[index];
}

// --- 0x0056FA94 (17B) / 0x0056FD7B (13B): the rowed obfuscated hooks fed one
// value twice (a sign-extended short, the +0x04 word); 0x0056FA94 does not
// read the receiver.
int Rva0056F690Hook(int a, int b);							// 0x0056F690
int Rva0056F84DHook(int a, int b);							// 0x0056F84D

class Rva0056FA94
{
public:
	int rva0056FA94(short value);
	int rva0056FD7B();
private:
	int m_00;
	int m_04;
};

int Rva0056FA94::rva0056FA94(short value)
{
	return Rva0056F690Hook(value, value);
}

int Rva0056FA94::rva0056FD7B()
{
	return Rva0056F84DHook(m_04, m_04);
}

// --- 0x0056FD88 / 0x0056FDB1 / 0x0056FDDA / 0x0056FE03 (41B each): a kind-2
// update stores +0x04, a kind-1 update passes the value to the rowed setter
// (0x0056FCDB, 0x0056FD14, 0x0056FD2D, 0x0056FD46); the receiver is answered.
class Rva0056FCDB
{
public:
	void rva0056FCDB(short value);							// 0x0056FCDB
};

class Rva0056FAA5
{
public:
	void rva0056FD14(int value);							// 0x0056FD14
	void rva0056FD2D(int value);							// 0x0056FD2D
	void rva0056FD46(short value);							// 0x0056FD46
};

class Rva0056FD88 : public Rva0056FCDB
{
public:
	Rva0056FD88 &rva0056FD88(int kind, short value, int stamp);
private:
	int m_00;
	int m_04;
};

Rva0056FD88 &Rva0056FD88::rva0056FD88(int kind, short value, int stamp)
{
	if (kind == 2)
		m_04 = stamp;
	if (kind == 1)
		rva0056FCDB(value);
	return *this;
}

class Rva0056FDB1 : public Rva0056FAA5
{
public:
	Rva0056FDB1 &rva0056FDB1(int kind, int value, int stamp);
	Rva0056FDB1 &rva0056FDDA(int kind, int value, int stamp);
	Rva0056FDB1 &rva0056FE03(int kind, short value, int stamp);
private:
	int m_00;
	int m_04;
};

Rva0056FDB1 &Rva0056FDB1::rva0056FDB1(int kind, int value, int stamp)
{
	if (kind == 2)
		m_04 = stamp;
	if (kind == 1)
		rva0056FD14(value);
	return *this;
}

Rva0056FDB1 &Rva0056FDB1::rva0056FDDA(int kind, int value, int stamp)
{
	if (kind == 2)
		m_04 = stamp;
	if (kind == 1)
		rva0056FD2D(value);
	return *this;
}

Rva0056FDB1 &Rva0056FDB1::rva0056FE03(int kind, short value, int stamp)
{
	if (kind == 2)
		m_04 = stamp;
	if (kind == 1)
		rva0056FD46(value);
	return *this;
}

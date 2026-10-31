// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (twenty-eighth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include <string.h>
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"

extern GameLogic *TheGameLogic;

// Declaration-only views of the STLport vector members these bodies call;
// no container code is instantiated here.
namespace _STL {
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	vector(const vector<T, A> &that);
	T *erase(T *first, T *last);
	void clear() { erase(m_start, m_finish); }
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

// --- 0x005079EF (21B, cdecl): whether the rowed 0x00360C1F comparison
// fails (its result read as a byte).
int Rva00360C1FEqual(const void *a, const void *b);			// 0x00360C1F

int isNotEqual(const void *a, const void *b)
{
	return !(unsigned char)Rva00360C1FEqual(a, b);
}

// --- 0x0050F702 (20B, cdecl): forward the string and comparator to the
// object's rowed 0x0050F1F0.
struct CharCompare
{
	int m_mode;
};

class Rva0050EE23
{
public:
	int rva0050F1F0(const char *text, CharCompare compare);	// 0x0050F1F0
};

int Rva0050F702(Rva0050EE23 *object, const char **text, CharCompare compare)
{
	return object->rva0050F1F0(*text, compare);
}

// --- 0x005148AA (83B) / 0x005148FD (83B): unless the running restart thread
// refuses (slot 0), stop the logic (rowed 0x00376E92), run the rowed
// 0x00444525 / 0x00516FA9 initialiser and release the thread (slot 2, then
// operator delete); 1 when refused, 2 otherwise.
class ThreadRestartObj
{
public:
	virtual bool slot00(int code);
	virtual void slot04();
	virtual void *stop(int code);
};

extern ThreadRestartObj *g_bfmeThreadAtE048E0;
void Rva00444525Init();										// 0x00444525
void rva00516FA9();											// 0x00516FA9

int Rva005148AA()
{
	if (g_bfmeThreadAtE048E0 && !g_bfmeThreadAtE048E0->slot00(1))
		return 1;
	TheGameLogic->clearGameData(false, false);
	Rva00444525Init();
	operator delete(g_bfmeThreadAtE048E0 ? g_bfmeThreadAtE048E0->stop(0) : 0);
	g_bfmeThreadAtE048E0 = 0;
	return 2;
}

int Rva005148FD()
{
	if (g_bfmeThreadAtE048E0 && !g_bfmeThreadAtE048E0->slot00(1))
		return 1;
	TheGameLogic->clearGameData(false, false);
	rva00516FA9();
	operator delete(g_bfmeThreadAtE048E0 ? g_bfmeThreadAtE048E0->stop(0) : 0);
	g_bfmeThreadAtE048E0 = 0;
	return 2;
}

// --- 0x0051E2BD (34B): scale the two floats componentwise.
struct Rva0051E2BDScale
{
	float x;
	float y;
};

class Rva0051E2BD
{
public:
	void rva0051E2BD(const Rva0051E2BDScale &scale);
private:
	float x;
	float y;
};

void Rva0051E2BD::rva0051E2BD(const Rva0051E2BDScale &scale)
{
	x = scale.x * x;
	y = scale.y * y;
}

// --- 0x005233FC (17B): the +0x184 colour packed with full alpha (rowed
// RGBColor::getAsInt).
class Rva005233FC
{
public:
	int getOpaqueColor() const;
private:
	char m_pad[0x184];
	RGBColor m_color;
};

int Rva005233FC::getOpaqueColor() const
{
	return m_color.getAsInt() | 0xFF000000;
}

// --- 0x00524F19 (28B): a word, a cleared flag and the -1.0 default.
class Rva00524F19
{
public:
	Rva00524F19(int value);
private:
	int m_value;
	bool m_flag;
	float m_08;
};

Rva00524F19::Rva00524F19(int value) : m_value(value), m_flag(false), m_08(-1.0f)
{
}

// --- 0x005260B1 (75B): the first object of the +0x10 record's +0x14 id list
// that the local player controls, or null.
class Player
{
public:
	bool isLocalPlayer() const;								// 0x002A9D89
};

class Object
{
public:
	Player *getControllingPlayer() const;					// 0x0028AFA9
	const AsciiString *rva00290E67() const;					// 0x00290E67
};

struct Rva005260B1Node
{
	Rva005260B1Node *m_next;
	Rva005260B1Node *m_prev;
	ObjectID m_id;
};

struct Rva005260B1List
{
	char m_pad[0x14];
	Rva005260B1Node *m_head;								// +0x14
};

class Rva005260B1
{
public:
	Object *rva005260B1();
private:
	char m_pad[0x10];
	Rva005260B1List *m_list;								// +0x10
};

Object *Rva005260B1::rva005260B1()
{
	Object *found = 0;
	Rva005260B1Node **head = &m_list->m_head;
	for (Rva005260B1Node *node = (*head)->m_next; node != *head; node = node->m_next)
	{
		Object *object = TheGameLogic->findObjectByID(node->m_id);
		if (object && object->getControllingPlayer()->isLocalPlayer())
		{
			found = object;
			break;
		}
	}
	return found;
}

// --- 0x005279C7 (22B): one more than the 16-bit count of the nested
// record, 1 without one.
struct Rva005279C7Record
{
	int m_00;
	unsigned short m_count;
};

struct Rva005279C7Outer
{
	Rva005279C7Record *m_record;
};

struct Rva005279C7Holder
{
	int m_00;
	Rva005279C7Outer *m_outer;
};

class Rva005279C7
{
public:
	int rva005279C7() const;
private:
	int m_00;
	Rva005279C7Holder *m_holder;
};

int Rva005279C7::rva005279C7() const
{
	Rva005279C7Record *record = m_holder->m_outer->m_record;
	if (record)
		return record->m_count + 1;
	return 1;
}

// --- 0x00527D8F (78B) / 0x00527DDD (40B) / 0x00527E05 (78B): button
// callbacks that, for a local player in state 2 (+0x750), queue message
// 0x46B / 0x46D / 0x46A and (except 0x46D) a 0x469 message carrying 0, 2.
class GameMessage
{
public:
	void appendIntegerArgument(int value);					// 0x0030F936
};

class MessageStream
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44();
	virtual GameMessage *appendMessage(int type);
};

extern MessageStream *TheMessageStream;

class PlayerList;
extern PlayerList *ThePlayerList;

struct Rva00527D8FPlayer
{
	char m_pad[0x750];
	int m_state;
};

struct Rva00527D8FList
{
	char m_pad[0x10];
	Rva00527D8FPlayer *m_local;
};

// Rva00527FA7's ctor (0x00527FA7) binds "_OnCancel", "_OnDeleteAction" and
// "_OnExecute" to these three bodies.
class Rva00527FA7
{
public:
	void OnCancel(const char *unused);
	void OnDeleteAction(const char *unused);
	void OnExecute(const char *unused);
};

void Rva00527FA7::OnCancel(const char *unused)
{
	Rva00527D8FPlayer *player = ((Rva00527D8FList *)ThePlayerList)->m_local;
	if (player && player->m_state == 2)
	{
		TheMessageStream->appendMessage(0x46B);
		GameMessage *msg = TheMessageStream->appendMessage(0x469);
		msg->appendIntegerArgument(0);
		msg->appendIntegerArgument(2);
	}
}

void Rva00527FA7::OnDeleteAction(const char *unused)
{
	Rva00527D8FPlayer *player = ((Rva00527D8FList *)ThePlayerList)->m_local;
	if (player && player->m_state == 2)
		TheMessageStream->appendMessage(0x46D);
}

void Rva00527FA7::OnExecute(const char *unused)
{
	Rva00527D8FPlayer *player = ((Rva00527D8FList *)ThePlayerList)->m_local;
	if (player && player->m_state == 2)
	{
		TheMessageStream->appendMessage(0x46A);
		GameMessage *msg = TheMessageStream->appendMessage(0x469);
		msg->appendIntegerArgument(0);
		msg->appendIntegerArgument(2);
	}
}

// --- 0x00528232 (14B): the indexed +0xDC word.
class Rva00528232
{
public:
	int rva00528232(int index) const;
private:
	char m_pad[0xDC];
	int m_DC[1];
};

int Rva00528232::rva00528232(int index) const
{
	return m_DC[index];
}

// --- 0x00529B4E (32B, cdecl): the object's rowed 0x00290E67 string, else
// the exported AsciiString::TheEmptyString (0x00DE0878) without the object.
const AsciiString *Rva00529B4E(ObjectID id)
{
	Object *object = TheGameLogic->findObjectByID(id);
	if (object)
		return object->rva00290E67();
	return &AsciiString::TheEmptyString;
}

// --- 0x0052D24B (18B): copy of a holder of the rowed 0x004334D7 vector.
struct BfmeE8;

class Rva0052D24B
{
public:
	Rva0052D24B(const Rva0052D24B &that);
private:
	_STL::vector<BfmeE8> m_records;
};

Rva0052D24B::Rva0052D24B(const Rva0052D24B &that) : m_records(that.m_records)
{
}

// --- 0x00531121 (17B): a 24000-entry rowed BooleanBitmapSet base.
class BooleanBitmapSet
{
public:
	BooleanBitmapSet(int count);							// 0x00530F47
private:
	int m_words[2];
};

class Rva00531121 : public BooleanBitmapSet
{
public:
	Rva00531121();
};

Rva00531121::Rva00531121() : BooleanBitmapSet(24000)
{
}

// --- 0x00531CF9 (15B) / 0x00531D9D (17B): read the indexed +0x0C 16-bit
// entry; bump the indexed +0x08 16-bit counter.
class Rva00531CF9
{
public:
	unsigned short rva00531CF9(unsigned short index) const;
	void rva00531D9D(unsigned short index);
private:
	int m_00;
	int m_04;
	unsigned short *m_counts;								// +0x08
	unsigned short *m_values;								// +0x0C
};

unsigned short Rva00531CF9::rva00531CF9(unsigned short index) const
{
	return m_values[index];
}

void Rva00531CF9::rva00531D9D(unsigned short index)
{
	++m_counts[index];
}

// --- 0x00531D40 (18B): restart the 16-bit cursor (+0x04 from +0x00) and
// clear the +0x06 / +0x02 halves.
class Rva00531D40
{
public:
	void rva00531D40();
private:
	unsigned short m_00;
	unsigned short m_02;
	unsigned short m_04;
	unsigned short m_06;
};

void Rva00531D40::rva00531D40()
{
	unsigned short start = m_00;
	m_06 = 0;
	m_02 = 0;
	m_04 = start;
}

// --- 0x00531EAB (13B) / 0x00531FB0 (14B): whether the range at +0x00 /
// +0x38 is not empty.
class Rva00531EAB
{
public:
	bool rva00531EAB() const;
private:
	int *m_begin;
	int *m_end;
};

bool Rva00531EAB::rva00531EAB() const
{
	return m_begin != m_end;
}

class Rva00531FB0
{
public:
	bool rva00531FB0() const;
private:
	char m_pad[0x38];
	int *m_begin;
	int *m_end;
};

bool Rva00531FB0::rva00531FB0() const
{
	return m_begin != m_end;
}

// --- 0x00531EFC (15B) / 0x00531F17 (14B) / 0x00531F0B (12B), cdecl: 16-bit
// and byte orderings.
bool Rva00531EFC(unsigned short a, unsigned short b)
{
	return a < b;
}

bool Rva00531F17(unsigned short a, unsigned short b)
{
	return !(b < a);
}

bool Rva00531F0B(int unused0, int unused1, unsigned char a, unsigned char b)
{
	return !(b < a);
}

// --- 0x00531F3C (12B): two zero 16-bit halves.
class Rva00531F3C
{
public:
	Rva00531F3C();
private:
	unsigned short m_00;
	unsigned short m_02;
};

Rva00531F3C::Rva00531F3C() : m_00(0), m_02(0)
{
}

// --- 0x00532283 (26B, cdecl): build a pair of 16-bit values in place.
struct Rva00532283Pair
{
	unsigned short m_first;
	unsigned short m_second;
};

void Rva00532283(Rva00532283Pair *out, const unsigned short *first, const unsigned short *second)
{
	out->m_first = *first;
	out->m_second = *second;
}

// --- 0x00532F91 (14B): empty the +0x38 particle-system id vector (rowed
// erase 0x00532803).
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

class Rva00532F91
{
public:
	void rva00532F91();
private:
	char m_pad[0x38];
	_STL::vector<ParticleSystemID> m_ids;
};

void Rva00532F91::rva00532F91()
{
	m_ids.clear();
}

// --- 0x00538224 (65B) / 0x00538265 (65B), cdecl: offset both corners of a
// rectangle; scale all four of its floats.
struct Rva00538224Offset
{
	float x;
	float y;
};

struct Rva00538224Point
{
	float x;
	float y;
	void add(const Rva00538224Offset &d) { x += d.x; y += d.y; }
	void scale(float s) { x *= s; y *= s; }
};

struct Rva00538224Rect
{
	Rva00538224Point lo;
	Rva00538224Point hi;
};

void Rva00538224(Rva00538224Rect *rect, const Rva00538224Offset *offset)
{
	rect->lo.add(*offset);
	rect->hi.add(*offset);
}

void Rva00538265(Rva00538224Rect *rect, float scale)
{
	rect->lo.scale(scale);
	rect->hi.scale(scale);
}

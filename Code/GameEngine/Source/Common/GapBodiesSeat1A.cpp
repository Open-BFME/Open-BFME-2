// cl: /O1 /G7 /arch:SSE /GX- /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// stlport46
// Small GameEngine bodies from .text gaps no ledger row covered (each begins
// after its neighbour's padding or return and ends in its own ret). Retail
// bytes establish every shape below; the owning classes are not recovered, so
// each keeps an address-derived name and a view of only the members it
// touches. Callees are the ledger's existing rows under their current
// spellings.
#include "GameLogicObjectLookupView.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include "RTS/XYDistanceCallView.h"

extern GameLogic *TheGameLogic;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// --- 0x00203582 (19B): adds the argument to the float at +0x48.
class Rva00203582
{
public:
	void rva00203582(float delta);
private:
	char m_pad00[0x48];
	float m_48;
};

void Rva00203582::rva00203582(float delta)
{
	m_48 += delta;
}

// --- 0x00203671 (23B): stores a non-negative argument into
// TheWritableGlobalData's word at +0xAC8; the receiver is unused.
struct Rva00203671GlobalDataView
{
	char m_pad000[0xAC8];
	int m_AC8;
};

class Rva00203671
{
public:
	void rva00203671(int value);
};

void Rva00203671::rva00203671(int value)
{
	if (value >= 0)
		((Rva00203671GlobalDataView *)TheWritableGlobalData)->m_AC8 = value;
}

// --- 0x00203E65 (17B): 1 when TheGameLogic->rva001DCD1C() is false, else 0
// (sibling of the rowed 0x00203688/0x00203693 wrappers).
class Rva00203E65
{
public:
	int rva00203E65();
};

int Rva00203E65::rva00203E65()
{
	return !TheGameLogic->rva001DCD1C();
}

// --- 0x00205A1B (16B): returns by value a pair {0, &this[+0x0C]}.
struct Rva00205A1BPair
{
	Rva00205A1BPair(void *p) : m_00(0), m_04(p) {}
	int m_00;
	void *m_04;
};

class Rva00205A1B
{
public:
	Rva00205A1BPair rva00205A1B();
private:
	char m_pad00[0x0C];
	int m_0C;
};

Rva00205A1BPair Rva00205A1B::rva00205A1B()
{
	return Rva00205A1BPair(&m_0C);
}

// --- 0x00210EAC (19B): returns a zero float pair by value; both word
// arguments and the receiver are unused.
struct Rva00210EACCoord2D
{
	Rva00210EACCoord2D(float ax, float ay) : x(ax), y(ay) {}
	float x;
	float y;
};

class Rva00210EAC
{
public:
	Rva00210EACCoord2D rva00210EAC(int a, int b);
};

Rva00210EACCoord2D Rva00210EAC::rva00210EAC(int, int)
{
	return Rva00210EACCoord2D(0.0f, 0.0f);
}

// --- 0x00215E5F (16B): 1 when the argument's first word equals this one's.
class Rva00215E5F
{
public:
	int rva00215E5F(const Rva00215E5F *other);
private:
	int m_00;
};

int Rva00215E5F::rva00215E5F(const Rva00215E5F *other)
{
	return other->m_00 == m_00;
}

// --- 0x00215E87 (18B): the index of the first null of two slots, else 2.
class Rva00215E87
{
public:
	unsigned int rva00215E87();
private:
	void *m_slots[2];
};

unsigned int Rva00215E87::rva00215E87()
{
	unsigned int i;
	for (i = 0; i < 2; ++i)
	{
		if (m_slots[i] == 0)
			return i;
	}
	return 2;
}

// --- 0x0021917A (18B): cdecl equality of two pointed-to words.
int Rva0021917A(const int *a, const int *b)
{
	return *b == *a;
}

// --- 0x0021982A (16B): the halfword at +4 of the node the first word points
// at, or 0 without a node.
struct Rva0021982ANode
{
	int m_00;
	unsigned short m_04;
};

class Rva0021982A
{
public:
	int rva0021982A();
private:
	Rva0021982ANode **m_node;
};

int Rva0021982A::rva0021982A()
{
	Rva0021982ANode *node = *m_node;
	if (node)
		return node->m_04;
	return 0;
}

// --- 0x002224DE (32B): false past the fourteenth 0x28-byte record at +0xF0,
// else the inverse of that record's second flag bit.
struct Rva002224DERecord
{
	unsigned char m_flag0 : 1;
	unsigned char m_flag1 : 1;
	char m_pad01[0x27];
};

class Rva002224DE
{
public:
	bool rva002224DE(unsigned int index);
private:
	char m_pad00[0xF0];
	Rva002224DERecord m_records[14];
};

bool Rva002224DE::rva002224DE(unsigned int index)
{
	if (index >= 14)
		return false;
	return !m_records[index].m_flag1;
}

// --- 0x002226A2 (28B): constructor from a flag and an eight-byte pair.
struct Rva002226A2Pair
{
	int m_00;
	int m_04;
};

class Rva002226A2
{
public:
	Rva002226A2(const bool &flag, const Rva002226A2Pair &pair);
private:
	bool m_00;
	Rva002226A2Pair m_04;
};

Rva002226A2::Rva002226A2(const bool &flag, const Rva002226A2Pair &pair) : m_00(flag), m_04(pair)
{
}

// --- 0x00225A81 (18B): copies an eight-byte pair to +0x38.
class Rva00225A81
{
public:
	void rva00225A81(const Rva002226A2Pair &pair);
private:
	char m_pad00[0x38];
	Rva002226A2Pair m_38;
};

void Rva00225A81::rva00225A81(const Rva002226A2Pair &pair)
{
	m_38 = pair;
}

// --- 0x0022CF6E, 0x0022CF9F (18B each): the rowed timing hooks applied to
// the argument twice, as the rowed 0x0022D189 setter calls the first.
int Rva0022CB5CHook(int a, int b);
int Rva0022CC0EHook(int a, int b);

class Rva0022CF6E
{
public:
	int rva0022CF6E(int value);
	int rva0022CF9F(int value);
};

int Rva0022CF6E::rva0022CF6E(int value)
{
	return Rva0022CB5CHook(value, value);
}

int Rva0022CF6E::rva0022CF9F(int value)
{
	return Rva0022CC0EHook(value, value);
}

// --- 0x0022D979 (20B): sets the timing value from the pointed word through
// the rowed 0x0022D189 setter and returns this.
class Rva00077710Value
{
public:
	void rva0022D189(int value);
	Rva00077710Value &rva0022D979(const int &value);
	int rva0022D98D();
	int m_a;
	int m_b;
};

Rva00077710Value &Rva00077710Value::rva0022D979(const int &value)
{
	rva0022D189(value);
	return *this;
}

// --- 0x0022D98D (13B): directly after it, reads the stored word at +4 back
// through the rowed 0x0022CC0E hook applied to it twice (the getter
// counterpart; same shape as Rva00435B71::rva00435D70 0x00435D70).
int Rva00077710Value::rva0022D98D()
{
	return Rva0022CC0EHook(m_b, m_b);
}

// --- 0x0023262C (23B): whether the halfword at +6 of the indexed 8-byte
// record at +0x18 shares a bit with the mask.
struct Rva0023262CRecord
{
	char m_pad00[6];
	unsigned short m_bits;
};

class Rva0023262C
{
public:
	int rva0023262C(unsigned char index, int mask);
private:
	char m_pad00[0x18];
	Rva0023262CRecord m_records[1];
};

int Rva0023262C::rva0023262C(unsigned char index, int mask)
{
	return (m_records[index].m_bits & mask) != 0;
}

// --- 0x0023426A (30B): constructor from an eight-byte pair and a halfword;
// 0x002342C5 (16B): copies the first halfword out and returns 1.
class Rva0023426A
{
public:
	Rva0023426A(const Rva002226A2Pair &pair, const short &value);
	int rva002342C5(short *out) const;
private:
	Rva002226A2Pair m_00;
	short m_08;
};

Rva0023426A::Rva0023426A(const Rva002226A2Pair &pair, const short &value) : m_00(pair), m_08(value)
{
}

int Rva0023426A::rva002342C5(short *out) const
{
	*out = *(const short *)&m_00;
	return 1;
}

// --- 0x00239B11 (24B): one node from the freelist pool at VA 0x00DBA5E0
// (rowed pop), none for a count above one; the second word is unused.
class FreelistPool
{
public:
	void *pop();
};
extern FreelistPool g_freelistPool00DBA5E0;

class Rva00239B11
{
public:
	void *rva00239B11(unsigned int count, const void *hint);
};

void *Rva00239B11::rva00239B11(unsigned int count, const void *)
{
	if (count > 1)
		return 0;
	return g_freelistPool00DBA5E0.pop();
}

// --- 0x0023DB48 (16B): latches +0x38 into an unset +0x40 and returns it.
class Rva0023DB48
{
public:
	int rva0023DB48();
private:
	char m_pad00[0x38];
	int m_38;
	int m_3C;
	int m_40;
};

int Rva0023DB48::rva0023DB48()
{
	if (m_40 == 0)
		m_40 = m_38;
	return m_40;
}

// --- 0x0023E887 (28B): constructor copying a word and building the string
// at +4 from the source's text.
struct Rva0023E887Source
{
	int m_00;
	const char *m_text;
};

class Rva0023E887
{
public:
	Rva0023E887(const Rva0023E887Source &source);
private:
	int m_00;
	AsciiString m_text;
};

Rva0023E887::Rva0023E887(const Rva0023E887Source &source) : m_00(source.m_00), m_text(source.m_text)
{
}

// --- 0x00254628 (34B) and 0x002546EB (34B): module-data field parsers,
// each the rowed base table 0x004CE29D at offset 8 then its own table (VA
// 0x00BF247C, VA 0x00BF2534); 0x0025464A (52B) and 0x0025470D (52B): their
// INI factories over 0x11C-byte data built by the rowed constructors
// 0x0025460F and 0x002546D2 (the latter folds with RadarUpgradeModuleData's).
struct FieldParse;
class ModuleData;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *table, unsigned int offset);	// 0x0002BC6E
};

class INI
{
public:
	void initFromINIMultiProc(void *what, void (*proc)(MultiIniFieldParse &p));	// 0x0002DEB5
};

int Rva004CE29DGet(void);
extern const FieldParse s_Rva00254628FieldParse[];			// VA 0x00BF247C
extern const FieldParse s_Rva002546EBFieldParse[];			// VA 0x00BF2534

class Rva0025460F
{
public:
	Rva0025460F();
private:
	char m_pad[0x11C];
};

class RadarUpgradeModuleData
{
public:
	RadarUpgradeModuleData();
private:
	unsigned char m_pad[0x11C];
};

class Rva00254628ModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};



class Rva002546EBModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};



// --- 0x0025F342 (67B): swaps a marker into the +0x80 list in place of the
// one with the same name, returning the unlinked one (or null); 0x0025F3AE
// (69B): unlinks and deletes the marker with the argument's name.
class CameraMarker
{
public:
	~CameraMarker();										// 0x0029D7C2
	CameraMarker *m_next;
	AsciiString m_name;
};

class Rva0025F342
{
public:
	CameraMarker *rva0025F342(CameraMarker *marker);
	void rva0025F3AE(const CameraMarker *marker);
private:
	char m_pad00[0x80];
	CameraMarker *m_markers;
};

CameraMarker *Rva0025F342::rva0025F342(CameraMarker *marker)
{
	CameraMarker *old = 0;
	for (CameraMarker **link = &m_markers; *link; link = &(*link)->m_next)
	{
		CameraMarker *cur = *link;
		if (cur->m_name.compare(marker->m_name) == 0)
		{
			old = *link;
			*link = marker;
			marker->m_next = old->m_next;
			old->m_next = 0;
			break;
		}
	}
	return old;
}

void Rva0025F342::rva0025F3AE(const CameraMarker *marker)
{
	for (CameraMarker **link = &m_markers; *link; link = &(*link)->m_next)
	{
		CameraMarker *cur = *link;
		if (cur->m_name.compare(marker->m_name) == 0)
		{
			CameraMarker *old = *link;
			*link = old->m_next;
			delete old;
			break;
		}
	}
}

// --- 0x002602C1 (25B): constructor from a unicode string and a word.
class Rva002602C1
{
public:
	Rva002602C1(const UnicodeString &text, int value);
private:
	UnicodeString m_text;
	int m_04;
};

Rva002602C1::Rva002602C1(const UnicodeString &text, int value) : m_text(text), m_04(value)
{
}

// --- 0x00260DCF (13B): bit 3 of the byte at +0x438.
class Rva00260DCF
{
public:
	bool rva00260DCF() const;
private:
	char m_pad000[0x438];
	unsigned char m_438;
};

bool Rva00260DCF::rva00260DCF() const
{
	return (m_438 >> 3) & 1;
}

// --- 0x00260DDC (17B) and 0x0026223A (17B): the +4 word of the record at
// +0x04 / +0x50, or 999999 without one.
struct Rva00260DDCRecord
{
	int m_00;
	int m_04;
};

class Rva00260DDC
{
public:
	int rva00260DDC() const;
private:
	int m_00;
	Rva00260DDCRecord *m_record;
};

int Rva00260DDC::rva00260DDC() const
{
	if (m_record)
		return m_record->m_04;
	return 999999;
}

class Rva0026223A
{
public:
	int rva0026223A() const;
	int rva00262254() const;
private:
	char m_pad00[0x50];
	Rva00260DDCRecord *m_record;
	int m_54;
};

int Rva0026223A::rva0026223A() const
{
	if (m_record)
		return m_record->m_04;
	return 999999;
}

// 0x00262254 (15B): a record is present and +0x54 is -1.
int Rva0026223A::rva00262254() const
{
	return m_record != 0 && m_54 == -1;
}

// --- 0x00262263 (14B): byte +8 set and byte +0x0A clear.
class Rva00262263
{
public:
	int rva00262263() const;
private:
	char m_pad00[8];
	bool m_08;
	bool m_09;
	bool m_0A;
};

int Rva00262263::rva00262263() const
{
	return m_08 && !m_0A;
}

// --- 0x00260E0D (17B): 1 when the object is not on an airborne locomotor.
enum ObjectStatusTypes { OBJECT_STATUS_4 = 4 };
enum ObjectScriptStatusBit { OBJECT_SCRIPT_STATUS_0 };
struct Coord3D;

class Object
{
public:
	bool isUsingAirborneLocomotor() const;					// 0x0028B81E
	int rva0028B511() const;								// 0x0028B511
	bool isMassSelectable() const;								// 0x00292FAC
	bool testStatus(ObjectStatusTypes status) const;		// 0x0004E536
	void rva0028D611(Object *other, int a, int b);
	float GetRelativeAngle(const Coord3D *pos) const;		// 0x000B4542
	float rva0028F8A3(const Object *other) const;
	void setScriptStatus(ObjectScriptStatusBit bit, bool set);	// 0x00292969
	void rva002934D9(ObjectScriptStatusBit bit);
	void rva00294C1A(Object *other, bool flag, float scale);	// 0x00294C1A
	int m_pad00[0x74 / 4];
	int m_74;												// +0x74
	char m_pad78[0x244 - 0x78];
	void **m_modules;										// +0x244, null-terminated
	char m_pad248[0x484 - 0x248];
	int m_484;												// +0x484
};

class Rva00260E0D
{
public:
	int rva00260E0D(const Object *obj);
};

int Rva00260E0D::rva00260E0D(const Object *obj)
{
	return !obj->isUsingAirborneLocomotor();
}

// --- 0x00260F3B (21B): the argument's +0x304 word equals this +8 word.
struct Rva00260F3BOther
{
	char m_pad000[0x304];
	int m_304;
};

class Rva00260F3B
{
public:
	int rva00260F3B(const Rva00260F3BOther *other);
private:
	int m_00;
	int m_04;
	int m_08;
};

int Rva00260F3B::rva00260F3B(const Rva00260F3BOther *other)
{
	return other->m_304 == m_08;
}

// --- 0x00261750 (30B): allow() of the thing-template partition filter
// (vftable 0x00C1FDEC; Zero Hour's PartitionFilterThing): whether the +8
// template's rowed isEquivalentTo the object's +4 template agrees with the
// +0x0C flag; 0x0026176E (34B): the same over the rowed 0x00376A62 test of
// that template's +0x64 name.
class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *tmpl) const;	// 0x0033BB04
};

class ObjectTypes
{
public:
	bool isInSet(const AsciiString &name) const;			// 0x00376A62
};

struct Rva00261750Template
{
	char m_pad00[0x64];
	AsciiString m_name;
};

struct Rva00261750Arg
{
	int m_00;
	const void *m_04;
};


class Rva000421C8
{
public:
	virtual ~Rva000421C8();
	virtual bool allow(Object *obj) = 0;
	Rva000421C8 *m_next;
};

class Rva00261750Filter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
	const ThingTemplate *m_template;
	bool m_match;
};

bool Rva00261750Filter::allow(Object *obj)
{
	return m_template->isEquivalentTo((const ThingTemplate *)((const Rva00261750Arg *)obj)->m_04) == m_match;
}

class Rva0026176EFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
	void *m_08;
	bool m_0C;
};

bool Rva0026176EFilter::allow(Object *obj)
{
	return ((const ObjectTypes *)m_08)->isInSet(((const Rva00261750Template *)((const Rva00261750Arg *)obj)->m_04)->m_name) == m_0C;
}

// --- 0x002619AE (19B): the argument's rowed BitFlags<69>::test of this
// +0x108.
template <int N> class BitFlags
{
public:
	bool test(const void *other) const;
};

// --- 0x002619A0 (14B): the rowed BitFlags<69>::test of the first argument run
// on the second; the receiver (ecx) is discarded, so the object carrying the
// flags arrives as the last argument.
bool Rva002619A0(const void *other, const BitFlags<69> *flags)
{
	return flags->test(other);
}

class Rva002619AE
{
public:
	bool rva002619AE(const BitFlags<69> *flags);
private:
	char m_pad000[0x108];
	int m_108;
};

bool Rva002619AE::rva002619AE(const BitFlags<69> *flags)
{
	return flags->test(&m_108);
}

// --- 0x002628E0 (25B): the +0x224 owner's rowed removeFromMatching of the
// argument's +0x74 word and the second argument.
class Rva00331CBAVectorOwner
{
public:
	void removeFromMatching(int entry, int key);			// 0x00331CBA
};

struct Rva002628E0Arg
{
	char m_pad00[0x74];
	int m_74;
};

class Rva002628E0
{
public:
	void rva002628E0(const Rva002628E0Arg *arg, int key);
private:
	char m_pad000[0x224];
	Rva00331CBAVectorOwner m_owner;
};

void Rva002628E0::rva002628E0(const Rva002628E0Arg *arg, int key)
{
	m_owner.removeFromMatching(arg->m_74, key);
}

// --- 0x00262B7D (44B): TheAI's pathfinder (+0x10) validates a position for
// the +8 object with its rowed 0x0028B511 answer and this +0x1DC word.
struct Coord3D;
class Pathfinder
{
public:
	bool IsValidMovementPositionForObject(const Coord3D *pos, int a, int b, const Object *obj);	// 0x002E909F
};

class AI;
extern AI *TheAI;

struct Rva00262B7DAIView
{
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};

class Rva00262B7D
{
public:
	bool rva00262B7D(const Coord3D *pos);
private:
	char m_pad000[8];
	Object *m_obj;
	char m_pad00C[0x1DC - 0x0C];
	int m_1DC;
};

bool Rva00262B7D::rva00262B7D(const Coord3D *pos)
{
	Rva00262B7DAIView *ai = (Rva00262B7DAIView *)TheAI;
	Object *obj = m_obj;
	int value = m_1DC;
	Pathfinder *pathfinder = ai->m_pathfinder;
	return pathfinder->IsValidMovementPositionForObject(pos, obj->rva0028B511(), value, obj);
}

// --- 0x002636E6 (16B): the rowed squared distance to the argument's +0x38
// point.
class Rva002636E6Arg
{
public:
	char m_pad00[0x38];
	Rva000CBA20Point *m_point;
};

class Rva002636E6 : public Rva000CBA20
{
public:
	float rva002636E6(const Rva002636E6Arg *arg);
};

float Rva002636E6::rva002636E6(const Rva002636E6Arg *arg)
{
	return distSq((const Rva000CBA20Point *)&arg->m_point);
}

// --- 0x002638CC, 0x002638E4 (14B each): Locomotor flag setters for flags 6
// and 3 through the rowed private setFlag.
class Locomotor
{
public:
	enum LocoFlag { LOCO_FLAG_1 = 1, LOCO_FLAG_3 = 3, LOCO_FLAG_6 = 6 };
	void rva002638CC(bool value);
	void rva002638E4(bool value);
	void rva00343095(bool value);
private:
	void setFlag(LocoFlag flag, bool value);				// 0x001E3459
};

void Locomotor::rva002638CC(bool value)
{
	setFlag(LOCO_FLAG_6, value);
}

void Locomotor::rva002638E4(bool value)
{
	setFlag(LOCO_FLAG_3, value);
}

// 0x00343095 (14B): the same for flag 1.
void Locomotor::rva00343095(bool value)
{
	setFlag(LOCO_FLAG_1, value);
}

// --- 0x00265681 (16B): returns by value the word the +4 handle's pointer
// addresses.
struct Rva00265681Word
{
	Rva00265681Word(int v) : m_value(v) {}
	int m_value;
};

class Rva00265681
{
public:
	Rva00265681Word rva00265681();
private:
	int m_00;
	int **m_handle;
};

Rva00265681Word Rva00265681::rva00265681()
{
	return Rva00265681Word(**m_handle);
}

// --- 0x0026891F (27B): constructor storing two words, then the rowed
// 0x002654D6 reset.
class Rva002654D6
{
public:
	Rva002654D6(int a, int b);
	void rva002654D6();										// 0x002654D6
private:
	int m_00;
	int m_04;
};

Rva002654D6::Rva002654D6(int a, int b) : m_00(a), m_04(b)
{
	rva002654D6();
}

// --- 0x00268B0C (20B, cdecl): whether the string differs from the text.
int Rva00268B0C(const AsciiString *str, const char *text)
{
	return str->compare(text) != 0;
}

// --- 0x0026FCF9 (14B): the indexed word of the array at +0x148.
class Rva0026FCF9
{
public:
	int rva0026FCF9(int index) const;
private:
	char m_pad000[0x148];
	int m_words[1];
};

int Rva0026FCF9::rva0026FCF9(int index) const
{
	return m_words[index];
}

// --- 0x0027175F (26B): 1 when the +0xFC object answers the rowed
// 0x00292FAC test.
class Rva0027175F
{
public:
	int rva0027175F() const;
private:
	char m_pad00[0xFC];
	Object *m_obj;
};

int Rva0027175F::rva0027175F() const
{
	if (m_obj && m_obj->isMassSelectable())
		return 1;
	return 0;
}

// --- 0x0027229B (15B): bit 20 of +0x98 clear.
class Rva0027229B
{
public:
	bool rva0027229B() const;
private:
	char m_pad00[0x98];
	unsigned int m_98;
};

bool Rva0027229B::rva0027229B() const
{
	bool set = (m_98 >> 20) & 1;
	return !set;
}

struct GapVoidVector
{
	void **m_start;
	void **m_finish;
	void **m_end;
};

static __forceinline int GapVoidVectorCount(const GapVoidVector *gapVoidVector) { return gapVoidVector->m_finish - gapVoidVector->m_start; }

// Dummy virtual slots for call views; only the slot index matters.
#define GAP_V1(n) virtual void v##n();
#define GAP_V10(n) GAP_V1(n##0) GAP_V1(n##1) GAP_V1(n##2) GAP_V1(n##3) GAP_V1(n##4) GAP_V1(n##5) GAP_V1(n##6) GAP_V1(n##7) GAP_V1(n##8) GAP_V1(n##9)

// --- 0x00272366 (45B): the +0x14C holder's object's slot-42 answer, when
// there is one, handles the three arguments in its slot 0; else false.
class Rva00272366Handler
{
public:
	virtual bool handle(int a, int b, int c);
};

class Rva00272366Target
{
public:
	GAP_V10(0) GAP_V10(1) GAP_V10(2) GAP_V10(3)
	GAP_V1(40) GAP_V1(41)
	virtual Rva00272366Handler *getHandler();				// slot 42
	GAP_V1(43) GAP_V1(44) GAP_V1(45) GAP_V1(46) GAP_V1(47) GAP_V1(48) GAP_V1(49)
	GAP_V1(50) GAP_V1(51) GAP_V1(52) GAP_V1(53)
	virtual void slot54(int a, int b);						// slot 54
};

class Rva00272366Holder
{
public:
	Rva00272366Target *get() const { return m_target; }
private:
	Rva00272366Target *m_target;
};

class Rva00272366
{
public:
	bool rva00272366(int a, int b, int c);
private:
	__forceinline Rva00272366Handler *handler() const
	{
		if (m_holder)
		{
			Rva00272366Target *target = m_holder->get();
			if (target)
				return target->getHandler();
		}
		return 0;
	}
	char m_pad000[0x14C];
	Rva00272366Holder *m_holder;
};

bool Rva00272366::rva00272366(int a, int b, int c)
{
	Rva00272366Handler *h = handler();
	if (h)
		return h->handle(a, b, c);
	return false;
}


// --- 0x002785D6 (37B): changes the +0x447 flag, then on set the rowed
// 0x002783F6(0), on clear the rowed 0x002743D7; 0x0027862C (24B): changes the
// +0x449 flag, then the rowed 0x002784EB.
class Rva002783F6Host
{
public:
	void rva002783F6(int value);							// 0x002783F6
};

class Drawable
{
public:
	void stopAmbientSound();										// 0x002743D7
	void rva002784EB();										// 0x002784EB
	void enableAmbientSound(bool value);
	void rva0027862C(bool value);
private:
	char m_pad000[0x447];
	bool m_447;
	bool m_448;
	bool m_449;
};

void Drawable::enableAmbientSound(bool value)
{
	if (m_447 != value)
	{
		m_447 = value;
		if (value)
			((Rva002783F6Host *)this)->rva002783F6(0);
		else
			stopAmbientSound();
	}
}

void Drawable::rva0027862C(bool value)
{
	if (m_449 != value)
	{
		m_449 = value;
		rva002784EB();
	}
}

// --- 0x0027C226 (10B, cdecl): sets the word at VA 0x00DBB708.
extern int g_Va00DBB708;

void Rva0027C226(int value)
{
	g_Va00DBB708 = value;
}

// --- 0x0027C280 (36B): stores three floats at +0x1C.
class Rva0027C280
{
public:
	void rva0027C280(float x, float y, float z);
private:
	char m_pad00[0x1C];
	float m_1C;
	float m_20;
	float m_24;
};

void Rva0027C280::rva0027C280(float x, float y, float z)
{
	m_1C = x;
	m_20 = y;
	m_24 = z;
}

// --- 0x0028565F (19B): calls the cdecl function pointer at +0x9C;
// 0x002856B7 (15B): the argument is at most +0x3C.
class Rva0028565F
{
public:
	int rva0028565F(int a, int b);
	bool rva002856B7(int value) const;
private:
	char m_pad00[0x3C];
	int m_3C;
	char m_pad40[0x9C - 0x40];
	int (*m_9C)(int a, int b);
};

int Rva0028565F::rva0028565F(int a, int b)
{
	return m_9C(a, b);
}

bool Rva0028565F::rva002856B7(int value) const
{
	return value <= m_3C;
}

// --- 0x00285760 (13B): drops a reference (+4) and frees through the rowed
// 0x0020DAE0 at zero.
void Rva0020DAE0(void *p);

class Rva00285760
{
public:
	void rva00285760();
private:
	int m_00;
	int m_refs;
};

void Rva00285760::rva00285760()
{
	if (--m_refs == 0)
		Rva0020DAE0(this);
}

// --- 0x00285A0A (12B, cdecl): the argument's slot 11 with 0.
class Rva00285A0ATarget
{
public:
	GAP_V10(0) GAP_V1(10)
	virtual void slot11(int value);
};

void Rva00285A0A(Rva00285A0ATarget *target)
{
	target->slot11(0);
}

// --- 0x00285A16, 0x0028878C (16B each): the rowed comparisons of the first
// argument with the second; the receiver is unused.
class Rva00285672
{
public:
	bool rva00285672(const Rva00285672 &other) const;		// 0x00285672
};

class ExperienceLevel
{
public:
	bool operator<(const ExperienceLevel &other) const;	// 0x00288621
};

class Rva00285A16
{
public:
	bool rva00285A16(const Rva00285672 *a, const Rva00285672 &b);
	bool rva0028878C(const ExperienceLevel *a, const ExperienceLevel &b);
};

bool Rva00285A16::rva00285A16(const Rva00285672 *a, const Rva00285672 &b)
{
	return a->rva00285672(b);
}

bool Rva00285A16::rva0028878C(const ExperienceLevel *experienceLevel, const ExperienceLevel &b)
{
	return experienceLevel->operator<(b);
}

// --- 0x0028667F (20B): the rowed 0x00286214 find returned by value.
struct Rva00286214Node;
struct Rva0028667FIterator
{
	Rva0028667FIterator(Rva00286214Node *node) : m_node(node) {}
	Rva00286214Node *m_node;
};

class Rva00286214
{
public:
	Rva00286214Node *rva00286214(const Rva00285672 *key);	// 0x00286214
	Rva0028667FIterator rva0028667F(const Rva00285672 *key);
};

Rva0028667FIterator Rva00286214::rva0028667F(const Rva00285672 *key)
{
	return Rva0028667FIterator(rva00286214(key));
}

// --- 0x002895AF (11B): erases every marker through the rowed erase.
class CameraMarkerVec
{
public:
	CameraMarker *erase(CameraMarker *first, CameraMarker *last);	// 0x0048D042
	void rva002895AF();
	CameraMarker *m_start;
	CameraMarker *m_finish;
	CameraMarker *m_end;
};

void CameraMarkerVec::rva002895AF()
{
	erase(m_start, m_finish);
}

// --- Object-region leaves: 0x0028A638 (12B) +0x464 set; 0x0028A644 (12B)
// bit 1 of +0x438; float setters 0x0028A6B6 (+0x444), 0x0028A7C7 (+0x200),
// 0x0028BB8D (+0x1B8); 0x0028A7B7 (16B) byte +1 equals the argument;
// 0x0028A84B (23B) bit test of +0x30; 0x0028B975 (15B) resets +0x490/+0x48C;
// 0x0028C8CD (18B) and 0x0028F2E6 (18B) pointer-vector counts at +0x234 and
// +0x4A4.
class Rva0028A638
{
public:
	bool rva0028A638() const;
	bool rva0028A644() const;
	void rva0028A6B6(float value);
	void rva0028A7C7(float value);
	void rva0028BB8D(float value);
	void rva0028B975();
	int rva0028C8CD() const;
	int rva0028F2E6() const;
private:
	char m_pad000[0x1B8];
	float m_1B8;
	char m_pad1BC[0x200 - 0x1BC];
	float m_200;
	char m_pad204[0x234 - 0x204];
	GapVoidVector m_234;
	char m_pad240[0x438 - 0x240];
	unsigned char m_438;
	char m_pad439[0x444 - 0x439];
	float m_444;
	char m_pad448[0x464 - 0x448];
	int m_464;
	char m_pad468[0x48C - 0x468];
	bool m_48C;
	char m_pad48D[0x490 - 0x48D];
	int m_490;
	char m_pad494[0x4A4 - 0x494];
	GapVoidVector m_4A4;
};

bool Rva0028A638::rva0028A638() const
{
	return m_464 != 0;
}

bool Rva0028A638::rva0028A644() const
{
	return (m_438 >> 1) & 1;
}

void Rva0028A638::rva0028A6B6(float value)
{
	m_444 = value;
}

void Rva0028A638::rva0028A7C7(float value)
{
	m_200 = value;
}

void Rva0028A638::rva0028BB8D(float value)
{
	m_1B8 = value;
}

void Rva0028A638::rva0028B975()
{
	m_490 = -1;
	m_48C = false;
}

int Rva0028A638::rva0028C8CD() const
{
	return GapVoidVectorCount(&m_234);
}

int Rva0028A638::rva0028F2E6() const
{
	return GapVoidVectorCount(&m_4A4);
}

class Rva0028A7B7
{
public:
	int rva0028A7B7(int value) const;
	int rva0028A84B(int bit) const;
private:
	unsigned char m_00;
	unsigned char m_01;
	char m_pad02[0x30 - 2];
	int m_30;
};

int Rva0028A7B7::rva0028A7B7(int value) const
{
	return m_01 == value;
}

int Rva0028A7B7::rva0028A84B(int bit) const
{
	return ((1 << bit) & m_30) != 0;
}

// --- 0x0028BC29 (18B): the +0x23C field's rowed flag, false without one.
class Rva003B8ACFCmpBoolField
{
public:
	bool get() const;										// 0x003B8ACF
};

class Rva0028BC29
{
public:
	bool rva0028BC29() const;
private:
	char m_pad000[0x23C];
	Rva003B8ACFCmpBoolField *m_field;
};

bool Rva0028BC29::rva0028BC29() const
{
	if (m_field == 0)
		return false;
	return m_field->get();
}

// --- 0x0028BC3B (18B): the same +0x23C field's second query, false without
// one; the tail jump to 0x004DF49C (list size != 0) shows a bool result.
class Rva00256AB0Owner
{
public:
	bool hasEntries() const;								// 0x004DF49C
};

class Rva0028BC3B
{
public:
	bool rva0028BC3B() const;
private:
	char m_pad000[0x23C];
	Rva00256AB0Owner *m_field;
};


// --- 0x0028C59F (14B): zeroes twenty bytes of this through the CRT memset
// thunk 0x006291AE.
// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)

class Rva0028C59F
{
public:
	void rva0028C59F();
private:
	int m_words[5];
};

void Rva0028C59F::rva0028C59F()
{
	memset(this, 0, 0x14);
}

// --- 0x0028D611 (111B): unless the other object shares this one's +0x484
// relation (against its +0x74 id) or both carry one, each module whose
// +0x0C interface (slot 1) yields a handler passes it the three arguments,
// stopping when this object has status 4.
class Rva0028D611Handler
{
public:
	virtual void handle(Object *other, int a, int b);
};

class Rva0028D611Interface
{
public:
	virtual void s0();
	virtual Rva0028D611Handler *getHandler();
};

void Object::rva0028D611(Object *other, int a, int b)
{
	if (other == 0 || m_484 == other->m_74)
		return;
	if (other->m_484 != 0 && m_74 != 0)
		return;
	for (void **module = m_modules; *module; ++module)
	{
		Rva0028D611Handler *handler = ((Rva0028D611Interface *)((char *)*module + 0x0C))->getHandler();
		if (handler)
		{
			if (testStatus(OBJECT_STATUS_4))
				return;
			handler->handle(other, a, b);
		}
	}
}

// --- 0x00282206 (12B): pops the last 8-byte element, running its rowed
// destructor 0x0027EA49.
class Rva0027EA49
{
public:
	~Rva0027EA49();											// 0x0027EA49
private:
	int m_00;
	int m_04;
};

class Rva00282206
{
public:
	void rva00282206();
private:
	Rva0027EA49 *m_start;
	Rva0027EA49 *m_finish;
};

void Rva00282206::rva00282206()
{
	--m_finish;
	m_finish->~Rva0027EA49();
}

// --- 0x00282794 (11B): reserves the +0x578 module-data vector;
// 0x0028A665 (11B): the +0x330 material pass's texture for a stage;
// 0x0028C8BD (11B): ORs a bitset into +0x284.
class ModuleData;
class TextureClass;
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class vector
	{
	public:
		void reserve(unsigned int n);
	private:
		T *m_start;
		T *m_finish;
		T *m_end;
	};
	template <int N> struct _Base_bitset
	{
		void _M_do_or(const _Base_bitset &other);
		unsigned int m_words[N / 32];
	};
}

class MaterialPassClass
{
public:
	TextureClass *Peek_Texture(int stage) const;			// 0x002C7469
};

class Rva00282794
{
public:
	void rva00282794(unsigned int n);
	TextureClass *rva0028A665(int stage) const;
	void rva0028C8BD(const _STL::_Base_bitset<32> &bits);
private:
	char m_pad000[0x284];
	_STL::_Base_bitset<32> m_284;
	char m_pad288[0x330 - 0x288];
	MaterialPassClass m_330;
	char m_pad331[0x578 - 0x331];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_578;
};

void Rva00282794::rva00282794(unsigned int n)
{
	m_578.reserve(n);
}

TextureClass *Rva00282794::rva0028A665(int stage) const
{
	return m_330.Peek_Texture(stage);
}

void Rva00282794::rva0028C8BD(const _STL::_Base_bitset<32> &bits)
{
	m_284._M_do_or(bits);
}

// --- 0x0028F898 (11B): assigns the argument to the +0x94 member through its
// rowed operator=.
class Rva001EAFC1
{
public:
	Rva001EAFC1 &operator=(const Rva001EAFC1 &other);		// 0x001EAFC1
};

class Rva0028F898
{
public:
	Rva001EAFC1 &rva0028F898(const Rva001EAFC1 &value);
private:
	char m_pad00[0x94];
	Rva001EAFC1 m_94;
};

Rva001EAFC1 &Rva0028F898::rva0028F898(const Rva001EAFC1 &value)
{
	return m_94 = value;
}

// --- 0x0028F8A3 (16B): the relative angle to the other object's +0x38
// position; 0x002934D9 (14B): clears a script status bit.
float Object::rva0028F8A3(const Object *other) const
{
	return GetRelativeAngle((const Coord3D *)((const char *)other + 0x38));
}

void Object::rva002934D9(ObjectScriptStatusBit bit)
{
	setScriptStatus(bit, false);
}


// --- 0x0028F92B (21B): returns by value the rowed 0x0028F633 pair of 0 and
// this +0x38 word.
class Rva0028F633
{
public:
	Rva0028F633(int a, int b);								// 0x0028F633
private:
	int m_00;
	int m_04;
};

class Rva0028F92B
{
public:
	Rva0028F633 rva0028F92B() const;
private:
	char m_pad00[0x38];
	int m_38;
};

Rva0028F633 Rva0028F92B::rva0028F92B() const
{
	return Rva0028F633(0, m_38);
}

// --- 0x00298941, 0x0029894C (11B, 14B): erase every element of the vector
// at +0 / +0x20 through the rowed EraseRange.
class Rva00297360Element;
class Rva002983DAVector
{
public:
	Rva00297360Element *EraseRange(Rva00297360Element *first, Rva00297360Element *last);	// 0x002983DA
	void rva00298941();
	void clear() { EraseRange(m_start, m_finish); }
	Rva00297360Element *m_start;
	Rva00297360Element *m_finish;
	Rva00297360Element *m_end;
};

void Rva002983DAVector::rva00298941()
{
	EraseRange(m_start, m_finish);
}

class Rva0029894C
{
public:
	void rva0029894C();
private:
	char m_pad00[0x20];
	Rva002983DAVector m_20;
};

void Rva0029894C::rva0029894C()
{
	m_20.clear();
}

// --- 0x0029A389 (19B, cdecl): mixes a word into a hash (rotate left 5).
unsigned int Rva0029A389(unsigned int hash, unsigned int value)
{
	return ((value >> 27) ^ (value << 5)) ^ hash;
}

// --- 0x0029A48A (30B): sets the low end of the +0x58 range of the +0
// record, if any.
struct Rva0029A48ARange
{
	void set(float l, float h) { lo = l; hi = h; }
	float lo;
	float hi;
};

struct Rva0029A48ARecord
{
	char m_pad00[0x58];
	Rva0029A48ARange m_range;
};

class Rva0029A48A
{
public:
	void rva0029A48A(float lo);
	float rva0029A4A8() const;
	float rva0029A4B9() const;
private:
	Rva0029A48ARecord *m_record;
};

void Rva0029A48A::rva0029A48A(float lo)
{
	if (m_record)
	{
		m_record->m_range.set(lo, m_record->m_range.hi);
	}
}

// --- 0x0029A4A8 / 0x0029A4B9 (17B each): the high / low end of that range,
// or zero without a record.
float Rva0029A48A::rva0029A4A8() const
{
	if (m_record)
		return m_record->m_range.hi;
	return 0.0f;
}

float Rva0029A48A::rva0029A4B9() const
{
	if (m_record)
		return m_record->m_range.lo;
	return 0.0f;
}

// --- 0x0029B5CD (11B): forwards to the rowed body on the +0x9BC object.
class AnimateWindow;
class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual bool reverseAnimateWindow(AnimateWindow *win);	// 0x005CB265
};

class Rva0029B5CD
{
public:
	bool rva0029B5CD(AnimateWindow *win);
private:
	char m_pad000[0x9BC];
	void *m_9BC;
};

bool Rva0029B5CD::rva0029B5CD(AnimateWindow *win)
{
	return ((ProcessAnimateWindowSlideFromBottomTimed *)m_9BC)->ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow(win);
}

// --- 0x0029E0E6 (24B): one node from the freelist pool at VA 0x00DA60E8
// (rowed pop), none for a count above one.
extern FreelistPool g_freelistPool;

class Rva0029E0E6
{
public:
	void *rva0029E0E6(unsigned int count, const void *hint);
};

void *Rva0029E0E6::rva0029E0E6(unsigned int count, const void *)
{
	if (count > 1)
		return 0;
	return g_freelistPool.pop();
}

// --- 0x0029FE9E (29B): the rowed 0x0029BA28 with the word, then appends it
// to the +0x18 int list.
namespace _STL
{
	template <class T, class A> class list
	{
	public:
		void push_back(const T &value);
	private:
		void *m_node;
	};
}

class Rva0029BA28
{
public:
	void rva0029BA28(int value);							// 0x0029BA28
	void rva0029FE9E(int value);
private:
	char m_pad00[0x18];
	_STL::list<int, _STL::allocator<int> > m_18;
};

void Rva0029BA28::rva0029FE9E(int value)
{
	rva0029BA28(value);
	m_18.push_back(value);
}

// --- Small Player-region leaves: 0x002A71B1 (11B) word of the +0x60 array;
// 0x002A73A4/0x002A73AE (10B) add/subtract +0x0C; 0x002A97ED/0x002A97F7
// (10B) add to +0x18/+0x1C.
class Rva002A71B1
{
public:
	int rva002A71B1(int index) const;
	void rva002A73A4(int value);
	void rva002A73AE(int value);
	void rva002A97ED(int value);
	void rva002A97F7(int value);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	char m_pad20[0x60 - 0x20];
	int m_60[1];
};

int Rva002A71B1::rva002A71B1(int index) const
{
	return m_60[index];
}

void Rva002A71B1::rva002A73A4(int value)
{
	m_0C += value;
}

void Rva002A71B1::rva002A73AE(int value)
{
	m_0C -= value;
}

void Rva002A71B1::rva002A97ED(int value)
{
	m_18 += value;
}

void Rva002A71B1::rva002A97F7(int value)
{
	m_1C += value;
}

// --- 0x002A7F6C (20B): the +0x0C field of the indexed 16-byte record at
// *(+0xF50); 0x002AAE59 (20B) and 0x002AAE6D (20B): the +0 halfword and the
// +0x0C field of the indexed 16-byte record at *(+0xF6C).
struct Rva002A7F6CRecord
{
	short m_00;
	char m_pad02[0x0C - 2];
	int m_0C;
};

class Rva002A7F6C
{
public:
	int *rva002A7F6C(int index);
	int rva002AAE59(int index);
	int *rva002AAE6D(int index);
private:
	char m_pad000[0xF50];
	Rva002A7F6CRecord *m_F50;
	char m_padF54[0xF6C - 0xF54];
	Rva002A7F6CRecord *m_F6C;
};

int *Rva002A7F6C::rva002A7F6C(int index)
{
	return &m_F50[index].m_0C;
}

int Rva002A7F6C::rva002AAE59(int index)
{
	return m_F6C[index].m_00;
}

int *Rva002A7F6C::rva002AAE6D(int index)
{
	return &m_F6C[index].m_0C;
}

// --- 0x002A87F9 (15B, cdecl): clears the two skirmish-AI words at VA
// 0x00DFEFC0 and 0x00DFEFC4.
extern unsigned g_00DFEFC0, g_AITargetThreatFinderSerial;

void Rva002A87F9()
{
	g_00DFEFC0 = 0;
	g_AITargetThreatFinderSerial = 0;
}

// --- 0x002A9BE3 (15B): constructor from a flag with a cleared +4 word.
class Rva002A9BE3
{
public:
	Rva002A9BE3(bool flag);
private:
	bool m_00;
	int m_04;
};

Rva002A9BE3::Rva002A9BE3(bool flag) : m_00(flag), m_04(0)
{
}

// --- 0x002AA2BB (14B): count of the 0xD8-byte records of the vector at +0;
// 0x002AAC2E (15B): the indexed record.
struct Rva002AA2BBRecord
{
	char m_data[0xD8];
};

class Rva002AA2BB
{
public:
	int rva002AA2BB() const;
	Rva002AA2BBRecord *rva002AAC2E(int index);
private:
	Rva002AA2BBRecord *m_start;
	Rva002AA2BBRecord *m_finish;
	Rva002AA2BBRecord *m_end;
};

int Rva002AA2BB::rva002AA2BB() const
{
	return m_finish - m_start;
}

Rva002AA2BBRecord *Rva002AA2BB::rva002AAC2E(int index)
{
	return &m_start[index];
}

// --- 0x002AA842 (21B): the pointer-vector count at +0x18C of the +0x34
// object.
struct Rva002AA842Inner
{
	char m_pad000[0x18C];
	GapVoidVector m_18C;
};

class Rva002AA842
{
public:
	int rva002AA842() const;
private:
	char m_pad00[0x34];
	Rva002AA842Inner *m_34;
};

int Rva002AA842::rva002AA842() const
{
	return GapVoidVectorCount(&m_34->m_18C);
}

// --- 0x002AAC3D (24B): returns a node to the free list at VA 0x00DBBD34.
struct PoolNode002ABAC0
{
	PoolNode002ABAC0 *m_next;
};
extern PoolNode002ABAC0 *g_00DBBD34;

class Rva002AAC3D
{
public:
	void rva002AAC3D(PoolNode002ABAC0 *node, unsigned int count);
};

void Rva002AAC3D::rva002AAC3D(PoolNode002ABAC0 *node, unsigned int)
{
	if (node)
	{
		node->m_next = g_00DBBD34;
		g_00DBBD34 = node;
	}
}

// --- 0x002AAEB5 (16B): the indexed 0x24-byte record at *(+0x324).
struct Rva002AAEB5Record
{
	char m_data[0x24];
};

class Rva002AAEB5
{
public:
	Rva002AAEB5Record *rva002AAEB5(int index);
private:
	char m_pad000[0x324];
	Rva002AAEB5Record *m_324;
};

Rva002AAEB5Record *Rva002AAEB5::rva002AAEB5(int index)
{
	return &m_324[index];
}

// --- 0x002ABB86 (24B): one node from the freelist pool at VA 0x00DBBD2C,
// none for a count above one; 0x002ACF8A (18B): constructor running the
// rowed init.
extern FreelistPool g_freelistPool009BBD2C;

class Rva002ABB86
{
public:
	void *rva002ABB86(unsigned int count, const void *hint);
};

void *Rva002ABB86::rva002ABB86(unsigned int count, const void *)
{
	if (count > 1)
		return 0;
	return g_freelistPool009BBD2C.pop();
}

class Rva002AC026Member
{
public:
	Rva002AC026Member(void *context);
	void *init(void *context);								// 0x002AC026
private:
	void *m_head;
};

Rva002AC026Member::Rva002AC026Member(void *context)
{
	init(context);
}

// --- 0x002AD7E9 (61B): the +8 interface of a player feeds the record's
// +0x34 word to its +0x3B4 member (rowed 0x0039B668), then grants each
// science of the record's +0x38 list through Player's rowed private
// addScience; 0x002B1192 (21B): the +4 interface stores Player's rowed
// 0x002AB855 answer for the hero data.
enum ScienceType { SCIENCE_INVALID = -1 };
class CreateAHeroData;

class Rva0039B668
{
public:
	void rva0039B668(int value);							// 0x0039B668
};

struct Rva002AD7E9Record
{
	char m_pad00[0x34];
	int m_34;
	int *m_sciencesStart;
	int *m_sciencesFinish;
};

class Rva002AD7E9Base0
{
	int m_00;
};

class Rva002B1192Interface
{
public:
	void rva002B1192(CreateAHeroData *data, bool *out);
private:
	int m_00;
};

class Rva002AD7E9Interface
{
public:
	void rva002AD7E9(const Rva002AD7E9Record *record);
private:
	char m_pad000[0x3B4];
	Rva0039B668 m_3B4;
};

class Player : public Rva002AD7E9Base0, public Rva002B1192Interface, public Rva002AD7E9Interface
{
	friend class Rva002AD7E9Interface;
	friend class Rva002B1192Interface;
public:
	bool rva002AB855(CreateAHeroData *data) const;			// 0x002AB855
private:
	bool addScience(ScienceType science);					// 0x002AD661
};

void Rva002AD7E9Interface::rva002AD7E9(const Rva002AD7E9Record *record)
{
	if (record)
	{
		m_3B4.rva0039B668(record->m_34);
		for (const int *it = record->m_sciencesStart; it != record->m_sciencesFinish; ++it)
			((Player *)((char *)this - 8))->addScience((ScienceType)*it);
	}
}

void Rva002B1192Interface::rva002B1192(CreateAHeroData *data, bool *out)
{
	*out = ((Player *)((char *)this - 4))->rva002AB855(data);
}

// --- LivingWorld-region leaves: 0x002B2221 (18B) copies a pair to +0x20;
// 0x002B2260 (14B) the +8 record's +0x4C word or 0; 0x002B229B (10B) ORs
// into +0x14; 0x002B238A (17B) float setter +0x1C8; 0x002B244D (14B) the
// +0x0C field of the indexed 16-byte record at +0.
struct Rva002B2260Record
{
	char m_pad00[0x4C];
	int m_4C;
};

class Rva002B2221
{
public:
	void rva002B2221(const Rva002226A2Pair &pair);
	int rva002B2260() const;
	void rva002B229B(int bits);
	void rva002B238A(float value);
private:
	int m_00;
	int m_04;
	Rva002B2260Record *m_08;
	int m_0C;
	int m_10;
	int m_14;
	char m_pad18[0x20 - 0x18];
	Rva002226A2Pair m_20;
	char m_pad28[0x1C8 - 0x28];
	float m_1C8;
};

void Rva002B2221::rva002B2221(const Rva002226A2Pair &pair)
{
	m_20 = pair;
}

int Rva002B2221::rva002B2260() const
{
	if (m_08)
		return m_08->m_4C;
	return 0;
}

void Rva002B2221::rva002B229B(int bits)
{
	m_14 |= bits;
}

void Rva002B2221::rva002B238A(float value)
{
	m_1C8 = value;
}

class Rva002B244D
{
public:
	int *rva002B244D(int index);
private:
	Rva002A7F6CRecord m_records[1];
};

int *Rva002B244D::rva002B244D(int index)
{
	return &m_records[index].m_0C;
}

// --- 0x002B22FA (21B): 1 for a second argument of 0 or 1.
class Rva002B22FA
{
public:
	int rva002B22FA(int unused, int value);
};

int Rva002B22FA::rva002B22FA(int, int value)
{
	if (value >= 0 && value <= 1)
		return 1;
	return 0;
}

// --- 0x002B2997 (38B): when TheLivingWorldLogic's +0xC8 flag is set, the
// campaign manager's rowed 0x003B8CAC runs and the flag clears.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
class LivingWorldCampaignManager
{
public:
	bool rva003B8CAC();										// 0x003B8CAC
};

struct Rva002B2997LogicView
{
	char m_pad00[0xC8];
	bool m_C8;
};

void Rva002B2997()
{
	if (((Rva002B2997LogicView *)TheLivingWorldLogic)->m_C8)
	{
		((LivingWorldCampaignManager *)TheCampaignManager)->rva003B8CAC();
		((Rva002B2997LogicView *)TheLivingWorldLogic)->m_C8 = false;
	}
}

// --- 0x002B29EA (14B): stores the second argument at +0x38 of the first.
struct Rva002B29EATarget
{
	char m_pad00[0x38];
	int m_38;
};

class Rva002B29EA
{
public:
	void rva002B29EA(Rva002B29EATarget *target, int value);
};

void Rva002B29EA::rva002B29EA(Rva002B29EATarget *target, int value)
{
	target->m_38 = value;
}

// --- 0x002B2B3F (28B): the current item's +0x88 flag when the +0xB0
// region manager exists; 0x002B2B94 (11B): the manager's rowed
// UpdateBattleMarkers.
struct Rva002B3740Item
{
	char m_pad00[0x88];
	bool m_88;
};

class LivingWorldRegionManager
{
public:
	void UpdateBattleMarkers();								// 0x0020EBA0
};

class Rva002E2903Player;
struct Rva002B488EResult;

class Rva002BA8F1Logic
{
public:
	Rva002B3740Item *rva002B2B2D();							// 0x002B2B2D
	void setLocal(Rva002E2903Player *player);				// 0x002B38F7
	Rva002B488EResult *rva002B488E(int value);				// 0x002B488E
	bool rva002B2B3F();
	void rva002B2B94();
private:
	char m_pad00[0x8C];
	Rva002E2903Player **m_playersStart;
	Rva002E2903Player **m_playersFinish;
	Rva002E2903Player **m_playersEnd;
	Rva002E2903Player *m_98;
	char m_pad9C[0xB0 - 0x9C];
	LivingWorldRegionManager *m_B0;
};

bool Rva002BA8F1Logic::rva002B2B3F()
{
	if (m_B0)
	{
		Rva002B3740Item *item = rva002B2B2D();
		if (item)
			return item->m_88;
	}
	return false;
}

void Rva002BA8F1Logic::rva002B2B94()
{
	m_B0->UpdateBattleMarkers();
}

// --- 0x002B2B9F (11B): TheScriptEngine's slot 10.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

class Rva002B2B9FView
{
public:
	GAP_V10(0)
	virtual void slot10();
};

void Rva002B2B9F()
{
	((Rva002B2B9FView *)TheScriptEngine)->slot10();
}

// --- 0x002B30D9 (19B): the +0x154 pointer vector is not empty;
// 0x002B30EC (15B): count of the 8-byte records of the +0x40 vector of the
// +0x78 object; 0x002B3150 (11B): pre-increments +0x9C.
static __forceinline bool GapVoidVectorAny(const GapVoidVector *gapVoidVector) { return gapVoidVector->m_start != gapVoidVector->m_finish; }

struct Rva002B30ECVector
{
	Rva002226A2Pair *m_start;
	Rva002226A2Pair *m_finish;
};

struct Rva002B30ECInner
{
	char m_pad00[0x40];
	Rva002B30ECVector m_40;
};

class Rva002B30D9
{
public:
	bool rva002B30D9() const;
	int rva002B30EC() const;
	int rva002B3150();
private:
	char m_pad000[0x78];
	Rva002B30ECInner *m_78;
	char m_pad07C[0x9C - 0x7C];
	int m_9C;
	char m_pad0A0[0x154 - 0xA0];
	GapVoidVector m_154;
};

bool Rva002B30D9::rva002B30D9() const
{
	return GapVoidVectorAny(&m_154);
}

static __forceinline int Rva002B30ECCount(const Rva002B30ECVector *v) { return v->m_finish - v->m_start; }

int Rva002B30D9::rva002B30EC() const
{
	return Rva002B30ECCount(&m_78->m_40);
}

int Rva002B30D9::rva002B3150()
{
	return ++m_9C;
}

// --- 0x002B386A (35B): names the campaign's GUI image by the campaign
// manager's +0x2C evil flag.
struct Rva002B386AManagerView
{
	char m_pad00[0x2C];
	bool m_evil;
};

class Rva002B386A
{
public:
	void rva002B386A(AsciiString *name);
};

void Rva002B386A::rva002B386A(AsciiString *name)
{
	if (((Rva002B386AManagerView *)TheCampaignManager)->m_evil)
		name->set("GUI:EvilCampaign");
	else
		name->set("GUI:GoodCampaign");
}

// --- 0x002B3DA4 (14B, cdecl): the rowed 0x002B3D81 value divided by the
// word at VA 0x00DBA4E4.
int rva002B3D81();
extern int BfmeLogicFramesPerSecond;

unsigned int Rva002B3DA4()
{
	return (unsigned int)rva002B3D81() / (unsigned int)BfmeLogicFramesPerSecond;
}

// --- 0x002B4404 (12B, cdecl): the rowed 0x002B2F49 with 0 on the argument.
class Rva002B2F49
{
public:
	void *rva002B2F49(unsigned int value);					// 0x002B2F49
};

void *Rva002B4404(Rva002B2F49 *target)
{
	return target->rva002B2F49(0);
}

// --- 0x002B4640 (16B): the indexed word of the array *(+0x170).
class Rva002B4640
{
public:
	int rva002B4640(int index) const;
private:
	char m_pad000[0x170];
	int *m_170;
};

int Rva002B4640::rva002B4640(int index) const
{
	return m_170[index];
}

// --- 0x002B4E6D (22B): copies the argument's +0x14 flag to +0xC8, then the
// rowed 0x002B4CED with it.
struct Rva002B4E6DArg
{
	char m_pad00[0x14];
	bool m_14;
};

class Rva002B4CED
{
public:
	void rva002B4CED(void *arg);							// 0x002B4CED
	void rva002B4E6D(Rva002B4E6DArg *arg);
private:
	char m_pad00[0xC8];
	bool m_C8;
};

void Rva002B4CED::rva002B4E6D(Rva002B4E6DArg *arg)
{
	m_C8 = arg->m_14;
	rva002B4CED(arg);
}

// --- 0x002B685D (24B): the rowed 0x002B5B55 on the rowed 0x002B488E result.
struct Rva002B488EResult;
class Rva002B5B55Arg;

class Rva002B685D
{
public:
	void rva002B685D(int value);
};

class Rva002B5B55
{
public:
	void rva002B5B55(Rva002B5B55Arg *arg);					// 0x002B5B55
};

void Rva002B685D::rva002B685D(int value)
{
	((Rva002B5B55 *)this)->rva002B5B55((Rva002B5B55Arg *)((Rva002BA8F1Logic *)this)->rva002B488E(value));
}

// --- 0x002B77A2 (11B): clears the +0xF0 unicode-string list.
namespace _STL
{
	template <class T, class A> class _List_base
	{
	public:
		void clear();
	private:
		void *m_node;
	};
}

class Rva002B77A2
{
public:
	void rva002B77A2();
private:
	char m_pad00[0xF0];
	_STL::_List_base<UnicodeString, _STL::allocator<UnicodeString> > m_F0;
};

void Rva002B77A2::rva002B77A2()
{
	m_F0.clear();
}

// Unattempted scalar leaves from the native gap audit. Each complete body
// starts after a preceding body's RET or padding and ends in its own RET.
// Native accesses establish the offsets and the 32-bit/byte ABI below;
// original classes, field meanings and signedness remain unasserted. These
// neutral views describe only the observed operations, as above.
class Rva000EF876
{
public:
 void rva000EF876();
private:
 char pad00[7]; unsigned char byte07;
};
// 000EF876..000EF87B: set bit 0 of byte +7; RET0.
void Rva000EF876::rva000EF876()
{
 byte07|=1;
}

class Rva000B22A9
{
public:
 void rva000B22A9(unsigned char value);
private:
 char pad00[0x30]; unsigned char byte30;
};
// 000B22A9..000B22B3: copy low argument byte to +30; RET4.
void Rva000B22A9::rva000B22A9(unsigned char value)
{
 byte30=value;
}

class Rva00234288
{
public:
 unsigned rva00234288() const;
private:
 unsigned word00, word04;
};
// 00234288..0023428D: return +4 word plus one without storing; RET0.
unsigned Rva00234288::rva00234288() const
{
 return word04+1;
}

class Rva004EA03E
{
public:
 void rva004EA03E();
private:
 char pad00[0x64]; unsigned char byte64;
 char pad65[7]; unsigned word6C;
};
// 004EA03E..004EA046: increment word +6C then clear byte +64; RET0.
void Rva004EA03E::rva004EA03E()
{
 ++word6C;
 byte64=0;
}

// --- 0x00235A00 (14B, RET4): a constructor copying its one word argument
// into both +0 and +4 and returning this (twin skeleton of
// Rva006CD500WordPair 0x006CD500). It follows the MultiPlayMults getters; the
// owner and the word's meaning are unknown.
class Rva00235A00WordPair
{
public:
	Rva00235A00WordPair(unsigned int word);
	unsigned int m_word0;
	unsigned int m_word4;
};

Rva00235A00WordPair::Rva00235A00WordPair(unsigned int word)
	: m_word0(word), m_word4(word)
{
}

// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers (seventh
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.

// --- 0x0033A7F7 (54B, cdecl): population count of a word.
int popCount(unsigned int bits)
{
	bits = bits - ((bits >> 1) & 0x55555555);
	bits = ((bits >> 2) & 0x33333333) + (bits & 0x33333333);
	return (((bits >> 4) + bits) & 0x0F0F0F0F) * 0x01010101 >> 24;
}

// --- 0x003F7141 (54B): all five +0x08..+0x18 values under 9999 with the
// +0x1C and +0x30 words set (the two arguments are unused).
class Rva003F7141
{
public:
	int rva003F7141(int a, int b) const;
private:
	char m_pad[8];
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	float m_18;
	int m_1C;
	char m_pad20[0x30 - 0x20];
	int m_30;
};

int Rva003F7141::rva003F7141(int, int) const
{
	const float limit = 9999.0f;
	int result = 0;
	if (m_08 < limit && m_0C < limit && m_10 < limit && m_14 < limit && m_18 < limit && m_1C && m_30)
		result = 1;
	return result;
}

// --- 0x004FBC17 (54B): vtable 0x00C634E4 over cleared words, a -1 id,
// three zero floats and three cleared flags.
struct Rva004FBC17Base
{
	int m_04;
	Rva004FBC17Base() : m_04(0) {}
};

struct Rva004FBC17Slot
{
	int m_10;
	int m_14;
	Rva004FBC17Slot() { m_14 = -1; m_10 = 0; }
};

class Rva004FBC17 : public Rva004FBC17Base
{
public:
	Rva004FBC17();
	virtual ~Rva004FBC17() {}
private:
	int m_08;
	int m_0C;
	Rva004FBC17Slot m_10;
	float m_18;
	float m_1C;
	float m_20;
	bool m_24;
	bool m_25;
	bool m_26;
};

Rva004FBC17::Rva004FBC17() : m_08(0), m_0C(0), m_18(0.0f), m_1C(0.0f), m_20(0.0f), m_24(false), m_25(false), m_26(false)
{
}

// --- 0x0055B417 (54B): types 3 and 7 need an empty +0x14 word in the
// current (+0x58) 8-byte record and a +0x50 value under 0.01; type 4 never;
// any other type always.
struct Rva0055B417Record
{
	int m_00;
	int m_04;
};

class Rva0055B417
{
public:
	bool rva0055B417(int type) const;
private:
	char m_pad[0x14];
	Rva0055B417Record m_records[7];							// +0x14
	char m_pad4C[0x50 - 0x4C];
	float m_50;
	int m_54;
	int m_current;											// +0x58
};

bool Rva0055B417::rva0055B417(int type) const
{
	switch (type)
	{
	case 3:
	case 7:
		return m_records[m_current].m_00 == 0 && m_50 < 0.01f;
	case 4:
		return false;
	}
	return true;
}

// --- 0x00261603 (55B): whether the +0x14 geometry's intersection test of
// the +0x08 point and +0x18 radius against the object's geometry (+0xA8),
// point (+0x38) and radius (+0x44) agrees with the +0x1C flag.
struct Coord3D;

class GeometryInfo
{
public:
	bool CollidesWith(const Coord3D &pos, float radius, const GeometryInfo &other, const Coord3D &otherPos, float otherRadius) const;	// 0x006BEB80
};

struct Rva00261603Object
{
	char m_pad[0x38];
	char m_pos[0x0C];										// +0x38 Coord3D
	float m_44;
	char m_pad48[0xA8 - 0x48];
	char m_geometry[4];										// +0xA8 GeometryInfo
};

class Object;
// Slot 1 (allow) of partition filter vftable 0x00BFB1B8.
class Rva00261603Filter
{
public:
	virtual ~Rva00261603Filter();
	virtual bool allow(Object *object);
private:
	char m_pad[4];
	char m_pos[0x0C];										// +0x08 Coord3D
	GeometryInfo *m_geometry;								// +0x14
	float m_radius;											// +0x18
	bool m_inside;											// +0x1C
};

bool Rva00261603Filter::allow(Object *object)
{
	const Rva00261603Object *obj = (const Rva00261603Object *)object;
	return m_geometry->CollidesWith(*(const Coord3D *)m_pos, m_radius, *(const GeometryInfo *)obj->m_geometry,
		*(const Coord3D *)obj->m_pos, obj->m_44) == m_inside;
}

// --- 0x00301E90 (50B, cdecl): two eight-entry key arrays (0x14-byte keys)
// are equal when no pair differs (rowed 0x00301E7B).
struct BfmeKeySX
{
	char m_data[0x14];
};

int Rva00301E7BNotEqual(const BfmeKeySX &a, const BfmeKeySX &b);	// 0x00301E7B

bool Rva00301E90(const BfmeKeySX *leftKeys, const BfmeKeySX *rightKeys)
{
	for (int i = 0; i < 8; ++i)
		if ((unsigned char)Rva00301E7BNotEqual(leftKeys[i], rightKeys[i]))
			return false;
	return true;
}

// --- 0x00341BF9 (26B): restart the +0x20 timer at the current logic frame,
// one second later when it was already running; returns 0.
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva00341BF9Logic
{
	char m_pad[0x40];
	int m_frame;
};
extern int BfmeLogicFramesPerSecond;

class Rva00341BF9
{
public:
	int restartTimer();
private:
	char m_pad[0x20];
	int m_20;
};

int Rva00341BF9::restartTimer()
{
	int frame = ((Rva00341BF9Logic *)TheGameLogic)->m_frame;
	if (m_20)
		frame += BfmeLogicFramesPerSecond;
	m_20 = frame;
	return 0;
}

// --- 0x00341C13 (29B): vtable 0x00C122F0 constructor over a cleared +0x04
// storing its two arguments.
class Rva00341C13
{
public:
	Rva00341C13(int a, int b);
	virtual ~Rva00341C13() {}
private:
	int m_04;
	int m_08;
	int m_0C;
};

Rva00341C13::Rva00341C13(int a, int b) : m_04(0), m_08(a), m_0C(b)
{
}

// --- 0x00367422 (55B): add a point into the +0x56C point.
struct Rva00367422Point
{
	float x;
	float y;
	float z;
	void add(const Rva00367422Point *a) { x += a->x; y += a->y; z += a->z; }
};

class Rva00367422
{
public:
	void addDelta(const Rva00367422Point *delta);
private:
	char m_pad[0x56C];
	Rva00367422Point m_56C;
};

void Rva00367422::addDelta(const Rva00367422Point *delta)
{
	m_56C.add(delta);
}

// --- 0x0050B4E2 (55B): the rowed 0x0050B479, then for a positive +0x12C
// value virtual slot 6 with the object's +0x38 point.
class Object;

class Made002CCB04
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5();
	virtual void s6(void *a, void *pos);
	void rva0050B479(void *a, Object *obj);					// 0x0050B479
	void rva0050B4E2(void *a, Object *obj);
private:
	char m_pad[0x12C - 4];
	float m_12C;
};

void Made002CCB04::rva0050B4E2(void *a, Object *obj)
{
	rva0050B479(a, obj);
	if (m_12C > 0.0f)
		s6(a, (char *)obj + 0x38);
}

// --- 0x0050E952 (56B): describe the +0x20 value into the buffer ("0"
// first; "%d" unless only the default is wanted).
extern "C" unsigned char *__cdecl _mbscpy(unsigned char *dest, const unsigned char *src);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *format, ...);

class Rva0050E952
{
public:
	void describeValue(int unused, char *buffer, bool defaultOnly);
private:
	char m_pad[0x20];
	int m_20;
};

void Rva0050E952::describeValue(int, char *buffer, bool defaultOnly)
{
	_mbscpy((unsigned char *)buffer, (const unsigned char *)"0");
	if (!defaultOnly)
		_snprintf(buffer, 255, "%d", m_20);
}

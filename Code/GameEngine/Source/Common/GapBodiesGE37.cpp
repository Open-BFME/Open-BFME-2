// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (thirty-seventh
// batch; see GapBodiesGE01.cpp). Each begins after its neighbour's padding or
// ret and ends in its own ret or tail jump. Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.

#include <mbstring.h>

class AsciiString;
class Vector2;

struct GapVec3
{
	float x;
	float y;
	float z;
};

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> > class vector
	{
	public:
		vector() {}
		vector(const vector &that);
		vector &operator=(const vector &that);
		T *erase(T *first, T *last);
		void clear() { erase(m_start, m_finish); }
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

// --- 0x000CB103 (25B): bit n of the +0x44 mask; 0x000CB11C (19B): add to
// the +0x2C float.
class Rva000CB103
{
public:
	bool isBitSet(int bit) const;
	void rva000CB11C(float delta);
private:
	char m_pad00[0x2C];
	float m_2C;
	char m_pad30[0x44 - 0x30];
	unsigned int m_44;
};

bool Rva000CB103::isBitSet(int bit) const
{
	return (m_44 & (1 << bit)) != 0;
}

void Rva000CB103::rva000CB11C(float delta)
{
	m_2C += delta;
}

// --- 0x000CDF71 (20B) / 0x000CDF85 (17B): store the +0x130 triple / the
// +0x13C float.
class Rva000CDF71
{
public:
	void rva000CDF71(const GapVec3 &value);
	void rva000CDF85(float value);
private:
	char m_pad00[0x130];
	GapVec3 m_130;
	float m_13C;
};

void Rva000CDF71::rva000CDF71(const GapVec3 &value)
{
	m_130 = value;
}

void Rva000CDF71::rva000CDF85(float value)
{
	m_13C = value;
}

// --- 0x000CF8EE (17B): the +0xD0 float; 0x000CF8FF (30B): set or clear
// bits of the +0xC8 mask.
class Rva000CF8EE
{
public:
	void rva000CF8EE(float value);
	void rva000CF8FF(unsigned int bits, bool on);
private:
	char m_pad00[0xC8];
	unsigned int m_C8;
	int m_CC;
	float m_D0;
};

void Rva000CF8EE::rva000CF8EE(float value)
{
	m_D0 = value;
}

void Rva000CF8EE::rva000CF8FF(unsigned int bits, bool on)
{
	if (on)
		m_C8 |= bits;
	else
		m_C8 &= ~bits;
}

// --- 0x000D1112 (18B): stream an entry's +8 name into an asset list through
// the rowed AssetList00208F90::operator<< 0x0006C950.
struct AssetList00208F90
{
	AssetList00208F90 &operator<<(const AsciiString &name);
};

struct GapNamedEntry
{
	int m_00;
	int m_04;
	char m_name[4];											// +0x08 (an AsciiString)
};

AssetList00208F90 &streamName(const GapNamedEntry *entry, AssetList00208F90 &list)
{
	return list << *(const AsciiString *)entry->m_name;
}

// --- 0x000D204B (20B): UV array i of the +0x94 material description through
// the rowed MeshMatDescClass::Get_UV_Array_By_Index 0x000D1F40.
class MeshMatDescClass
{
public:
	Vector2 *Get_UV_Array_By_Index(int index, bool create);
};

class Rva000D204B
{
public:
	Vector2 *getUvArray(int index);
private:
	char m_pad00[0x94];
	MeshMatDescClass *m_matDesc;							// +0x94
};

Vector2 *Rva000D204B::getUvArray(int index)
{
	return m_matDesc->Get_UV_Array_By_Index(index, false);
}

// --- 0x000E01F4 (20B): hash of a two-word key (xor) modulo n; 0x000E0208
// (29B): the same modulo the +4 bucket vector's size.
struct GapPairKey
{
	unsigned int a;
	unsigned int b;
};

class Rva000E01F4
{
public:
	unsigned int rva000E01F4(const GapPairKey *key, unsigned int bucketCount) const;
	unsigned int rva000E0208(const GapPairKey *key) const;
private:
	int m_00;
	void **m_bucketsStart;									// +0x04
	void **m_bucketsFinish;									// +0x08
};

unsigned int Rva000E01F4::rva000E01F4(const GapPairKey *key, unsigned int bucketCount) const
{
	return (key->b ^ key->a) % bucketCount;
}

unsigned int Rva000E01F4::rva000E0208(const GapPairKey *key) const
{
	unsigned int n = m_bucketsFinish - m_bucketsStart;
	return (key->b ^ key->a) % n;
}

// --- 0x000E0254 (11B): clear a leading Coord3D vector through its rowed
// erase 0x00081A24.
struct Coord3D;

class Rva000E0254
{
public:
	void clearPoints();
private:
	_STL::vector<Coord3D> m_points;
};

void Rva000E0254::clearPoints()
{
	m_points.clear();
}

// --- 0x000E3BEC (18B): copy construction through the rowed assignment
// 0x000E3A8D.
class Rva000E3A8D
{
public:
	Rva000E3A8D(const Rva000E3A8D &that);
	Rva000E3A8D &rva000E3A8D(const Rva000E3A8D &that);	// 0x000E3A8D
};

Rva000E3A8D::Rva000E3A8D(const Rva000E3A8D &that)
{
	rva000E3A8D(that);
}

// --- 0x000E43CE (17B), 0x00106F71 (17B): float setters at +0x88 / +0x80.
class Rva000E43CE
{
public:
	void rva000E43CE(float value);
	void rva00106F71(float value);
private:
	char m_pad00[0x80];
	float m_80;
	char m_pad84[0x88 - 0x84];
	float m_88;
};

void Rva000E43CE::rva000E43CE(float value)
{
	m_88 = value;
}

void Rva000E43CE::rva00106F71(float value)
{
	m_80 = value;
}

// --- 0x000EF99D (6B): _mbslen forwarder; 0x000EF9A3 (5B): the second
// argument; 0x000EF9A8 (6B) / 0x000EF9AE (20B): StringClass's header ahead
// of the buffer and its length store unless the buffer is m_EmptyString.

unsigned int rva000EF99D(const unsigned char *s)
{
	return _mbslen(s);
}

int rva000EF9A3(int, int second)
{
	return second;
}

class Rva000EF9A8;

class StringClass
{
	friend class Rva000EF9A8;
	static char *m_EmptyString;
};

struct GapStringHeader
{
	int m_allocated;
	int m_length;
};

class Rva000EF9A8
{
public:
	GapStringHeader *getHeader() const;
	void setLength(int length);
private:
	char *m_buffer;
};

GapStringHeader *Rva000EF9A8::getHeader() const
{
	return (GapStringHeader *)(m_buffer - sizeof(GapStringHeader));
}

void Rva000EF9A8::setLength(int length)
{
	if (m_buffer != StringClass::m_EmptyString)
		getHeader()->m_length = length;
}

// --- 0x000EFAEE (31B): zero +0x58/+0x5C, 20.0f at +0x60, clear +0x64.
class Rva000EFAEE
{
public:
	void rva000EFAEE();
private:
	char m_pad00[0x58];
	float m_58;
	float m_5C;
	float m_60;
	bool m_64;
};

void Rva000EFAEE::rva000EFAEE()
{
	m_58 = 0.0f;
	m_5C = 0.0f;
	m_60 = 20.0f;
	m_64 = false;
}

// --- 0x000FD58A (45B): vtable 0x00BCF410 over two zero words, four zero
// bytes, two zero floats and a zero word.
class Rva000FD58A
{
public:
	Rva000FD58A();
	virtual ~Rva000FD58A() {}
private:
	int m_04;
	int m_08;
	unsigned char m_0C;
	unsigned char m_0D;
	unsigned char m_0E;
	unsigned char m_0F;
	float m_10;
	float m_14;
	int m_18;
};

Rva000FD58A::Rva000FD58A() : m_04(0), m_08(0), m_0C(0), m_0D(0), m_0E(0), m_0F(0), m_10(0.0f), m_14(0.0f), m_18(0)
{
}

// --- 0x001021DA (18B): copy construction of a leading EvaMessageInfo vector
// through its rowed assignment 0x001020BA; 0x001021EC (11B): clear it
// through the rowed range erase 0x00102087.
struct EvaMessageInfo;

class Rva001021DA
{
public:
	Rva001021DA(const Rva001021DA &that);
private:
	_STL::vector<EvaMessageInfo> m_messages;
};

Rva001021DA::Rva001021DA(const Rva001021DA &that)
{
	m_messages = that.m_messages;
}

class Rva00102087
{
public:
	EvaMessageInfo *rva00102087(EvaMessageInfo *first, EvaMessageInfo *last);	// 0x00102087
	void clearMessages();
private:
	EvaMessageInfo *m_start;
	EvaMessageInfo *m_finish;
};

void Rva00102087::clearMessages()
{
	rva00102087(m_start, m_finish);
}

// --- 0x00102542 (23B): the smaller of two floats.
float rva00102542(float a, float b)
{
	if (b > a)
		return a;
	return b;
}

// --- 0x00104E8E (49B): update the +0xC8 / +0xCC words, marking +0xD5 when
// either changes.
class Rva00104E8E
{
public:
	void rva00104E8E(int a, int b);
private:
	__forceinline void update(int &field, int value)
	{
		if (field != value)
		{
			field = value;
			m_D5 = true;
		}
	}
	char m_pad00[0xC8];
	int m_C8;
	int m_CC;
	char m_padD0[0xD5 - 0xD0];
	bool m_D5;
};

void Rva00104E8E::rva00104E8E(int a, int b)
{
	update(m_C8, a);
	update(m_CC, b);
}

// --- 0x00108492 (21B) / 0x001084A7 (14B): read the +0x58/+0x5C floats /
// store the +0x60 float; 0x001084B5 (33B) / 0x001084FD (29B): store / read
// the same pair on the i-th child in the +0x58 pointer table.
class Rva00108492
{
public:
	void rva00108492(float *a, float *b) const;
	void rva001084A7(float value);
private:
	char m_pad00[0x58];
	float m_58;
	float m_5C;
	float m_60;
};

void Rva00108492::rva00108492(float *a, float *b) const
{
	*a = m_58;
	*b = m_5C;
}

void Rva00108492::rva001084A7(float value)
{
	m_60 = value;
}

struct GapChildFloats
{
	char m_pad00[0x58];
	float m_58;
	float m_5C;
};

class Rva001084B5
{
public:
	void rva001084B5(int i, float a, float b);
	void rva001084FD(int i, float *a, float *b) const;
private:
	char m_pad00[0x58];
	GapChildFloats *m_children[1];							// +0x58
};

void Rva001084B5::rva001084B5(int i, float a, float b)
{
	GapChildFloats *child = m_children[i];
	child->m_58 = a;
	child->m_5C = b;
}

void Rva001084B5::rva001084FD(int i, float *a, float *b) const
{
	const GapChildFloats *child = m_children[i];
	*a = child->m_58;
	*b = child->m_5C;
}

// --- 0x0010E664 (18B): copy construction of a leading Rva0007BB16Record
// vector through its rowed copy constructor 0x0010E604.
struct Rva0007BB16Record;

class Rva0010E664
{
public:
	Rva0010E664(const Rva0010E664 &that);
private:
	_STL::vector<Rva0007BB16Record> m_records;
};

Rva0010E664::Rva0010E664(const Rva0010E664 &that) : m_records(that.m_records)
{
}

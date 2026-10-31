// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (thirty-fifth
// batch; see GapBodiesGE01.cpp). Each begins after its neighbour's padding or
// ret and ends in its own ret or tail jump. Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.

struct GapVec3
{
	float x;
	float y;
	float z;
};

// --- 0x00094C09 (32B): copy out the +0xD4 triple and the +0xE0 float.
class Rva00094C09
{
public:
	void rva00094C09(GapVec3 *pos, float *angle) const;
private:
	char m_pad00[0xD4];
	GapVec3 m_pos;											// +0xD4
	float m_angle;											// +0xE0
};

void Rva00094C09::rva00094C09(GapVec3 *pos, float *angle) const
{
	*pos = m_pos;
	*angle = m_angle;
}

// --- 0x00098529 (19B): the +0x20 triple returned by value.
class Rva00098529
{
public:
	GapVec3 rva00098529() const;
private:
	char m_pad00[0x20];
	GapVec3 m_20;
};

GapVec3 Rva00098529::rva00098529() const
{
	return m_20;
}

// --- 0x0009AA2D (27B): integer pair difference returned by value.
struct GapIPair
{
	int x;
	int y;
	GapIPair() {}
	GapIPair(const GapIPair &o) : x(o.x), y(o.y) {}
};

GapIPair subtractPoints(GapIPair a, const GapIPair &b)
{
	GapIPair result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

// --- 0x0009B254 (18B): element count of the +0x8C pointer vector.
struct GapPtrVector
{
	void **m_start;
	void **m_finish;
	int size() const { return m_finish - m_start; }
};

class Rva0009B254
{
public:
	int rva0009B254() const;
private:
	char m_pad00[0x8C];
	GapPtrVector m_items;									// +0x8C
};

int Rva0009B254::rva0009B254() const
{
	return m_items.size();
}

// --- 0x000A8F13 (15B), 0x000A8F22 / 0x000A8F2C (10B each): setters of
// g_Va00DEC49C and the 0x00DB5FB0 / 0x00DB5FC8 words.
extern float g_Va00DEC49C;
extern int g_00DB5FB0;
extern int g_Va00DB5FC8;

void rva000A8F13(float z)
{
	g_Va00DEC49C = z;
}

void rva000A8F22(int value)
{
	g_00DB5FB0 = value;
}

void rva000A8F2C(int value)
{
	g_Va00DB5FC8 = value;
}

// --- 0x000ABCC7 (57B): eight zero floats, two zero bytes and a zero word.
class Rva000ABCC7
{
public:
	Rva000ABCC7();
private:
	float m_f[8];
	unsigned char m_20;
	unsigned char m_21;
	unsigned short m_22;
};

Rva000ABCC7::Rva000ABCC7()
{
	m_f[0] = 0.0f;
	m_f[1] = 0.0f;
	m_f[2] = 0.0f;
	m_f[3] = 0.0f;
	m_f[4] = 0.0f;
	m_f[5] = 0.0f;
	m_f[6] = 0.0f;
	m_f[7] = 0.0f;
	m_20 = 0;
	m_21 = 0;
	m_22 = 0;
}

// --- 0x000AC296 (96B): mark every present +0xB0 object (+0x2AB8/+0x2ABC)
// and every 0x28-byte record from +0x80CC (+0x18/+0x1C) with 2; returns 0x800.
struct GapMarked
{
	char m_pad00[0x2AB8];
	int m_2AB8;
	int m_2ABC;
};

struct GapRecord28
{
	char m_pad00[0x18];
	int m_18;
	int m_1C;
	char m_pad20[0x28 - 0x20];
};

class Rva000AC296
{
public:
	int rva000AC296(int unused);
private:
	char m_pad00[0xA8];
	int m_objectCount;										// +0xA8
	int m_AC;
	GapMarked *m_objects[1];								// +0xB0
	char m_padB4[0x80C8 - 0xB4];
	int m_recordCount;										// +0x80C8
	GapRecord28 m_records[1];								// +0x80CC
};

int Rva000AC296::rva000AC296(int unused)
{
	int i;
	for (i = 0; i < m_objectCount; ++i)
	{
		if (m_objects[i])
		{
			m_objects[i]->m_2AB8 = 2;
			m_objects[i]->m_2ABC = 2;
		}
	}
	for (i = 0; i < m_recordCount; ++i)
	{
		m_records[i].m_18 = 2;
		m_records[i].m_1C = 2;
	}
	return 0x800;
}

// --- 0x000ADC81 (18B): copy constructor of a holder whose first member is
// an AssetReference (rowed copy ctor 0x000424BB).
class AssetReference
{
public:
	AssetReference(const AssetReference &that);
};

class Rva000ADC81
{
public:
	Rva000ADC81(const Rva000ADC81 &that);
private:
	AssetReference m_ref;
};

Rva000ADC81::Rva000ADC81(const Rva000ADC81 &that) : m_ref(that.m_ref)
{
}

// --- 0x000ADC93 (80B): a height-map cell's class through the rowed
// WorldHeightMap::rva000AC4C6, or -1 off the map or (unless forced) when
// either +0x9C / +0xA4 per-cell word is set.
class WorldHeightMap
{
public:
	int rva000AC4C6(int value);								// 0x000AC4C6
	int rva000ADC93(int x, int y, bool force);
private:
	char m_pad00[8];
	int m_width;											// +0x08
	char m_pad0C[0x20 - 0x0C];
	int m_cellCount;										// +0x20
	char m_pad24[0x98 - 0x24];
	short *m_cells;											// +0x98
	int *m_9C;												// +0x9C
	int m_A0;
	int *m_A4;												// +0xA4
};

int WorldHeightMap::rva000ADC93(int x, int y, bool force)
{
	int index = m_width * y + x;
	if (index >= 0 && index < m_cellCount)
	{
		int value = m_cells[index];
		if (force || (m_9C[index] == 0 && m_A4[index] == 0))
			return rva000AC4C6(value);
	}
	return -1;
}

// --- 0x000B1984 (29B) / 0x000B2308 (33B): reset a flags word to bit 0 (bits
// 31 and 0 kept, the rest cleared), store +4 and clear +8/+0x0C; 0x000B2329
// (18B): keep only bit 31 and clear the rest; 0x000B233B (6B): low three
// bits; 0x000B2349 (24B): set bit 30.
struct GapFlagBits
{
	unsigned int low : 3;
	unsigned int mid : 27;
	unsigned int bit30 : 1;
	unsigned int bit31 : 1;
};

class Rva000B1984
{
public:
	void rva000B1984(int value);
	Rva000B1984 *rva000B2308(int value);
	void rva000B2329();
	unsigned int rva000B233B() const;
	unsigned char rva000B2341() const;
	void rva000B2349(bool on);
private:
	union
	{
		unsigned int m_word;
		GapFlagBits m_bits;
	};
	int m_04;
	int m_08;
	int m_0C;
};

void Rva000B1984::rva000B1984(int value)
{
	m_08 = 0;
	m_0C = 0;
	m_word = (m_word & 0x80000001) | 1;
	m_04 = value;
}

Rva000B1984 *Rva000B1984::rva000B2308(int value)
{
	m_08 = 0;
	m_0C = 0;
	m_word = (m_word & 0x80000001) | 1;
	m_04 = value;
	return this;
}

void Rva000B1984::rva000B2329()
{
	m_word &= 0x80000000;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
}

unsigned int Rva000B1984::rva000B233B() const
{
	return m_bits.low;
}

unsigned char Rva000B1984::rva000B2341() const
{
	unsigned char val = m_word >> 30;
	val &= 1;
	return val;
}

void Rva000B1984::rva000B2349(bool on)
{
	m_bits.bit30 = on ? 1 : 0;
}

// --- 0x000B2273 (19B): any of the given bits in the +0x437 byte.
class Rva000B2273
{
public:
	bool rva000B2273(unsigned char bits) const;
private:
	char m_pad00[0x437];
	unsigned char m_437;
};

bool Rva000B2273::rva000B2273(unsigned char bits) const
{
	return (m_437 & bits) != 0;
}

// --- 0x000B22F3 (21B): float +0x20 of the optional +4 object.
struct GapFloat20
{
	char m_pad00[0x20];
	float m_20;
};

class Rva000B22F3
{
public:
	void rva000B22F3(float value);
private:
	int m_00;
	GapFloat20 *m_target;									// +0x04
};

void Rva000B22F3::rva000B22F3(float value)
{
	if (m_target)
		m_target->m_20 = value;
}

// --- 0x000B29B2 (17B): clear a word and two floats.
class Rva000B29B2
{
public:
	void rva000B29B2();
private:
	int m_00;
	float m_04;
	float m_08;
};

void Rva000B29B2::rva000B29B2()
{
	m_00 = 0;
	m_04 = 0.0f;
	m_08 = 0.0f;
}

// --- 0x000B2D3A (19B): store +0x15C of an optional object.
struct GapWord15C
{
	char m_pad00[0x15C];
	int m_15C;
};

void rva000B2D3A(GapWord15C *target, int value)
{
	if (target)
		target->m_15C = value;
}

// --- 0x000B4122 (27B): a dereferenced word and two words.
class Rva000B4122
{
public:
	Rva000B4122(const int *a, int b, int c);
private:
	int m_a;
	int m_b;
	int m_c;
};

Rva000B4122::Rva000B4122(const int *a, int b, int c) : m_a(*a), m_b(b), m_c(c)
{
}

// --- 0x000B4299 (20B): assign a seven-word block, returning this;
// 0x000B42AD (29B): build from a four-word and a three-word block.
struct GapWords7
{
	int w[7];
};

struct GapWords4
{
	int w[4];
};

class Rva000B4299
{
public:
	Rva000B4299 *rva000B4299(const GapWords7 &value);
private:
	GapWords7 m_value;
};

Rva000B4299 *Rva000B4299::rva000B4299(const GapWords7 &value)
{
	m_value = value;
	return this;
}

class Rva000B42AD
{
public:
	Rva000B42AD(const GapWords4 &a, const GapVec3 &b);
private:
	GapWords4 m_a;
	GapVec3 m_b;
};

Rva000B42AD::Rva000B42AD(const GapWords4 &a, const GapVec3 &b) : m_a(a), m_b(b)
{
}

// --- 0x000B4670 (18B): store a value into the slot the rowed 0x000B2361
// picks for a key.
class Rva000B2361
{
public:
	int *rva000B2361(int key);								// 0x000B2361
	void rva000B4670(int value, int key);
};

void Rva000B2361::rva000B4670(int value, int key)
{
	*rva000B2361(key) = value;
}

// --- 0x000B69BD (27B): four zero words, a zero float, a zero byte;
// 0x000B69D8 (18B): slot 4 (+0x10) of the optional +0x1AC object.
class GapSlot4View
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void slot4(int value);
};

class Rva000B69BD
{
public:
	Rva000B69BD();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	bool m_14;
};

Rva000B69BD::Rva000B69BD() : m_00(0), m_04(0), m_08(0), m_0C(0), m_10(0.0f), m_14(false)
{
}

class Rva000B69D8
{
public:
	void rva000B69D8(int value);
private:
	char m_pad00[0x1AC];
	GapSlot4View *m_1AC;
};

void Rva000B69D8::rva000B69D8(int value)
{
	GapSlot4View *target = m_1AC;
	if (target)
		target->slot4(value);
}

// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// Float-handling straight-line vtable slot bodies below 0x00400000 that
// tools/vftable_map.py reports with no ledger owner (--unclaimed); the
// integer ones are in VtableSlotBodiesR3.cpp. Each keeps an address-derived
// class (the owner is not recovered) whose only purpose is the retail
// __thiscall convention and the member offsets the body touches; types are
// inferred from the instructions (movss / fld / fild / cvttss2si) and the
// literals are the retail .rdata values (1.0f at 0x00BBB8D8, 0.0f at
// 0x00BBAEAC, 0.7f at 0x00BC8180, 10.0f at 0x00BC2428, FLT_MAX at 0x00BBB8E0).

class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;	// VA 0x00DE1EAC
extern int g_Va00DE204C;										// VA 0x00DE204C

// Value types the by-value returns construct; which constructor each body
// uses is read off its load/store shape (x87 for the first member, movss
// for the rest when built from components; member-wise copies otherwise).
struct Rva00SlotFloat2
{
	float x, y;
	Rva00SlotFloat2() {}
	Rva00SlotFloat2(float ax, float ay) { x = ax; y = ay; }
};

struct Rva00SlotFloat2Copy
{
	float x, y;
	Rva00SlotFloat2Copy() {}
	Rva00SlotFloat2Copy(const Rva00SlotFloat2Copy &that) { x = that.x; y = that.y; }
};

struct Rva00SlotFloat2FromInts
{
	float x, y;
	Rva00SlotFloat2FromInts(int ax, int ay) { x = (float)ax; y = (float)ay; }
};

struct Rva00SlotFloat3
{
	float x, y, z;
	Rva00SlotFloat3() {}
	Rva00SlotFloat3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};

struct Rva00SlotFloat3Copy
{
	float x, y, z;
	Rva00SlotFloat3Copy() {}
	Rva00SlotFloat3Copy(const Rva00SlotFloat3Copy &that) { x = that.x; y = that.y; z = that.z; }
};

// 0x0007E0A2: adds the argument times the +0x28 float of the object at +0xC
// to the float at +0x10.
struct Rva0007E0A2Rate
{
	char m_pad00[0x28];
	float m_rate28;
};

class Rva0007E0A2
{
public:
	void rva0007E0A2(float scale);
private:
	char m_pad00[0x0C];
	Rva0007E0A2Rate *m_rate0C;
	float m_value10;
};

void Rva0007E0A2::rva0007E0A2(float scale)
{
	m_value10 += m_rate0C->m_rate28 * scale;
}

// 0x003ABD04 / 0x003ABD6B: return the float pairs at +0xA4 / +0x34 by value.
class Rva003ABD04
{
public:
	Rva00SlotFloat2 rva003ABD04();
private:
	char m_pad00[0xA4];
	float m_xA4;
	float m_yA8;
};

Rva00SlotFloat2 Rva003ABD04::rva003ABD04()
{
	return Rva00SlotFloat2(m_xA4, m_yA8);
}

class Rva003ABD6B
{
public:
	Rva00SlotFloat2 rva003ABD6B();
private:
	char m_pad00[0x34];
	float m_x34;
	float m_y38;
};

Rva00SlotFloat2 Rva003ABD6B::rva003ABD6B()
{
	return Rva00SlotFloat2(m_x34, m_y38);
}

// 0x0008BC2B: clears the float at +0x98; 0x0008BC3E: stores two floats at
// +0xAC / +0xB0.
class Rva0008BC2B
{
public:
	void rva0008BC2B();
	void rva0008BC3E(float a, float b);
private:
	char m_pad00[0x98];
	float m_value98;
	char m_pad9C[0xAC - 0x9C];
	float m_valueAC;
	float m_valueB0;
};

void Rva0008BC2B::rva0008BC2B()
{
	m_value98 = 0.0f;
}

void Rva0008BC2B::rva0008BC3E(float a, float b)
{
	m_valueAC = a;
	m_valueB0 = b;
}

// 0x00285CD1: the integer pair at +8 / +0xC as a float pair, by value.
class Rva00285CD1
{
public:
	Rva00SlotFloat2FromInts rva00285CD1();
private:
	char m_pad00[8];
	int m_x08;
	int m_y0C;
};

Rva00SlotFloat2FromInts Rva00285CD1::rva00285CD1()
{
	return Rva00SlotFloat2FromInts(m_x08, m_y0C);
}

// 0x0029A872 / 0x00095343: return the float pair at +0x808 / the float
// triple at +0xD4 by value.
class Rva0029A872
{
public:
	Rva00SlotFloat2Copy rva0029A872();
private:
	char m_pad00[0x808];
	Rva00SlotFloat2Copy m_value808;
};

Rva00SlotFloat2Copy Rva0029A872::rva0029A872()
{
	return m_value808;
}

class Rva00095343
{
public:
	Rva00SlotFloat3Copy rva00095343();
private:
	char m_pad00[0xD4];
	Rva00SlotFloat3Copy m_valueD4;
};

Rva00SlotFloat3Copy Rva00095343::rva00095343()
{
	return m_valueD4;
}

// 0x0004C6C6 (slot 51 of W3DGameClient's table): truncates its float
// argument into the global at 0x00DE204C.
class Rva0004C6C6
{
public:
	void rva0004C6C6(float value);
};

void Rva0004C6C6::rva0004C6C6(float value)
{
	g_Va00DE204C = (int)value;
}

// 0x00062E4F: ten times the +0x10 integer of the terrain render object's
// +0x37C0 block.
struct Rva00062E4FBlock
{
	char m_pad00[0x10];
	int m_value10;
};

struct Rva00062E4FTerrain
{
	char m_pad00[0x37C0];
	Rva00062E4FBlock *m_block37C0;
};

class Rva00062E4F
{
public:
	float rva00062E4F();
};

float Rva00062E4F::rva00062E4F()
{
	return ((Rva00062E4FTerrain *)TheTerrainRenderObject)->m_block37C0->m_value10 * 10.0f;
}

// 0x000851B7 / 0x000851CD / 0x000851E2 / 0x00086093: setters of the words
// at +0x58 / +0x5C / +0x60 and the floats at +0x64 / +0x68 (the last also
// sets the flag at +0x27D).
class Rva000851B7
{
public:
	void rva000851B7(int value);
	void rva000851CD(int value, float amount);
	void rva000851E2();
	void rva00086093(int value, float amount);
private:
	char m_pad00[0x58];
	int m_value58;
	int m_value5C;
	int m_value60;
	float m_amount64;
	float m_amount68;
	char m_pad6C[0x27D - 0x6C];
	bool m_flag27D;
};

void Rva000851B7::rva000851B7(int value)
{
	m_value58 = value;
	m_value60 = 0;
	m_amount64 = 0.0f;
}

void Rva000851B7::rva000851CD(int value, float amount)
{
	m_value60 = value;
	m_amount64 = amount;
}

void Rva000851B7::rva000851E2()
{
	m_value58 = 0;
	m_value5C = 0;
	m_amount68 = 0.0f;
}

void Rva000851B7::rva00086093(int value, float amount)
{
	m_value60 = value;
	m_amount64 = amount;
	m_flag27D = true;
}

// 0x000858E4: the float at +0xA8 times the float at +0x3C.
class Rva000858E4
{
public:
	float rva000858E4();
private:
	char m_pad00[0x3C];
	float m_value3C;
	char m_pad40[0xA8 - 0x40];
	float m_valueA8;
};

float Rva000858E4::rva000858E4()
{
	return m_valueA8 * m_value3C;
}

// 0x000910C7: stores its float argument into the +0x20 float of the object
// at +0x2C.
struct Rva000910C7Target
{
	char m_pad00[0x20];
	float m_value20;
};

class Rva000910C7
{
public:
	void rva000910C7(float value);
private:
	char m_pad00[0x2C];
	Rva000910C7Target *m_target2C;
};

void Rva000910C7::rva000910C7(float value)
{
	m_target2C->m_value20 = value;
}

// 0x0009862E: answers (1, 1, 1) by value; two arguments unused.
class Rva0009862E
{
public:
	Rva00SlotFloat3 rva0009862E(int a, int b);
};

Rva00SlotFloat3 Rva0009862E::rva0009862E(int, int)
{
	return Rva00SlotFloat3(1.0f, 1.0f, 1.0f);
}

// 0x003425A0: sets the +0x1A0 float of the object three links down
// (+0x18, +0x14, +0x258) to FLT_MAX; one argument unused.
struct Rva003425A0Leaf
{
	char m_pad00[0x1A0];
	float m_value1A0;
};

struct Rva003425A0Mid
{
	char m_pad00[0x258];
	Rva003425A0Leaf *m_leaf258;
};

struct Rva003425A0Top
{
	char m_pad00[0x14];
	Rva003425A0Mid *m_mid14;
};

class Rva003425A0
{
public:
	void rva003425A0(int unused);
private:
	char m_pad00[0x18];
	Rva003425A0Top *m_top18;
};

void Rva003425A0::rva003425A0(int)
{
	m_top18->m_mid14->m_leaf258->m_value1A0 = 3.402823466e+38f;
}

// 0x0039D840: the +0x21C integer of the object at +0x2C as a float.
struct Rva0039D840Target
{
	char m_pad00[0x21C];
	int m_value21C;
};

class Rva0039D840
{
public:
	float rva0039D840();
private:
	char m_pad00[0x2C];
	Rva0039D840Target *m_target2C;
};

float Rva0039D840::rva0039D840()
{
	return (float)m_target2C->m_value21C;
}

// 0x003ABEFD / 0x003A3700 / 0x003A36F7 / 0x003F7257: float constants
// (0.7, 1.0 and 0.0) taking none, one, one and two arguments.
class Rva003ABEFD
{
public:
	float rva003ABEFD();
	float rva003A3700(int a);
	float rva003A36F7(int a);
	float rva003F7257(int a, int b);
};

float Rva003ABEFD::rva003ABEFD()
{
	return 0.7f;
}

float Rva003ABEFD::rva003A3700(int)
{
	return 1.0f;
}

float Rva003ABEFD::rva003A36F7(int)
{
	return 0.0f;
}

float Rva003ABEFD::rva003F7257(int, int)
{
	return 0.0f;
}

// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
// ??0Rva0009D55BProduct@@QAE@XZ retail 0x0009D55B..0x0009D6E8 (397 bytes EH).
// Product of the W3D game client factory 0x0004C8DD (vtable 0x00BC4738;
// new 0x1D4). Runs the LivingWorld constructor 0x002C0120 (its unwind
// funclet 0x00760638 calls the base dtor 0x002BFB2D) then stores vtable
// 0x00BC89C8 and initialises its own members: six zeroed words (+0xC0)
// two 1.0 floats (+0xD8) five float triples (+0xE0 zero / +0xEC 0.9 /
// +0xF8 +0x104 +0x110 zero) then 0 / 10.0 at +0x11C/+0x120 and 1.0 / 0 /
// pi/6 at +0x134..+0x13C; four 12-byte elements at +0x140 built through
// the vector constructor iterator 0x00001423 with the folded trivial ctor
// 0x0047A6A9; zeroed words and floats at +0x188..+0x1AC; two zeroed int
// pairs (+0x1B0 +0x1B8); an STLport vector at +0x1C0 (folded _Vector_base
// ctor 0x00211E58) and two zeroed words. The deleting dtor 0x0009D9A1 and
// dtor 0x0009D6FA are rowed under the opaque name Rva009D6FA. Member
// meanings element types and the class name are unresolved.
#include <vector>

// 12-byte element whose out-of-line default constructor is the ICF-folded
// trivial ctor 0x0047A6A9 (rowed as ??0ICoord3D@@QAE@XZ among others).
struct ICoord3D
{
	ICoord3D();
	int x;
	int y;
	int z;
};

struct Rva0009D55BVec3
{
	float x, y, z;
	Rva0009D55BVec3(float v) : x(v), y(v), z(v) {}
};

struct Rva0009D55BPair
{
	int a, b;
	Rva0009D55BPair() : a(0), b(0) {}
};

class LivingWorld
{
public:
	LivingWorld();
	virtual ~LivingWorld();

private:
	char m_body[0xC0 - 4];
};

class Rva0009D55BProduct : public LivingWorld
{
public:
	Rva0009D55BProduct();
	virtual ~Rva0009D55BProduct();

private:
	int m_C0;
	int m_C4;
	int m_C8;
	int m_CC;
	int m_D0;
	int m_D4;
	float m_D8;
	float m_DC;
	Rva0009D55BVec3 m_E0;
	Rva0009D55BVec3 m_EC;
	Rva0009D55BVec3 m_F8;
	Rva0009D55BVec3 m_104;
	Rva0009D55BVec3 m_110;
	float m_11C;
	float m_120;
	char m_pad124[0x134 - 0x124];
	float m_134;
	float m_138;
	float m_13C;
	ICoord3D m_140[4];
	char m_pad170[0x188 - 0x170];
	int m_188;
	int m_18C;
	int m_190;
	int m_194;
	float m_198;
	int m_19C;
	char m_pad1A0[0x1AC - 0x1A0];
	float m_1AC;
	Rva0009D55BPair m_1B0;
	Rva0009D55BPair m_1B8;
	std::vector<int> m_1C0;
	int m_1CC;
	int m_1D0;
};

Rva0009D55BProduct::Rva0009D55BProduct()
	: m_C0(0), m_C4(0), m_C8(0), m_CC(0), m_D0(0), m_D4(0),
	  m_D8(1.0f), m_DC(1.0f),
	  m_E0(0.0f), m_EC(0.9f), m_F8(0.0f), m_104(0.0f), m_110(0.0f),
	  m_11C(0.0f), m_120(10.0f), m_134(1.0f), m_138(0.0f), m_13C(0.52359879f),
	  m_188(0), m_18C(0), m_190(0), m_194(0), m_198(0.0f), m_19C(0), m_1AC(0.0f),
	  m_1CC(0), m_1D0(0)
{
}

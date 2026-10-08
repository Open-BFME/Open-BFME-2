// ?rva003FBB99@Rva003FBA58@@QAEXXZ
// partial score=0.97 date=2026-10-07
// ?d_003fbb99@@YAXXZ
// partial score=0.94 date=2026-10-07
// ?d_003fbb99@@YAXXZ
// partial score=0.8 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva003FBA58@Rva003FBA58@@QAEXXZ @0x003FBA58 140B
// Chain lane: calls 0x003FB9C8 just landed; vtable slot 10 of 0x008747B8
// (class of ??1Rva005C4B1B). Prev 0x003FBA0E in Rva003FBA0ERva003FBA0E.cpp
// same layout +0x2C +0x34 +0x3C +0x40 +0x44 +0x48 +0x50 +0x54 float.
// Calls rowed Rva003FB9C8/Rva003FB9EB/Rva003FBA0E helpers and slot 0x30
// with 0; float vs BfmeZeroRange; clears +0x2C via and in zero branch.
class Rva003FBA0E
{
public:
	void rva003FBA0E(int a, int b, int c, int d, int e, float f);
};

class Rva003FB9C8
{
public:
	void rva003FB9C8(int a, int b);
	void rva003FB9EB(int a, int b);
};

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3 &v) : x(v.x), y(v.y), z(v.z) {}
    float getX() const { return x; }
};
static __forceinline Vec3 subtract3FBB99(Vec3 a, const Vec3 &b) {
    Vec3 r;
    r.x=a.x-b.x; r.y=a.y-b.y; r.z=a.z-b.z;
    return r;
}

class Rva003F936EHost
{
public:
    void rva003FB793(Vec3 *out);
};
class Rva003FB793Inner
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void vfunc20();
};

class Rva003FBA58
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07(Vec3 *position);
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12(bool a);
	void rva003FBA58();
	void rva003FBAE4(bool enabled);
    void rva003FBB99();
private:
	char m_pad04[4];
	void *m_08; // +0x08
	char m_pad0C[0x2C - 0x0C];
	int m_2c; // +0x2C
	int m_30;
	int m_34; // +0x34
	int m_38; // +0x38
	int m_3c; // +0x3C
	int m_40; // +0x40
	int m_44; // +0x44
	int m_48; // +0x48
	int m_4c; // +0x4C
	int m_50; // +0x50
	float m_54; // +0x54
    bool m_58;
    char m_pad59[3];
    Vec3 m_from, m_to; // +5C and +68
    float m_rate; // +74
    char m_pad78[0xA0 - 0x78];
	float m_a0, m_a4, m_a8;
};

// Native 3FBB99..3FBC4D RET0. The rowed siblings establish the receiver,
// +08 child and +4C mode; this body adds the +58 enable byte and vectors
// +5C/+68. Snapshot helper3FB793 is already rowed; original names unknown.
void Rva003FBA58::rva003FBB99()
{
    if (!m_58 || m_4c == 0)
        return;
    reinterpret_cast<Rva003FB793Inner *>(m_08)->vfunc20();
    Vec3 position;
    reinterpret_cast<Rva003F936EHost *>(this)->rva003FB793(&position);
    Vec3 delta = subtract3FBB99(m_to, m_from);
    float factor;
    if (m_4c == 1)
        factor = m_rate;
    else if (m_4c == 2)
        factor = 0.0f - m_rate;
    else
        goto apply;
    delta.x = factor * delta.getX();
    delta.y *= factor;
    delta.z *= factor;
apply:
    float x = position.x + delta.x;
    Vec3 next;
    *(volatile float *)&next.y = position.y + delta.y;
    next.x = x;
    next.z = position.z + delta.z;
    s07(&next);
}

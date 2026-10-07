// cl: /DNDEBUG /MD
//
// Straight-line vtable slot bodies below 0x00400000 that tools/vftable_map.py
// reports with no ledger owner (--unclaimed): each is reached only through a
// vtable slot, so no caller or donor names it. As in
// VtableConstantPredicates.cpp, each keeps an address-derived class (the
// owner is not recovered) whose only purpose is the retail __thiscall
// convention and the member offsets the body touches. Return and parameter
// types are inferred from the registers the body reads and writes; field
// names are offsets.
//
// Not here: seven bodies whose bool result is left in al over a live upper
// eax (sete/setne/setge al with no zeroing, and byte-load bitfield reads
// masked with and eax,1): 0x003F7133, 0x00090F7D, 0x00094DA8, 0x002614DF,
// 0x002611AF, 0x0026119D and 0x002611DD (recorded blocked).

class GameLogic;
class GlobalData;
extern GameLogic *TheGameLogic;					// VA 0x00DFE78C
extern GlobalData *TheWritableGlobalData;		// VA 0x00DFE758

struct Rva00SlotTriple { int a, b, c; };
struct Rva00SlotQuad { int a, b, c, d; };

// 0x0035D1BD (slot 3 of 0x00C150D1's table): clears the two flag bytes.
class Rva0035D1BD
{
public:
	void rva0035D1BD();
private:
	char m_pad00[8];
	bool m_flag08;
	bool m_flag09;
};

void Rva0035D1BD::rva0035D1BD()
{
	m_flag08 = false;
	m_flag09 = false;
}

// 0x0035D4DB: sets the two flag bytes; one argument unused.
class Rva0035D4DB
{
public:
	void rva0035D4DB(int unused);
private:
	char m_pad00[8];
	bool m_flag08;
	bool m_flag09;
};

void Rva0035D4DB::rva0035D4DB(int)
{
	m_flag08 = true;
	m_flag09 = true;
}

// 0x0007E103: sets the flag byte at +0x1C; one argument unused.
class Rva0007E103
{
public:
	void rva0007E103(int unused);
private:
	char m_pad00[0x1C];
	bool m_flag1C;
};

void Rva0007E103::rva0007E103(int)
{
	m_flag1C = true;
}

// 0x000F6335: four arguments, answers false.
class Rva000F6335
{
public:
	bool rva000F6335(int a, int b, int c, int d);
};

bool Rva000F6335::rva000F6335(int, int, int, int)
{
	return false;
}

// 0x00049F35 (slot 26 of BfmeStrVM0's table): sets three bool outputs
// (third first) and answers true; two further arguments unused.
class Rva00049F35
{
public:
	bool rva00049F35(bool *a, bool *b, bool *c, int d, int e);
};

bool Rva00049F35::rva00049F35(bool *a, bool *b, bool *c, int, int)
{
	*c = true;
	*b = true;
	*a = true;
	return true;
}

// 0x0006DD63 (slot 3 of LightClass's RefCountClass table): constant 14.
class Rva0006DD63
{
public:
	int rva0006DD63();
};

int Rva0006DD63::rva0006DD63()
{
	return 14;
}

// 0x0018077E: constant 0x44.
class Rva0018077E
{
public:
	int rva0018077E();
};

int Rva0018077E::rva0018077E()
{
	return 0x44;
}

// 0x003FD370: constant 0x10.
class Rva003FD370
{
public:
	int rva003FD370();
};

int Rva003FD370::rva003FD370()
{
	return 0x10;
}

// 0x0008BB27: copies the 12 bytes at +0x0C out.
class Rva0008BB27
{
public:
	void rva0008BB27(Rva00SlotTriple *out);
private:
	char m_pad00[0x0C];
	Rva00SlotTriple m_value0C;
};

void Rva0008BB27::rva0008BB27(Rva00SlotTriple *out)
{
	*out = m_value0C;
}

// 0x0008BBB8: sets the two words at +0x8C and +0x90 to -1.
class Rva0008BBB8
{
public:
	void rva0008BBB8();
private:
	char m_pad00[0x8C];
	int m_value8C;
	int m_value90;
};

void Rva0008BBB8::rva0008BBB8()
{
	m_value8C = -1;
	m_value90 = -1;
}

// 0x0008BBE0: returns the 12 bytes at +0x8C by value.
class Rva0008BBE0
{
public:
	Rva00SlotTriple rva0008BBE0();
private:
	char m_pad00[0x8C];
	Rva00SlotTriple m_value8C;
};

Rva00SlotTriple Rva0008BBE0::rva0008BBE0()
{
	return m_value8C;
}

// 0x00222471: clears the flag byte at +0x329.
class Rva00222471
{
public:
	void rva00222471();
private:
	char m_pad00[0x329];
	bool m_flag329;
};

void Rva00222471::rva00222471()
{
	m_flag329 = false;
}

// 0x00251C2C: clears the flag byte at +0x18.
class Rva00251C2C
{
public:
	void rva00251C2C();
private:
	char m_pad00[0x18];
	bool m_flag18;
};

void Rva00251C2C::rva00251C2C()
{
	m_flag18 = false;
}

// 0x0029A60C: stores the inverse of its bool argument at +0x14.
class Rva0029A60C
{
public:
	void rva0029A60C(bool value);
private:
	char m_pad00[0x14];
	bool m_flag14;
};

void Rva0029A60C::rva0029A60C(bool value)
{
	m_flag14 = !value;
}

// 0x0029A9B4: the word at +0x53C.
class Rva0029A9B4
{
public:
	int rva0029A9B4();
private:
	char m_pad00[0x53C];
	int m_value53C;
};

int Rva0029A9B4::rva0029A9B4()
{
	return m_value53C;
}

// 0x003B03F3: whether the words at +0x34 and +0x38 differ.
class Rva003B03F3
{
public:
	bool rva003B03F3();
private:
	char m_pad00[0x34];
	int m_value34;
	int m_value38;
};

bool Rva003B03F3::rva003B03F3()
{
	return m_value34 != m_value38;
}

// 0x00044FB9: copies 16 bytes in to +0x16C and sets the flag at +0x17C.
class Rva00044FB9
{
public:
	void rva00044FB9(const Rva00SlotQuad *value);
private:
	char m_pad00[0x16C];
	Rva00SlotQuad m_value16C;
	bool m_flag17C;
};

void Rva00044FB9::rva00044FB9(const Rva00SlotQuad *value)
{
	m_value16C = *value;
	m_flag17C = true;
}

// 0x000515B3: clears the flag at +0x6AC and stores its argument at +0x6B0.
class Rva000515B3
{
public:
	void rva000515B3(int value);
private:
	char m_pad00[0x6AC];
	bool m_flag6AC;
	int m_value6B0;
};

void Rva000515B3::rva000515B3(int value)
{
	m_flag6AC = false;
	m_value6B0 = value;
}

// 0x000518A4: indexes the word array at +0xB3C.
class Rva000518A4
{
public:
	int rva000518A4(int index);
private:
	char m_pad00[0xB3C];
	int m_values[1];
};

int Rva000518A4::rva000518A4(int index)
{
	return m_values[index];
}

// 0x00072740 / 0x0007274B (slots 9 and 10 of BfmeOwnerCC's table): mark the
// flag at +0x48 and answer the address of the word at +8 / +0xC of the block
// at +0x40.
class Rva00072740
{
public:
	int *rva00072740();
	int *rva0007274B();
private:
	char m_pad00[0x40];
	int *m_block40;
	char m_pad44[4];
	bool m_flag48;
};

int *Rva00072740::rva00072740()
{
	m_flag48 = true;
	return &m_block40[2];
}

int *Rva00072740::rva0007274B()
{
	m_flag48 = true;
	return &m_block40[3];
}

// 0x00086A82: whether the word at +0x23CC equals its argument.
class Rva00086A82
{
public:
	bool rva00086A82(int value);
private:
	char m_pad00[0x23CC];
	int m_value23CC;
};

bool Rva00086A82::rva00086A82(int value)
{
	return m_value23CC == value;
}

// 0x00090838: the word at +0x40 divided by the word at +0x44.
class Rva00090838
{
public:
	int rva00090838();
private:
	char m_pad00[0x40];
	int m_value40;
	int m_value44;
};

int Rva00090838::rva00090838()
{
	return m_value40 / m_value44;
}

// 0x000E132C: copies the 16 bytes at +0x3898 out.
class Rva000E132C
{
public:
	void rva000E132C(Rva00SlotQuad *out);
private:
	char m_pad00[0x3898];
	Rva00SlotQuad m_value3898;
};

void Rva000E132C::rva000E132C(Rva00SlotQuad *out)
{
	*out = m_value3898;
}

// 0x000E4886: sets the flag bytes at +0x22 and +0x21.
class Rva000E4886
{
public:
	void rva000E4886();
private:
	char m_pad00[0x21];
	bool m_flag21;
	bool m_flag22;
};

void Rva000E4886::rva000E4886()
{
	m_flag22 = true;
	m_flag21 = true;
}

// 0x000E7529: sets four flag bytes deep in a large object.
class Rva000E7529
{
public:
	void rva000E7529();
private:
	char m_pad00[0x4FB5C];
	bool m_flag4FB5C;
	bool m_flag4FB5D;
	char m_pad4FB5E[0x4FB6E - 0x4FB5E];
	bool m_flag4FB6E;
	char m_pad4FB6F[0x51274 - 0x4FB6F];
	bool m_flag51274;
};

void Rva000E7529::rva000E7529()
{
	m_flag4FB6E = true;
	m_flag51274 = true;
	m_flag4FB5C = true;
	m_flag4FB5D = true;
}

// 0x000F6329: clears its bool output and answers false; one argument unused.
class Rva000F6329
{
public:
	bool rva000F6329(bool *out, int unused);
};

bool Rva000F6329::rva000F6329(bool *out, int)
{
	*out = false;
	return false;
}

// 0x000F6D4F: clears the word at +4 and answers 0.
class Rva000F6D4F
{
public:
	int rva000F6D4F();
private:
	char m_pad00[4];
	int m_value04;
};

int Rva000F6D4F::rva000F6D4F()
{
	m_value04 = 0;
	return 0;
}

// 0x00135E60: 20000 when the word at +0x54 is set, else 0.
class Rva00135E60
{
public:
	int rva00135E60();
private:
	char m_pad00[0x54];
	int m_value54;
};

int Rva00135E60::rva00135E60()
{
	return m_value54 ? 20000 : 0;
}

// 0x0015140A: 0x28 when the word at +0x14 is set, else 0.
class Rva0015140A
{
public:
	int rva0015140A();
private:
	char m_pad00[0x14];
	int m_value14;
};

int Rva0015140A::rva0015140A()
{
	return m_value14 ? 0x28 : 0;
}

// 0x0016814C: twice the word at +0xD0, less 2.
class Rva0016814C
{
public:
	int rva0016814C();
private:
	char m_pad00[0xD0];
	int m_valueD0;
};

int Rva0016814C::rva0016814C()
{
	return m_valueD0 * 2 - 2;
}

// 0x00188170: two arguments, answers true.
class Rva00188170
{
public:
	bool rva00188170(int a, int b);
};

bool Rva00188170::rva00188170(int, int)
{
	return true;
}

// 0x00216239: stores the word at +0xC into the +0x38 word of the object at +8;
// one argument unused.
struct Rva00216239Target
{
	char m_pad00[0x38];
	int m_value38;
};

class Rva00216239
{
public:
	void rva00216239(int unused);
private:
	char m_pad00[8];
	Rva00216239Target *m_target08;
	int m_value0C;
};

void Rva00216239::rva00216239(int)
{
	m_target08->m_value38 = m_value0C;
}

// 0x00222A2B: one more than the +8 word of the object at +4.
struct Rva00222A2BTarget
{
	char m_pad00[8];
	int m_value08;
};

class Rva00222A2B
{
public:
	int rva00222A2B();
private:
	char m_pad00[4];
	Rva00222A2BTarget *m_target04;
};

int Rva00222A2B::rva00222A2B()
{
	return m_target04->m_value08 + 1;
}

// 0x00251C08: whether the word at +0xC is positive.
class Rva00251C08
{
public:
	bool rva00251C08();
private:
	char m_pad00[0xC];
	int m_value0C;
};

bool Rva00251C08::rva00251C08()
{
	return m_value0C > 0;
}

// 0x001F01E8 / 0x0025EF07 / 0x0025EF01: empty bodies taking four, six and
// seven arguments.
class Rva001F01E8
{
public:
	void rva001F01E8(int a, int b, int c, int d);
	void rva0025EF07(int a, int b, int c, int d, int e, int f);
	void rva0025EF01(int a, int b, int c, int d, int e, int f, int g);
};

void Rva001F01E8::rva001F01E8(int, int, int, int)
{
}

void Rva001F01E8::rva0025EF07(int, int, int, int, int, int)
{
}

void Rva001F01E8::rva0025EF01(int, int, int, int, int, int, int)
{
}

// The partition filter base (ctor 0x000421C8, vftable 0x00BC26E0).
class Object;
class Rva000421C8
{
public:
	virtual ~Rva000421C8();
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

// 0x00260E1E: one shifted left by the +0x54 word of the object at +8.
struct Rva00260E1ETarget
{
	char m_pad00[0x54];
	int m_shift54;
};

class Rva00260E2AFilter : public Rva000421C8
{
public:
	virtual int getPlayerMask();
private:
	Rva00260E1ETarget *m_target08;
};

int Rva00260E2AFilter::getPlayerMask()
{
	return 1 << m_target08->m_shift54;
}

// 0x0026118B: whether the +0x258 word of the argument is set.
struct Rva0026118BTarget
{
	char m_pad00[0x258];
	int m_value258;
};

class Rva0026118BFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *target);
};

bool Rva0026118BFilter::allow(Object *target)
{
	return ((Rva0026118BTarget *)target)->m_value258 != 0;
}

// 0x00285703: the 16-bit constant 1.
class Rva00285703
{
public:
	short rva00285703();
};

short Rva00285703::rva00285703()
{
	return 1;
}

// 0x00306C49: sets the word at +8 to the word at +4 plus its argument and
// answers true; 0x00306C58: whether the word at +8 has reached the word at
// +0xC (unsigned).
class Rva00306C49
{
public:
	bool rva00306C49(int offset);
	bool rva00306C58();
private:
	char m_pad00[4];
	unsigned int m_base04;
	unsigned int m_cursor08;
	unsigned int m_end0C;
};

bool Rva00306C49::rva00306C49(int offset)
{
	m_cursor08 = m_base04 + offset;
	return true;
}

bool Rva00306C49::rva00306C58()
{
	return m_cursor08 >= m_end0C;
}

// 0x00330CC2: copies 12 bytes in to +0x14.
class Rva00330CC2
{
public:
	void rva00330CC2(const Rva00SlotTriple *value);
private:
	char m_pad00[0x14];
	Rva00SlotTriple m_value14;
};

void Rva00330CC2::rva00330CC2(const Rva00SlotTriple *value)
{
	m_value14 = *value;
}

// 0x00355DD4: clears the words at +8 and +0x10.
class Rva00355DD4
{
public:
	void rva00355DD4();
private:
	char m_pad00[8];
	int m_value08;
	int m_value0C;
	int m_value10;
};

void Rva00355DD4::rva00355DD4()
{
	m_value08 = 0;
	m_value10 = 0;
}

// 0x0036803F: stores TheGameLogic's +0x40 word plus 2 at +0x20 and answers 0.
struct Rva0036803FLogic
{
	char m_pad00[0x40];
	int m_value40;
};

class Rva0036803F
{
public:
	int rva0036803F();
private:
	char m_pad00[0x20];
	int m_value20;
};

int Rva0036803F::rva0036803F()
{
	m_value20 = ((Rva0036803FLogic *)TheGameLogic)->m_value40 + 2;
	return 0;
}

// 0x0037DE70: bumps the word at +4 and answers 1; one argument unused.
class Rva0037DE70
{
public:
	int rva0037DE70(int unused);
private:
	char m_pad00[4];
	int m_count04;
};

int Rva0037DE70::rva0037DE70(int)
{
	++m_count04;
	return 1;
}

// 0x003F718D: whether the word at +8 is set; two arguments unused.
class Rva003F718D
{
public:
	bool rva003F718D(int a, int b);
private:
	char m_pad00[8];
	int m_value08;
};

bool Rva003F718D::rva003F718D(int, int)
{
	return m_value08 != 0;
}

// 0x00203665: TheWritableGlobalData's +0xAC8 word.
struct Rva00203665Data
{
	char m_pad00[0xAC8];
	int m_valueAC8;
};

class Rva00203665
{
public:
	int rva00203665();
};

int Rva00203665::rva00203665()
{
	return ((Rva00203665Data *)TheWritableGlobalData)->m_valueAC8;
}

// 0x00345F76: 0 when bit 0x2000 of the +0x114 word four links down (+0x18,
// +0x14, +4) is set, else -2.
struct Rva00345F76Leaf
{
	char m_pad00[0x114];
	unsigned int m_flags114;
};

struct Rva00345F76Mid
{
	char m_pad00[4];
	Rva00345F76Leaf *m_leaf04;
};

struct Rva00345F76Top
{
	char m_pad00[0x14];
	Rva00345F76Mid *m_mid14;
};

class Rva00345F76
{
public:
	int rva00345F76();
private:
	char m_pad00[0x18];
	Rva00345F76Top *m_top18;
};

int Rva00345F76::rva00345F76()
{
	return (m_top18->m_mid14->m_leaf04->m_flags114 & 0x2000) ? 0 : -2;
}
struct IDirect3DSurface8;
// Native 0x11D330 Clear uses WWMath's class-tagged 12B Vector3 view.
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};
class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *surface, bool flag);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};
class Rva000F6D56Filter
{
public:
	virtual bool preRender(bool &skip, int &mode);

private:
	char m_pad00[0x18];
	IDirect3DSurface8 *m_surface; // +0x1C
};

#ifndef NULL
#define NULL 0
#endif

bool Rva000F6D56Filter::preRender(bool &skip, int &mode)
{
	skip = false;
	DX8Wrapper::Set_Render_Target(m_surface, true);
	float one = 1.0f;
	Vector3 black;
	black.X = 0.0f;
	black.Y = 0.0f;
	black.Z = 0.0f;
	DX8Wrapper::Clear(true, false, false, black, 0.0f, one, 0);
	mode = 6;
	return true;
}

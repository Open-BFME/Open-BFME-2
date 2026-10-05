// cl: /O1
//
// Three small Object readers (retail 0x0028AD6C/16 + 0x0028ADE0/12 +
// 0x0028ADF7/28). /O1 selects the retail size idioms throughout: jne plus
// inc-from-known-zero for the null-or-one reader, xor-first cmp-mem-reg for
// the flag test, and hoisted xor plus inc for the bit-test's 1<<slot.

struct Coord3D
{
	float x, y, z;
};

// The object at Object+0xA4. Its float getter at 0x004DD843 is rowed under
// this address-derived class name, so the forwarders below reuse it; the
// remaining methods are pinned from the forwarders' own REL32 targets.
class Rva004DD843
{
public:
	void rva004DE24B(int arg);
	void rva004DE4E2(int arg);
	void rva004DE511(int arg, int arg2);
	void rva004DE109(int arg, float value, int arg2);
	void rva004DDD80();
	void rva004DDD6E();
	bool rva004DD80A(Coord3D *out);
	float rva004DD843();
	void rva004DE2ED();
	void rva004DDD92();
	bool rva004DD84D(Coord3D *out);
	bool rva004DD637();

	char m_pad[0x28];				// +0x000..+0x028 unknown
	int m_value;					// +0x028
};

struct Rva0028AF76Sub
{
	char m_pad[0x44];				// +0x000..+0x044 unknown
	int m_value;					// +0x044
	float m_float48;				// +0x048
	int m_int4C;					// +0x04C
	int m_int50;					// +0x050

	void rva0028A82A(void *dst) const;
};

class GameLogic
{
public:
	char m_pad[0x40];
	int m_frame; // +0x40, proven by Rva002039B6Host
};
extern GameLogic *TheGameLogic;


class Object;

class WeaponSet
{
public:
	void reloadAllAmmo(const Object *obj, bool now);
	bool isOutOfAmmo() const;
};

class Object
{
	char m_pad0[0xA4];				// +0x000..+0x0A4 unknown
	Rva004DD843 *m_sub;				// +0x0A4
	char m_pad1[0x240 - 0xA4 - 4];	// +0x0A8..+0x240 unknown
	Rva0028AF76Sub *m_sub240;		// +0x240
	char m_pad2[0x358 - 0x244];		// +0x244..+0x358 unknown
	int m_flag358;					// +0x358
	int m_pad358;					// +0x35C unknown
	int m_mask360;					// +0x360
	char m_pad364[0x40C - 0x364];	// +0x364..+0x40C unknown
	int m_value40C;					// +0x40C
	char m_pad410[0x48C - 0x410];	// +0x410..+0x48C unknown
	unsigned char m_flag48C;		// +0x48C
	char m_pad48D[0x490 - 0x48D];	// +0x48D..+0x490 pad
	int m_frame490;					// +0x490 cached frame

public:
	void rva0028ACCA(int arg);
	void rva0028ACDC(int arg);
	void rva0028ACEE(int arg, int arg2);
	void rva0028AD00(int arg, float value, int arg2);
	void rva0028AD22();
	void rva0028AD32();
	bool rva0028AD42(Coord3D *out) const;
	float rva0028AD56() const;
	int rva0028AD6C() const;
	void rva0028AD7C();
	void rva0028AD8C();
	bool rva0028AD9C(Coord3D *out) const;
	bool rva0028ADB0() const;
	void reloadAllAmmo(bool now);
	bool rva0028ADE0() const;
	int rva0028ADF7(int slot) const;
	int rva0028AF76() const;
	int rva0028B511() const;
	void rva0028B95F();
	bool isOutOfAmmo() const;
};

// Null-checked forwarders through the Object+0xA4 object (retail
// 0x0028ACCA..0x0028ADC1, between the rowed 0x0028ACA0 and 0x0028AD6C/
// 0x0028ADD5 Object rows). Each loads +0xA4, returns (or answers false /
// 0.0f) when it is null and otherwise tail-jumps to the method; the
// three-argument float forward at 0x0028AD00 re-pushes its arguments and
// calls instead.
void Object::rva0028ACCA(int arg)
{
	if (m_sub)
		m_sub->rva004DE24B(arg);
}

void Object::rva0028ACDC(int arg)
{
	if (m_sub)
		m_sub->rva004DE4E2(arg);
}

void Object::rva0028ACEE(int arg, int arg2)
{
	if (m_sub)
		m_sub->rva004DE511(arg, arg2);
}

void Object::rva0028AD00(int arg, float value, int arg2)
{
	if (m_sub)
		m_sub->rva004DE109(arg, value, arg2);
}

void Object::rva0028AD22()
{
	if (m_sub)
		m_sub->rva004DDD80();
}

void Object::rva0028AD32()
{
	if (m_sub)
		m_sub->rva004DDD6E();
}

bool Object::rva0028AD42(Coord3D *out) const
{
	if (!m_sub)
		return false;
	return m_sub->rva004DD80A(out);
}

float Object::rva0028AD56() const
{
	if (!m_sub)
		return 0.0f;
	return m_sub->rva004DD843();
}

// ?rva0028AD6C@Object@@QBEHXZ
int Object::rva0028AD6C() const
{
	const Rva004DD843 *sub = m_sub;
	if (sub == 0)
		return 1;
	return sub->m_value;
}

void Object::rva0028AD7C()
{
	if (m_sub)
		m_sub->rva004DE2ED();
}

void Object::rva0028AD8C()
{
	if (m_sub)
		m_sub->rva004DDD92();
}

bool Object::rva0028AD9C(Coord3D *out) const
{
	if (!m_sub)
		return false;
	return m_sub->rva004DD84D(out);
}

bool Object::rva0028ADB0() const
{
	if (!m_sub)
		return false;
	return m_sub->rva004DD637();
}

// ?reloadAllAmmo@Object@@QAEX_N@Z, retail 0x0028ADC2 (19B): Zero Hour's
// Object::reloadAllAmmo, immediately before isOutOfAmmo as in Object.cpp.
void Object::reloadAllAmmo(bool now)
{
	WeaponSet *ws = (WeaponSet *)((char *)this + 0x330);
	ws->reloadAllAmmo(this, now);
}

// ?rva0028ADE0@Object@@QBE_NXZ
// ?rva0028ADE0@Object@@QBE_NXZ
bool Object::rva0028ADE0() const
{
	return m_flag358 != 0;
}

// ?rva0028ADF7@Object@@QBEHH@Z
// ?rva0028ADF7@Object@@QBEHH@Z
int Object::rva0028ADF7(int slot) const
{
	return (m_mask360 & (1 << slot)) != 0 ? 1 : 0;
}

int Object::rva0028AF76() const
{
	int result = 0;
	const Rva0028AF76Sub *sub = m_sub240;
	if (sub != 0)
		result = sub->m_value;
	return result;
}

int Object::rva0028B511() const
{
	if (m_flag48C != 0)
		return 1;
	return m_value40C;
}

// ?rva0028B95F@Object@@QAEXXZ, retail 0x0028B95F, 22 bytes.
// Sets the +0x48C flag and caches TheGameLogic frame at +0x490. Evidence:
// flag byte proven by rva0028B511 in this TU, frame slot +0x40 proven by
// Rva002039B6Host, callers at 0x0046E268 0x0046E297 iterate and call with
// Object this.
void Object::rva0028B95F()
{
	m_flag48C = 1;
	m_frame490 = TheGameLogic->m_frame;
}

bool Object::isOutOfAmmo() const
{
	const WeaponSet *ws = (const WeaponSet *)((const char *)this + 0x330);
	return ws->isOutOfAmmo();
}

void Rva0028AF76Sub::rva0028A82A(void *dst) const
{
	char *d = (char *)dst;
	*(float *)d = m_float48;
	*(int *)(d + 4) = m_int4C;
	*(int *)(d + 8) = m_int50;
}

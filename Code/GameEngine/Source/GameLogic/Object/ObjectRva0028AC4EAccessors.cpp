// cl: /O1 /arch:SSE
//
// Object entry-accessor family around the holder at +0x258 (retail
// 0x0028AC4E/20 + 0x0028AC62/27 + 0x0028AC7D/35; ghidra FUN_0068ac4e/62/7d).
// The getter reads the holder's entry at +0x1F0 with a null check; the bool
// reads the entry's next link at +0x4 and its flag byte at +0x150; the float
// reads the entry through the rowed disp8 float getter at 0x0008BB38 and
// falls back to a global when the entry is missing or non-positive.
//
// The getter is defined (not rowed: its false-path tail is the rowed 3B zero
// getter at 0x0028AC5F, so a row here would partially overlap) and pinned so
// both callers resolve. /O1 keeps the getter's explicit xor plus the lea-free
// direct count shape; /arch:SSE selects the retail fldz/fld/fcompi float
// compare (plain /O2 emits fcoms/fnstsw against a static zero).

class Rva0008BB38FloatField
{
public:
	float get() const;
};

extern float g_Va00BBAEAC;

struct Rva0028AC4EQ
{
	char m_pad[0x150];				// +0x000..+0x150 unknown
	bool m_flag;					// +0x150
};

struct Rva0028AC4EEntry
{
	char m_pad0[4];					// +0x000..+0x004 unknown
	Rva0028AC4EQ *m_next;			// +0x004
	char m_pad1[0x40 - 8];			// +0x008..+0x040 unknown
	float m_float;					// +0x040 (read via 0x8BB38, never directly)
};

struct Rva0028AC4EHolder
{
	char m_pad[0x1F0];				// +0x000..+0x1F0 unknown
	Rva0028AC4EEntry *m_entry;		// +0x1F0
};

class Object
{
	char m_pad[0x258];				// +0x000..+0x258 unknown
	Rva0028AC4EHolder *m_holder;		// +0x258

public:
	__declspec(noinline) const Rva0028AC4EEntry *rva0028AC4E() const;
	bool rva0028AC62() const;
	float rva0028AC7D() const;
};

// ?rva0028AC4E@Object@@QBEPBURva0028AC4EEntry@@XZ present-unmatched
__declspec(noinline) const Rva0028AC4EEntry *Object::rva0028AC4E() const
{
	Rva0028AC4EHolder *holder = m_holder;
	return holder != 0 ? holder->m_entry : 0;
}

// ?rva0028AC62@Object@@QBE_NXZ
bool Object::rva0028AC62() const
{
	if (rva0028AC4E() != 0)
		return rva0028AC4E()->m_next->m_flag;
	return false;
}

// ?rva0028AC7D@Object@@QBEMXZ
// ?rva0028AC7D@Object@@QBEMXZ present-unmatched
float Object::rva0028AC7D() const
{
	const Rva0028AC4EEntry *entry = rva0028AC4E();
	if (entry == 0)
		return g_Va00BBAEAC;
	float m = ((const Rva0008BB38FloatField *)entry)->get();
	if (m > 0.0f)
		return m;
	return g_Va00BBAEAC;
}

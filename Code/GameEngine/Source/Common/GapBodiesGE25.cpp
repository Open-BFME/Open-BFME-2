// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// platformsdk
// Small bodies from .text gaps no Ghidra function covers (twenty-fifth
// batch; see GapBodiesGE01.cpp). Each begins after its neighbour's padding or
// ret and ends in its own ret. Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.

#include <windows.h>

// --- 0x00040FB5 (24B): pulse the +4 event handle when there is one.
class Rva00040FB5
{
public:
	bool rva00040FB5();
private:
	int m_00;
	void *m_event;											// +0x04
};

bool Rva00040FB5::rva00040FB5()
{
	if (m_event)
		return PulseEvent(m_event) != 0;
	return false;
}

// --- 0x0004114E (26B): bounds-checked byte of the +8 array (+0x0C count).
class Rva0004114E
{
public:
	char rva0004114E(int i) const;
private:
	int m_00;
	int m_04;
	char *m_bytes;											// +0x08
	int m_count;											// +0x0C
};

char Rva0004114E::rva0004114E(int i) const
{
	if (i >= 0 && i < m_count)
		return m_bytes[i];
	return 0;
}

// --- 0x00041F69 (24B): clear the leading byte and run the rowed
// 0x00041D22 unless told not to.
class Rva00041D03
{
public:
	Rva00041D03(int skip);
	void rva00041D22();										// 0x00041D22
private:
	bool m_00;
};

Rva00041D03::Rva00041D03(int skip)
{
	m_00 = false;
	if (!skip)
		rva00041D22();
}

// --- 0x000422F3 (6B), 0x000422F9 / 0x00042303 / 0x0004230D / 0x00042317
// (10B each): out-of-line copies of WW3D's inline static accessors over
// IsInitted, ThumbnailEnabled, IsScreenUVBiased, the 0x00DB5F88 word and
// AreStaticSortListsEnabled.
class Rva000422F3;

class WW3D
{
	friend class Rva000422F3;
	static bool IsInitted;
	static bool ThumbnailEnabled;
	static bool IsScreenUVBiased;
	static bool AreStaticSortListsEnabled;
	enum PrelitModeEnum { PRELIT_MODE_VERTEX, PRELIT_MODE_LIGHTMAP_MULTI_PASS, PRELIT_MODE_LIGHTMAP_MULTI_TEXTURE };
	static PrelitModeEnum PrelitMode;	// VA 0x00DB5F88; ww3d.cpp defines it
};

class Rva000422F3
{
public:
	static bool rva000422F3();
	static void rva000422F9(bool on);
	static void rva00042303(bool on);
	static void rva0004230D(int value);
	static void rva00042317(bool on);
};

bool Rva000422F3::rva000422F3()
{
	return WW3D::IsInitted;
}

void Rva000422F3::rva000422F9(bool on)
{
	WW3D::ThumbnailEnabled = on;
}

void Rva000422F3::rva00042303(bool on)
{
	WW3D::IsScreenUVBiased = on;
}

void Rva000422F3::rva0004230D(int value)
{
	WW3D::PrelitMode = (WW3D::PrelitModeEnum)value;
}

void Rva000422F3::rva00042317(bool on)
{
	WW3D::AreStaticSortListsEnabled = on;
}

// --- 0x00042FC7 (29B): copy a three-word value into +0x144.
struct GapTriple
{
	int a;
	int b;
	int c;
	void set(const GapTriple &gapTriple)
	{
		a = gapTriple.a;
		b = gapTriple.b;
		c = gapTriple.c;
	}
};

class Rva00042FC7
{
public:
	void rva00042FC7(const GapTriple &value);
private:
	char m_pad00[0x144];
	GapTriple m_value;										// +0x144
};

void Rva00042FC7::rva00042FC7(const GapTriple &value)
{
	m_value.set(value);
}

// --- 0x00043CE9 (38B): two calls on the +0x278 object: slot 10 (+0x28)
// with (-1, 0xFF000000), slot 14 (+0x38) with (3, 20, 1, 1).
class GapSlotView
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual void slot10(int a, unsigned int color);
	virtual void v11(); virtual void v12(); virtual void v13();
	virtual void slot14(int a, int b, int c, int d);
};

class Rva00043CE9
{
public:
	void rva00043CE9();
private:
	char m_pad00[0x278];
	GapSlotView *m_target;									// +0x278
};

void Rva00043CE9::rva00043CE9()
{
	m_target->slot10(-1, 0xFF000000);
	m_target->slot14(3, 20, 1, 1);
}

// --- 0x00049D10 (16B): the +4 float of the i-th record in the +0x10 table.
struct GapFloatRecord
{
	int m_00;
	float m_value;											// +0x04
};

class Rva00049D10
{
public:
	float rva00049D10(int i) const;
private:
	char m_pad00[0x10];
	GapFloatRecord **m_records;								// +0x10
};

float Rva00049D10::rva00049D10(int i) const
{
	return m_records[i]->m_value;
}

// --- 0x00050D2A / 0x00050D34 (10B each): virtual slot 0 with a zero word on
// the objects embedded at +0x44 / +0x4C.
class GapSlot0View
{
public:
	virtual void slot0(int flags);
};

class Rva00050D2A
{
public:
	void rva00050D2A();
	void rva00050D34();
private:
	char m_pad00[0x44];
	GapSlot0View m_44;										// +0x44
	char m_pad48[4];
	GapSlot0View m_4C;										// +0x4C
};

void Rva00050D2A::rva00050D2A()
{
	GapSlot0View *gapSlot0View = &m_44;
	gapSlot0View->slot0(0);
}

void Rva00050D2A::rva00050D34()
{
	GapSlot0View *gapSlot0View = &m_4C;
	gapSlot0View->slot0(0);
}

// --- 0x00050F41 / 0x00050F51 (16B each): any of the given bits set in the
// +0x48 / +0x4C masks.
class Rva00050F41
{
public:
	bool rva00050F41(unsigned int bits) const;
	bool rva00050F51(unsigned int bits) const;
private:
	char m_pad00[0x48];
	unsigned int m_48;
	unsigned int m_4C;
};

bool Rva00050F41::rva00050F41(unsigned int bits) const
{
	return (m_48 & bits) != 0;
}

bool Rva00050F41::rva00050F51(unsigned int bits) const
{
	return (m_4C & bits) != 0;
}

// --- 0x00051155 (22B): consume the AudioEventsReloaded flag.
extern bool AudioEventsReloaded;

class MilesAudioManager
{
public:
	virtual bool vslot05();
	class GlobalVolumeData
	{
	public:
		void rva00052015(int value);						// 0x00052015
	private:
		char m_pad[0x1C4];
	};
	char m_pad00[0x128];
	GlobalVolumeData m_volumes[3];							// +0x12C
};

bool MilesAudioManager::vslot05()
{
	if (AudioEventsReloaded)
	{
		AudioEventsReloaded = false;
		return true;
	}
	return false;
}

// --- 0x0005150B / 0x00051518 (13B each): differences of +0x67C/+0x684 and
// +0x680/+0x688.
class Rva0005150B
{
public:
	int rva0005150B() const;
	int rva00051518() const;
private:
	char m_pad00[0x67C];
	int m_67C;
	int m_680;
	int m_684;
	int m_688;
};

int Rva0005150B::rva0005150B() const
{
	return m_67C - m_684;
}

int Rva0005150B::rva00051518() const
{
	return m_680 - m_688;
}

// --- 0x000515CE (22B): a word and a float.
class Rva000515CE
{
public:
	Rva000515CE(int a, float b);
private:
	int m_a;
	float m_b;
};

Rva000515CE::Rva000515CE(int a, float b) : m_a(a), m_b(b)
{
}

// --- 0x000517E0 (17B): +0x9D0 below +0x9CC (unsigned).
class Rva000517E0
{
public:
	bool rva000517E0() const;
private:
	char m_pad00[0x9CC];
	unsigned int m_9CC;
	unsigned int m_9D0;
};

bool Rva000517E0::rva000517E0() const
{
	return m_9D0 < m_9CC;
}

// --- 0x00051E6A (19B): the +0xB8 range is not empty.
struct GapRange
{
	int *m_begin;
	int *m_end;
	bool notEmpty() const { return m_begin != m_end; }
};

class Rva00051E6A
{
public:
	bool rva00051E6A() const;
private:
	char m_pad00[0xB8];
	GapRange m_range;										// +0xB8
};

bool Rva00051E6A::rva00051E6A() const
{
	return m_range.notEmpty();
}

// --- 0x0005247A (48B): apply a value to TheAudio's three 0x1C4-byte
// MilesAudioManager::GlobalVolumeData records at +0x12C through the rowed
// 0x00052015.

class AudioManager;
extern AudioManager *TheAudio;

void rva0005247A(int value)
{
	if (TheAudio)
		for (int i = 0; i < 3; ++i)
			((MilesAudioManager *)TheAudio)->m_volumes[i].rva00052015(value);
}

// --- 0x00052857 (19B): bit 3 of the +0x4C word of an object's +8 member.
struct GapFlagsHolder
{
	char m_pad00[0x4C];
	unsigned int m_flags;									// +0x4C
};

struct GapFlagsOwner
{
	int m_00;
	int m_04;
	GapFlagsHolder *m_holder;								// +0x08
};

class Rva00052857
{
public:
	unsigned int rva00052857(const GapFlagsOwner *owner) const;
};

unsigned int Rva00052857::rva00052857(const GapFlagsOwner *owner) const
{
	return (owner->m_holder->m_flags >> 3) & 1;
}

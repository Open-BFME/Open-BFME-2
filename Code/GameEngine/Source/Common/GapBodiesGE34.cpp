// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (thirty-fourth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.
#include <stdio.h>
#include <string.h>

// --- 0x0059EE87 (15B): clear the +0x4A8 id and mark +0x4A0.
class Rva0059EE87
{
public:
	void rva0059EE87();
private:
	char m_pad[0x4A0];
	bool m_4A0;
	char m_pad4A1[0x4A8 - 0x4A1];
	int m_4A8;
};

void Rva0059EE87::rva0059EE87()
{
	m_4A8 = -1;
	m_4A0 = true;
}

// --- 0x0059F9D7 (18B) / 0x0059F9E9 (18B), cdecl: open the custom-match
// connection screen of the 0x00E063EC instance (rowed 0x0059F37C with true,
// false).
class AptOnlineCustomMatch
{
public:
	void OpenConnectionScreen(bool show);					// 0x0059F37C
};

extern int g_currentAptOnlineCustomMatch;

void Rva0059F9D7()
{
	if (g_currentAptOnlineCustomMatch)
		((AptOnlineCustomMatch *)g_currentAptOnlineCustomMatch)->OpenConnectionScreen(true);
}

void Rva0059F9E9()
{
	if (g_currentAptOnlineCustomMatch)
		((AptOnlineCustomMatch *)g_currentAptOnlineCustomMatch)->OpenConnectionScreen(false);
}

// --- 0x005A683C (19B) / 0x005A6869 (22B): store a slot below 8 at +0x0C;
// set the 16-bit value of the +0x90C entry the +0x14 index selects.
struct Rva005A6869Entry
{
	int m_00;
	short m_04;
};

class Rva005A683C
{
public:
	void setSlot(unsigned short slot);
	void rva005A6869(short value);
private:
	char m_pad[0x0C];
	int m_slot;												// +0x0C
	int m_10;
	int m_index;											// +0x14
	char m_pad18[0x90C - 0x18];
	Rva005A6869Entry *m_entries[1];							// +0x90C
};

// --- 0x005AE659 (18B): whether the cursor's referenced node is the stored
// one.
struct Rva005AE659Node;

class Rva005AE659
{
public:
	int rva005AE659(Rva005AE659Node **const *cursor) const;
private:
	Rva005AE659Node *m_node;
};

int Rva005AE659::rva005AE659(Rva005AE659Node **const *cursor) const
{
	return **cursor == m_node;
}

// --- 0x005B0207 (21B) / 0x005B021C (14B): a zero float and the value; the
// indexed +0x418 word.
class Rva005B0207
{
public:
	void rva005B0207(float value);
	int rva005B021C(int index) const;
private:
	float m_00;
	float m_04;
	char m_pad08[0x418 - 0x08];
	int m_418[1];
};

void Rva005B0207::rva005B0207(float value)
{
	m_00 = 0.0f;
	m_04 = value;
}

int Rva005B0207::rva005B021C(int index) const
{
	return m_418[index];
}

// --- 0x005B0357 (93B): text callback writing "1" / "0" for whether the hero
// earned the indexed award (rowed 0x00406E7D count, 0x00406E8F id, award
// table 0x00E02F74 lookup 0x0040AAD5, CreateAHeroHero::HasEarnedAward).
struct BfmePod40;
class CreateAHeroAward;

class Rva0040AAD5
{
public:
	BfmePod40 *rva0040AAD5(int id);							// 0x0040AAD5
};

extern Rva0040AAD5 *TheAwardSystemManager;

class Rva00406E7D
{
public:
	int rva00406E7D();										// 0x00406E7D
};

class Rva00406E8F
{
public:
	int rva00406E8F(unsigned index);						// 0x00406E8F
};

class CreateAHeroHero
{
public:
	bool HasEarnedAward(const CreateAHeroAward *award) const;	// 0x00406EA7
	void rva005B0357(int index, char *buffer, int unused);
};

void CreateAHeroHero::rva005B0357(int index, char *buffer, int unused)
{
	*buffer = 0;
	if (index < ((Rva00406E7D *)this)->rva00406E7D())
	{
		BfmePod40 *award = TheAwardSystemManager->rva0040AAD5(((Rva00406E8F *)this)->rva00406E8F(index));
		if (award)
		{
			if (HasEarnedAward((const CreateAHeroAward *)award))
				strncpy(buffer, "1", 0xFF);
			else
				strncpy(buffer, "0", 0xFF);
		}
	}
}

// --- 0x005B03B4 (98B): text callback by field: the 0x00E06450 value, the
// hero manager's +0x1D4 value, or "1" / "0" for the +0x48 flag without the
// 0x00DFE34C override.
class CreateAHeroManager;
extern CreateAHeroManager *TheCreateAHeroManager;
extern int g_00E06450;
extern unsigned char g_rva005B5C02Flag;
// Defined here: nothing else in the tree did. Retail VA 0x00DFE34C
// (RVA 0x009FE34C), zero-filled .bss byte read by seven matched units.
unsigned char g_rva005B5C02Flag;

struct Rva005B03B4Manager
{
	char m_pad[0x1D4];
	int m_1D4;
};

class Rva005B03B4
{
public:
	void rva005B03B4(int field, char *buffer, int unused);
private:
	char m_pad[0x48];
	bool m_48;
};

void Rva005B03B4::rva005B03B4(int field, char *buffer, int unused)
{
	switch (field)
	{
	case 0:
		_snprintf(buffer, 0xFF, "%d", g_00E06450);
		break;
	case 1:
		_snprintf(buffer, 0xFF, "%d", ((Rva005B03B4Manager *)TheCreateAHeroManager)->m_1D4);
		break;
	case 2:
		strcpy(buffer, m_48 && !g_rva005B5C02Flag ? "1" : "0");
		break;
	}
}

// --- 0x005B0608 (64B) / 0x005B0648 (70B) / 0x005B068E (64B) / 0x005B06CE
// (87B): text callbacks writing one more than the indexed +0x174 record's
// +0x08 / rowed-0x00407E28-mapped +0x00 / +0x0C value, and (after "0" unless
// skipped) the indexed +0x180 record's +0x04 value.
struct Rva005B0608Record
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

struct Rva005B0608Vector
{
	__forceinline unsigned size() const { return m_end - m_begin; }
	__forceinline const Rva005B0608Record &operator[](unsigned i) const { return m_begin[i]; }
	Rva005B0608Record *m_begin;
	Rva005B0608Record *m_end;
	Rva005B0608Record *m_storage;
};

class Rva00407E28
{
public:
	int rva00407E28(int key);								// 0x00407E28
};

class Rva005B0608
{
public:
	void rva005B0608(unsigned index, char *buffer, int unused);
	void rva005B0648(unsigned index, char *buffer, int unused);
	void rva005B068E(unsigned index, char *buffer, int unused);
	void rva005B06CE(unsigned index, char *buffer, bool skip);
private:
	char m_pad[0x174];
	Rva005B0608Vector m_174;
	Rva005B0608Vector m_180;
};

void Rva005B0608::rva005B0608(unsigned index, char *buffer, int unused)
{
	const Rva005B0608Vector &records = m_174;
	if (index < records.size())
		_snprintf(buffer, 0xFF, "%d", records[index].m_08 + 1);
}

void Rva005B0608::rva005B0648(unsigned index, char *buffer, int unused)
{
	const Rva005B0608Vector &records = m_174;
	if (index < records.size())
		_snprintf(buffer, 0xFF, "%d", ((Rva00407E28 *)this)->rva00407E28(records[index].m_00) + 1);
}

void Rva005B0608::rva005B068E(unsigned index, char *buffer, int unused)
{
	const Rva005B0608Vector &records = m_174;
	if (index < records.size())
		_snprintf(buffer, 0xFF, "%d", records[index].m_0C + 1);
}

void Rva005B0608::rva005B06CE(unsigned index, char *buffer, bool skip)
{
	if (skip)
		return;
	strcpy(buffer, "0");
	const Rva005B0608Vector &records = m_180;
	if (index < records.size())
		_snprintf(buffer, 0xFF, "%d", records[index].m_04);
}

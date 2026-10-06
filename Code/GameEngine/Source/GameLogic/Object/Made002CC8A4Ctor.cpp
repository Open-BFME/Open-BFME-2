// cl: /MD /EHsc /DNDEBUG
// Made002CC8A4 ctor, retail 0x0050A39B (263 bytes). Built from the banked
// attempt reverse/attempts/0x0050a39b.cpp; fix: m_150 is assigned before
// m_144, which is the order retail stores the two zeroed floats.
//
// Evidence: pin; base Rva00507823 0x0050775B; vtable 0x008649A0; pi via 0x007C7468;
// 1.0 via 0x007BB8D8; 2.0 via 0x007C28F4; 100.0 via 0x007C292C; filter at +0x160
// via 0x003623E5 plus FixedStorage from 0x009FEFA4 via 0x0004543D to 0x00362087;
// caller parseMetaImpactNugget 0x002CC8C9 news 0x164.

class BfmeFixedStorage0004543D
{
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[28];
};

// Retail's shared fixed-storage object at RVA 0x009FEFA4 (pinned).
extern const BfmeFixedStorage0004543D g_009FEFA4;

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);
private:
	int m_x;
};

// Rowed pool-aware member dtor at 0x00360D26 lives under this name
// (ObjectFilterRelease.cpp). Same 4-byte handle as above; the ctor twin
// at 0x003623E5 is also rowed under both names, so construction bytes
// are unchanged while the implicit ~Made dtor now calls the row.
class Rva00360D26Member
{
public:
	Rva00360D26Member();
	~Rva00360D26Member();
private:
	int m_x;
};

class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
private:
	char m_pad[0x128 - 4];
};

class Made002CC8A4 : public Rva00507823
{
public:
	Made002CC8A4();
private:
	float m_128;
	float m_12C;
	float m_130;
	bool m_134;
	char m_pad135[3];
	float m_138;
	float m_13C;
	float m_140;
	float m_144;
	int m_148;
	bool m_14C;
	bool m_14D;
	char m_pad14E[2];
	float m_150;
	bool m_154;
	bool m_155;
	char m_pad156[2];
	float m_158;
	float m_15C;
	Rva00360D26Member m_160;
};

Made002CC8A4::Made002CC8A4()
{
	m_128 = 0.0f;
	m_12C = 0.0f;
	m_130 = 3.1415927f;
	m_134 = false;
	m_138 = 0.0f;
	m_13C = 0.0f;
	m_140 = 1.0f;
	m_150 = 0.0f;
	m_144 = 0.0f;
	m_148 = 0;
	m_14C = false;
	m_14D = false;
	m_154 = false;
	m_155 = false;
	m_158 = 2.0f;
	m_15C = 100.0f;
	((Rva003623E5Member *)&m_160)->initFromStorages(
		BfmeFixedStorage0004543D(g_009FEFA4),
		BfmeFixedStorage0004543D(g_009FEFA4));
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_009FEFA4@@3VBfmeFixedStorage0004543D@@B=?g_00DFEFA4StoragePrototype@@3PAEA")

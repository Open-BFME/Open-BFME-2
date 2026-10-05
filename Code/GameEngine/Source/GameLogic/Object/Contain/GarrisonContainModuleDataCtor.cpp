// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ??0GarrisonContainModuleData@@QAE@XZ, retail 0x0047978F, 143 bytes
// (pinned). Over the pinned ModuleData base 0x00465124 (whose dtor
// 0x00257481 is state 0 of retail's unwind map): default the initial-roster
// name at +0xA4 (state 1), reset the base's +0x40 filter through 0x00362192
// with BitSet(0, 8) and a copy of the default storage at 0x00DFEFA4 (both
// built in place in the argument slots), then the Zero Hour defaults:
// mobile garrison, heal objects, frames for full heal (1.0 here),
// clear-building immunity and roster count. Field names follow ZH
// GarrisonContainModuleData; the +0x40 member is the Rva003623E5Member
// filter record (its rowed initFromStorages 0x00362087 is a sibling method),
// and 0x00362192 is pinned under an address name from this call and its three siblings (TunnelContain
// 0x002579D5, 0x0039A14A, 0x004A045E).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[0x1C];
};

class Rva00045411BitSet
{
public:
	Rva00045411BitSet(int a, int b);
	Rva00045411BitSet(const Rva00045411BitSet &other);
private:
	unsigned char m_bytes[0x1C];
};

extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

class Rva003623E5Member
{
public:
	void rva00362192(Rva00045411BitSet bits, BfmeFixedStorage0004543D storage);
private:
	unsigned char m_bytes[0x58];
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
private:
	void *m_data;
};

class OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();
protected:
	unsigned char m_pad04[0x3C];
	Rva003623E5Member m_filter40;
};

class GarrisonContainModuleData : public OpenContainModuleData
{
public:
	GarrisonContainModuleData();
	virtual ~GarrisonContainModuleData();
private:
	bool m_doIHealObjects;			// +0x98
	float m_framesForFullHeal;		// +0x9C
	bool m_mobileGarrison;			// +0xA0
	bool m_immuneToClearBuildingAttacks;	// +0xA1
	AsciiString m_initialRosterTemplateName;	// +0xA4
	int m_initialRosterCount;		// +0xA8
};

GarrisonContainModuleData::GarrisonContainModuleData()
{
	m_filter40.rva00362192(Rva00045411BitSet(0, 8), g_defaultStorage009FEFA4);
	m_mobileGarrison = false;
	m_doIHealObjects = false;
	m_framesForFullHeal = 1.0f;
	m_immuneToClearBuildingAttacks = false;
	m_initialRosterCount = 0;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_defaultStorage009FEFA4@@3VBfmeFixedStorage0004543D@@B=?g_00DFEFA4StoragePrototype@@3PAEA")

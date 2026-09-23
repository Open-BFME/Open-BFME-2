// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE /GX
// stlport
//
// ??0ModelConditionSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x00490DDB,
// 132 bytes. ModelCondition data ctor over the pinned Rva0044EB54 base
// (0x44EB54, 0xC8 bytes): installs vtable 0x00C4D828 via the ??_7 pin,
// constructs the ObjectFilter member at +0xD4 through the pinned 0x3623E5
// nullary, sets WhichSpecialPower at +0xC8 to 1, clears GenerateTerror at
// +0xCC and GenerateUncontrollableFear at +0xCD, loads EmotionPulseRadius
// at +0xD0 from the 50.0f pool literal, then feeds the filter a 28-byte
// temp copied from the 0xDFEFA4 mask global through the rowed
// BfmeFixedStorage0004543D copy into the pinned 0x362120 applyFilter.
// Table 0x00BEED0 proves the five fields at identical offsets; factory
// 0x24D6AB news 0xD8 (sole caller); pool key 0x490D96. Row supersedes the
// ctor pin. Recipe: DominateEnemy precedent verbatim (virtual base with
// declared-only dtor plus virtual derived, init-list base, body stores
// plus by-value applyFilter through a file-local defaults global).

class Rva0044EB54
{
public:
	Rva0044EB54();
	virtual ~Rva0044EB54();

private:
	unsigned char m_pad[0xC8 - 4];
};

class BfmeFixedStorage0004543D
{
	char m_bytes[28];
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};

extern const BfmeFixedStorage0004543D g_modelConditionFilterDefaults;

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D arg);
	~Rva003623E5Filter();

private:
	int m_handle;
};

const float c_emotionPulseRadiusDefault = 50.0f;

class ModelConditionSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	ModelConditionSpecialAbilityUpdateModuleData();
	virtual ~ModelConditionSpecialAbilityUpdateModuleData();

private:
	int m_whichSpecialPower; // +0xC8 WhichSpecialPower
	bool m_generateTerror; // +0xCC GenerateTerror
	bool m_generateUncontrollableFear; // +0xCD GenerateUncontrollableFear
	float m_emotionPulseRadius; // +0xD0 EmotionPulseRadius
	Rva003623E5Filter m_objectFilter; // +0xD4 ObjectFilter
};

// ??0ModelConditionSpecialAbilityUpdateModuleData@@QAE@XZ @0x490DDB
ModelConditionSpecialAbilityUpdateModuleData::ModelConditionSpecialAbilityUpdateModuleData()
	: Rva0044EB54()
{
	m_whichSpecialPower = 1;
	m_generateTerror = false;
	m_generateUncontrollableFear = false;
	m_emotionPulseRadius = c_emotionPulseRadiusDefault;
	m_objectFilter.applyFilter(g_modelConditionFilterDefaults);
}

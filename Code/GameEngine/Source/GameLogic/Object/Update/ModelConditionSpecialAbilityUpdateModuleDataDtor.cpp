// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE /DNDEBUG
//
// ??1ModelConditionSpecialAbilityUpdateModuleData@@UAE@XZ, retail 0x00490E7B,
// 56 bytes. Destroys the ObjectFilter at +0xD4 through the rowed pool member
// dtor 0x00360D26 under EH state 0, then calls the rowed base dtor
// ??1Rva0044ECCE@@UAE@XZ (0x0044ECCE). Layout follows the rowed ctor
// 0x00490DDB (ModelConditionSpecialAbilityUpdateModuleDataCtor2.cpp: base
// 0xC8, scalars +0xC8..+0xD0, filter +0xD4, vtable 0x00C4D828). Called by the
// rowed ??_G 0x00490E5F. No derived vptr store, so novtable as in
// WeaponFireSpecialAbilityUpdateModuleDataDtor.cpp.

class Rva0044ECCE
{
public:
	Rva0044ECCE();
	virtual ~Rva0044ECCE();

private:
	unsigned char m_pad[0xC8 - 4];
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	int m_handle;
};

class __declspec(novtable) ModelConditionSpecialAbilityUpdateModuleData : public Rva0044ECCE
{
public:
	virtual ~ModelConditionSpecialAbilityUpdateModuleData();

private:
	int m_whichSpecialPower; // +0xC8
	bool m_generateTerror; // +0xCC
	bool m_generateUncontrollableFear; // +0xCD
	float m_emotionPulseRadius; // +0xD0
	Rva00360D26Member m_objectFilter; // +0xD4
};

ModelConditionSpecialAbilityUpdateModuleData::~ModelConditionSpecialAbilityUpdateModuleData()
{
}

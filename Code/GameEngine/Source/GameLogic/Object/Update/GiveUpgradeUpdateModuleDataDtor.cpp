// cl: /O1 /GX /arch:SSE /MD /DNDEBUG
//
// ??1GiveUpgradeUpdateModuleData@@UAE@XZ, retail 0x0049C640, 62 bytes.
// Dtor over ctor TU layout GiveUpgradeUpdateModuleDataCtor.cpp (vtable
// 0x00851280 with slot 0 ??_G at 0x0049C624 calling here; base
// DamageModuleBase 0xC8 via pinned 0x44EB54 ctor and pinned 0x44ECCE dtor;
// vector payload at +0xC8 via folded Vector_base 0x211E58 plus ints at
// +0xD4/+0xD8 plus float at +0xDC plus bool at +0xE0 total 0xE4 matching
// factory 0x24E800 news). Frees buffer at +0xC8 via rowed _free 0x30830
// then base DamageModuleBase via pinned 0x44ECCE. Shape follows
// OilSpillUpdateDtor (void* plus free plus base) with HeroMode precedent
// (novtable suppresses derived vtable store retail lacks). Donor: BFME1
// GiveUpgradeUpdateModuleDataDestructor.cpp virtual dtor.
extern "C" void free(void *p);

class DamageModuleBase
{
public:
	virtual ~DamageModuleBase();

private:
	unsigned char m_pad[0xC8 - 4];
};

class __declspec(novtable) GiveUpgradeUpdateModuleData : public DamageModuleBase
{
public:
	virtual ~GiveUpgradeUpdateModuleData();

private:
	void *m_bufC8; // +0xC8 vector payload stand-in
	unsigned char m_padCC[0xD4 - 0xCC]; // +0xCC..+0xD3 vector tail stand-in
	int m_intD4; // +0xD4
	int m_intD8; // +0xD8
	float m_floatDC; // +0xDC
	bool m_flagE0; // +0xE0
	unsigned char m_padE1[0xE4 - 0xE1];
};

GiveUpgradeUpdateModuleData::~GiveUpgradeUpdateModuleData()
{
	if (m_bufC8)
		free(m_bufC8);
}

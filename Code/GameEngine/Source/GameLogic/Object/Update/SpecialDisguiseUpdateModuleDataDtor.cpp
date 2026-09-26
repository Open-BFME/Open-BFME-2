// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
//
// ??1SpecialDisguiseUpdateModuleData@@UAE@XZ, retail 0x004B0468, 74 bytes.
// SpecialDisguiseUpdate ModuleData dtor (ctor rowed at 0x004B0255 in
// SpecialDisguiseUpdateModuleDataCtor.cpp, vtable 0x008563F8 with slot 0
// ??_G at 0x004B044C). Destroys the AsciiString members at +0xD4 (state 1)
// then +0xD0 (state 0) through the pinned 0x36410 body (AsciiString pin
// shares the address with the StringBase<char> pin), then the
// DamageModuleBase base through the pinned 0x44ECCE body. Layout follows the
// ctor TU (0xC8 base plus bool at +0xC8 plus float at +0xCC plus strings at
// +0xD0/+0xD4 plus int at +0xD8 plus bool at +0xDC, total 0xE0 matching the
// factory news) and table 0xBEF8B8. novtable suppresses the derived vtable
// store retail lacks. Donor: BFME1
// SpecialDisguiseUpdateModuleDataDestructorThunk.cpp virtual dtor.

class DamageModuleBase
{
public:
	virtual ~DamageModuleBase();

private:
	unsigned char m_pad[0xC8 - 4];
};

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class __declspec(novtable) SpecialDisguiseUpdateModuleData : public DamageModuleBase
{
public:
	virtual ~SpecialDisguiseUpdateModuleData();

private:
	bool m_triggerInstantlyOnCreate; // +0xC8
	unsigned char m_padC9[3];
	float m_opacityTarget; // +0xCC
	AsciiString m_disguiseAsTemplate; // +0xD0
	AsciiString m_disguisedAsEnemy; // +0xD4
	int m_disguiseFX; // +0xD8
	bool m_forceMounted; // +0xDC
	unsigned char m_padDD[3];
};

SpecialDisguiseUpdateModuleData::~SpecialDisguiseUpdateModuleData()
{
}

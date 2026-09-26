// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
//
// ??1HeroModeSpecialAbilityUpdateModuleData@@UAE@XZ, retail 0x004922F1, 56 bytes.
// HeroModeSpecialAbilityUpdate ModuleData dtor (ctor rowed at 0x0049227B in
// HeroModeSpecialAbilityUpdateModuleDataCtor.cpp, vtable 0x0084DF58 with slot 0
// ??_G at 0x004922D5). Destroys the AsciiString member at +0xC8 through the
// pinned 0x36410 body (AsciiString pin shares the address with the
// StringBase<char> pin), then the DamageModuleBase base through the pinned
// 0x44ECCE body. Layout follows the ctor TU (0xC8 base plus string at +0xC8
// plus int at +0xCC plus bools at +0xD0/+0xD1). novtable suppresses the
// derived vtable store retail lacks; the base call restores the base table.
// Donor: BFME1 HeroModeSpecialAbilityUpdateModuleDataCtorThunk.cpp virtual dtor.

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

class __declspec(novtable) HeroModeSpecialAbilityUpdateModuleData : public DamageModuleBase
{
public:
	virtual ~HeroModeSpecialAbilityUpdateModuleData();

private:
	AsciiString m_stringC8; // +0xC8
	int m_intCC; // +0xCC
	bool m_flagD0; // +0xD0
	bool m_flagD1; // +0xD1
};

HeroModeSpecialAbilityUpdateModuleData::~HeroModeSpecialAbilityUpdateModuleData()
{
}

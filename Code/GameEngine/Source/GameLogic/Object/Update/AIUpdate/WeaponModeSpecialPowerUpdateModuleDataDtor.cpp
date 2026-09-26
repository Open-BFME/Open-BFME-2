// cl: /O1 /GX /DNDEBUG /MD
//
// ??1WeaponModeSpecialPowerUpdateModuleData@@UAE@XZ, retail 0x00494D7C, 53 bytes.
// WeaponMode ModuleData dtor: destroys the AsciiString member at +0x18 via
// the folded StringBase<char> body at 0x00036410, then calls the rowed base
// ??1AIUpdateModuleData@@UAE@XZ at 0x00494BE4. No derived vtable store
// (novtable, like FXListAtBonePosFXNuggetDtor sibling); single EH state for
// the string member (EH prolog with funclet 0xB8CEF8). Layout from the rowed
// ctor at 0x00494D26 (vtable 0x0084EA88 at +0, base AIUpdateModuleData 0x18
// bytes, string at +0x18, ints at +0x1C/+0x20, bitset at +0x24) with slot 0
// ??_G at 0x00494D60 calling here. Shape follows BuffNuggetFXNuggetDtor /
// FXListAtBonePosFXNuggetDtor (TU-local AsciiString via folded 0x36410,
// empty novtable derived body, base call last).

template <typename T>
class StringBase
{
	friend class AsciiString;

protected:
	~StringBase();

	void *m_data;

private:
	StringBase(const char *str);
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *str) : StringBase<char>(str) {}
	~AsciiString();
};

class AIUpdateModuleData
{
public:
	virtual ~AIUpdateModuleData();

private:
	unsigned char m_base[0x18 - 4];
};

class __declspec(novtable) WeaponModeSpecialPowerUpdateModuleData : public AIUpdateModuleData
{
public:
	virtual ~WeaponModeSpecialPowerUpdateModuleData();

private:
	AsciiString m_str18; // +0x18
	int m_1C; // +0x1C
	int m_count20; // +0x20
	unsigned long m_bits24[4]; // +0x24
};

typedef char BaseExtent[sizeof(AIUpdateModuleData) == 0x18 ? 1 : -1];
typedef char AsciiExtent[sizeof(AsciiString) == 4 ? 1 : -1];

WeaponModeSpecialPowerUpdateModuleData::~WeaponModeSpecialPowerUpdateModuleData()
{
}

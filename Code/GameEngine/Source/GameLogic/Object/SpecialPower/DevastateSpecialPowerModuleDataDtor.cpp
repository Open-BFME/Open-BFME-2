// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1DevastateSpecialPowerModuleData@@UAE@XZ, retail 0x004C8537, 56 bytes.
// DevastateSpecialPower ModuleData dtor (ctor rowed at 0x004C84BD in
// DevastateSpecialPowerModuleDataCtor.cpp, vtable 0x00C5E518 with slot 0
// ??_G at 0x004C851B). Destroys the AsciiString member at +0x8C through the
// pinned 0x00036410 body, then the SpecialPowerModuleData base through the rowed
// 0x0049334F body. Layout follows the ctor TU (0x7C base plus float at
// +0x7C plus FX at +0x80 plus floats at +0x84/+0x88 plus FireWeapon string
// at +0x8C, total 0x90 matching the factory 0x00252653 news). novtable
// suppresses the derived vtable store retail lacks (CloudBreak precedent);
// the base call restores the base table.

template <typename T>
class StringBase
{
public:
	~StringBase();

private:
	T *m_data;
};

class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C - 4];
};

class __declspec(novtable) DevastateSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~DevastateSpecialPowerModuleData();

private:
	float m_radius; // +0x7C
	void *m_fx; // +0x80
	float m_treeValueMultiplier; // +0x84
	float m_treeValueTotalCap; // +0x88
	StringBase<char> m_fireWeapon; // +0x8C
};

DevastateSpecialPowerModuleData::~DevastateSpecialPowerModuleData()
{
}

// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1TaintSpecialPowerModuleData@@UAE@XZ, retail 0x004C4B07, 53 bytes.
// TaintSpecialPower ModuleData dtor (ctor rowed at 0x004C4AB8 in
// TaintSpecialPowerModuleDataCtor.cpp, vtable 0x00C5D608 with slot 0 ??_G
// at 0x004C4AEB). Destroys the AsciiString member at +0x7C through the
// pinned 0x00036410 body, then the SpecialPowerModuleData base through the rowed
// 0x0049334F body. Layout follows the ctor TU (0x7C base plus string at
// +0x7C plus float at +0x80 plus ints at +0x84/+0x88, total 0x8C).
// novtable suppresses the derived vtable store retail lacks (Invisibility
// precedent); the base call restores the base table.

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

class __declspec(novtable) TaintSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~TaintSpecialPowerModuleData();

private:
	StringBase<char> m_taintObject; // +0x7C
	float m_taintRadius; // +0x80
	int m_taintFX; // +0x84
	int m_taintOCL; // +0x88
};

TaintSpecialPowerModuleData::~TaintSpecialPowerModuleData()
{
}

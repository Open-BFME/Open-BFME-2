// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??0W3DSupplyDrawModuleData@@QAE@XZ, retail 0x000CAF17, 25 bytes.
// W3DSupplyDraw ModuleData ctor: calls the W3DModelDrawModuleData base ctor
// (pinned at 0xC8EEF), installs vtable 0xBCC0D0, zeroes the single INI
// string slot at +0x188 (SupplyBonePrefix per the chained table; the
// sibling dtor at 0xCAF30 tears it down through the AsciiString dtor at
// 0x36410, proving the type). Layout is the base 0x188 bytes plus one
// AsciiString; the factory at 0x64A61 news 0x18C (= 0x188 + 4) and is the
// sole caller of this ctor. Same opaque-base + explicit-vtable recipe as
// the landed W3DTruckDrawModuleData ctor.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	const char *m_data;
};

class W3DModelDrawModuleData
{
public:
	W3DModelDrawModuleData();
};

class W3DSupplyDrawModuleData : public W3DModelDrawModuleData
{
public:
	W3DSupplyDrawModuleData();

private:
	const void *m_vtable; // +0x00
	// Base occupies +0x04..+0x187 (0x188 bytes); the base ctor fills it.
	unsigned char m_basePad[0x188 - 4]; // +0x04
	AsciiString m_supplyBonePrefix; // +0x188
};

// ??0W3DSupplyDrawModuleData@@QAE@XZ @0xCAF17
W3DSupplyDrawModuleData::W3DSupplyDrawModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BCC0D0))
{
}

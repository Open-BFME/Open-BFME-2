// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??1W3DProjectileStreamDrawModuleData@@UAE@XZ, retail 0x000D1226, 54 bytes.
// W3DProjectileStreamDraw ModuleData dtor: reinstalls vtable 0x00BCDF18,
// tears down Texture string at +0x08 through the folded AsciiString dtor at
// 0x00036410, then installs base vtable 0x00BBB554 with trivial inline base.
// File-unit companion to the landed ctor at 0x000D11D2.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	void *m_data;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	virtual ~UpdateModuleData() {}
};

class W3DProjectileStreamDrawModuleData : public UpdateModuleData
{
public:
	W3DProjectileStreamDrawModuleData();
	virtual ~W3DProjectileStreamDrawModuleData();

private:
	unsigned int m_unused04; // +0x04
	AsciiString m_texture; // +0x08
	float m_width; // +0x0C
	float m_tileFactor; // +0x10
	float m_scrollRate; // +0x14
	int m_maxSegments; // +0x18
};

W3DProjectileStreamDrawModuleData::~W3DProjectileStreamDrawModuleData()
{
}

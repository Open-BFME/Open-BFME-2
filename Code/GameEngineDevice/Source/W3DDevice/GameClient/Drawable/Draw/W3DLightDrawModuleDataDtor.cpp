// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// ??1W3DLightDrawModuleData@@UAE@XZ, retail 0x000CFBA9, 54 bytes.
// W3DLightDraw ModuleData dtor: reinstalls the vtable 0x00BCD820, tears
// down the AttachToBoneInAnotherModule string at +0x44 through the folded
// AsciiString dtor at 0x36410 (pin ??1AsciiString@@QAE@XZ), then restores
// the Snapshot base vtable 0x00BBB554 through the TU-local inline base
// dtor. Single EH state for the one string member; frameless companion
// ctor at 0xCFB3E proves the layout (vptr +0, pad +0x04..+0x43, string
// +0x44, size 0x48 per the factory at 0x64E2F). Shape follows the landed
// W3DSupplyDrawModuleDataDtor TU; the own vtable resolves through the
// ??_7 pin at 0x00BCD820.

class Snapshot
{
public:
	virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class W3DLightDrawModuleData : public Snapshot
{
public:
	virtual ~W3DLightDrawModuleData();

private:
	unsigned char m_pad04[0x44 - 4]; // +0x04
	AsciiString m_attachToBone; // +0x44 AttachToBoneInAnotherModule
};

// ??1W3DLightDrawModuleData@@UAE@XZ @0xCFBA9
W3DLightDrawModuleData::~W3DLightDrawModuleData()
{
}

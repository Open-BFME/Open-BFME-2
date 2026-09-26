// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
//
// ??1AODCrushCollideModuleData@@UAE@XZ, retail 0x004BC088, 48 bytes.
// Collide-side ModuleData dtor (ctor rowed at 0x004BBF89 in
// AODCrushCollideModuleDataCtor.cpp, vtable 0x0085A350 with slot 0 ??_G at
// 0x004BC06C). Tears down the filter member at +0x2C through the pinned
// 0x360D26 body, then restores the Snapshot base vtable 0x00BBB554. Layout
// follows the ctor TU and its table 0x0085A4A8 (six FX/OCL slots at
// +0x08/+0x0C/+0x10/+0x14/+0x18/+0x1C plus DamageType at +0x20 plus pad at
// +0x24 plus Damage at +0x28 plus filter at +0x2C). Empty derived body;
// novtable suppresses the derived store retail lacks (Topple precedent).

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class __declspec(novtable) AODCrushCollideModuleData : public Snapshot
{
public:
	virtual ~AODCrushCollideModuleData();

private:
	int m_unused04; // +0x04
	void *m_smallFX; // +0x08
	void *m_smallOCL; // +0x0C
	void *m_mediumFX; // +0x10
	void *m_mediumOCL; // +0x14
	void *m_largeFX; // +0x18
	void *m_largeOCL; // +0x1C
	int m_damageType; // +0x20
	int m_unused24; // +0x24
	float m_damage; // +0x28
	Rva00360D26Member m_filter; // +0x2C
};

AODCrushCollideModuleData::~AODCrushCollideModuleData()
{
}

// cl: /O1 /GX /arch:SSE /DNDEBUG /MD
//
// ??1ToppleUpdateModuleData@@UAE@XZ, retail 0x004A83A7, 48 bytes.
// ModuleData dtor: tears down the StumpName string at +0x10 through the
// folded 0x36410 body (AsciiString pin shares the address with the
// StringBase<char> pin retail calls), then restores the Snapshot base
// vtable 0x00BBB554. Empty derived body; the string is the only tracked
// member giving EH state 0 exactly as retail. Shape follows the landed
// SpecialEnemySenseUpdateModuleDataDtor (same 48B single-member plus
// BBB554 restore with TU-local Snapshot and novtable suppressing the
// derived store). Layout from the rowed ctor 0x004A8173 (vtable 0x00C538A0
// at +0 plus unused +4 plus ToppleFX +8 plus BounceFX +0x0C plus StumpName
// +0x10 plus four reals +0x14/+0x18/+0x1C/+0x20 plus five flags
// +0x24/+0x25/+0x26/+0x27/+0x28) joined to the ZH ToppleUpdate donor and
// the own INI table at 0x00C53980. Caller is the slot-0 ??_G at 0x004A838B
// (vtable 0x008538A0). BFME1 donor hits ToppleUpdateModuleDataDestructorThunk.

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

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class __declspec(novtable) ToppleUpdateModuleData : public Snapshot
{
public:
	virtual ~ToppleUpdateModuleData();

private:
	int m_unused04; // +0x04
	void *m_toppleFX; // +0x08
	void *m_bounceFX; // +0x0C
	AsciiString m_stumpName; // +0x10
	float m_initialVelocityPercent; // +0x14
	float m_initialAccelPercent; // +0x18
	float m_bounceVelocityPercent; // +0x1C
	float m_minimumToppleSpeed; // +0x20
	bool m_killWhenToppled; // +0x24
	bool m_killWhenStartToppled; // +0x25
	bool m_killStumpWhenToppled; // +0x26
	bool m_toppleLeftOrRightOnly; // +0x27
	bool m_reorientToppledRubble; // +0x28
};

ToppleUpdateModuleData::~ToppleUpdateModuleData()
{
}

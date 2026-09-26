// cl: /O1 /GX /DNDEBUG /MD
//
// ??1AudioLoopUpgradeModuleData@@UAE@XZ, retail 0x004B7C4C, 58 bytes.
// AudioLoop upgrade ModuleData dtor: restores own vtable 0x00C58CF8, releases
// the +0x08 sound holder through rowed Release_Ref at 0x50ED3 when non-null,
// then restores Snapshot base vtable 0x00BBB554. Holder dtor is inline and
// throwing (EH-tracked state 0); +0x14/+0x124 members are trivial pads.
// Layout from ctor TU (factory 0x250798 news 0x154); shape follows
// FlammableUpdateModuleDataDtor (Release_Ref holder plus BBB554 base).

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

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct SoundHolder
{
	~SoundHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

class AudioLoopUpgradeModuleData : public Snapshot
{
public:
	virtual ~AudioLoopUpgradeModuleData();

private:
	int m_unused04;
	SoundHolder m_sound08;
	int m_killAfter0C;
	bool m_killOnDeath10;
	unsigned char m_pad11[3];
	unsigned char m_member14[0x110];
	unsigned char m_die124[0x30];
};

// ??1AudioLoopUpgradeModuleData@@UAE@XZ @0x004B7C4C
AudioLoopUpgradeModuleData::~AudioLoopUpgradeModuleData()
{
}

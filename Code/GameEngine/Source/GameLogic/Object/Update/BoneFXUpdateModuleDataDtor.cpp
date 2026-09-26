// cl: /O1 /GX /DNDEBUG /MD
//
// ??1BoneFXUpdateModuleData@@UAE@XZ, retail 0x00487877, 111 bytes.
//
// BoneFXUpdateModuleData virtual dtor. Same layout as the rowed ctor TU
// (BoneFXUpdateModuleDataCtor.cpp): Snapshot base (vtable at +0, base
// restores 0xBBB554 via inline dtor, RefundDie precedent), unused04 at +4,
// damage words at +8/+0x48C/+0x910, three [4][8] 0x24-byte arrays at
// +0x0C/+0x490/+0x914 with AsciiString at +0 (declared-only dtor folds to
// the rowed 0x48BA39 clear/dtor). Empty body: the three reverse-order
// ??_M array destroys (0x629110 helper, dtor 0x48BA39, count 0x20, size
// 0x24) plus the base restore are compiler-generated. No base call in
// retail (Snapshot dtor inline). /O1 /GX matches the ctor TU and gives the
// EH prologue with states 2/1/0 exactly as retail.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class GameClientRandomVariable
{
public:
	float getValue() const;

private:
	int m_type;
	float m_low;
	float m_high;
};

class GameLogicRandomVariable
{
public:
	float getValue() const;

private:
	int m_type;
	float m_low;
	float m_high;
};

class FXList;
class ObjectCreationList;
class ParticleSystemTemplate;

struct BoneFXListInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	bool onlyOnce;
	unsigned char m_pad[3];
	const FXList *fx;
};

struct BoneOCLInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	bool onlyOnce;
	unsigned char m_pad[3];
	const ObjectCreationList *ocl;
};

struct BoneParticleSystemInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	bool onlyOnce;
	unsigned char m_pad[3];
	const ParticleSystemTemplate *particleSysTemplate;
};

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

enum { BONE_FX_MAX_BONES = 8 };
enum { BODYDAMAGETYPE_COUNT = 4 };

class __declspec(novtable) BoneFXUpdateModuleData : public Snapshot
{
public:
	virtual ~BoneFXUpdateModuleData();

private:
	unsigned int m_unused04;
	int m_damageFXTypes;
	BoneFXListInfo m_fxList[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_damageOCLTypes;
	BoneOCLInfo m_OCL[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_damageParticleTypes;
	BoneParticleSystemInfo m_particleSystem[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
};

BoneFXUpdateModuleData::~BoneFXUpdateModuleData()
{
}

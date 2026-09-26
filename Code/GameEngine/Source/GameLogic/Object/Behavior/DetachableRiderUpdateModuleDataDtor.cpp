// cl: /O1 /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1DetachableRiderUpdateModuleData@@UAE@XZ, retail 0x004AEB3F, 69 bytes.
// DetachableRiderUpdate ModuleData dtor (ctor rowed at 0x004AEAB7 in
// PropagandaTowerBehaviorModuleDataCtor.cpp, vtable 0x00855510 with slot 0
// ??_G at 0x004AEB23). Destroys the AsciiString vector at +0x14 through the
// rowed 0x2CC70 body (state 1), frees the trivial-vector storage at +0x08
// through the rowed _free at 0x30830 (state 0), then restores the Snapshot
// base vtable 0x00BBB554. Layout follows the ctor TU (two vectors at
// +0x08/+0x14 plus int at +0x20 plus bytes at +0x24/+0x25, factory news
// 0x28). novtable suppresses the derived store retail lacks (CivilianSpawn
// precedent).
#include <vector>

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

extern "C" void free(void *block);

struct TrivialVec08
{
	~TrivialVec08()
	{
		if (m_start != 0)
			free(m_start);
	}

	void *m_start;
	void *m_finish;
	void *m_end;
};

class __declspec(novtable) DetachableRiderUpdateModuleData : public Snapshot
{
public:
	virtual ~DetachableRiderUpdateModuleData();

private:
	int m_unused04; // +0x04
	TrivialVec08 m_vec08; // +0x08 trivial 16-byte-element vector storage
	_STL::vector<AsciiString> m_vec14; // +0x14
	int m_unk20; // +0x20
	unsigned char m_unk24; // +0x24
	unsigned char m_unk25; // +0x25
};

DetachableRiderUpdateModuleData::~DetachableRiderUpdateModuleData()
{
}

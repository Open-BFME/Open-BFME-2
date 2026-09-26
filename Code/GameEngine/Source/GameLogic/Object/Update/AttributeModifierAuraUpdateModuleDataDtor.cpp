// cl: /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ??1AttributeModifierAuraUpdateModuleData@@UAE@XZ, retail 0x0049BF6C,
// 75 bytes. Aura-side ModuleData dtor: destroys the ObjectFilter at +0x24
// through the pinned 0x360D26 forwarder (state 2) then the AsciiString
// vector at +0x0C through the rowed 0x2CC70 body (state 1) then the
// BonusName string at +0x08 through the folded 0x36410 (state 0) then
// restores the Snapshot base vtable 0x00BBB554. Layout from the rowed ctor
// 0x0049BBD5 (vtable 0x00C50EE8 plus string +0x08 plus vector +0x0C via
// 0x211E58 plus filter +0x24 via 0x3623E5 plus member +0x28 plus table
// 0x00C50DC8 plus factory 0x24E65C news 0x154) and the slot-0 ??_G at
// 0x0049BF50. Shape follows LargeGroupBonusUpdateModuleDataDtor (TU-local
// Snapshot with inline BBB554-restoring dtor plus novtable derived
// suppressing the entry store retail lacks plus filter plus vector plus
// string members). Donor is BFME1
// AttributeModifierAuraUpdateModuleDataDestructorThunk.cpp:59.

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

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class __declspec(novtable) AttributeModifierAuraUpdateModuleData : public Snapshot
{
public:
	virtual ~AttributeModifierAuraUpdateModuleData();

private:
	int m_unused04; // +0x04
	AsciiString m_bonusName; // +0x08
	_STL::vector<AsciiString> m_vec0C; // +0x0C
	int m_refreshDelay; // +0x18
	float m_range; // +0x1C
	bool m_allowPower; // +0x20
	bool m_targetEnemy; // +0x21
	unsigned char m_pad22[2];
	Rva00360D26Member m_filter24; // +0x24
	unsigned char m_pad28[0x154 - 0x28];
};

// ??1AttributeModifierAuraUpdateModuleData@@UAE@XZ @0x0049BF6C
AttributeModifierAuraUpdateModuleData::~AttributeModifierAuraUpdateModuleData()
{
}

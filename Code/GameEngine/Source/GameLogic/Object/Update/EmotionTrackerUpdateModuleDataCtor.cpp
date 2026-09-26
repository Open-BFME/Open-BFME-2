// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy- /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0EmotionTrackerUpdateModuleData@@QAE@XZ, retail 0x004B115A (299 bytes).
// EmotionTracker data ctor over the BFME1 EmotionTrackerUpdate donor (value
// fields, four name/filter members, entry vector). RespawnBodyModuleDataCtor
// precedent: virtual class with declared-only virtual dtor over an
// UpdateModuleData base (inline-empty ctor, declared-only dtor, vtable plus
// m_value04), EH states from the non-trivial members, FixedStorage by-value
// temps copy-constructed in place from the prototype at 0x00DFEFA4 through
// the rowed copy ctor, consumed by value through the pinned initFromStorages.
// BFME2 changes from the donor: +0x08 zeroes as a float, four filter members
// construct through the opaque 0x3623E5 pin (4-byte stride, Respawn spelling),
// +0x30 is a new int retail sets to 5, and the entry vector at +0x34 builds
// through the rowed E16 Vector_base (BfmeE16 stand-in spelling, e16 precedent:
// only the 16-byte element size is evidence-backed). Factory 0x24FAF0 news
// 0x40 (sole caller); proc 0x4B235D is the rowed buildFieldParse.

#include <vector>

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

struct BfmeE16 { float x, y, z, w; };

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	virtual ~UpdateModuleData();

private:
	unsigned int m_value04;
};

class EmotionTrackerUpdateModuleData : public UpdateModuleData
{
public:
	EmotionTrackerUpdateModuleData();
	virtual ~EmotionTrackerUpdateModuleData();

private:
	float m_float08;							// +0x08 retail zeroes as float
	unsigned int m_value0C : 32;				// +0x0C retail zeroes via and
	Rva003623E5Member m_name0;					// +0x10
	Rva003623E5Member m_name1;					// +0x14
	Rva003623E5Member m_name2;					// +0x18
	Rva003623E5Member m_name3;					// +0x1C
	float m_value20;							// +0x20
	float m_value24;							// +0x24
	float m_value28;							// +0x28
	unsigned char m_flag2C;						// +0x2C
	unsigned char m_pad2D[3];
	unsigned int m_unk30;						// +0x30 retail sets 5; no donor counterpart
	_STL::vector<BfmeE16> m_entries;			// +0x34
};

// ??0EmotionTrackerUpdateModuleData@@QAE@XZ @0x4B115A
EmotionTrackerUpdateModuleData::EmotionTrackerUpdateModuleData()
	: m_float08( 0.0f )
	, m_value0C( 0 )
	, m_value20( 0.0f )
	, m_value24( 0.0f )
	, m_value28( 0.0f )
	, m_flag2C( 0 )
	, m_unk30( 5 )
{
	m_name0.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
	m_name1.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
	m_name2.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
	m_name3.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}

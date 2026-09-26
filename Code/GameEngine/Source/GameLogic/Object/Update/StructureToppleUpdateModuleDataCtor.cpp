// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0StructureToppleUpdateModuleData@@QAE@XZ, retail 0x00257A5E, 256 bytes.
// StructureTopple data ctor over vtable 0x00BF43A8. Donor is ZH
// StructureToppleUpdate.h (same member order and values) with BFME2
// changes: DieMuxData member at +8 constructed through its rowed init at
// 0x004CE534, an extra float at +0x48 (0.06), the damage-flags word as -1
// at +0x4C, and an extra float at +0xB8. Total size 0xBC matches the
// friend_newModuleData `new 0xBC`.
//
// Layout: vtable slot +0, DieMuxData +8 (0x30, opaque: retail issues no
// member-construction calls for it, only init), delays +0x38/+0x3C,
// integrity +0x40 (0.1), decay +0x44, unk48 +0x48 (0.06), unk4C +0x4C (-1
// via the or-idiom), five FXList nulls +0x50..+0x60, crushing weapon
// string +0x64 (zero-init then set("")), burst delays +0x68/+0x6C,
// OCLVec m_ocls[3] +0x70 (3 12B vectors through ehvecctor 0x629512; the
// element setup/teardown immediates are DIR32 slots the patcher copies
// from retail per the CrushDie precedent), oclCount triple +0x94 (1,1,1
// via unrolled pointer stores), fxbones +0xA0 (8B FXBoneInfo, E16 base
// plus erase-clear through rowed 0x207F0D), angleFX +0xAC (8B
// AngleFXInfo, E16 base plus erase-clear through the Pod8 alias at
// 0x3FA4DB), trailer float +0xB8.
//
// Schedule notes: the DieMux init call sits at the member-construction
// position, so the member is modeled with an inline default ctor that
// forwards to init (no separate construction call exists in retail). The
// scalar stores, the weapon set, the oclCount stores and the two erases
// are body statements (ProductionUpdate erase-begin-end idiom for both;
// named reference for fxbones to home the base, direct for angleFX).
// The empty UpdateModuleData base (declared-only dtor) carries
// unwindability for EH states 0/1/4; the vector bases arm none.

#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;

class AsciiString
{
public:
	AsciiString(int zero) : m_data(reinterpret_cast<void *>(zero)) {}
	~AsciiString();
	void set(const char *str);

private:
	void *m_data;
};

struct FXBoneInfo
{
	AsciiString m_boneName;
	const void *m_particleSystemTemplate;
};

struct AngleFXInfo
{
	float m_angle;
	const void *m_fxList;
};

class ObjectCreationList;

class DieMuxData
{
public:
	DieMuxData() { init(); }
	DieMuxData *init();

private:
	unsigned char m_data[0x30];
};

enum
{
	ST_PHASE_COUNT = 3,
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

namespace _STL
{

// Declared-only explicit specializations: keep the calls external (the
// FXBoneInfo erase resolves to its rowed true name; the two _Vector_base
// ctors and the AngleFXInfo erase resolve through twin/alias pins) and
// throwing (retail arms EH states around the later calls only).
template <>
_Vector_base<FXBoneInfo, allocator<FXBoneInfo> >::_Vector_base(
	const allocator<FXBoneInfo> &storage) throw();
template <>
_Vector_base<AngleFXInfo, allocator<AngleFXInfo> >::_Vector_base(
	const allocator<AngleFXInfo> &storage) throw();
template <>
vector<FXBoneInfo, allocator<FXBoneInfo> >::iterator
vector<FXBoneInfo, allocator<FXBoneInfo> >::erase(
	vector<FXBoneInfo, allocator<FXBoneInfo> >::iterator first,
	vector<FXBoneInfo, allocator<FXBoneInfo> >::iterator last);
template <>
vector<AngleFXInfo, allocator<AngleFXInfo> >::iterator
vector<AngleFXInfo, allocator<AngleFXInfo> >::erase(
	vector<AngleFXInfo, allocator<AngleFXInfo> >::iterator first,
	vector<AngleFXInfo, allocator<AngleFXInfo> >::iterator last);

}

class StructureToppleUpdateModuleData : public UpdateModuleData
{
public:
	StructureToppleUpdateModuleData();

private:
	const void *m_vtable; // +0, retail 0x00BF43A8
	int m_unused04; // +4, untouched padding
	DieMuxData m_dieMuxData; // +8
	Int m_minToppleDelay; // +0x38
	Int m_maxToppleDelay; // +0x3C
	float m_structuralIntegrity; // +0x40
	float m_structuralDecay; // +0x44
	float m_unk48; // +0x48
	Int m_unk4C; // +0x4C
	void *m_toppleStartFXList; // +0x50
	void *m_toppleDelayFXList; // +0x54
	void *m_toppleDoneFXList; // +0x58
	void *m_toppleFXList; // +0x5C
	void *m_crushingFXList; // +0x60
	AsciiString m_crushingWeaponName; // +0x64
	Int m_minToppleBurstDelay; // +0x68
	Int m_maxToppleBurstDelay; // +0x6C
	_STL::vector<const ObjectCreationList *,
		_STL::allocator<const ObjectCreationList *> > m_ocls[3]; // +0x70
	Int m_oclCount[3]; // +0x94
	_STL::vector<FXBoneInfo, _STL::allocator<FXBoneInfo> > m_fxbones; // +0xA0
	_STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> > m_angleFX; // +0xAC
	float m_unkB8; // +0xB8
};

// ??0StructureToppleUpdateModuleData@@QAE@XZ @0x00257A5E
StructureToppleUpdateModuleData::StructureToppleUpdateModuleData()
	: UpdateModuleData()
	, m_vtable(reinterpret_cast<const void *>(0x00BF43A8))
	, m_crushingWeaponName(0)
{
	m_minToppleDelay = 0;
	m_maxToppleDelay = 0;
	m_structuralIntegrity = 0.1f;
	m_unk4C = -1;
	m_minToppleBurstDelay = 0;
	m_maxToppleBurstDelay = 0;
	m_structuralDecay = 0.0f;
	m_toppleStartFXList = 0;
	m_toppleDelayFXList = 0;
	m_toppleFXList = 0;
	m_toppleDoneFXList = 0;
	m_crushingFXList = 0;
	m_crushingWeaponName.set("");
	m_unk48 = 0.06f;
	m_unkB8 = -9.87654f;
	for (int i = 0; i < ST_PHASE_COUNT; ++i)
		m_oclCount[i] = 1;
	_STL::vector<FXBoneInfo, _STL::allocator<FXBoneInfo> > &bones = m_fxbones;
	bones.erase(bones.begin(), bones.end());
	_STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> > &angleBones = m_angleFX;
	angleBones.erase(angleBones.begin(), angleBones.end());
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0TransitionDamageFXModuleData@@QAE@XZ, retail 0x004BA58A, 367 bytes.
// TransitionDamageFX ModuleData ctor over three [4][12] 0x1C records plus
// two [4] vector wrappers plus tail vector. Donor is BFME1 TransitionDamageFX
// ctor (null + zero + COORD + FALSE over [4][12], flip flags) plus BFME2
// vector tail (Vector_base 0x211E58 plus EraseRange 0x4BA399, Production
// precedent). Layout matches the landed destructor thunk (base 0xC, arrays
// at +0xC/+0x550/+0xA94, wrappers at +0xFD4/+0x1004, tail at +0x1034).
// Evidence: factory 0x2549E2 news 0x1040 sole caller; vtable 0xC59B20;
// callees rowed Vector_base 0x211E58 plus EraseRange 0x4BA399.

#include <vector>

typedef int Int;

struct TransitionDamageFXRecordA
{
	TransitionDamageFXRecordA();
	~TransitionDamageFXRecordA();

	void *m_value;
	unsigned char m_locType;
	unsigned char m_pad05[3];
	unsigned char m_boneName[4];
	unsigned char m_randomBone;
	unsigned char m_pad0D[3];
	float m_loc[3];
};

struct TransitionDamageFXRecordB
{
	TransitionDamageFXRecordB();
	~TransitionDamageFXRecordB();

	void *m_value;
	unsigned char m_locType;
	unsigned char m_pad05[3];
	unsigned char m_boneName[4];
	unsigned char m_randomBone;
	unsigned char m_pad0D[3];
	float m_loc[3];
};

struct TransitionDamageFXRecordC
{
	TransitionDamageFXRecordC();
	~TransitionDamageFXRecordC();

	void *m_value;
	unsigned char m_locType;
	unsigned char m_pad05[3];
	unsigned char m_boneName[4];
	unsigned char m_randomBone;
	unsigned char m_pad0D[3];
	float m_loc[3];
};

class TransitionSmallVec
{
public:
	TransitionSmallVec();
	~TransitionSmallVec();

private:
	unsigned char m_data[0x0C];
};

class Rva004BA1C8
{
public:
	~Rva004BA1C8();
	Rva004BA1C8 &operator=(const Rva004BA1C8 &other);

private:
	unsigned char m_data[0x2C];
};

namespace _STL
{

// Declared-only explicit specialization: keep the call external (resolved
// through twin pin to the folded BfmeE16 base at 0x211E58) and nothrow
// (retail does not arm a state before this call; it stays at 4 then arms 6
// before the loop for the throwing EraseRange; throw() removes the state).
// ProductionUpdate precedent arms states for throwing bases; here the base
// is nothrow per retail bytes.
template <>
_Vector_base<Rva004BA1C8, allocator<Rva004BA1C8> >::_Vector_base(
	const allocator<Rva004BA1C8> &storage) throw();

}

class Rva004BA399Vector
{
public:
	Rva004BA1C8 *EraseRange(Rva004BA1C8 *first, Rva004BA1C8 *last);

private:
	Rva004BA1C8 *m_first;
	Rva004BA1C8 *m_finish;
	int m_end;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

enum { BODYDAMAGETYPE_COUNT = 4 };
enum { DAMAGE_MODULE_MAX_FX = 12 };

class TransitionDamageFXModuleData : public UpdateModuleData
{
public:
	TransitionDamageFXModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	int m_damageFXTypes;
	TransitionDamageFXRecordA m_fxList[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];
	int m_damageOCLTypes;
	TransitionDamageFXRecordB m_ocl[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];
	int m_damageParticleTypes;
	TransitionDamageFXRecordC m_particleSystem[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];
	TransitionSmallVec m_unkFD4[4];
	TransitionSmallVec m_unk1004[4];
	_STL::vector<Rva004BA1C8> m_tail;
};

// ??0TransitionDamageFXModuleData@@QAE@XZ @0x004BA58A
TransitionDamageFXModuleData::TransitionDamageFXModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C59B20))
{
	Int i, j;
	for (i = 0; i < BODYDAMAGETYPE_COUNT; ++i) {
		for (j = 0; j < DAMAGE_MODULE_MAX_FX; ++j) {
			m_fxList[i][j].m_value = 0;
			m_fxList[i][j].m_loc[0] = 0.0f;
			m_fxList[i][j].m_loc[1] = 0.0f;
			m_fxList[i][j].m_loc[2] = 0.0f;
			m_fxList[i][j].m_locType = 1;
			m_fxList[i][j].m_randomBone = 0;
			m_ocl[i][j].m_value = 0;
			m_ocl[i][j].m_loc[0] = 0.0f;
			m_ocl[i][j].m_loc[1] = 0.0f;
			m_ocl[i][j].m_loc[2] = 0.0f;
			m_ocl[i][j].m_locType = 1;
			m_ocl[i][j].m_randomBone = 0;
			m_particleSystem[i][j].m_value = 0;
			m_particleSystem[i][j].m_loc[0] = 0.0f;
			m_particleSystem[i][j].m_loc[1] = 0.0f;
			m_particleSystem[i][j].m_loc[2] = 0.0f;
			m_particleSystem[i][j].m_locType = 1;
			m_particleSystem[i][j].m_randomBone = 0;
		}
	}

	_STL::vector<Rva004BA1C8> &tail = m_tail;
	Rva004BA399Vector &tailErase = reinterpret_cast<Rva004BA399Vector &>(tail);
	tailErase.EraseRange(tail.begin(), tail.end());

	m_damageFXTypes |= -1;
	m_damageOCLTypes |= -1;
	m_damageParticleTypes |= -1;
}

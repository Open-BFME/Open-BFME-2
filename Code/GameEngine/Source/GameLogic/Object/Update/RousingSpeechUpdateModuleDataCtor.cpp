// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0RousingSpeechUpdateModuleData@@QAE@XZ, retail 0x004AD0EE, 136 bytes.
// Rousing-speech behavior data: the own table at 0x00C54F28 carries
// BonusRadius at +0xC8, SpeechDuration at +0xCC, UpdateInterval at +0xD0,
// LeaderFX at +0xD4, FollowerFX at +0xD8, CreateWave at +0xDC, WaveWidth
// at +0xE0, ModifierName at +0xE4, LevelUp at +0xF0 and ObjectFilter at
// +0xF4, matching every store below; the ModuleData factory at 0x24F58C
// news 0xF8 and the pool key at 0x4ACED8 proves the class. Shape follows
// SupplyCenterProductionExitUpdateCtor (opaque 0xC8 virtual base through
// the 0x44EB54 pin, derived virtuals) plus the AutoPickUp/Bored recipe
// (string-vector member through the 0x211E58 fold, filter with declared
// dtor, /arch:SSE float zeros). Retail runs base-call, state-0, vtable,
// zeros, vector-call, byte, filter-call, state-1, which the all-init-list
// transcription reproduces. The native ModifierName field entry uses
// INI::parseAsciiStringVectorAppend at +0xE4; the destructor and trigger
// agree on vector<AsciiString> at that offset.

#include <vector>

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<AsciiString,_STL::allocator<AsciiString> >::~_Vector_base(); }
// bfme link decl-only end
// bfme link decl-only AsciiString
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::~vector(); }
// Suppress this TU's non-retail AsciiString proxy deallocate copy:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
}

// Existing four-byte pool-index view used by the seed and its destructor.
// ObjectFilter.cpp owns this constructor's folded native 0x3623E5 body;
// ObjectFilterRelease.cpp owns its 0x360D26 release destructor.
class Rva00360D26Member
{
public:
	Rva00360D26Member();
	~Rva00360D26Member();

private:
	int m_x;
};

class SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();
	virtual ~SpecialAbilityUpdateModuleData();

protected:
	unsigned char m_pad[0xC8 - 4];
};

class RousingSpeechUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	RousingSpeechUpdateModuleData();
	virtual ~RousingSpeechUpdateModuleData();

private:
	float m_bonusRadius; // +0xC8
	int m_speechDuration; // +0xCC
	int m_updateInterval; // +0xD0
	int m_leaderFX; // +0xD4
	int m_followerFX; // +0xD8
	unsigned char m_createWave; // +0xDC
	unsigned char m_padDD[3]; // +0xDD
	float m_waveWidth; // +0xE0
	_STL::vector<AsciiString> m_modifierNames; // +0xE4, ModifierName parser
	unsigned char m_levelUp; // +0xF0
	unsigned char m_padF1[3]; // +0xF1
	Rva00360D26Member m_objectFilter; // +0xF4
};

// RousingSpeechUpdateModuleData::~RousingSpeechUpdateModuleData: defined in RousingSpeechUpdateModuleDataDtor.cpp (its row's unit).

// ??0RousingSpeechUpdateModuleData@@QAE@XZ @0x4AD0EE
RousingSpeechUpdateModuleData::RousingSpeechUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
	, m_bonusRadius(0.0f)
	, m_speechDuration(0)
	, m_updateInterval(0)
	, m_leaderFX(0)
	, m_followerFX(0)
	, m_createWave(0)
	, m_waveWidth(0.0f)
	, m_levelUp(0)
{
}

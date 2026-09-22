// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0SpecialPowerModuleData@@QAE@XZ at retail 0x005488C5 (36B). The
// intermediate SpecialPowerModuleData base is 0x18 bytes: vtable 0xC6A520
// at +0, a vector member at +4 built through the ICF-folded empty
// _Vector_base at 0x211E58, and nulls at +0x10/+0x14. The ZH donor body
// (SpecialPowerModule.cpp) keeps the old field set without the vector, so
// this is a retail-faithful transcription, not a donor copy. The vector
// element type is invisible in retail bytes (the base call folds for every
// spelling); it is modeled as AsciiString after the SpawnBehavior
// precedent, which resolves with zero new pins. Six derived ModuleData
// ctors call this base (see FireWeaponPower.cpp). Row supersedes the pin.
#include <vector>

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();

private:
	void *m_vtable; // +0
	_STL::vector<AsciiString> m_stringList; // +4
	void *m_unused10; // +0x10
	void *m_unused14; // +0x14
};

// ??0SpecialPowerModuleData@@QAE@XZ @0x5488C5
SpecialPowerModuleData::SpecialPowerModuleData()
	: m_vtable(reinterpret_cast<void *>(0x00C6A520))
{
	m_unused10 = NULL;
	m_unused14 = NULL;
}

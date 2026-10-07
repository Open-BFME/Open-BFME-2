// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /GX
// stlport
//
// ??0ProductionSpeedBonusModuleData@@QAE@XZ, retail 0x004C2FE6, 98 bytes.
// ProductionSpeedBonus data ctor over the pinned SpecialPowerModuleData base
// (0x4930A0, 0x7C bytes): installs vtable 0x00C5CA80 via the ??_7 pin,
// constructs the Type string list at +0x84 through the ICF-folded
// Vector_base at 0x00211E58, zeroes NumberOfFrames at +0x7C and
// SpeedMultiplier at +0x80, then clears the list through the rowed
// vector<AsciiString>::erase at 0x002CCFC. Table 0x00C5C9A0 proves the
// three fields at identical offsets (NumberOfFrames/SpeedMulitplier/
// Type); factory 0x251AFE news 0x90 (sole caller); pool key rowed.
// Row supersedes the ctor pin. Recipe: virtual base with defined empty
// dtor plus virtual derived for compiler vtable placement; body-order
// stores with the erase spelled through a named vector reference (homes
// the list in edi for the [edi+4]/[edi] pushes); no barrier (a fence
// traps the EH state-1 store early).

#include <vector>

#include "ascii_string.h"

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

protected:
	unsigned char m_pad[0x7C - 4];
};

// ??1SpecialPowerModuleData owned by SpecialPowerModuleDataDtor.cpp (row at 0x0049334F):
// declared above so calls keep the same name without a second definition.

class ProductionSpeedBonusModuleData : public SpecialPowerModuleData
{
public:
	ProductionSpeedBonusModuleData();
	virtual ~ProductionSpeedBonusModuleData();

private:
	int m_numberOfFrames; // +0x7C NumberOfFrames
	float m_speedMultiplier; // +0x80 SpeedMulitplier
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_type; // +0x84 Type
};

ProductionSpeedBonusModuleData::ProductionSpeedBonusModuleData()
	: SpecialPowerModuleData()
{
	m_numberOfFrames = 0;
	m_speedMultiplier = 0.0f;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > &typeList = m_type;
	typeList.erase(typeList.begin(), typeList.end());
}
